#ifndef MYVIEW_H
#define MYVIEW_H

#include <QKeyEvent>
#include<QWheelEvent>
#include <QGraphicsView>
#include<QObject>
#include<QMimeData>
#include<QMouseEvent>
#include<QVector>
class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    MyView(QWidget *parent);
    int node_num = 0;
protected:
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
};
#endif // MYVIEW_H
