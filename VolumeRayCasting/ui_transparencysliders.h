/********************************************************************************
** Form generated from reading UI file 'transparencysliders.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSPARENCYSLIDERS_H
#define UI_TRANSPARENCYSLIDERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_transparencySliders
{
public:
    QTabWidget *Slices;
    QWidget *tab_3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_9;
    QSlider *TransferOffset;
    QLabel *label;
    QSlider *TransprencySlider;
    QLabel *label_5;
    QSlider *SamplingRateSlider;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *Boundingbox;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *AmbientOcclusion;
    QCheckBox *Preintegration;
    QWidget *widget;
    QFrame *TransferFunctionWidget;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *INteractiveWidgetLayout;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QWidget *tab_4;
    QPushButton *pushButton;
    QPushButton *TFFiles;
    QPushButton *pushButton_3;
    QTextEdit *TransferFunctionPAth;
    QWidget *tab_5;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_12;
    QSlider *SliceXleft;
    QLabel *label_13;
    QSlider *SliceXright;
    QLabel *label_14;
    QSlider *SliceYleft;
    QLabel *label_17;
    QSlider *SliceYright;
    QLabel *label_15;
    QSlider *SliceZleft;
    QLabel *label_16;
    QSlider *SliceZright;
    QWidget *tab;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QCheckBox *AmbientCheckbox;
    QSlider *AmbientLightSLider;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QCheckBox *SpeculaCheckbox;
    QSlider *SpecularLightSlider;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_8;
    QCheckBox *DiffuseCheckbox;
    QSlider *DiffuseSlider;
    QLabel *label_3;
    QSlider *shineSlider;
    QLabel *label_2;
    QSlider *SlideAmbienOcclusionSlider;
    QWidget *tab_7;
    QTextEdit *Dataset_Path;
    QPushButton *OKButtonDataset;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QLabel *label_10;
    QPlainTextEdit *x;
    QPlainTextEdit *y;
    QPlainTextEdit *z;
    QWidget *tab_2;
    QPushButton *Snapshot;

    void setupUi(QWidget *transparencySliders)
    {
        if (transparencySliders->objectName().isEmpty())
            transparencySliders->setObjectName(QStringLiteral("transparencySliders"));
        transparencySliders->resize(348, 677);
        Slices = new QTabWidget(transparencySliders);
        Slices->setObjectName(QStringLiteral("Slices"));
        Slices->setGeometry(QRect(0, 0, 341, 671));
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayoutWidget = new QWidget(tab_3);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 9, 403, 346));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(verticalLayoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout->addWidget(label_9);

        TransferOffset = new QSlider(verticalLayoutWidget);
        TransferOffset->setObjectName(QStringLiteral("TransferOffset"));
        TransferOffset->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(TransferOffset);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        TransprencySlider = new QSlider(verticalLayoutWidget);
        TransprencySlider->setObjectName(QStringLiteral("TransprencySlider"));
        TransprencySlider->setValue(0);
        TransprencySlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(TransprencySlider);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        SamplingRateSlider = new QSlider(verticalLayoutWidget);
        SamplingRateSlider->setObjectName(QStringLiteral("SamplingRateSlider"));
        SamplingRateSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(SamplingRateSlider);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        Boundingbox = new QCheckBox(verticalLayoutWidget);
        Boundingbox->setObjectName(QStringLiteral("Boundingbox"));
        Boundingbox->setChecked(false);

        horizontalLayout_6->addWidget(Boundingbox);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        AmbientOcclusion = new QCheckBox(verticalLayoutWidget);
        AmbientOcclusion->setObjectName(QStringLiteral("AmbientOcclusion"));

        horizontalLayout_2->addWidget(AmbientOcclusion);

        Preintegration = new QCheckBox(verticalLayoutWidget);
        Preintegration->setObjectName(QStringLiteral("Preintegration"));
        Preintegration->setChecked(false);

        horizontalLayout_2->addWidget(Preintegration);


        verticalLayout->addLayout(horizontalLayout_2);

        widget = new QWidget(tab_3);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 380, 401, 251));
        TransferFunctionWidget = new QFrame(widget);
        TransferFunctionWidget->setObjectName(QStringLiteral("TransferFunctionWidget"));
        TransferFunctionWidget->setGeometry(QRect(0, 0, 401, 251));
        verticalLayoutWidget_4 = new QWidget(TransferFunctionWidget);
        verticalLayoutWidget_4->setObjectName(QStringLiteral("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(-1, -1, 331, 251));
        INteractiveWidgetLayout = new QVBoxLayout(verticalLayoutWidget_4);
        INteractiveWidgetLayout->setObjectName(QStringLiteral("INteractiveWidgetLayout"));
        INteractiveWidgetLayout->setContentsMargins(0, 0, 0, 0);
        dockWidget = new QDockWidget(verticalLayoutWidget_4);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        dockWidget->setWidget(dockWidgetContents);

        INteractiveWidgetLayout->addWidget(dockWidget);

        Slices->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        pushButton = new QPushButton(tab_4);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(190, 20, 99, 27));
        TFFiles = new QPushButton(tab_4);
        TFFiles->setObjectName(QStringLiteral("TFFiles"));
        TFFiles->setGeometry(QRect(190, 80, 99, 27));
        pushButton_3 = new QPushButton(tab_4);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(60, 80, 99, 27));
        TransferFunctionPAth = new QTextEdit(tab_4);
        TransferFunctionPAth->setObjectName(QStringLiteral("TransferFunctionPAth"));
        TransferFunctionPAth->setGeometry(QRect(10, 20, 161, 41));
        Slices->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        verticalLayoutWidget_3 = new QWidget(tab_5);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(9, 9, 321, 361));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(verticalLayoutWidget_3);
        label_12->setObjectName(QStringLiteral("label_12"));

        verticalLayout_3->addWidget(label_12);

        SliceXleft = new QSlider(verticalLayoutWidget_3);
        SliceXleft->setObjectName(QStringLiteral("SliceXleft"));
        SliceXleft->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(SliceXleft);

        label_13 = new QLabel(verticalLayoutWidget_3);
        label_13->setObjectName(QStringLiteral("label_13"));

        verticalLayout_3->addWidget(label_13);

        SliceXright = new QSlider(verticalLayoutWidget_3);
        SliceXright->setObjectName(QStringLiteral("SliceXright"));
        SliceXright->setValue(99);
        SliceXright->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(SliceXright);

        label_14 = new QLabel(verticalLayoutWidget_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        verticalLayout_3->addWidget(label_14);

        SliceYleft = new QSlider(verticalLayoutWidget_3);
        SliceYleft->setObjectName(QStringLiteral("SliceYleft"));
        SliceYleft->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(SliceYleft);

        label_17 = new QLabel(verticalLayoutWidget_3);
        label_17->setObjectName(QStringLiteral("label_17"));

        verticalLayout_3->addWidget(label_17);

        SliceYright = new QSlider(verticalLayoutWidget_3);
        SliceYright->setObjectName(QStringLiteral("SliceYright"));
        SliceYright->setValue(99);
        SliceYright->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(SliceYright);

        label_15 = new QLabel(verticalLayoutWidget_3);
        label_15->setObjectName(QStringLiteral("label_15"));

        verticalLayout_3->addWidget(label_15);

        SliceZleft = new QSlider(verticalLayoutWidget_3);
        SliceZleft->setObjectName(QStringLiteral("SliceZleft"));
        SliceZleft->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(SliceZleft);

        label_16 = new QLabel(verticalLayoutWidget_3);
        label_16->setObjectName(QStringLiteral("label_16"));

        verticalLayout_3->addWidget(label_16);

        SliceZright = new QSlider(verticalLayoutWidget_3);
        SliceZright->setObjectName(QStringLiteral("SliceZright"));
        SliceZright->setValue(99);
        SliceZright->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(SliceZright);

        Slices->addTab(tab_5, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayoutWidget_2 = new QWidget(tab);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 10, 281, 307));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_6 = new QLabel(verticalLayoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout->addWidget(label_6);

        AmbientCheckbox = new QCheckBox(verticalLayoutWidget_2);
        AmbientCheckbox->setObjectName(QStringLiteral("AmbientCheckbox"));
        AmbientCheckbox->setChecked(true);

        horizontalLayout->addWidget(AmbientCheckbox);


        verticalLayout_2->addLayout(horizontalLayout);

        AmbientLightSLider = new QSlider(verticalLayoutWidget_2);
        AmbientLightSLider->setObjectName(QStringLiteral("AmbientLightSLider"));
        AmbientLightSLider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(AmbientLightSLider);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_7 = new QLabel(verticalLayoutWidget_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_3->addWidget(label_7);

        SpeculaCheckbox = new QCheckBox(verticalLayoutWidget_2);
        SpeculaCheckbox->setObjectName(QStringLiteral("SpeculaCheckbox"));
        SpeculaCheckbox->setChecked(true);

        horizontalLayout_3->addWidget(SpeculaCheckbox);


        verticalLayout_2->addLayout(horizontalLayout_3);

        SpecularLightSlider = new QSlider(verticalLayoutWidget_2);
        SpecularLightSlider->setObjectName(QStringLiteral("SpecularLightSlider"));
        SpecularLightSlider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(SpecularLightSlider);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_8 = new QLabel(verticalLayoutWidget_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_4->addWidget(label_8);

        DiffuseCheckbox = new QCheckBox(verticalLayoutWidget_2);
        DiffuseCheckbox->setObjectName(QStringLiteral("DiffuseCheckbox"));
        DiffuseCheckbox->setChecked(true);

        horizontalLayout_4->addWidget(DiffuseCheckbox);


        verticalLayout_2->addLayout(horizontalLayout_4);

        DiffuseSlider = new QSlider(verticalLayoutWidget_2);
        DiffuseSlider->setObjectName(QStringLiteral("DiffuseSlider"));
        DiffuseSlider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(DiffuseSlider);

        label_3 = new QLabel(verticalLayoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        shineSlider = new QSlider(verticalLayoutWidget_2);
        shineSlider->setObjectName(QStringLiteral("shineSlider"));
        shineSlider->setValue(80);
        shineSlider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(shineSlider);

        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        SlideAmbienOcclusionSlider = new QSlider(verticalLayoutWidget_2);
        SlideAmbienOcclusionSlider->setObjectName(QStringLiteral("SlideAmbienOcclusionSlider"));
        SlideAmbienOcclusionSlider->setSliderPosition(3);
        SlideAmbienOcclusionSlider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(SlideAmbienOcclusionSlider);

        Slices->addTab(tab, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        Dataset_Path = new QTextEdit(tab_7);
        Dataset_Path->setObjectName(QStringLiteral("Dataset_Path"));
        Dataset_Path->setGeometry(QRect(10, 20, 161, 41));
        OKButtonDataset = new QPushButton(tab_7);
        OKButtonDataset->setObjectName(QStringLiteral("OKButtonDataset"));
        OKButtonDataset->setGeometry(QRect(190, 220, 99, 27));
        pushButton_8 = new QPushButton(tab_7);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(70, 220, 99, 27));
        pushButton_9 = new QPushButton(tab_7);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(180, 30, 99, 27));
        label_10 = new QLabel(tab_7);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 70, 151, 17));
        x = new QPlainTextEdit(tab_7);
        x->setObjectName(QStringLiteral("x"));
        x->setGeometry(QRect(10, 100, 41, 31));
        y = new QPlainTextEdit(tab_7);
        y->setObjectName(QStringLiteral("y"));
        y->setGeometry(QRect(70, 100, 41, 31));
        z = new QPlainTextEdit(tab_7);
        z->setObjectName(QStringLiteral("z"));
        z->setGeometry(QRect(130, 100, 41, 31));
        Slices->addTab(tab_7, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        Snapshot = new QPushButton(tab_2);
        Snapshot->setObjectName(QStringLiteral("Snapshot"));
        Snapshot->setGeometry(QRect(90, 80, 131, 27));
        Slices->addTab(tab_2, QString());
        QWidget::setTabOrder(TransprencySlider, SamplingRateSlider);
        QWidget::setTabOrder(SamplingRateSlider, Slices);
        QWidget::setTabOrder(Slices, pushButton);
        QWidget::setTabOrder(pushButton, TFFiles);
        QWidget::setTabOrder(TFFiles, pushButton_3);
        QWidget::setTabOrder(pushButton_3, TransferFunctionPAth);

        retranslateUi(transparencySliders);

        Slices->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(transparencySliders);
    } // setupUi

    void retranslateUi(QWidget *transparencySliders)
    {
        transparencySliders->setWindowTitle(QApplication::translate("transparencySliders", "Form", 0));
        label_9->setText(QApplication::translate("transparencySliders", "Transfer offset", 0));
        label->setText(QApplication::translate("transparencySliders", "Transfer Scale", 0));
        label_5->setText(QApplication::translate("transparencySliders", "Sampling Distance", 0));
        Boundingbox->setText(QApplication::translate("transparencySliders", "Bounding box", 0));
        AmbientOcclusion->setText(QApplication::translate("transparencySliders", "Ambient Occlusion", 0));
        Preintegration->setText(QApplication::translate("transparencySliders", "PreIntegration", 0));
        Slices->setTabText(Slices->indexOf(tab_3), QApplication::translate("transparencySliders", "TF", 0));
        pushButton->setText(QApplication::translate("transparencySliders", "Browse", 0));
        TFFiles->setText(QApplication::translate("transparencySliders", "OK", 0));
        pushButton_3->setText(QApplication::translate("transparencySliders", "Cancel", 0));
        Slices->setTabText(Slices->indexOf(tab_4), QApplication::translate("transparencySliders", "TF files", 0));
        label_12->setText(QApplication::translate("transparencySliders", "Slice X Left", 0));
        label_13->setText(QApplication::translate("transparencySliders", "Slice X Right", 0));
        label_14->setText(QApplication::translate("transparencySliders", "Slice Y Left ", 0));
        label_17->setText(QApplication::translate("transparencySliders", "Slice Y Right", 0));
        label_15->setText(QApplication::translate("transparencySliders", "Slice Z Left", 0));
        label_16->setText(QApplication::translate("transparencySliders", "Slice Z Right", 0));
        Slices->setTabText(Slices->indexOf(tab_5), QApplication::translate("transparencySliders", "Slices", 0));
        label_6->setText(QApplication::translate("transparencySliders", "Ambient Light", 0));
        AmbientCheckbox->setText(QApplication::translate("transparencySliders", "Ambient Light", 0));
        label_7->setText(QApplication::translate("transparencySliders", "Specular Light ", 0));
        SpeculaCheckbox->setText(QApplication::translate("transparencySliders", "Specular Light", 0));
        label_8->setText(QApplication::translate("transparencySliders", "Diffuse light", 0));
        DiffuseCheckbox->setText(QApplication::translate("transparencySliders", "Diffuse light", 0));
        label_3->setText(QApplication::translate("transparencySliders", "Shininess (Specular Coefficient)", 0));
        label_2->setText(QApplication::translate("transparencySliders", "Ray step size (Ambient Occlusion)", 0));
        Slices->setTabText(Slices->indexOf(tab), QApplication::translate("transparencySliders", "Phongs ", 0));
        OKButtonDataset->setText(QApplication::translate("transparencySliders", "OK", 0));
        pushButton_8->setText(QApplication::translate("transparencySliders", "Cancel", 0));
        pushButton_9->setText(QApplication::translate("transparencySliders", "Browse", 0));
        label_10->setText(QApplication::translate("transparencySliders", "Enter XYZ dimensions: ", 0));
        Slices->setTabText(Slices->indexOf(tab_7), QApplication::translate("transparencySliders", "Dataset", 0));
        Snapshot->setText(QApplication::translate("transparencySliders", "Take Snapshot", 0));
        Slices->setTabText(Slices->indexOf(tab_2), QApplication::translate("transparencySliders", "Snap", 0));
    } // retranslateUi

};

namespace Ui {
    class transparencySliders: public Ui_transparencySliders {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSPARENCYSLIDERS_H
