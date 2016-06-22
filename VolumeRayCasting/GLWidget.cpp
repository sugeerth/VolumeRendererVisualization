#include "GLWidget.h"
#include <QDebug>
#include <fstream>
#include "GLTexture.h"
#include <vector>
#include<iostream>
#include <fstream>
//#include<glew/>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <sstream>
#include <vector>
#include<GLFramebuffer.h>
using namespace std;

GLWidget::GLWidget(const QGLFormat &format, QWidget *parent) :
    QGLWidget(format, parent)
{
    setFocusPolicy(Qt::ClickFocus);
    setMinimumSize(256, 256);
    setWindowTitle("Volume Rendering on the GPU");
}
void GLWidget::InitializeParameters()
{
    Shininess = 80;
    Density = 1.0f;
    Brightness = 0.95f;
    SamplingRate = 0.003f;
    transferScale = 1.0f;
    DiffuseContribution = 0.65;
    SpecularContribution = 0.3;
    AmbienceCoefficient = 0.30f;
    transferOffset = 0.00f;
    Shininess = 80;
    RayStepSize = 1/401;

    SliceXleft = 0;
    SliceXright = 0.99;

    SliceYleft = 0;
    SliceYright = 0.99;

    SliceZleft = 0;
    SliceZright = 0.99;

    transferFuncData.push_back(Vec4f(1.0f, 0.0f, 0.0f, 0.0f));
    transferFuncData.push_back(Vec4f(1.0f, 0.0f, 0.0f, 0.0f));
    transferFuncData.push_back(Vec4f(1.0f, 0.0f, 0.0f, 0.0f));
    transferFuncData.push_back(Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
    transferFuncData.push_back(Vec4f(1.0f, 0.0f, 0.0f, 0.0f));
    transferFuncData.push_back(Vec4f(1.0f, 0.0f, 0.0f, 0.0f));
}

void  GLWidget::InitializeRect(std::vector<Vec2f> & rectVertice, GLArrayBuffer::Ptr & rectVertex, GLVertexArray::Ptr & VertexArray,float Start,float End)
{

    //std::vector<Vec2f> rectVertices;
    rectVertice.push_back(Vec2f(Start, Start));
    rectVertice.push_back(Vec2f(Start, End));
    rectVertice.push_back(Vec2f(End, End));
    rectVertice.push_back(Vec2f(End, Start));
    rectVertex = GLArrayBuffer::create(GL_ARRAY_BUFFER);
    rectVertex->update(rectVertice.size() * sizeof(Vec2f), &rectVertice.front(), GL_STATIC_DRAW);
    VertexArray = GLVertexArray::create();
}

vector<string> GLWidget::split(const string &s, char delim) {
     vector<string> elems;
     stringstream ss(s);
     string item;
     while (getline(ss, item, delim)) {
         elems.push_back(item);
     }
     return elems;
 }

void GLWidget::changeTF(string Path)
{
    std::vector<unsigned char> TFdata;
    std::ifstream ifs;
    ifs.open(Path);

    string STRING;
    if(!ifs.is_open())
    {
        qDebug() << "Failed to open Transfer Functions!";
        close();
    }
    vector<string> x;
    while(ifs) // To get you all the lines.
     {
        getline(ifs,STRING); // Saves the line in STRING
        x = split(STRING,' ');
        cout<<x[1];
//        transferFuncData.push_back(Vec4f(stof(x[1]),stof(x[2]),stof(x[3]),stof(x[4])));
         cout<<STRING; // Prints our STRING.
     }
    ifs.close();
}


void GLWidget::initializeGL()
{
#ifndef __APPLE__1
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
        qDebug() << glewGetErrorString(err);
#endif


    InitializeParameters();

    InitializeRect(rectVertices,rectVertexBuffer,rectVertexArray,0.0,1.0);

    InitializeRect(rectVertices1,rectVertexBuffer1,rectVertexArray1,-1.0,1.0);

    InitializeRect(rectVertices2,rectVertexBuffer2,rectVertexArray2,0.0,1.0);


    this->Dataset("/home/sugeerth/Visual_REcognition/VolumeRayCasting/SampleVolume.raw","32","32","32");

}

void GLWidget::Dataset(string Path, string X, string Y, string Z)
{
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glDisable(GL_DEPTH_TEST);
        glColorMask(true, true, true, true);
        glDepthMask(true);

        rotation = Mat3f::identity();
        translation = Vec3f(0.0f, 0.0f, -2.0f);
        // load sample data volume
        volumeDim.x = stoi(X);
        volumeDim.y = stoi(Y);
        volumeDim.z = stoi(Z);

        int volumeSize = volumeDim.x * volumeDim.y * volumeDim.z;
        std::vector<unsigned char> volumeData;
        volumeData.resize(volumeSize);
        std::ifstream ifs(Path, std::ios::binary);

        if(!ifs.is_open())
        {
            qDebug() << "Failed to open sample volume!";
            close();
        }

        ifs.read(reinterpret_cast<char *>(&volumeData.front()), volumeSize * sizeof(unsigned char));
        ifs.close();

        // create OpenGL textures
        volumeTex = GLTexture::create();
        volumeTex->updateTexImage3D(GL_R8, volumeDim, GL_RED, GL_UNSIGNED_BYTE, &volumeData.front());

        ChangeTransferFunction();


}
void GLWidget::ChangeTransferFunction()
{

        //CREATE the transfer function with the data and size
        transferFuncTex = GLTexture::create();
//        transferFuncTex->updateTexImage2D(GL_RGBA32F, Vec2i(int(transferFuncData.size()), 1), GL_RGBA, GL_FLOAT, &transferFuncData.front());

        //Initialize the frame buffer and bind it
        //Ambient occlusion Frame buffer object
        initFBO = GLFramebuffer::create();

        ambientOcclusionFBO = GLFramebuffer::create();


        //GENERATE TEXTURE
        //Upload the texture back to the frame buffer
        PreIntTex = GLTexture::create();
//        PreIntTex->updateTexImage2D(GL_RGBA32F, Vec2i(int(transferFuncData.size()), int(transferFuncData.size())), GL_RGBA, GL_FLOAT, NULL);
//        glBindTexture(PreIntTex->type(), PreIntTex->textureID());

        //Ambient textrures 3D textures
        //Binding3D texture onto the Ambient occlusion texture
        AmbbientTex = GLTexture::create();
//        AmbbientTex->updateTexImage3D(GL_R8, volumeDim, GL_RED, GL_UNSIGNED_BYTE, 0);
//        glBindTexture(AmbbientTex->type(), AmbbientTex->textureID());

        //Bind the type "TEXTURE_2D with the texture ID"
        // COMPUTE preintegration method in a different shader

        //COMPUTE THE PREINTEGRATION METHOD
        preIntProg= GLShaderProgram::create("PreIntVertex.vert", "PreIntFrag.frag");
        if(preIntProg== NULL)
            close();
        // Set the vertex array and the sampleRate
         preIntProg->setVertexAttribute("V", rectVertexArray1, rectVertexBuffer1, 2, GL_FLOAT, false);

        //COMPILE the shader program
        volumeRayCastingProgram = GLShaderProgram::create("VolumeRayCasting.vert", "VolumeRayCasting.frag");
        if(volumeRayCastingProgram == NULL)
            close();
        // assign vertex buffer to the shader attribute input called "Vertex"
        volumeRayCastingProgram->setVertexAttribute("Vertex", rectVertexArray, rectVertexBuffer, 2, GL_FLOAT, false);

        //COMPUTE THE AMBIENT OCCLUSION METHOD
        ambOcclProg= GLShaderProgram::create("ambientOcclusion.vert", "ambientOcclusion.frag");
        if(ambOcclProg == NULL)
            close();

        // Set the vertex array and the sampleRate
        ambOcclProg->setVertexAttribute("V", rectVertexArray2, rectVertexBuffer2, 2, GL_FLOAT, false);

        preIntegrate();

        //Compute Ambient Occlusion
        AmbientOcclusion();
}


void GLWidget::getTransferValues(std::vector<Vec4f> & transfer)
{
    transferFuncData = transfer;

    ChangeTransferFunction();

//    this->Dataset("/home/sugeerth/Visual_REcognition/VolumeRayCasting/SampleVolume.raw","32","32","32");
}

void GLWidget::preIntegrate()
{
    transferFuncTex->updateTexImage2D(GL_RGBA32F, Vec2i(int(transferFuncData.size()), 1), GL_RGBA, GL_FLOAT, &transferFuncData.front());
    PreIntTex->updateTexImage2D(GL_RGBA32F, Vec2i(int(transferFuncData.size()), int(transferFuncData.size())), GL_RGBA, GL_FLOAT, NULL);
    glDisable(GL_BLEND);
    //Bind the buffer
    initFBO->bind();

    //clear the Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLenum colAtt = GL_COLOR_ATTACHMENT0;
    glDrawBuffers(1, &colAtt);

    //ATTACH THE TEXTURE WITH THE CHANNEL THAT CAN BE WRITTEN
    initFBO->attachTexture(GL_COLOR_ATTACHMENT0,PreIntTex);

    preIntProg->setTexture("transferFuncTex", transferFuncTex);
    preIntProg->setUniform("d", SamplingRate);

    //Setting the viewport
    glViewport(0,0,transferFuncData.size(),transferFuncData.size());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Draw the QUADS WHERE YOU CAN RENDER THE DATA
    preIntProg->begin();
    rectVertexArray1->drawArrays(GL_TRIANGLE_FAN, 4);
    preIntProg->end();

    // DETACH THE FRAMEBUFFER AND SAVE IT INTO THE PRE INTEGRATION TEXTURE
    glViewport(0,0, width(),height());
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, 0, 0);

    glEnable(GL_BLEND);
    //unbind THE FRAMEBUFFER
    GLenum colAtt2 = GL_BACK_LEFT;
    glDrawBuffers(1, &colAtt2);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    update();
//    updateGL();
}

