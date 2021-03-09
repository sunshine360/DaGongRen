#ifndef KEYBOARD_H
#define KEYBOARD_H

//keyboard.h
//模拟键盘的常见操作
// https://blog.csdn.net/lxj434368832/article/details/60875450?utm_medium=distribute.pc_aggpage_search_result.none-task-blog-2~all~first_rank_v2~rank_v28-4-60875450.nonecase

class KEYBOARD
{
public:
    void    PressStr(char *str);
    void    PressKey(BYTE bVk);
    void    KeyDown(BYTE bVk);
    void    KeyUp(BYTE bVk);
};

//按键（虚拟键值）
void KEYBOARD::PressKey(BYTE bVk)
{
    ::keybd_event(bVk,0,0,0);
    ::keybd_event(bVk,0,KEYEVENTF_KEYUP,0);
}

//按下（虚拟键值）
void KEYBOARD::KeyDown(BYTE bVk)
{
    ::keybd_event(bVk,0,0,0);
}

//抬起（虚拟键值）
void KEYBOARD::KeyUp(BYTE bVk)
{
    ::keybd_event(bVk,0,KEYEVENTF_KEYUP,0);
}

//发送字符串（字符串）
void KEYBOARD::PressStr(char *str)
{
    for (unsigned i=0;i
    {
        if (str[i]>0x60 && str[i]<0x7B)
            this->PressKey(str[i]-0x20);
        else
            this->PressKey(str[i]);
    }
}

#endif // KEYBOARD_H
