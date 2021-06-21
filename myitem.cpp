#include "myitem.h"
#include <QPainter>
#include <QCursor>
#include <QKeyEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneContextMenuEvent>
#include<QObject>
#include<iostream>
#include <QMenu>
#include<dialog.h>
#include<QTime>
#include<QString>
#include <ui_mainwindow.h>
#include<QGraphicsLineItem>
#include<mainwindow.h>
#include<QDialog>
#include "ui_dialog.h"
#include<QColorDialog>
extern QVector<MyItem*> node_data;
MyItem::MyItem()
{
    brushColor = Qt::blue;
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setAcceptHoverEvents(true);

}
// 首先对一些方法进行重写

QRectF MyItem::boundingRect() const
{
    double adjust = 0.5;
    return QRectF(-10 - adjust, -10 - adjust,20 + adjust, 20 + adjust);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,QWidget *)
{
//    painter->setRenderHint(QPainter::Antialiasing, true);//抗锯齿
    if (hasFocus()) {
        painter->setPen(QPen(Qt::black));
        painter->setPen(Qt::PenStyle(50));
    } else {
        painter->setPen(QPen(Qt::white));
    }
    painter->setBrush(brushColor);
    painter->drawEllipse(-10, -10, 20,20);
}

// 鼠标按下事件处理函数，设置被点击的图形项获得焦点，并改变光标外观,在编辑框里面打印相关信息
void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    setFocus();
    setCursor(Qt::ClosedHandCursor); //设置光标为手握下的形状
    MainWindow::mutualUi->ui->textBrowser->setText("节点编号为："+QString::number(this->number)+"\n节点的度为："+QString::number(this->line_num)+"\n节点名称为："+this->label_name+"\n所处类别："+this->value+"\n自定义信息：\n"+this->data);
}

// 悬停事件处理函数，设置光标外观和提示
void MyItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    setCursor(Qt::OpenHandCursor); //设置光标为手张开的形状
    setToolTip("Node");
    setOpacity(0.6);
    for (int i = 0;i<this->nodes.length();i++) {
        node_data[this->nodes[i]]->setOpacity(0.6);
    }
    for (int i = 0;i<this->lines.length();i++) {
        this->lines[i]->setOpacity(0.6);
    }
}
void MyItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setOpacity(1);
    for (int i = 0;i<this->nodes.length();i++) {
        node_data[this->nodes[i]]->setOpacity(1);
    }
    for (int i = 0;i<this->lines.length();i++) {
        this->lines[i]->setOpacity(1);
    }
}
// 右键菜单事件处理函数，为图形项添加一个右键菜单
void MyItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *moveAction = menu.addAction("移回原点");
    QAction *biggerAction = menu.addAction("增大节点");
    QAction *inputData = menu.addAction("设置");
    QAction *color = menu.addAction("选择颜色");
    QAction *selectedAction = menu.exec(event->screenPos());

    if (selectedAction == moveAction) {
        this->setPos(0, 0);
        this->text->setPos(0,0);
    }
    if(selectedAction == biggerAction){
        this->setScale(this->scale()*1.2);
        this->text->setFont(QFont("华文琥珀",this->size++));
    }
    if(selectedAction == inputData){
        Dialog *dialog;
        dialog = new Dialog();

        dialog->number = this->number;
        dialog->ui->textEdit->setText(node_data[this->number]->data);
        dialog->ui->lineEdit_2->setText(node_data[this->number]->value);
        dialog->ui->lineEdit->setText(QString::number(node_data[this->number]->scale()));
        dialog->show();
    }
    if(selectedAction == color){
        QColorDialog dlg;
        dlg.setWindowTitle("Color Editor");         // 设置窗口名称
        dlg.setCurrentColor(QColor(0, 0, 0)); // 设置当前窗口颜色
        if( dlg.exec() == QColorDialog::Accepted )
        {
            QColor color = dlg.selectedColor();
            this->setColor(color);
        }
     }

}

//void MyItem::moveto(qreal x, qreal y){
//    qreal deltax = (x - this->pos().rx())/1000;
//    qreal deltay = (y - this->pos().ry())/1000;

//    for (int i = 0;i<1000;i++) {
//        QTime time;
//        time.start();
//        while(time.elapsed() < 1);
//        qreal xx = this->pos().rx();
//        qreal yy = this->pos().ry();
//        this->setPos(xx+deltax,yy+deltay);
//        this->show();
//        this->update();
//    }
//}
