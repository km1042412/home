
#include "xvideothread.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;
//video  capture
static VideoCapture cap1;
static bool isexit = false;


bool XVideoThread::Open(const std::string file)
{
    cout <<"open :"<< file << endl;
    mutex.lock();
    //open video file
    bool re  = cap1.open(file);
    mutex.unlock();
    cout << re << endl;
    return re;
}

void XVideoThread::run()
{
    Mat mat1;
    for (;;)
    {
        mutex.lock();
        if (isexit)
        {
            mutex.unlock();
            break;
        }
        // open ok ?
        if (!cap1.isOpened())
        {
            mutex.unlock();
            msleep(5);
            continue;
        }
        // read frame
        if (!cap1.read(mat1) || mat1.empty())
        {
            mutex.unlock();
            msleep(5);
            continue;
        }
        //dispay
        ViewImage1(mat1);
        msleep(40);
        mutex.unlock();
    }
}

XVideoThread::XVideoThread()
{
    //start the Thread
    start();
}


XVideoThread::~XVideoThread()
{
    mutex.lock();
    isexit = true;
    mutex.unlock();
}
