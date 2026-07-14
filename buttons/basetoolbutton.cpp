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
 *@brief:  基础工具按钮
 */
#include "basetoolbutton.h"

/*
 *@brief:   构造函数
 *@date:    2019.8.20
 *@param:   parent:父对象
 */
BaseToolButton::BaseToolButton(QWidget *parent)
    :QToolButton(parent)
{

}
/*
 *@brief:   设置按钮防抖属性
 *@date:    2022.4.6
 *@param:   antiShakeEnabled:防抖使能状态
 *@param:   antiShakeMs:防抖时间 ms
 */
void BaseToolButton::setBtnAntiShakeProperty(bool antiShakeEnabled, uint antiShakeMs)
{
    this->antiShakeEnabled = antiShakeEnabled;
    if(this->antiShakeEnabled)//防抖功能使能
    {
        //初始化防抖定时器
        if(!antiShakeTimer)
        {
            antiShakeTimer = new QTimer(this);
            antiShakeTimer->setSingleShot(true);//单次定时器
        }
        antiShakeTimer->setInterval(antiShakeMs);
    }
    else//防抖功能禁用
    {
        if(antiShakeTimer)
        {
            antiShakeTimer->deleteLater();//清理防抖定时器
            antiShakeTimer = nullptr;
        }
    }
}
/*
 *@brief:   设置按钮长按属性
 *@date:    2019.12.17
 *@param:   longPressEnabled:长按使能状态
 *@param:   longPressRespondMs:长按响应时间 ms
 *@param:   longPressMaxRespondedCount:长按最大响应次数
 */
void BaseToolButton::setBtnLongPressProperty(bool longPressEnabled, uint longPressRespondMs,
                                             uint longPressMaxRespondedCount)
{
    this->longPressEnabled = longPressEnabled;
    this->longPressMaxRespondedCount = longPressMaxRespondedCount;
    if(this->longPressEnabled)//长按功能使能
    {
        //初始化长按定时器
        if(!longPressTimer)
        {
            longPressTimer = new QTimer(this);
            connect(longPressTimer,SIGNAL(timeout()),this,SLOT(longPressTimerSlot()));
            /* 当鼠标在按钮上按下然后脱离按钮区域时会触发released信号，但不会执行mouseReleaseEvent
             * 处理函数(释放鼠标才进入该函数)，所以为了确保鼠标离开按钮区域就不再发送长按信号，这里
             * 关联了released信号和长按定时器的stop槽*/
            connect(this,SIGNAL(released()),longPressTimer,SLOT(stop()));
        }
        longPressTimer->setInterval(longPressRespondMs);
    }
    else//长按功能禁用
    {
        if(longPressTimer)
        {
            longPressTimer->deleteLater();//清理长按定时器
            longPressTimer = nullptr;
        }
    }
}
/*
 *@brief:   手动释放按钮
 *避免因长按信号触发(半)模态窗口导致按钮释放操作无法响应
 *@date:    2020.02.22
 */
void BaseToolButton::releaseBtn()
{
    /* 模拟一个鼠标释放事件
     * 第二个参数表示鼠标指针相对按钮的位置,这里设置为(-1,-1)表示鼠标是在按钮之外释放的，这样既不会
     * 触发按钮的clicked()信号,也能让按钮(样式)回到正常状态。*/
    QMouseEvent mouseEvent(QMouseEvent::MouseButtonRelease,
                           QPoint(-1,-1),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
    mouseReleaseEvent(&mouseEvent);
}
/*
 *@brief:   这是QAbstractButton类提供的一个抽象方法,当按钮被点击时会自动调用。该方法默认的实现是
 *"calls setChecked(!isChecked()) if the button isCheckable()."，这里重新实现该方法，通过
 *一个标志变量来控制按钮是否可以通过点击自动切换check状态。
 *@date:    2019.09.03
 */
void BaseToolButton::nextCheckState()
{
    if(isAutoChecked)
    {
        QToolButton::nextCheckState();
    }
}
/*
 *@brief:   鼠标按下事件处理  重写该函数给按钮添加防抖和长按功能
 *@date:    2019.09.11
 *@param:   e:鼠标事件
 */
void BaseToolButton::mousePressEvent(QMouseEvent *e)
{
    /*防抖功能激活，防抖时间内则直接返回不做响应
     *查看QAbstractButton::mousePressEvent()的源码实现可知,如果这里没有调用父类的处理函数，则在
     *mouseReleaseEvent()处理函数中也不会发出released和clicked信号,即这里添加防抖处理不会引起信号逻辑混乱*/
    if(antiShakeEnabled && antiShakeTimer->isActive())
    {
        return;
    }

    QToolButton::mousePressEvent(e);
    //如果防抖使能，则开启防抖定时器
    if(antiShakeEnabled)
    {
        antiShakeTimer->start();
    }
    //如果长按使能，则开启长按定时器
    if(longPressEnabled)
    {
        longPressRespondedCount = 0;
        longPressTimer->start();
    }
}
/*
 *@brief:   鼠标释放事件处理  重写添加长按功能
 *@date:    2019.12.17
 *@param:   e:鼠标事件
 */
void BaseToolButton::mouseReleaseEvent(QMouseEvent *e)
{
    //如果长按使能，则关闭长按定时器
    if(longPressEnabled)
    {
        longPressTimer->stop();
        //释放按钮时如果已经响应过长按信号，则模拟一个鼠标释放事件(按钮外释放)，避免响应单次点击信号
        if(longPressRespondedCount)
        {
            QMouseEvent mouseEvent(QMouseEvent::MouseButtonRelease,
                                   QPoint(-1,-1),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
            QToolButton::mouseReleaseEvent(&mouseEvent);
            return;
        }
    }
    QToolButton::mouseReleaseEvent(e);
}
/*
 *@brief:   长按定时器的响应槽
 *@date:    2019.12.17
 */
void BaseToolButton::longPressTimerSlot()
{
    longPressRespondedCount++;
    if(longPressRespondedCount >= longPressMaxRespondedCount)
    {
        longPressTimer->stop();
    }
    emit longPressSig(longPressRespondedCount);//上报长按信号
}

