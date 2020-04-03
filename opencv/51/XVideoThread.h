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
#include <QThread>
#include "opencv2/core.hpp"
class XVideoThread:public QThread
{

	Q_OBJECT

public:
	int fps = 0;

	//单件模式 获取对象
	static XVideoThread* Get()
	{
		static XVideoThread vt;
		return &vt;
	}
	//打开一号视频源文件
	bool Open(const std::string file);

	//返回当前播放的位置
	double GetPos();

	//跳转视频 
	///@para frame int 帧位置
	bool Seek(int frame);
	bool Seek(double pos);

	~XVideoThread();

	//线程入口函数
	void run();

signals:
	//显示原视频1图像
	void ViewImage1(cv::Mat mat);

	//显示生成后图像
	void ViewDes(cv::Mat mat);
protected:
	QMutex mutex;
	XVideoThread();
};