void GLWidget::AmbientOcclusion()
{

    AmbbientTex->updateTexImage3D(GL_R8, volumeDim, GL_RED, GL_UNSIGNED_BYTE, 0);

    ambientOcclusionFBO->bind();
    float Z;

    for(int i=0;i<volumeDim.z-1;i++)
    {
        //Draw the frame buffers slice by slice
        GLenum colAtt = GL_COLOR_ATTACHMENT0;
        glDrawBuffers(1, &colAtt);
        ambientOcclusionFBO->attachTexture(GL_COLOR_ATTACHMENT0,AmbbientTex,0,i);

        //Setting the viewport
        glViewport(0,0,volumeDim.x,volumeDim.y);

        //Z value in texture co-ordintates
        Z=float(i+0.5)/volumeDim.z;

        ambOcclProg->setTexture("volumeTex", volumeTex);
        ambOcclProg->setTexture("volumeScale", volumeTex);
        ambOcclProg->setTexture("tranrsferFuncTex", transferFuncTex);
        ambOcclProg->setTexture("PreIntTex", PreIntTex);
        ambOcclProg->setUniform("SamplingRate", SamplingRate);
        ambOcclProg->setUniform("RayStepSize",RayStepSize);
        ambOcclProg->setUniform("layer", Z);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //Draw the QUADS WHERE YOU CAN RENDER THE DATA
        ambOcclProg->begin();
        rectVertexArray1->drawArrays(GL_TRIANGLE_FAN, 4);
        ambOcclProg->end();

    }
        // DETACH THE FRAMEBUFFER AND SAVE IT INTO THE PRE INTEGRATION TEXTURE
        glViewport(0,0, width(),height());
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_3D, 0, 0);

        //unbind THE FRAMEBUFFER
        GLenum colAtt2 = GL_BACK_LEFT;
        glDrawBuffers(1, &colAtt2);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        updateGL();
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    projectionMatrix = Mat4f::perspective(Math::pi<float>() * 0.25f, float(w) / float(h), 0.01f, 10.0f);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    getIntermediateValues();
    Vec3f volumeScale = Vec3f(volumeDim);
    volumeScale = volumeScale / volumeScale.norm();
    modelViewMatrix = Mat4f(rotation, translation);
    Mat4f transform = Mat4f::ortho(0, 1, 0, 1, -1, 1);
    Mat4f invModelView = modelViewMatrix.inverse();


    volumeRayCastingProgram->setUniform("volumeScale", volumeScale);
    volumeRayCastingProgram->setUniform("transform", transform);
    volumeRayCastingProgram->setUniform("invModelView", invModelView);
    volumeRayCastingProgram->setUniform("StepSize", StepSize);
    volumeRayCastingProgram->setUniform("Brightness", Brightness);
    volumeRayCastingProgram->setUniform("offset", offset);
    volumeRayCastingProgram->setUniform("SamplingRate", SamplingRate);
    volumeRayCastingProgram->setUniform("Density", Density);
    volumeRayCastingProgram->setUniform("transparency", transparency);
    volumeRayCastingProgram->setUniform("SpecularContribution", SpecularContribution);
    volumeRayCastingProgram->setUniform("AmbienceCoefficient", AmbienceCoefficient);
    volumeRayCastingProgram->setUniform("DiffuseContribution", DiffuseContribution);
    volumeRayCastingProgram->setUniform("preIntCheck", PreIntegrate);
    volumeRayCastingProgram->setUniform("checkAmbient", checkAmbient);

    volumeRayCastingProgram->setUniform("SliceXleft",SliceXleft);
    volumeRayCastingProgram->setUniform("SliceXright",SliceXright);

    volumeRayCastingProgram->setUniform("SliceYleft",SliceYleft);
    volumeRayCastingProgram->setUniform("SliceYright",SliceYright);

    volumeRayCastingProgram->setUniform("SliceZleft",SliceZleft);
    volumeRayCastingProgram->setUniform("SliceZright",SliceZright);
    volumeRayCastingProgram->setUniform("BoundingBox", BoundingBox);

    volumeRayCastingProgram->setUniform("Shininess", Shininess);
    volumeRayCastingProgram->setUniform("transferScale",transferScale);
    volumeRayCastingProgram->setUniform("transferOffset",transferOffset);
    volumeRayCastingProgram->setUniform("aspect", float(width()) / float(height()));
    volumeRayCastingProgram->setUniform("cotFOV", projectionMatrix.elem[1][1]);
    volumeRayCastingProgram->setTexture("volumeTex", volumeTex);

    preIntProg->setTexture("transferFuncTex", transferFuncTex);
    preIntProg->setUniform("d", SamplingRate);

    volumeRayCastingProgram->setTexture("AmbbientTex", AmbbientTex);
    volumeRayCastingProgram->setTexture("transferFuncTex", transferFuncTex);
    volumeRayCastingProgram->setTexture("PreIntTex", PreIntTex);

    volumeRayCastingProgram->begin();
    rectVertexArray->drawArrays(GL_TRIANGLE_FAN, 4);
    volumeRayCastingProgram->end();


    //    ambOcclProg->begin();
    //    rectVertexArray1->drawArrays(GL_TRIANGLE_FAN, 4);
    //    ambOcclProg->end();
}

