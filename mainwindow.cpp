#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QGraphicsEllipseItem>
#include<QObject>
#include <QApplication>
#include "myitem.h"
#include "myview.h"
#include <QTime>
#include<QListWidget>
#include<iostream>
#include<stdlib.h>
#include<QVector>
#include<QGraphicsLineItem>
#include<QGraphicsView>
#include<QWidget>
#include<QMouseEvent>
#include<fstream>
#include<QTimer>
#include<QString>
#include<ui_mainwindow.h>
#include<QMap>
#include<math.h>
#include<QSet>
#include<QColorDialog>
#include<graph.h>
MainWindow *MainWindow::mutualUi = nullptr;
double K_r = 70000;
double K_s = 0.1;
double x0 = -30;
double delta_t = 0.01;
QVector<MyItem *>node_data;
int ss = 0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
ui(new Ui::MainWindow)
{
    int nodess = 10;
    ui->setupUi(this);
    mutualUi = this;
    //设置UI
    ui->textBrowser->setTextColor(QColor(0,0,0));
    ui->textBrowser->setFontPointSize(10);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    QGraphicsScene *scene = new QGraphicsScene(-575, -425, 1150, 850);
    MyView *view = new MyView(this);
    //增加节点
    for (int i = 0; i < nodess; ++i) {
        MyItem *item = new MyItem;
        item->number = i;
        item->setZValue(1);
        view->node_num++;

        ui->comboBox->addItem("节点"+QString::number(i),i);
        ui->comboBox_2->addItem("节点"+QString::number(i),i);
        item->s = QColor(qrand() % 256, qrand() % 256, qrand() % 256);
        item->setColor(item->s);
        item->setPos(qrand()%1000-500, qrand()%700-350);
        item->text->setText(QString::number(i));
        item->text->setBrush(Qt::black);
        item->text->setPos(item->pos().rx()-item->scale()-item->text->text().length(),item->pos().ry()-item->scale()*4);
        item->text->setScale(1);
        item->text->setZValue(5);
        scene->addItem(item->text);
        node_data.append(item);
    }
    //增加边
    for (int i = 0;i<nodess;i++) {
        for (int j=i+1;j<nodess;j++) {
            QGraphicsLineItem *line = scene->addLine(QLineF(node_data[i]->pos().rx(),node_data[i]->pos().ry(),node_data[j]->pos().rx(), node_data[j]->pos().ry()));
            node_data[i]->addLines(line,true);
            node_data[j]->addLines(line,false);
            node_data[i]->nodes.push_back(j);
            node_data[j]->nodes.push_back(i);
        }
    }
    view->setRenderHint(QPainter::Antialiasing, true);
    view->setScene(scene);
    view->setGeometry(25, 25, 1175, 900);
    view->show();
    this->myview = view;
    for (int i=0;i<node_data.length();i++) {
        scene->addItem(node_data[i]);//先画点再画线
    }
    this->myview->setBackgroundBrush(Qt::white);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MyView::keyPressEvent(QKeyEvent *event){
    switch (event->key())
    {
    case Qt::Key_Up :
        for (int i = 0;i<node_data.length();i++) {
            node_data[i]->moveBy(0,-10);
            node_data[i]->text->moveBy(0,-10);
        }
        break;
    case Qt::Key_Down:
        for (int i = 0;i<node_data.length();i++) {
            node_data[i]->moveBy(0,10);
            node_data[i]->text->moveBy(0,10);
        }
        break;
    case Qt::Key_Left :
        for (int i = 0;i<node_data.length();i++) {
            node_data[i]->moveBy(-10,0);
            node_data[i]->text->moveBy(-10,0);
        }
        break;
    case Qt::Key_Right :
        for (int i = 0;i<node_data.length();i++) {
            node_data[i]->moveBy(10,0);
            node_data[i]->text->moveBy(10,0);
        }
        break;
    case Qt::Key_Plus :
        scale(1.2, 1.2);
        break;
    case Qt::Key_Minus :
        scale(1 / 1.2, 1 / 1.2);
        break;
    case Qt::Key_Space :
            rotate(10);
            break;

    MyView::keyPressEvent(event);
    }
}
//按钮放大
void MainWindow::on_pushButton_clicked()
{
    this->myview->scale(1.2,1.2);
}

//按钮增加节点
void MainWindow::on_pushButton_2_clicked()
{
    MyItem *item = new MyItem;
    item->number = this->myview->node_num;
    ui->comboBox->addItem("节点"+QString::number(item->number),item->number);
    ui->comboBox_2->addItem("节点"+QString::number(item->number),item->number);
    this->myview->node_num++;
    item->s = QColor(qrand() % 256, qrand() % 256, qrand() % 256);
    item->setColor(item->s);
    item->setPos(qrand()%1000-500, qrand()%700-350);
    item->text->setText(QString::number(this->myview->node_num-1));
    item->text->setBrush(Qt::black);
    item->text->setPos(item->pos().rx()-item->scale()-item->text->text().length(),item->pos().ry()-item->scale()*4);
    item->text->setScale(1);
    item->text->setZValue(5);
    this->myview->scene()->addItem(item->text);
    this->myview->scene()->addItem(item);
    item->setZValue(1);
    node_data.push_back(item);
}

void MainWindow::on_pushButton_3_clicked()
{
    int i = ui->comboBox->currentIndex();
    int j = ui->comboBox_2->currentIndex();
    i = ui->comboBox->itemData(i).toInt();
    j = ui->comboBox_2->itemData(j).toInt();
    QGraphicsLineItem *line = this->myview->scene()->addLine(QLineF(node_data[i]->pos().rx(),node_data[i]->pos().ry(),node_data[j]->pos().rx(), node_data[j]->pos().ry()));
    line->setZValue(0);
    if(this->myview->backgroundBrush().color()==Qt::white){
        line->setPen(QPen(Qt::black));
    }else{
        line->setPen(QPen(Qt::white));
}

    node_data[i]->addLines(line,true);
    node_data[j]->addLines(line,false);
    node_data[i]->nodes.push_back(j);
    node_data[j]->nodes.push_back(i);
}

void MainWindow::on_pushButton_4_clicked()
{
    this->myview->scale(1/1.2,1/1.2);
}

void MainWindow::on_pushButton_5_clicked()
{
    this->myview->setBackgroundBrush(Qt::black);
    for (int i=0;i<this->myview->node_num;i++) {
        for (int j = 0;j<node_data[i]->line_num;j++) {
            node_data[i]->lines[j]->setPen(QPen(Qt::white));
        }
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    this->myview->setBackgroundBrush(Qt::white);
    for (int i=0;i<this->myview->node_num;i++) {
        for (int j = 0;j<node_data[i]->line_num;j++) {
            node_data[i]->lines[j]->setPen(QPen(Qt::black));
        }
    }
}
void MainWindow::on_pushButton_10_clicked(){
    this->myview->setBackgroundBrush(QColor(255, 148, 26));
}


void MainWindow::clear(){
    this->myview->scene()->clear();
    this->myview->node_num = 0;
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    node_data.clear();
    ss = 0;
    this->ui->comboBox_3->clear();
}


void MainWindow::on_pushButton_7_clicked(){
    QSet<QString> label_set;
    clear();
    QString gml_data;
    gml_data = ui->lineEdit->text();
    Graph g;
    if(ui->checkBox->isChecked()==false){
        g.read_gml_id(gml_data);
        g.read_gml_edge(gml_data);
    }
    else {
        g.read_gml_id_label(gml_data);
        g.read_gml_edge(gml_data);
    }
    if(ui->checkBox_2->isChecked()==true){
        g.read_value(gml_data);
    }
    for (int i = 0; i < g.id.size(); ++i) {
        MyItem *item = new MyItem;
        item->number = g.id[i];
        item->setZValue(1);
        this->myview->node_num++;
        ui->comboBox->addItem("节点"+QString::number(i),i);
        ui->comboBox_2->addItem("节点"+QString::number(i),i);
        item->s = QColor(qrand() % 256, qrand() % 256, qrand() % 256);
        item->setColor(item->s);
//        item->setPos(4*i*cos(i/1.5), 4*i*sin(i/1.5));
        item->setPos(qrand()%1000-500, qrand()%700-350);
        if(ui->checkBox->isChecked()==true){
            item->label_name = g.label_name[i];
        }
        if(ui->checkBox_2->isChecked()==true){
            item->value = g.value[i];
        }else{
            item->value = "";
        }
        label_set.insert(item->value);
        item->text->setText(QString::number(g.id[i]));
        item->text->setBrush(Qt::black);
        item->text->setPos(item->pos().rx()-item->scale()-item->text->text().length()*2,item->pos().ry()-item->scale()-3);
        item->text->setScale(1);
        item->text->setZValue(5);
        this->myview->scene()->addItem(item->text);
        node_data.append(item);
        this->myview->scene()->addItem(item);

    }
    for(int i = 0;i<g.edge.size();i++){
        for (int j = 0;j<g.edge[i].size();j++) {
            int node2 = g.edge[i][j];
            QGraphicsLineItem *line = this->myview->scene()->addLine(QLineF(node_data[i]->pos().rx(),node_data[i]->pos().ry(),node_data[node2]->pos().rx(), node_data[node2]->pos().ry()));
            node_data[i]->addLines(line,true);
            node_data[node2]->addLines(line,false);
            node_data[i]->nodes.push_back(node2);
            node_data[node2]->nodes.push_back(i);
        }
    }
    for (QSet<QString>::iterator i = label_set.begin();i!=label_set.end();i++) {
        MainWindow::mutualUi->ui->comboBox_3->addItem(*i);
    }
}
void MainWindow::on_pushButton_8_clicked(){
    if (ui->checkBox_3->isChecked()==false){
        for (int i = 0;i<node_data.size();i++) {
            node_data[i]->setScale(node_data[i]->scale()*1.2);
            node_data[i]->text->setFont(QFont("华文琥珀",node_data[i]->size++));
        }
    }else {
        QString aim = this->ui->comboBox_3->currentText();
        for(int i = 0;i<node_data.size();i++){
            if(node_data[i]->value==aim){
                node_data[i]->setScale(node_data[i]->scale()*1.2);
                node_data[i]->text->setFont(QFont("华文琥珀",node_data[i]->size++));
            }
        }
}

}
void MainWindow::on_pushButton_9_clicked(){
    if (ui->checkBox_3->isChecked()==false){
        for (int i = 0;i<node_data.size();i++) {
            node_data[i]->setScale(node_data[i]->scale()/1.2);
            node_data[i]->text->setFont(QFont("华文琥珀",node_data[i]->size--));
        }
    }else {
        QString aim = this->ui->comboBox_3->currentText();
        for(int i = 0;i<node_data.size();i++){
            if(node_data[i]->value==aim){
                node_data[i]->setScale(node_data[i]->scale()/1.2);
                node_data[i]->text->setFont(QFont("华文琥珀",node_data[i]->size--));
            }
        }
}
}
void MainWindow::on_pushButton_12_clicked(){

    for (int i=0;i<this->myview->node_num;i++) {
        for (int j = 0;j<node_data[i]->line_num;j++) {
            QPen temp;
            temp = node_data[i]->lines[j]->pen();
            node_data[i]->lines[j]->setPen(QPen(Qt::white,temp.width()));
        }
    }
}
void MainWindow::on_pushButton_13_clicked(){
    for (int i=0;i<this->myview->node_num;i++) {
        for (int j = 0;j<node_data[i]->line_num;j++) {
            QPen temp;
            temp = node_data[i]->lines[j]->pen();
            node_data[i]->lines[j]->setPen(QPen(Qt::black,temp.width()));
        }
    }
}
void MainWindow::on_pushButton_14_clicked(){
    for (int i=0;i<this->myview->node_num;i++) {
        for (int j = 0;j<node_data[i]->line_num;j++) {
            QPen temp;
            temp = node_data[i]->lines[j]->pen();
            node_data[i]->lines[j]->setPen(QPen(node_data[i]->s,temp.width()));
        }
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    for (int i=0;i<this->myview->node_num;i++) {
        for (int j = 0;j<node_data[i]->line_num;j++) {
            QPen temp;
            temp = node_data[i]->lines[j]->pen();
            temp.setWidth(temp.width()+1);
            node_data[i]->lines[j]->setPen(temp);
        }
    }
}

void MainWindow::on_pushButton_15_clicked()
{
    for (int i=0;i<this->myview->node_num;i++) {
        for (int j = 0;j<node_data[i]->line_num;j++) {
            QPen temp;
            temp = node_data[i]->lines[j]->pen();
            temp.setWidth(temp.width()-1);
            node_data[i]->lines[j]->setPen(temp);
        }
    }
}
void MainWindow::on_pushButton_16_clicked(){
    if(node_data[0]->text->isVisible()){
        for (int i = 0;i<node_data.size();i++) {
            node_data[i]->text->hide();
        }
    }else {
        for (int i = 0;i<node_data.size();i++) {
            node_data[i]->text->show();
        }
}

}

//更新库伦斥力
void updateReplusion()
{
    double dx,dy,f,fx,fy,d,dsq;
    for(int i=0;i<node_data.length()-1;i++)
    {
        for(int j=i+1;j<node_data.length();j++)
        {
                dx=node_data[j]->pos().rx() - node_data[i]->pos().rx();//计算j节点对i节点x轴距离
                dy=node_data[j]->pos().ry() - node_data[i]->pos().ry();//计算j节点对i节点y轴距离
                if(dx!=0||dy!=0)
                {
                    dsq=dx*dx+dy*dy;
                    d=sqrt(dsq);
                    f=K_r/dsq;
                    fx=f*dx/d;
                    fy=f*dy/d;
                    //计算j节点与i节点之间的斥力大小
                    node_data[i]->force_x-=fx;
                    node_data[i]->force_y-=fy;
                    node_data[j]->force_x+=fx;
                    node_data[j]->force_y+=fy;
                }
        }
     }

}
//更新弹簧引力
void updateSpring()
{
    int i2;
    double dx,dy,f,fx,fy,d;
    for(int i=0;i<node_data.length();i++)
    {
        for(int j = 0;j<node_data[i]->line_num;j++)
        {
            //进行参数的计算
            i2=node_data[i]->nodes[j];
            dx=node_data[i2]->pos().rx()-node_data[i]->pos().rx();
            dy=node_data[i2]->pos().ry()-node_data[i]->pos().ry();
            if(dx!=0||dy!=0)
            {
                d=sqrt(dx*dx+dy*dy);
                f=K_s*(d-x0);
                fx=f*dx/d;
                fy=f*dy/d;
                //通过公式计算i2节点与i节点之间的斥力大小
                node_data[i]->force_x+=fx;
                node_data[i]->force_y+=fy;
                node_data[i2]->force_x-=fx;
                node_data[i2]->force_y-=fy;
            }
        }
    }
}
//更新位置
void updates()
{
    double dx,dy,dsq,s;
    for(int i=0;i<node_data.length();i++)
    {
        dx=delta_t*node_data[i]->force_x;//通过x轴力大小计算位移距离
        dy=delta_t*node_data[i]->force_y;//通过y轴力大小计算位移距离
        dsq=dx*dx+dy*dy;
        node_data[i]->setPos(node_data[i]->pos().rx()+dx,node_data[i]->pos().ry()+dy);
    }
}
//迭代n次
void repeatCalc(int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<node_data.length();j++)
            node_data[j]->force_x=0.0,node_data[j]->force_y=0.0;
        updateReplusion();
        updateSpring();
        updates();
    }
}
QTimer *timer=new QTimer;
void MainWindow::on_pushButton_17_clicked()
{
    connect(timer, &QTimer::timeout, this, [&](){
        repeatCalc(1);
    });
    timer->start(20);
    ui->label_4->setText("布局算法正在运行");
}
void MainWindow::on_pushButton_18_clicked()
{
    ui->label_4->setText("");
    timer->stop();
}
int find_index(QVector<QString> values,QString aim){
    for (int i = 0;i<values.length();i++) {
        if(values[i]==aim){
            return i;
        }
    }
    return -1;
}
void MainWindow::on_pushButton_19_clicked(){
    QVector<QString> values;
    QVector<QColor> colors;
    for (int i = 0;i<node_data.length();i++) {
        if(find_index(values,node_data[i]->value)==-1){
            values.push_back(node_data[i]->value);
            std::cout<<node_data[i]->value.toStdString()<<endl;
        }
    }
    for (int i = 0;i<node_data.length();i++) {
        colors.push_back(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
    }
    for (int i = 0;i<node_data.length();i++) {
        node_data[i]->setColor(colors[find_index(values,node_data[i]->value)]);
        node_data[i]->s = colors[find_index(values,node_data[i]->value)];
        node_data[i]->setFocus();
    }
}

void MainWindow::on_pushButton_20_clicked()
{
    x0 += 10;
}

void MainWindow::on_pushButton_21_clicked()
{
    x0 -= 10;
}

void MainWindow::on_pushButton_22_clicked()
{
    if(ss==0){
    float t0 = 0;
    for (int i = 0;i<node_data.length();i++) {
        if(t0<node_data[i]->line_num){
            t0 = node_data[i]->line_num;
        }
    }
    for (int i = 0;i<node_data.length();i++) {
        node_data[i]->setScale(exp(float(node_data[i]->line_num+1)/(t0+1))/2);
    }
    ss = 1;
    }
    else{
        for (int i = 0;i<node_data.length();i++) {
            node_data[i]->setScale(1.1);
        }
        ss = 0;
    }
}
void lpa(){
    MainWindow::mutualUi->ui->comboBox_3->clear();
    for (int i = 0;i<node_data.length();i++) {
        node_data[i]->lpa_label = node_data[i]->number;//初始化标签
    }
    int isactive = 1,times = 0;
    while (isactive&&(times<40)) {//当节点标签存在更改或迭代次数未达到最高
        isactive = 0;
        for (int i = 0;i<node_data.length();i++) {//对每个节点进行标签更新
            if(node_data[i]->line_num==0){//如果节点没有边，节点标签可以直接确定
                node_data[i]->lpa_label = node_data[i]->number;
                node_data[i]->value = QString::number(node_data[i]->number);
                continue;
            }
            QMap<int,int> map;
            for (int j = 0;j<node_data[i]->line_num;j++) {//遍历节点的邻居节点标签，以此确定新标签
                int neighbor = node_data[i]->nodes[j];
                if(map.find(node_data[neighbor]->lpa_label)==map.end()){//通过map记录各个标签出现次数
                    map[node_data[neighbor]->lpa_label] = 1;
                }else {
                    map[node_data[neighbor]->lpa_label]++;
                }
            }
            int max_oh = map.begin().value();
            QVector<int> bigoh;
            for (QMap<int,int>::iterator i = map.begin();i != map.end();i++) {//寻找出现次数最多的标签
                if(i.value()>max_oh){
                    bigoh.clear();
                    max_oh = i.value();
                    bigoh.append(i.key());
                }else if (i.value()==max_oh) {
                    bigoh.append(i.key());
                }
            }
            int thend = rand()%bigoh.length();
            thend = bigoh[thend];
            if(node_data[i]->lpa_label==thend){//进行标签的更新，并记录标签是否被更新
                node_data[i]->lpa_label = thend;
                node_data[i]->value = QString::number(thend);
            }else {
                node_data[i]->lpa_label = thend;
                node_data[i]->value = QString::number(thend);
                isactive =1;
        }
        }
        times++;
    }
    QSet<int> labelss;
    QMap <int,QColor> colorss;
    for (int i = 0;i<node_data.length();i++) {
        labelss.insert(node_data[i]->lpa_label);
    }
    for (QSet<int>::iterator i = labelss.begin();i!=labelss.end();i++) {
        colorss[*i] = QColor(qrand() % 256, qrand() % 256, qrand() % 256);
        MainWindow::mutualUi->ui->comboBox_3->addItem(QString::number(*i));
    }
    for (int i = 0;i<node_data.length();i++) {
        node_data[i]->setColor(colorss[node_data[i]->lpa_label]);
        node_data[i]->s = colorss[node_data[i]->lpa_label];
    }

}
void MainWindow::on_pushButton_23_clicked()
{
    lpa();
    for (int i = 0;i<node_data.length();i++) {
        node_data[i]->setFocus();
    }
}

void MainWindow::on_pushButton_24_clicked()
{
  clear();
}

void MainWindow::on_pushButton_25_clicked()
{
    QColorDialog dlg;
    QColor color;
    dlg.setWindowTitle("Color Editor");         // 设置窗口名称
    dlg.setCurrentColor(QColor(0, 0, 0)); // 设置当前窗口颜色
    if( dlg.exec() == QColorDialog::Accepted )
    {
        color = dlg.selectedColor();
    }
    if(this->ui->checkBox_3->isChecked()==false){
        for(int i = 0;i<node_data.size();i++){
            node_data[i]->setColor(color);
            node_data[i]->s = color;
        }
    }else {
        QString aim = this->ui->comboBox_3->currentText();
        for(int i = 0;i<node_data.size();i++){
            if(node_data[i]->value==aim){
                node_data[i]->setColor(color);
                node_data[i]->s = color;
            }
        }
}
}
