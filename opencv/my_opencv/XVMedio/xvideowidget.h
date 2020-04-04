#ifndef XVIDEOWIDGET_H
#define XVIDEOWIDGET_H

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
    //is slots
    void SetImage(cv::Mat mat);
protected:
    QImage img;
};


#endif // XVIDEOWIDGET_H
