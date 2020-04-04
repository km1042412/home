
#include "xvideowidget.h"
#include <QPainter>
#include <opencv2/imgproc.hpp>

using namespace cv;
void XVideoWidget::SetImage(cv::Mat mat)
{
    if (img.isNull())
    {
        uchar *buf = new uchar[width()*height() * 3];
        img = QImage(buf, width(), height(), QImage::Format_RGB888);
    }
    Mat des;
    //ÉèÖÃÍ¼Ïñ´óÐ¡
    cv::resize(mat, des, Size(img.size().width(), img.size().height()));

    //ÉèÖÃÍ¼ÏñÑÕÉ«¸ñÊ½
    cv::cvtColor(des, des, COLOR_BGR2RGB);

    //¸´ÖÆÄÚ´æ¿Õ¼ä
    memcpy(img.bits(), des.data, des.cols*des.rows*des.elemSize());
    update();
}

XVideoWidget::XVideoWidget(QWidget *p) :QOpenGLWidget(p)
{

}

//update->paintEvent
void XVideoWidget::paintEvent(QPaintEvent*e)
{
    QPainter p;
    p.begin(this);
    //draw
    p.drawImage(QPoint(0, 0), img);
    p.end();
}

XVideoWidget::~XVideoWidget()
{
}
