/*******************************************************************************
**                                                                                           **
**                    Jiedi(China nanjing)Ltd.                                 **
**	      ��Ȩ���Ĳܿ����У��˴���ֻ����Ϊѧϰ�ο�                **                                                                            **
*******************************************************************************/

/*****************************FILE INFOMATION***********************************
**
** Project        : XVideoEdit
** Description : ��Ƶ�༭��
** Contact       : xiacaojun@qq.com
**	 QQȺ	      ��559312905 (������ѯ����)
** ΢�Ź��ں�  : jiedi2007
**
*******************************************************************************/

#include "XVideoUI.h"
#include <QFileDialog>
#include <string>
#include <QMessageBox>
#include "XVideoThread.h"
#include "XFilter.h"
using namespace std;
static bool pressSlider = false;

XVideoUI::XVideoUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	qRegisterMetaType<cv::Mat>("cv::Mat");

	//ԭ��Ƶ��ʾ�ź�
	QObject::connect(XVideoThread::Get(),
		SIGNAL(ViewImage1(cv::Mat)),
		ui.src1,
		SLOT(SetImage(cv::Mat))
		);

	//�����Ƶ��ʾ�ź�
	QObject::connect(XVideoThread::Get(),
		SIGNAL(ViewDes(cv::Mat)),
		ui.des,
		SLOT(SetImage(cv::Mat))
		);

	startTimer(40);
}
void XVideoUI::timerEvent(QTimerEvent *e)
{
	if (pressSlider)return;
	double pos = XVideoThread::Get()->GetPos();
	ui.playSlider->setValue(pos*1000);

}
//����ƵԴ�¼�
void XVideoUI::Open()
{
	QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("��ѡ����Ƶ�ļ�"));
	if (name.isEmpty())return;
	string file = name.toLocal8Bit().data();
	if (!XVideoThread::Get()->Open(file))
	{
		QMessageBox::information(this, "error", name+" open failed!");
		return;
	}
		
	//QMessageBox::information(this, "", name);
}

void XVideoUI::SliderPress()
{
	pressSlider = true;
}

void XVideoUI::SliderRelease()
{
	pressSlider = false;
}
//�������϶�
void XVideoUI::SetPos(int pos)
{
	XVideoThread::Get()->Seek((double)pos / 1000.);
}

//���ù�����
void XVideoUI::Set()
{
	XFilter::Get()->Clear();
	//�ԱȶȺ�����
	if (ui.bright->value() > 0 || 
		ui.contrast->value()>1)
	{
		XFilter::Get()->Add(XTask{ XTASK_GAIN,
		{ (double)ui.bright->value(), ui.contrast->value() } 
		});
	}
}