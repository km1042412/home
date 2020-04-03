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

#include "XVideoThread.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <XFilter.h>
using namespace std;
using namespace cv;

//һ����ƵԴ
static VideoCapture cap1;
static bool isexit = false;


bool XVideoThread::Seek(double pos)
{
	double count = cap1.get(CAP_PROP_FRAME_COUNT);
	int frame = pos *count;
	return Seek(frame);
}
//��ת��Ƶ 
///@para frame int ֡λ��
bool XVideoThread::Seek(int frame)
{
	mutex.lock();
	if (!cap1.isOpened())
	{
		mutex.unlock();
		return  false;
	}
	int re = cap1.set(CAP_PROP_POS_FRAMES, frame);
	mutex.unlock();
	return re;
}
//���ص�ǰ���ŵ�λ��
double XVideoThread::GetPos()
{
	double pos = 0;
	mutex.lock();
	if (!cap1.isOpened())
	{
		mutex.unlock();
		return pos;
	}
	double count = cap1.get(CAP_PROP_FRAME_COUNT);
	double cur = cap1.get(CAP_PROP_POS_FRAMES);
	if (count>0.001)
		pos = cur / count;
	mutex.unlock(); 
	return pos;
}
//��һ����ƵԴ�ļ�
bool XVideoThread::Open(const std::string file)
{
	cout <<"open :"<< file << endl;
	mutex.lock();
	bool re  = cap1.open(file);
	mutex.unlock();
	cout << re << endl;
	if (!re)
		return re;
	fps = cap1.get(CAP_PROP_FPS);
	if (fps <= 0) fps = 25;
	return true;
}
void XVideoThread::run()
{
	Mat mat1;
	//for (;;)
	while (!isexit)
	{
		mutex.lock();
		if (isexit)
		{
			mutex.unlock();
			break;
		}
		//�ж���Ƶ�Ƿ��
		if (!cap1.isOpened())
		{
			mutex.unlock();
			msleep(5);
			continue;
		}
		//��ȡһ֡��Ƶ�����벢��ɫת��
		if (!cap1.read(mat1) || mat1.empty())
		{
			mutex.unlock();
			msleep(5);
			continue;
		}
		//��ʾͼ��1
		ViewImage1(mat1);

		//ͨ��������������Ƶ
		Mat des = XFilter::Get()->Filter(mat1, Mat());

		//��ʾ���ɺ�ͼ��
		ViewDes(des);

		//sleep(40);
		int s = 0;
		s = 1000 / fps;
		msleep(s);

		mutex.unlock();
	}
}
XVideoThread::XVideoThread()
{
	start();
	
}


XVideoThread::~XVideoThread()
{
	
	mutex.lock();
	isexit = true;
	mutex.unlock();
	wait();
}
