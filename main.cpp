#include <QApplication>
#include "myitem.h"
#include "myview.h"
#include <QTime>
#include<iostream>
#include<QVector>
#include<QGraphicsLineItem>
#include<QObject>
#include<mainwindow.h>
#include<QWidget>
#include<QGridLayout>

int main(int argc, char* argv[ ])
{
    QApplication app(argc, argv);
    MainWindow m;
    m.show();
    return app.exec();
}

