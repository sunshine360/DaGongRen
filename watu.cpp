#include "watu.h"
#include "mouse.h"
#include <chrono>
#include <QThread>
#include <QElapsedTimer>

Watu::Watu(qint32 sec,double x,double y, qint32 t, qint32 times, QObject *parent)
    :QObject(parent), _second(sec), _input_posx(x), _input_posy(y), _times(t), _watu_times(times)
{
    _total_times = 0;
    _rand_sec = 0;
    _count_mouse_click = 0;
    // 关联定时器
    _fTimer = new QTimer(this);
    _fTimer->stop();
    _fTimer->setInterval(_second*1000+rand()%999); // 定是周期1000毫秒
    connect(_fTimer, &QTimer::timeout, this, &Watu::on_timer_timeout);
}

void Watu::mouseClick(double posx, double posy)
{
    _mouse.MouseMove(posx, posy);//鼠标移动到指定位置
    _mouse.MouseLeftDown();//鼠标左键点下
    _mouse.MouseLeftUp();
    _count_mouse_click++;
}

void Watu::doManual(double x,double y)
{
    double tempx = 0.0;
    double tempy = 0.0;
    _mouse.getStartPos(tempx, tempy);

    _input_posx = x;
    _input_posy = y;
    //emit doLog(QString::asprintf("x:%.1f,y:%.1f", x, y));

    // 手动模式下，7秒钟的间隔时间内，鼠标点击次数 12 - 20 次
    // TODO: 网络卡顿会导致超过7秒，此时已经打乱了整个节奏
    _count_mouse_click = 0;
    QElapsedTimer timerElapsed;
    timerElapsed.start();
    for (qint32 i = 0; i<=_times ; i++) {

        mouseClick(_input_posx, _input_posy);
        Sleep(rand()%400);

        mouseClick(_input_posx, _input_posy);
        Sleep(rand()%1200);
    }
    qint64 elstime = timerElapsed.elapsed();
    //  随机点击一次
    if( elstime%2 ==0 )
        mouseClick(_input_posx, _input_posy);

    // 太快了，休息下
    if(elstime < 7200){
        Sleep( static_cast<DWORD>(7200.0 - elstime));
        //休息完补点一次
        mouseClick(_input_posx, _input_posy);
    }

    emit doLog(QString::asprintf("间隔：%dms，点击次数：%d",
                                 timerElapsed.elapsed(), _count_mouse_click));

    _mouse.setStartPos(tempx, tempy);
}

void Watu::setMouseKicks(qint32 kick_times)
{
    _times = kick_times;
    emit doLog(QString::asprintf("设置鼠标点击次数：%d",_times) );
}

void Watu::setWatuKicks(qint32 times)
{
    _watu_times = times;
    emit doLog(QString::asprintf("设置挖土次数：%d",_watu_times) );
}

void Watu::on_timer_timeout()
{
    _rand_sec = _second*1000+rand()%77;
    _fTimer->stop();
    _fTimer->setInterval(_rand_sec); // 定是周期1000毫秒
    _fTimer->start();

    emit doLog(QString::asprintf("总次数:%d，下次时间：%dms", _total_times, _rand_sec));
    doManual(_input_posx, _input_posy);

    //判断是否自动结束
    if(_total_times >= _watu_times){
        stopWork();
    }

    _total_times++;

}

void Watu::stopWork()
{
    emit doLog(QString::asprintf("打工人下班了！次数:%d", _total_times));
    _total_times = 0;
    _fTimer->stop();
}

void Watu::doWork(qint32 sec)
{
    _second = sec;

    emit doLog("打工人上班了！");
    doManual(_input_posx, _input_posy);
    _total_times++;

    _fTimer->start();

}

