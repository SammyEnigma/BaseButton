/*
 *@author:  缪庆瑞
 *@date:    2020.04.03
 *@brief:   用来测试基类按钮的功能接口
 */
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;


};

#endif // WIDGET_H
