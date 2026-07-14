/*
 *@author:  缪庆瑞
 *@date:    2020.04.03
 *@brief:   用来测试基类按钮的功能接口
 */
#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