void GLWidget::getIntermediateValues()
{
    StepSize = 0.02;
    Brightness = 10;
}

void GLWidget::checkSnapshot()
{
     ofstream myfile;
     myfile.open ("Snapshot.txt",ios::app);
     myfile << "Configuration: "<<"SamplingRate: "<<endl<<SamplingRate<<endl<<"Density:"<<Density<<endl<<"Shininess:"<<Shininess<<endl<<"Density:"<<Density<<endl<<"Brightness:"<<Brightness<<endl<<"transferOffset:"<<transferOffset<<endl<<"transferScale"<<transferScale<<endl<<"DiffuseContribution"<<DiffuseContribution<<endl<<"AmbienceCoefficient"<<AmbienceCoefficient<<endl<<"SpecularContribution"<<SpecularContribution<<endl;
     myfile.close();
     cout<<"Writing configuration to Snapshot.txt"<<endl;
}

void GLWidget::checkAmbience(bool value)
{
    if (value == false){
        AmbienceCoefficientOld = AmbienceCoefficient;
        AmbienceCoefficient= 0;}
    else{
        AmbienceCoefficient= AmbienceCoefficientOld;
        }
    update();

}

void GLWidget::changeDataset(string Path,string X,string Y,string Z)
{
    cout<<Path;
    this->Dataset(Path,X,Y,Z);
}

