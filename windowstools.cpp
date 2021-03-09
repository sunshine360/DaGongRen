#include "windowstools.h"

WindowsTools::WindowsTools()
{
}

bool WindowsTools::setActive()
{
    HWND h = ::FindWindow(_wtitle.data(), _wyyswinclass.data());
    if(h!=nullptr){
        ::SetActiveWindow(h);
        ::SwitchToThisWindow(h, true);
        return true;
    }
    return false;
}

bool WindowsTools::getMousePos(double &x, double &y)
{
    HWND h = ::FindWindow(_wtitle.data(), _wyyswinclass.data());
    if(h!=nullptr){
        RECT rc;
        ::GetWindowRect(h, static_cast<LPRECT>(&rc));
        x = rc.left;
        y = rc.bottom;
        return true;
    }
    return false;
}

bool WindowsTools::init(QString title, QString winclass)
{
    _fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;//获取屏幕分辨率宽度
    _fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;//获取屏幕分辨率高度
//  GetSystemMetrics ( SM_CXVIRTUALSCREEN ); //双屏时用

//#ifdef _MSC_VER
// return std::wstring((const wchar_t *)str.utf16());
//#else
// return str.toStdWString()

//    _wtitle = title.toStdWString();
//    _wyyswinclass = winclass.toStdWString();
    _wtitle = std::wstring((const wchar_t *)title.utf16());
    _wyyswinclass = std::wstring((const wchar_t *)winclass.utf16());
    HWND h = ::FindWindow(_wtitle.data(), _wyyswinclass.data());
    if(h!=nullptr){

        return true;
    }
    return false;
}
