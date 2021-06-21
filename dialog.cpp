#include "dialog.h"
#include "ui_dialog.h"
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
#include<mainwindow.h>
extern QVector<MyItem*> node_data;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    node_data[this->number]->data = this->ui->textEdit->toPlainText();
    node_data[this->number]->setScale((this->ui->lineEdit->text()).toFloat());
    node_data[this->number]->value = this->ui->lineEdit_2->text();
    MainWindow::mutualUi->ui->comboBox_3;
    int ischange = 1;
    for (int i = 0;i<MainWindow::mutualUi->ui->comboBox_3->count();i++) {
        QString temp = MainWindow::mutualUi->ui->comboBox_3->itemText(i);
        if(temp == this->ui->lineEdit_2->text()){
            ischange = 0;
        }
    }
    if(ischange){
        MainWindow::mutualUi->ui->comboBox_3->addItem(this->ui->lineEdit_2->text());
    }
    this->setVisible(false);

}