void GLWidget::checkDiffusion(bool value)
{
    if (value == false){
        DiffuseContributionOld = DiffuseContribution;
        DiffuseContribution = 0;}
    else{
        DiffuseContribution = DiffuseContributionOld;
        }
    update();
}

void GLWidget::PreIntegration(bool value)
{
    if (value == false){
        PreIntegrate = 0; }
    else{
        PreIntegrate = 1;
        }
    update();
}

void GLWidget::checkBoundingBox(bool value)
{
    if (value == false){
        BoundingBox = 0; }
    else{
        BoundingBox = 1;
        }
    update();
}

void GLWidget::checkAmbientOcclusion(bool value)
{
    if (value == false){
        checkAmbient = 0; }
    else{
        checkAmbient = 1;
        }
    update();
}

void GLWidget::checkSpecular(bool value)
{
    if (value == false){
        SpecularContributionOld = SpecularContribution;
        SpecularContribution = 0;}
    else{
        SpecularContribution = SpecularContributionOld;
        }
    update();
}

void GLWidget::changeShine(int value)
{
    Shininess = float(value);
    update();
}

//Handling SLots from Transparency Sliders
void GLWidget::changeDensity(int value)
{
    Density = float(float(value)/100.0);
    cout<<"Density"<<Density<<endl;
    update();
}

void GLWidget::changeDiffuse(int value)
{
    DiffuseContribution = 0.65 + float(value)/1000.0;
    cout<<DiffuseContribution<<endl;
    update();
}

