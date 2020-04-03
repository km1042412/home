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
#include <QOpenGLWidget>
#include <opencv2/core.hpp>
class XVideoWidget :public QOpenGLWidget
{
	Q_OBJECT

public:
	XVideoWidget(QWidget *p);
	void paintEvent(QPaintEvent*e);
	virtual ~XVideoWidget();
public slots:
	//界面刷新
	void SetImage(cv::Mat mat);
protected:
	QImage img;
};

