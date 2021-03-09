#ifndef WATU_H
#define WATU_H

#include <QMainWindow>
#include <QObject>
#include <QThread>
#include <QTime>
#include <QTimer>
#include "mouse.h"

class Watu : public QObject
{
    Q_OBJECT
public:
    explicit Watu(qint32 sec, double posx,double posy, qint32 t, qint32 times, QObject *parent = nullptr);
    void mouseClick(double posx,double posy);

public slots:
    void doWork(qint32 sec);
    void doManual(double x,double y);
    void setMouseKicks(qint32 kick_times);
    void setWatuKicks(qint32 times);
    void stopWork();
    void on_timer_timeout();

signals:
    void doLog(const QString &result);

private:
    void gan();

private:
    qint32 _second;
    qint32 _rand_sec;
    double _input_posx;
    double _input_posy;
    qint32 _times;
    qint32 _watu_times;
    qint32 _total_times;
    qint32 _count_mouse_click;

    Mouse _mouse;
    QTimer* _fTimer{nullptr}; //定时器
    QTime fTimeCounter; // 计时器
};

#endif // WATU_H
