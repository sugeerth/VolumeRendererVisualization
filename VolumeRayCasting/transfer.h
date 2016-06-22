#ifndef TRANSFER_H
#define TRANSFER_H
#include<QPaintEvent>
#include <QWidget>
#include <QPen>
#include <QPainter>
#include <GLWidget.h>
#include <vector>
#include<QColor>

namespace Ui {
class Transfer;
}

class Transfer : public QWidget
{
    Q_OBJECT

public:
    explicit Transfer(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);
    ~Transfer();
    void acceptGLWidget(GLWidget *w);
    GLWidget *W;
    void virtual drawLines(QPainter *p);


    QPoint startPos;
    QPoint RealStart;
    QPoint interMediatePos;
    QPoint endPos;
    QVector<QLine> lines;
    bool inDrawing = false;

    QColor ColorSelected[512] = {QColor(0,0,0)};

    QColor ColorSelected1;
    QColor ColorSelected2;
    QColor ColorSelected3;
    QColor ColorSelected4;
    QColor ColorSelected5;
    QColor ColorSelected6;

    float DeltaColor = 400/6;
    QPolygonF polygon;
    std::vector<Vec4f> transferFuncData;

    std::vector<Vec4f> ColorData;

    bool linevariable=false;

    QImage TransferFunction;
    QPointF endPoint= QPointF(0,0);
    QPointF lastPoint= QPointF(0,0);

    bool Pressed = false;
    bool DoublePressed = false;
    void mousePressEvent(QMouseEvent *);

    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void moveT(QPointF A);
    void moveT(QPointF &A);
    virtual void Clear();


private slots:
    void on_Sendingtransfervalues_clicked();

private:
    Ui::Transfer *ui;
};

#endif // TRANSFER_H
