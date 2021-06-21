#include "myview.h"
#include <QKeyEvent>
#include<QWheelEvent>
#include<QObject>
#include<QMimeData>
#include<QDrag>
#include<QGraphicsSceneMouseEvent>
#include<iostream>
MyView::MyView(QWidget *parent) :
    QGraphicsView(parent)
{
}
//键盘+-

//滚轮事件
void MyView::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0){
        scale(1.2,1.2);
    }
    else {
        scale(1/1.2,1/1.2);
    }
    QGraphicsView::wheelEvent(event);

}
