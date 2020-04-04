
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <string>
#include <QMessageBox>
#include "xvideothread.h"
#include "iostream"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    //register for slot
    qRegisterMetaType<cv::Mat>("cv::Mat");

    //single send for XVideoThread::Get ,send kind of ViewImage, receive ui->src1 of SLOT(SetImage)
    QObject::connect(XVideoThread::Get(),
        SIGNAL(ViewImage1(cv::Mat)),
        ui->src1,
        SLOT(SetImage(cv::Mat))
        );
}

void MainWindow::Open()
{
    QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("open the file"));
    if (name.isEmpty())return;
    string file = name.toLocal8Bit().data();
    if (!XVideoThread::Get()->Open(file))
    {
        QMessageBox::information(this, "error", name+" open failed!");
        return;
    }

}


MainWindow::~MainWindow()
{
    delete ui;
}


