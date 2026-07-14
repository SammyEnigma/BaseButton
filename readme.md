# BaseButton
这是一个基于Qt的按钮基础组件项目，旨在封装不同的按钮基类，去实现特定的按钮功能。  
## 1.BaseToolButton/BasePushButton
### 功能概述：
这两个类分别继承自QToolButton/QPushButton，内部封装的接口完全一致，可以根据需求和使用习惯选择对应的基类。  
1.该类重新实现了QAbstractButton的nextCheckState()方法，方便通过check状态模拟按钮的"开关"状态，并可以配置在点击时自动/手动切换状态。  
2.该类重新实现了mousePressEvent()和mouseReleaseEvent()鼠标事件处理方法，添加了防抖和长按的功能处理。  
### 接口函数：
```
    //设置按钮是否可以自动check
    void setBtnAutoChecked(bool isAutoChecked){this->isAutoChecked = isAutoChecked;}
    //设置按钮防抖属性
    void setBtnAntiShakeProperty(bool antiShakeEnabled,uint antiShakeMs = 200);
    //设置按钮长按属性
    void setBtnLongPressProperty(bool longPressEnabled,uint longPressRespondMs = 3000,
                                 uint longPressMaxRespondedCount=1);
    void releaseBtn();//手动释放按钮

```
## 作者联系方式:
**邮箱:justdoit_mqr@163.com**  
