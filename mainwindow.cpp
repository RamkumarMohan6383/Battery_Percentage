#include "mainwindow.h"
#include "ui_mainwindow.h"
#define ADC_BASE 100
#define SPI_CHAN 0
const double Vref = 5.0; // Set your reference voltage here
const double minVoltage = 3.5; // Set the minimum voltage of your battery
const double maxVoltage = 5.0; // Set the maximum voltage of your battery

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
     ui->label_3->setVisible(false);
    wiringPiSetup();
    mcp3004Setup (ADC_BASE, SPI_CHAN);
    ui->label_3->setAttribute(Qt::WA_TranslucentBackground);
    timer = new QTimer(this);
    connect(timer ,SIGNAL(timeout()) , this ,SLOT(Call())); // Main Reading Function
    timer->setTimerType(Qt::PreciseTimer);
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::readadc( int pin)
{
    unsigned char buff[] = {static_cast<char>(0x6 | ((pin & 0x7) >> 2)),
                            static_cast<char>((pin & 0x7) << 6),
                            static_cast<char>(0)};

    wiringPiSPIDataRW(SPI_CHAN, buff, 3);
    return ((buff[1] & 0xf) << 8) | buff[2];
}

void MainWindow::Call()
{
    int adcValue = readadc(7);
   /* QString adc=QString::number(adcValue,'f',2);
    double ADC=adc.toInt();*/
    double voltage = (adcValue / 4096.0) * Vref;
    double batteryPercentage = static_cast<double>(round(((voltage - minVoltage) / (maxVoltage - minVoltage)) * 100));
    int battery = ((voltage - minVoltage) / (maxVoltage - minVoltage)) * 100;
    qDebug() << "ADC : "<<adcValue<<" "<<"Battery Percentage: " << batteryPercentage << "%"<<" "<<"Battey : "<<QString::number(battery,'f',2);
    ui->label_3->setText(QString("%1%").arg(battery));
    ui->label->setText(QString::number(adcValue));
    if(batteryPercentage<=10)
    {
        ui->label_5->setStyleSheet("background-color:red;border:none;");
        ui->label_6->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_7->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_8->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_10->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_11->setStyleSheet("background-color:rgb(82, 144, 198);border:none;");
        ui->label_12->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_13->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_14->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_15->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
    }
    else if(batteryPercentage>10 && batteryPercentage<20)
    {
        ui->label_5->setStyleSheet("background-color:red;border:none;");
        ui->label_6->setStyleSheet("background-color: red;border:none;");
        ui->label_7->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_8->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_10->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_11->setStyleSheet("background-color:rgb(82, 144, 198);border:none;");
        ui->label_12->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_13->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_14->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_15->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
    }
    else if(batteryPercentage>20 && batteryPercentage<30)
    {
        ui->label_5->setStyleSheet("background-color:red;border:none;");
        ui->label_6->setStyleSheet("background-color: red;border:none;");
        ui->label_7->setStyleSheet("background-color: green;border:none;");
        ui->label_8->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_10->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_11->setStyleSheet("background-color:rgb(82, 144, 198);border:none;");
        ui->label_12->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_13->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_14->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_15->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
    }
    else if(batteryPercentage>30 && batteryPercentage<40)
    {
        ui->label_5->setStyleSheet("background-color: green;border:none;");
        ui->label_6->setStyleSheet("background-color: green;border:none;");
        ui->label_7->setStyleSheet("background-color: green;border:none;");
        ui->label_8->setStyleSheet("background-color: green;border:none;");
        ui->label_10->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_11->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_12->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_13->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_14->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_15->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
    }
    else if(batteryPercentage>40 && batteryPercentage<50)
    {
        ui->label_5->setStyleSheet("background-color: green;border:none;");
        ui->label_6->setStyleSheet("background-color: green;border:none;");
        ui->label_7->setStyleSheet("background-color: green;border:none;");
        ui->label_8->setStyleSheet("background-color: green;border:none;");
        ui->label_10->setStyleSheet("background-color: green;border:none;");
        ui->label_11->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_12->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_13->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_14->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_15->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
    }
    else if(batteryPercentage>50 && batteryPercentage<60)
    {
        ui->label_5->setStyleSheet("background-color: green;border:none;");
        ui->label_6->setStyleSheet("background-color: green;border:none;");
        ui->label_7->setStyleSheet("background-color: green;border:none;");
        ui->label_8->setStyleSheet("background-color: green;border:none;");
        ui->label_10->setStyleSheet("background-color: green;border:none;");
        ui->label_11->setStyleSheet("background-color: green;border:none;");
        ui->label_12->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_13->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_14->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_15->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
    }
    else if(batteryPercentage>60 && batteryPercentage<70)
    {
        ui->label_5->setStyleSheet("background-color: green;border:none;");
        ui->label_6->setStyleSheet("background-color: green;border:none;");
        ui->label_7->setStyleSheet("background-color: green;border:none;");
        ui->label_8->setStyleSheet("background-color: green;border:none;");
        ui->label_10->setStyleSheet("background-color: green;border:none;");
        ui->label_11->setStyleSheet("background-color: green;border:none;");
        ui->label_12->setStyleSheet("background-color: green;border:none;");
        ui->label_13->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_14->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_15->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
    }
    else if(batteryPercentage>70 && batteryPercentage<80)
    {
        ui->label_5->setStyleSheet("background-color: green;border:none;");
        ui->label_6->setStyleSheet("background-color: green;border:none;");
        ui->label_7->setStyleSheet("background-color: green;border:none;");
        ui->label_8->setStyleSheet("background-color: green;border:none;");
        ui->label_10->setStyleSheet("background-color: green;border:none;");
        ui->label_11->setStyleSheet("background-color: green;border:none;");
        ui->label_12->setStyleSheet("background-color: green;border:none;");
        ui->label_13->setStyleSheet("background-color: green;border:none;");
        ui->label_14->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
        ui->label_15->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
    }
    else if(batteryPercentage>80 && batteryPercentage<90)
    {
        ui->label_5->setStyleSheet("background-color: green;border:none;");
        ui->label_6->setStyleSheet("background-color: green;border:none;");
        ui->label_7->setStyleSheet("background-color: green;border:none;");
        ui->label_8->setStyleSheet("background-color: green;border:none;");
        ui->label_10->setStyleSheet("background-color: green;border:none;");
        ui->label_11->setStyleSheet("background-color: green;border:none;");
        ui->label_12->setStyleSheet("background-color: green;border:none;");
        ui->label_13->setStyleSheet("background-color: green;border:none;");
        ui->label_14->setStyleSheet("background-color: green;border:none;");
        ui->label_15->setStyleSheet("background-color: rgb(82, 144, 198);border:none;");
    }
    else if(batteryPercentage>90 && batteryPercentage<100)
    {
        ui->label_5->setStyleSheet("background-color: green;border:none;");
        ui->label_6->setStyleSheet("background-color: green;border:none;");
        ui->label_7->setStyleSheet("background-color: green;border:none;");
        ui->label_8->setStyleSheet("background-color: green;border:none;");
        ui->label_10->setStyleSheet("background-color: green;border:none;");
        ui->label_11->setStyleSheet("background-color: green;border:none;");
        ui->label_12->setStyleSheet("background-color: green;border:none;");
        ui->label_13->setStyleSheet("background-color: green;border:none;");
        ui->label_14->setStyleSheet("background-color: green;border:none;");
        ui->label_15->setStyleSheet("background-color: green;border:none;");
    }

}
