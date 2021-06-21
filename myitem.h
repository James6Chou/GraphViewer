#ifndef MYITEM_H
#define MYITEM_H

#include<QObject>
#include <QGraphicsItem>
#include<QWheelEvent>
#include<QVector>
#include<iostream>
class MyItem : public QGraphicsItem
{
public:
    int lpa_label;
    QString data;
    QVector<QGraphicsLineItem *> lines;
    QGraphicsSimpleTextItem *text = new QGraphicsSimpleTextItem;
    int number;
    QString value = "";
    QColor s;
    QVector<int> nodes;
    bool isP1[1000];
    double force_x = 0,force_y = 0;
    QString label_name = "None";
    int line_num=0;
    int size = 10;
    MyItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void setColor(const QColor &color) { brushColor = color; }
    //下面为了能增加节点之间的线，进行方法重写
    void addLines(QGraphicsLineItem *line, bool isPoint1){
        this->hasLine = 1;
        this->lines.push_back(line);
        this->line_num++;
        isP1[this->line_num-1] = isPoint1;
    }

    QVariant itemChange(GraphicsItemChange change, const QVariant &value)
    {
        if(hasLine){
        if (change == ItemPositionChange && scene()) {
            //处于新位置
            QPointF newPos = value.toPointF();
            moveLineToCenter(newPos);
        }}
        if (change == ItemPositionChange && scene()){
            this->text->setPos(this->pos().rx()-this->scale()-this->text->text().length(),this->pos().ry()-this->scale()-3);
        }

        return QGraphicsItem::itemChange(change, value);
    }
    void moveLineToCenter(QPointF newPos) {
        int xOffset = -10 + 10;
        int yOffset = -10 + 10;
        QPointF newCenterPos = QPointF(newPos.x() + xOffset, newPos.y() + yOffset);
        for (int ii = 0;ii<this->line_num;ii++) {
            QPointF p1 = isP1[ii] ? newCenterPos : this->lines[ii]->line().p1();
            QPointF p2 = isP1[ii] ? this->lines[ii]->line().p2() : newCenterPos;//其实就是根据true还是false来判断是哪一端
            this->lines[ii]->setLine(QLineF(p1, p2));
        }
    }
private:
    QColor brushColor;
    int hasLine = 0;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};
#endif // MYITEM_H
