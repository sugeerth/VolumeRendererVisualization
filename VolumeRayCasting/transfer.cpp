#include "transfer.h"
#include "ui_transfer.h"
#include <GLWidget.h>
#include <QtGui/qcolor.h>
#include <QColorDialog>
#include <QGraphicsItem>
Transfer::Transfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Transfer)
{
    ui->setupUi(this);
    setWindowTitle("Interactive transfer function");
    resize(410,250);
    ColorSelected1 = QColor(255,0,0);
    ColorSelected2 = QColor(255,0,255);
    ColorSelected3 = QColor(255,0,255);
    ColorSelected4 = QColor(0,255,0);
    DeltaColor = 400/4;
    Clear();
}
void Transfer::Clear(){
        ColorData.clear();

        int myint=401;
        for(int i = 0;i< 401;i++){
        ColorData.push_back(Vec4f(0.0f,0.0f,0.0f,0.0f));}
//        cout<<"Size"<<ColorData.size();
}

void Transfer::acceptGLWidget(GLWidget *w)
{
    W=w;
    cout<<"Transfer Function";
}

void Transfer::mousePressEvent(QMouseEvent *e)
{
    Clear();
    if (e->buttons() & Qt::LeftButton)
    {
        lines.clear();
        if (!linevariable)
        {
            cout<<"Clicked";
            startPos = e->pos();
            RealStart = startPos;
            QLine line = QLine(QPoint(startPos.x()-5,200),startPos-QPoint(5,0));
            lines.append(line);
        }
        else
        {
            cout<<"Clicked2";

        }
        linevariable = ! linevariable;
    }
}

void Transfer::mouseMoveEvent(QMouseEvent *e)
{
        if (linevariable)
        {
//            cout<<"Moved";
            endPos = e->pos();
            if (endPos.x() > startPos.x()){
                QColor a= TransferFunction.pixel(e->x()+5,4);
                QLine line = QLine(startPos-QPoint(5,0), endPos-QPoint(5,0));
            startPos = endPos;
            lines.append(line);
//            update();

           float opacity=(1-(float(e->y())/240.0));

           float index=0;

            if((e->x()-5) < 0)
                index=0.0f;
            else if(((e->x())-5) > 400)
                index=400;
            else
                index =(e->x())-5;

            if(opacity > 1.0f)
                opacity =1.0f;
            else if(opacity < 0.0f)
                opacity = 0.0f;

            ColorData[index]=Vec4f(float(a.red())/255,float(a.green())/255,float(a.blue())/255,opacity);}
//            cout<<"index : "<<index<<" Red :"<<a.red()<<" Green : "<<a.green()<<" Blue :"<<a.blue() <<" opacity " <<opacity<<" Pos : X "<<e->pos().x()<<" Pos : Y "<<e->pos().y();
            update();
        }

}

void Transfer::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton && linevariable) {
             linevariable = false;
//             QLine line = QLine(startPos-QPoint(5,0),QPoint(e->x()-5,200));
//             QLine line1 = QLine(QPoint(e->x()-5,200),QPoint(390,210));
//             lines.append(line);
             update();
         }
//    cout<<"Size While releaseing "<<ColorData.size()<< ;
    W->getTransferValues(ColorData);
}

void Transfer::mouseDoubleClickEvent(QMouseEvent *e)
{
//    cout<<"YOLO"<<e->x()<<" "<<e->y()<<DeltaColor;
    DoublePressed = true;
    QColorDialog ab;
    if (e->x() < 0.25*400){
        ColorSelected1 = QColorDialog::getColor(Qt::blue);
        cout<<ColorSelected1.red();}
    else if ((e->x() > DeltaColor) && (e->x() < 2*DeltaColor))
        ColorSelected2 = ab.currentColor();
    if ((e->x() > 2*DeltaColor) && (e->x() < 3*DeltaColor))
        ColorSelected3 = QColorDialog::getColor(Qt::blue);
    if ((e->x() > 3*DeltaColor) && (e->x() < 4*DeltaColor))
        ColorSelected4 = QColorDialog::getColor(Qt::blue);

    TransferFunction.save("Image.PNG");

    update();
}

void Transfer::drawLines(QPainter *p)
{
    p->setPen(QPen(Qt::black, 1));
    if (!startPos.isNull() && !endPos.isNull())
    {
        p->drawLine(QPointF(0,200), QPointF(RealStart.x()-5,200));
        p->drawLine(QPointF(startPos.x()-5,200),startPos-QPointF(5,0));
        p->drawLine(startPos-QPointF(5,0), endPos-QPointF(5,0));
        p->drawLine(endPos-QPointF(5,0),QPointF(endPos.x()-5,200));
        p->drawLine(QPointF(endPos.x()-5,200),QPointF(400,200));
    }
    p->drawLines(lines);
}

Transfer::~Transfer()
{
    delete ui;
}

// Left for now to implement the interactive transfer functions

void Transfer::paintEvent(QPaintEvent *e)
{
    QRect rec(0,0,400,250);

    QPixmap *pix = new QPixmap(400,240);
    QPainter painter(pix);
    QLinearGradient grad1(0,0,400,0);

    //Setting the gradient !!
    grad1.setColorAt(0.2,ColorSelected1);
    grad1.setColorAt(0.5,ColorSelected2);
    grad1.setColorAt(0.6,ColorSelected3);
    grad1.setColorAt(0.8,ColorSelected4);

    cout<<endl;
    painter.fillRect(rec,grad1);

    drawLines(&painter);

    painter.drawRect(rec);
    QPainter painter2(this);
    painter2.drawPixmap(5,5,400,240,*pix);
    TransferFunction = pix->toImage();
//    TransferFunction.save("Image.PNG");
}
void Transfer::on_Sendingtransfervalues_clicked()
{
}

