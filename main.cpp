#include "mainwindow.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    //支持高分屏
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // 防止判断为机器作弊
    QTime temp = QTime::currentTime();
    qsrand(static_cast<unsigned int>(QTime(0, 0, 0).secsTo(temp)));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
