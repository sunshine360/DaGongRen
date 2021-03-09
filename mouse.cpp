#include "mouse.h"
#include <iostream>
#include <math.h>
#include <QTime>

Mouse::Mouse()
{
    _fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;//获取屏幕分辨率宽度
    _fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;//获取屏幕分辨率高度
    _needRand = true;
    _last_posx = 0;
    _last_posy = 0;

    std::wstring title = L"阴阳师-网易游戏";
    std::wstring yyswinclass = L"Win32Window";
}

// 获取启动的鼠标相对位置
bool Mouse::getStartPos(double &x, double &y)
{
    POINT p;
    ::GetCursorPos(&p);
    x = p.x;
    y = p.y;
    return true;
//    HWND h = ::FindWindow(yyswinclass.data(), title.data());
//    if(h!=nullptr){
//        WINDOWINFO pwi;
//        bool ret = ::GetWindowInfo(h, &pwi);
//        x = pwi.cbSize;
//        y = pwi.cbSize;
//        return ret;
//    }
//    return false;
}

void Mouse::setStartPos(double x, double y)
{
    ::SetCursorPos(static_cast<int>(x), static_cast<int>(y));
}

void Mouse::RandPos(double &x, double&y)
{
    // 最大随机数RAND_MAX=32767
    // 随机出一个 0.001 - 7.001 之间的随机数
    double rang = 7.0;
    x = x + qrand()*(rang / RAND_MAX);
    y = y + qrand()*(rang / RAND_MAX);
}

void Mouse::MouseMove(double x, double y)//鼠标移动到指定位置
{
    //随机移动7个像素
    //double fx = x*(static_cast<double>(65535.0f) / _fScreenWidth);
    //double fy = y*(static_cast<double>(65535.0f) / _fScreenHeight);
    //RandPos(_last_posx, _last_posy);
    double rang = 7.0;
    _last_posx = x + qrand()*(rang / RAND_MAX);
    _last_posy = y + qrand()*(rang / RAND_MAX);
    double dx = _last_posx * (65536 / _fScreenWidth);
    double dy = _last_posy * (65536 / _fScreenHeight);

    INPUT  Input = {};
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    Input.mi.dx = static_cast<long>(dx);
    Input.mi.dy = static_cast<long>(dy);
    SendInput(1, &Input, sizeof(INPUT));
}

void Mouse::MouseLeftDown()//鼠标左键按下
{
    INPUT  Input= {};
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &Input, sizeof(INPUT));
}

void Mouse::MouseLeftUp()//鼠标左键放开
{
    INPUT  Input;
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &Input, sizeof(INPUT));
}

void Mouse::MouseRightDown()//鼠标右键按下
{
    INPUT  Input;
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &Input, sizeof(INPUT));
}

void Mouse::MouseRightUp()//鼠标右键放开
{
    INPUT  Input;
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, &Input, sizeof(INPUT));
}

QString Mouse::getPos()
{
    return QString::asprintf("x:%.1f,y:%.1f,", _last_posx, _last_posy);
}
