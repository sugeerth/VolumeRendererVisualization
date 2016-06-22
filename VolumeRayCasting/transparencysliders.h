#ifndef TRANSPARENCYSLIDERS_H
#define TRANSPARENCYSLIDERS_H

#include <QWidget>
#include<GLWidget.h>

namespace Ui {
class transparencySliders;
}

class transparencySliders : public QWidget
{
    Q_OBJECT

public:
    explicit transparencySliders(QWidget *parent = 0);
    void acceptGLWidget(GLWidget *w);
    GLWidget *W;
    ~transparencySliders();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_9_clicked();

    void on_OKButtonDataset_clicked();

    void on_Preintegration_clicked(bool checked);

    void on_TFFiles_clicked(bool checked);

private:
    Ui::transparencySliders *ui;
};

#endif // TRANSPARENCYSLIDERS_H
