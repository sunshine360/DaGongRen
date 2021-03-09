#ifndef WINDOWSTOOLS_H
#define WINDOWSTOOLS_H

#include <Windows.h>
#include <iostream>
#include <QString>
#include <QRect>

class WindowsTools
{
public:
    explicit WindowsTools();
    bool init(QString title,QString winclass);
    bool setActive();
    bool getMousePos(double& x, double& y);

private:
    double _fScreenWidth;
    double _fScreenHeight;

    double _posx;
    double _posy;

    std::wstring _wtitle;
    std::wstring _wyyswinclass;
};

#endif // WINDOWSTOOLS_H
