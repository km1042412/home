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
#pragma once

#include <QtWidgets/QWidget>
#include "ui_XVideoUI.h"

class XVideoUI : public QWidget
{
    Q_OBJECT

public:
    XVideoUI(QWidget *parent = Q_NULLPTR);
	void timerEvent(QTimerEvent *e);
public slots:
	//打开视频源事件
	void Open();
	void SliderPress();
	void SliderRelease();
	//滑动条拖动
	void SetPos(int);
	//设置过滤器
	void Set();

	//导出视频
	void Export();

	//导出结束
	void ExportEnd();

private:
    Ui::XVideoUIClass ui;
};
