#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "watu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initWatu();

signals:
    void do_watu(qint32 sec);
    void do_once(double x,double y);
    void stop_watu();
    void set_mouse_kicks(qint32 kick_times);
    void set_watu_kicks(qint32 times);

private slots:
    void on_pushButton_clicked();

    void on_pb_getoff_clicked();

    void on_bt_once_clicked();

    void on_bt_getpos_clicked();

    void onLog(const QString &str);

    void on_bt_mouse_kick_clicked();

    void on_bt_watu_kick_clicked();

private:
    Ui::MainWindow *ui{nullptr};
    QThread* _workerThread{nullptr};

    Watu* tool_watu{nullptr};
};

#endif // MAINWINDOW_H
