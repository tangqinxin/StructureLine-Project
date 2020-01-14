#ifndef IMGPROCESSFUN_H
#define IMGPROCESSFUN_H
#include<opencv2/opencv.hpp>
#include<opencv/highgui.h>
#include<opencv2/imgproc.hpp>
#include<opencv2/calib3d.hpp>


//  ********图像预处理*********//
// InputImg-输入图片-I
// m_AreaThreshold-面积阈值-I
// m_PixelThreshold-I 灰度阈值
// 功能滤除灰度不足的和面积不足的部分
cv::Mat FillterSmallArea(cv::Mat& InputImg, double m_AreaThreshold, double m_percent);

// **判断当前ContourSet内的点是否达到面积阈值**//
// 函数符写法
// 去除面积未达到阈值的部分
class AreaThresholdJudge {
private:
    double AreaThreshold;
public:
    AreaThresholdJudge(double x) :AreaThreshold(x) {}
    bool operator()(const std::vector<cv::Point>& ContourSet){ return cv::contourArea(ContourSet) < AreaThreshold;}//小于阈值返回true
};


#endif // IMGPROCESSFUN_H
