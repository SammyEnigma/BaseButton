/****************************************************************************
*
* Copyright (C) 2019-2026 MiaoQingrui. All rights reserved.
* Author: 缪庆瑞 <justdoit_mqr@163.com>
*
****************************************************************************/
/*
 *@author: 缪庆瑞
 *@date:   2019.8.19
 *@update: 2026.7.10
 *@brief:  基础push按钮
 *
 * 1.该类重新实现了QAbstractButton的nextCheckState()方法，方便通过check状态模拟按钮的"开关"状态，
 * 并可以配置在点击时自动/手动切换状态。
 * 2.该类重新实现了mousePressEvent()和mouseReleaseEvent()鼠标事件处理方法，添加了防抖和长按的功
 * 能处理。
 *
 */
#ifndef BASEPUSHBUTTON_H
#define BASEPUSHBUTTON_H

#include <QPushButton>
#include <QTimer>
#include <QMouseEvent>

class BasePushButton : public QPushButton
{
    Q_OBJECT
public:
    BasePushButton(QWidget *parent=0);

    //设置按钮是否可以自动check
    void setBtnAutoChecked(bool isAutoChecked){this->isAutoChecked = isAutoChecked;}
    //设置按钮防抖属性
    void setBtnAntiShakeProperty(bool antiShakeEnabled,uint antiShakeMs = 200);
    //设置按钮长按属性
    void setBtnLongPressProperty(bool longPressEnabled,uint longPressRespondMs = 3000,
                                 uint longPressMaxRespondedCount=1);
    void releaseBtn();//手动释放按钮

protected:
    virtual void nextCheckState();
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);

private:
    /*按钮自动check*/
    bool isAutoChecked = true;
    /*按钮防抖*/
    bool antiShakeEnabled = false;//防抖使能标记
    QTimer *antiShakeTimer = nullptr;//按钮防抖定时器
    /*按钮长按*/
    bool longPressEnabled = false;//长按使能标记
    QTimer *longPressTimer = nullptr;//按钮长按定时器
    uint longPressRespondedCount = 0;//按钮长按响应计数(长按定时器的超时次数)
    uint longPressMaxRespondedCount = 1;//按钮长按最大响应次数

signals:
    void longPressSig(uint longPressRespondedCount);//长按信号,参数为长按响应次数

public slots:
    void longPressTimerSlot();//长按定时器的响应槽
};

#endif // BASEPUSHBUTTON_H
