#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mouse.h"
#include "watu.h"
#include "windowstools.h"

#include <Windows.h>
#include <QDateTime>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    _workerThread = new QThread();

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete tool_watu;
    _workerThread->quit();
    _workerThread->wait();
    delete _workerThread;
    delete ui;
}

void MainWindow::onLog(const QString &str)
{
    QString when = QDateTime::currentDateTime().toString("hh:mm:ss ");
    ui->tedit_logger->append(when.append(str));
}

void MainWindow::initWatu()
{
    if(tool_watu!=nullptr)
    {
        onLog("挖土已经启动");
        return;
    }

    QString seconds = ui->m_watu_second->text();
    QString posx = ui->line_posx->text();
    QString posy = ui->line_posy->text();
    QString times = ui->ed_times->text();
    QString watu_times = ui->m_watu_times->text();

    tool_watu= new Watu(seconds.toInt(), posx.toDouble(), posy.toDouble(), times.toInt(), watu_times.toInt(), nullptr);
    tool_watu->moveToThread(_workerThread);
    connect(_workerThread, &QThread::finished, tool_watu, &QObject::deleteLater);
    connect(this, &MainWindow::do_once, tool_watu, &Watu::doManual);
    connect(this, &MainWindow::do_watu, tool_watu, &Watu::doWork);
    connect(this, &MainWindow::set_mouse_kicks, tool_watu, &Watu::setMouseKicks);
    connect(this, &MainWindow::set_watu_kicks, tool_watu, &Watu::setWatuKicks);
    connect(this, &MainWindow::stop_watu, tool_watu, &Watu::stopWork);
    connect(tool_watu, &Watu::doLog, this, &MainWindow::onLog);

    _workerThread->start();
}

//   自动定时挖土
void MainWindow::on_pushButton_clicked()
{
    initWatu();
    qint32 sec = ui->m_watu_second->text().toInt();
    emit do_watu(sec);
}

//   手动单次点击
void MainWindow::on_bt_once_clicked()
{
    initWatu();
    QString posx = ui->line_posx->text();
    QString posy = ui->line_posy->text();
    emit do_once(posx.toDouble(), posy.toDouble());
}

void MainWindow::on_bt_getpos_clicked()
{
    WindowsTools w;

    QString title = ui->ed_title->text();
    QString yyswinclass = ui->ed_class->text();
    w.init(title, yyswinclass);
    double x = {0};
    double y = {0};
    w.getMousePos(x, y);
    ui->line_posx->setText(QString::asprintf("%d",x));
    ui->line_posy->setText(QString::asprintf("%d",y));
}

void MainWindow::on_pb_getoff_clicked()
{
    emit stop_watu();
}

void MainWindow::on_bt_mouse_kick_clicked()
{
    QString kick_times = ui->ed_times->text();
    emit set_mouse_kicks(kick_times.toInt());
}

void MainWindow::on_bt_watu_kick_clicked()
{
    QString times = ui->m_watu_times->text();
    emit set_watu_kicks(times.toInt());
}
