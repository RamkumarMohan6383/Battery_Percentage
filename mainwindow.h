#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <wiringPi.h>
#include <QThread>
#include <QDebug>
#include <wiringPiSPI.h>
#include <softPwm.h>
#include <Iir.h>
#include <mcp3004.h>
#include <ads1115.h>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    int readadc(int);

    void Call();

private:
    Ui::MainWindow *ui;

    QTimer * timer;
};

#endif // MAINWINDOW_H
