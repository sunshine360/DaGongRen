#ifndef MOUSE_H
#define MOUSE_H

#include <Windows.h>
#include <iostream>
#include <QString>

class Mouse
{
public:
    Mouse();

    bool setActive();
    bool getStartPos(double &x, double &y);
    void setStartPos(double x, double y);
    void RandPos(double& x, double& y);

public:

    void MouseMove(double x, double y); //鼠标移动到指定位置
    void MouseLeftDown();//鼠标左键按下
    void MouseLeftUp();//鼠标左键放开
    void MouseRightUp();//鼠标左键放开
    void MouseRightDown();//鼠标右键按下

    QString getPos();

private:
    double _fScreenWidth;
    double _fScreenHeight;
    bool _needRand;

    double _last_posx;
    double _last_posy;

    std::wstring title;
    std::wstring yyswinclass;
};

#endif // MOUSE_H
