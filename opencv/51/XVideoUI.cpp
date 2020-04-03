/*******************************************************************************
**                                                                                           **
**                    Jiedi(China nanjing)Ltd.                                 **
**	      版权归夏曹俊所有，此代码只能作为学习参考                **                                                                            **
*******************************************************************************/

/*****************************FILE INFOMATION***********************************
**
** Project        : XVideoEdit
** Description : 视频编辑器
** Contact       : xiacaojun@qq.com
**	 QQ群	      ：559312905 (可以咨询问题)
** 微信公众号  : jiedi2007
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

	//原视频显示信号
	QObject::connect(XVideoThread::Get(),
		SIGNAL(ViewImage1(cv::Mat)),
		ui.src1,
		SLOT(SetImage(cv::Mat))
		);

	//输出视频显示信号
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
//打开视频源事件
void XVideoUI::Open()
{
	QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("请选择视频文件"));
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
//滑动条拖动
void XVideoUI::SetPos(int pos)
{
	XVideoThread::Get()->Seek((double)pos / 1000.);
}

//设置过滤器
void XVideoUI::Set()
{
	XFilter::Get()->Clear();
	//对比度和亮度
	if (ui.bright->value() > 0 || 
		ui.contrast->value()>1)
	{
		XFilter::Get()->Add(XTask{ XTASK_GAIN,
		{ (double)ui.bright->value(), ui.contrast->value() } 
		});
	}
}