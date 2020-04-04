#ifndef XVIDEOTHREAD_H
#define XVIDEOTHREAD_H


#include <QThread>
#include <QtCore/qmutex.h>
#include "opencv2/core.hpp"

class XVideoThread:public QThread
{
    Q_OBJECT

public:


    static XVideoThread* Get()
    {
        static XVideoThread vt;
        return &vt;
    }
    bool Open(const std::string file);
    ~XVideoThread();

    void run();

signals:
    void ViewImage1(cv::Mat mat);
protected:
    QMutex mutex;
    XVideoThread();
};


#endif // XVIDEOTHREAD_H
