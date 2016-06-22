#ifndef GL_WIDGET_H
#define GL_WIDGET_H

#include "GLArrayBuffer.h"
#include "GLShaderProgram.h"
#include "GLTexture.h"
#include "GLVertexArray.h"
#include "Mat.h"
#include "Vec.h"
#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QGLWidget>
#include <QMenu>
#include <QMenuBar>
#include <QMouseEvent>
#include <QGLWidget>
#include <QDebug>
#include <fstream>
#include <vector>
#include<iostream>
#include<GLFramebuffer.h>
using namespace std;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(const QGLFormat &format = QGLFormat::defaultFormat(), QWidget *parent = 0);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    virtual void Dataset(string, string,string,string);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void getIntermediateValues();
public slots:
    virtual void changeDensity(int);
    virtual void changeDiffuse(int);
    virtual void changeAmbience(int);
    virtual void changeSpecular(int);
    virtual void changeBrighness(int);
    virtual void changeSampleRate(int);
    virtual void changeTransparency(int);
    virtual void ChangeTransferFunction();
//    virtual void changeDataSet(char *);


    virtual void InitializeParameters();
    virtual void InitializeRect(std::vector<Vec2f> & vertice,GLArrayBuffer::Ptr & ArrayBuffer,GLVertexArray::Ptr & VertexArray ,float Start, float End);

    virtual void changeSliceXleft(int);
    virtual void changeSliceXright(int);

    virtual void changeSliceYleft(int);
    virtual void changeSliceYright(int);

    virtual void changeSliceZleft(int);
    virtual void changeSliceZright(int);

    virtual void changeShine(int);
    virtual void checkSnapshot();
    virtual void PreIntegration(bool);

    virtual void preIntegrate();

//    virtual void getTransferValues(int);

    virtual void getTransferValues(std::vector<Vec4f> & transfer);

//    virtual void Print(const std::vector<Vec4f> & v);


    virtual void checkAmbientOcclusion(bool);
    virtual void AmbientOcclusion();
    virtual void checkAmbience(bool);
    virtual void checkSpecular(bool);
    virtual vector<string> split(const string &s, char delim);
    virtual void checkBoundingBox(bool);
    virtual void changeTF(string Path);
    virtual void checkDiffusion(bool);
    virtual void changeRayStepSize(int);
    virtual void changeTransferOffset(int);
    virtual void changeDataset(string Path,string x,string y,string z);

protected:
    QPointF mousePos;
    Mat3f rotation;
    Vec3f translation;
    Mat4f modelViewMatrix;
    Mat4f projectionMatrix;
    float StepSize;
    float Brightness;
    float Density;
    float offset;
    float PreIntegrate;
    float Shininess;
    float DiffuseContribution;
    float DiffuseContributionOld;
    float SpecularContributionOld;
    float AmbienceCoefficientOld;
    float AmbienceCoefficient;
    float transferScale;
    float BoundingBox;
    float checkAmbient;
    float SpecularContribution;
    float SamplingRate;
    float transparency;
    float RayStepSize;

    float SliceXleft;
    float SliceXright;

    float SliceYleft;
    float SliceYright;

    float SliceZleft;
    float SliceZright;


    GLFramebuffer::Ptr initFBO;
    GLFramebuffer::Ptr ambientOcclusionFBO;

    float transferOffset;
    GLuint preInt;
    GLuint FBO;

    std::vector<Vec2f> rectVertices;
    std::vector<Vec2f> rectVertices1;
    std::vector<Vec2f> rectVertices2;

    Vec3i volumeDim;
    GLTexture::Ptr volumeTex;
    GLTexture::Ptr AmbbientTex;
    GLTexture::Ptr PreIntTex;
    GLTexture::Ptr transferFuncTex;
    std::vector<Vec4f> transferFuncData;

    GLArrayBuffer::Ptr rectVertexBuffer;
    GLArrayBuffer::Ptr rectIndexBuffer;
    GLVertexArray::Ptr rectVertexArray;

    GLArrayBuffer::Ptr rectVertexBuffer1;
    GLArrayBuffer::Ptr rectIndexBuffer1;

    GLVertexArray::Ptr rectVertexArray1;
    GLVertexArray::Ptr rectVertexArray2;

    GLArrayBuffer::Ptr rectVertexBuffer2;
    GLArrayBuffer::Ptr rectIndexBuffer2;
    GLVertexArray::Ptr rectAmbientOcclusionVertexArray;

    GLShaderProgram::Ptr volumeRayCastingProgram;
    GLShaderProgram::Ptr preIntProg;
    GLShaderProgram::Ptr ambOcclProg;

};

#endif // GLWIDGET_H

