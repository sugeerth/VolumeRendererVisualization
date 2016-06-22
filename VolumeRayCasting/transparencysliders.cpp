#include "transparencysliders.h"
#include "ui_transparencysliders.h"
#include <QFileDialog>
#include<QMessageBox>
#include "GLWidget.h"
#include<iostream>
#include <QColorDialog>
#include <transfer.h>


using namespace std;

transparencySliders::transparencySliders(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::transparencySliders)
{
    ui->setupUi(this);

//    ui->INteractiveWidgetLayout->addWidget(&Yes);
}

void transparencySliders::acceptGLWidget(GLWidget *w)
{
    W=w;
    cout<<"TransparencySliders";


    connect(ui->AmbientLightSLider,SIGNAL(valueChanged(int)),w,SLOT(changeAmbience(int)));
    connect(ui->SpecularLightSlider,SIGNAL(valueChanged(int)),w,SLOT(changeSpecular(int)));

//    connect(ui->DensitySlider,SIGNAL(valueChanged(int)),w,SLOT(changeDensity(int)));
    connect(ui->DiffuseSlider,SIGNAL(valueChanged(int)),w,SLOT(changeDiffuse(int)));
//    connect(ui->BrightnessSlider,SIGNAL(valueChanged(int)),w,SLOT(changeTransparency(int)));
    connect(ui->shineSlider,SIGNAL(valueChanged(int)),w,SLOT(changeShine(int)));

    connect(ui->SamplingRateSlider,SIGNAL(valueChanged(int)),w,SLOT(changeSampleRate(int)));
    connect(ui->TransprencySlider,SIGNAL(valueChanged(int)),w,SLOT(changeTransparency(int)));
    connect(ui->SlideAmbienOcclusionSlider,SIGNAL(valueChanged(int)),w,SLOT(changeRayStepSize(int)));

    //X
    connect(ui->SliceXleft,SIGNAL(valueChanged(int)),w,SLOT(changeSliceXleft(int)));
    connect(ui->SliceXright,SIGNAL(valueChanged(int)),w,SLOT(changeSliceXright(int)));
    //Y
    connect(ui->SliceYleft,SIGNAL(valueChanged(int)),w,SLOT(changeSliceYleft(int)));
    connect(ui->SliceYright,SIGNAL(valueChanged(int)),w,SLOT(changeSliceYright(int)));
    //Z
    connect(ui->SliceZleft,SIGNAL(valueChanged(int)),w,SLOT(changeSliceZleft(int)));
    connect(ui->SliceZright,SIGNAL(valueChanged(int)),w,SLOT(changeSliceZright(int)));
    connect(ui->AmbientOcclusion,SIGNAL(clicked(bool)),w,SLOT(checkAmbientOcclusion(bool)));
    connect(ui->Boundingbox,SIGNAL(clicked(bool)),w,SLOT(checkBoundingBox(bool)));
    connect(ui->DiffuseCheckbox,SIGNAL(clicked(bool)),w,SLOT(checkDiffusion(bool)));
    connect(ui->AmbientCheckbox,SIGNAL(clicked(bool)),w,SLOT(checkAmbience(bool)));
    connect(ui->SpeculaCheckbox,SIGNAL(clicked(bool)),w,SLOT(checkSpecular(bool)));

    connect(ui->Preintegration,SIGNAL(clicked(bool)),w,SLOT(PreIntegration(bool)));

    connect(ui->TransferOffset,SIGNAL(valueChanged(int)),w,SLOT(changeTransferOffset(int)));
    connect(ui->Snapshot,SIGNAL(clicked()),w,SLOT(checkSnapshot()));







    QColor color = QColorDialog::customColor(24);


//    connect(ui->Dataset_Path,SIGNAL(),w,SLOT(checkSnapshot()));


}

transparencySliders::~transparencySliders()
{
    delete ui;
}

void transparencySliders::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,tr("Open File"),"C://","All Files (*.*);;Text File (*.txt)");

    ui->TransferFunctionPAth->setText(filename);

//    QMessageBox::information(this,tr("File name"),filename);
}

void transparencySliders::on_pushButton_9_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,tr("Open File"),"C://","Raw File (*.raw);;All Files (*.*)");
    ui->Dataset_Path->setText(filename);
}

void transparencySliders::on_OKButtonDataset_clicked()
{
    string Path = ui->Dataset_Path->toPlainText().toLocal8Bit().constData();
    string X = ui->x->toPlainText().toLocal8Bit().constData();
    string Y = ui->y->toPlainText().toLocal8Bit().constData();
    string Z = ui->z->toPlainText().toLocal8Bit().constData();
    W->changeDataset(Path,X,Y,Z);
    cout<<Path<<X<<Y<<Z;
}
void transparencySliders::on_Preintegration_clicked(bool checked)
{
    cout<<checked<<endl;
}

void transparencySliders::on_TFFiles_clicked(bool checked)
{
    string Path = ui->TransferFunctionPAth->toPlainText().toLocal8Bit().constData();
    W->changeTF(Path);
}