void GLWidget::changeSampleRate(int value)
{
    SamplingRate = float(value)/1000.0f;
    preIntegrate();
    AmbientOcclusion();
    update();
}

void GLWidget::changeRayStepSize(int value)
{
    RayStepSize = float(value)/1000.0f;
    cout<<RayStepSize<<endl;
    preIntegrate();
    AmbientOcclusion();
    update();
}

void GLWidget::changeSliceXleft(int value)
{
    SliceXleft = float(value)/100.0f;
//    cout<<SliceXleft<<endl;
    update();
    }

void GLWidget::changeSliceXright(int value)
{
    SliceXright= float(value)/100.0f;
//    cout<<SliceXright<<endl;
    update();
}

void GLWidget::changeSliceYleft(int value)
{
    SliceYleft = float(value)/100.0f;
//    cout<<SliceYleft<<endl;
    update();
}

void GLWidget::changeSliceYright(int value)
{
    SliceYright= float(value)/100.0f;
//    cout<<SliceYright<<endl;
    update();
}

void GLWidget::changeSliceZleft(int value)
{
    SliceZleft = float(value)/100.0f;
//    cout<<SliceZleft<<endl;
    update();
}

void GLWidget::changeSliceZright(int value)
{
        SliceZright= float(value)/100.0f;
//        cout<<SliceZright<<endl;
        update();
}

void GLWidget::changeSpecular(int value)
{
    SpecularContribution= 0.30 + float(value)/1000.0;
    cout<<SpecularContribution<<endl;
    update();
}
//Actually this is change transfer Scale just a bit lazy
void GLWidget::changeTransparency(int value)
{
    transferScale = 1.00 + float(value)/100.0f;
    cout<<transferScale<<endl;
    update();
}

void GLWidget::changeTransferOffset(int value)
{
    transferOffset = float(value)/100.0f;
    cout<<transferOffset<<endl;
    update();
}

void GLWidget::changeBrighness(int value)
{
    Brightness = value/100;
    cout<<Brightness<<endl;
    update();
}

void GLWidget::changeAmbience(int value)
{
    AmbienceCoefficient= 0.30 + float(value)/1000.0;
    cout<<AmbienceCoefficient<<endl;
    update();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos = event->localPos();
    float dx = pos.x() - mousePos.x();
    float dy = pos.y() - mousePos.y();
    mousePos = pos;

    Qt::MouseButtons mouseButtons = event->buttons();

    if(mouseButtons & Qt::LeftButton)
    {
        rotation = Mat3f::fromAxisAngle(Vec3f::unitY(), dx * 0.005f) * rotation;
        rotation = Mat3f::fromAxisAngle(Vec3f::unitX(), dy * 0.005f) * rotation;
        rotation.orthonormalize();
    }

    if(mouseButtons & Qt::RightButton)
    {
        translation.z += dy * 0.005f;
        translation.z = clamp(translation.z, -9.0f, 1.0f);
    }

    if(mouseButtons & Qt::MidButton)
    {
        float scale = -std::min(translation.z, 0.0f) * 0.001f + 0.000025f;
        translation.x += dx * scale;
        translation.y -= dy * scale;
    }

    updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{

    mousePos = event->localPos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mousePos = event->localPos();
}

void GLWidget::wheelEvent(QWheelEvent * event)
{
    QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta() / 8;
    float dx = 0.0f, dy = 0.0f;
    if(!numPixels.isNull())
    {
        dx = numPixels.x();
        dy = numPixels.y();
    }
    else if(!numDegrees.isNull())
    {
        dx = numDegrees.x() / 15;
        dy = numDegrees.y() / 15;
        dy = numDegrees.y() * -1;
    }

    Qt::KeyboardModifiers km = QApplication::keyboardModifiers();

    if(km & Qt::ControlModifier)
    {
        rotation = Mat3f::fromAxisAngle(Vec3f::unitY(), dx * 0.005f) * rotation;
        rotation = Mat3f::fromAxisAngle(Vec3f::unitX(), dy * 0.005f) * rotation;
    }
    else if(km & Qt::AltModifier)
    {
        float scale = -std::min(translation.z, 0.0f) * 0.001f + 0.000025f;
        translation.x += dx * scale;
        translation.y -= dy * scale;
    }
    else// if(km & Qt::ShiftModifier)
    {
        translation.z += dy * 0.005f;
        translation.z = clamp(translation.z, -9.0f, 1.0f);
    }

    updateGL();
}
