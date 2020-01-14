#include"imgprocessfun.h"
#include<vector>

// *******************根据灰度自适应滤除小面积区域****************//
// 函数基本过程：
// 1 对原图InputImg高斯滤波
// 2 灰度阈值滤波，将图片转换为二值图
// 3 根据2中的二值图进行面积滤波，前3步的本质是得到一个mask
// 4 根据3中的面积滤波结果，得到最终的滤波后图片,每个像素和InputImg在亮的部分是相同的
cv::Mat FillterSmallArea(cv::Mat& InputImg, double m_AreaThreshold, double m_percent) {

    cv::Mat tempImg;
    InputImg.copyTo(tempImg);//新建一个矩阵
    if (tempImg.type() != CV_8UC1) {
        cv::cvtColor(tempImg, tempImg, cv::COLOR_BGR2GRAY);//如果输入是RGB图，则RGB转灰度图
    }

    // 1 高斯滤波
    cv::GaussianBlur(tempImg, tempImg, cv::Size(5, 5), 1.6, 1.6);//对原图进行高斯滤波得到I

    // 2 将图片转换为二值图
    double maxval;
    minMaxLoc(tempImg, NULL, &maxval, NULL, NULL);	// 找到最大灰度值
    double percent = m_percent;//分割比例
    cv::threshold(tempImg, tempImg, maxval*percent, 255, cv::THRESH_BINARY);//先进行二值化，便于进行后续的面积分割

    // 3 对tempImg进行面积滤波
    std::vector<std::vector<cv::Point>> ContourPtSet;//边界轮廓集
    cv::findContours(tempImg, ContourPtSet, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//仅提取外轮廓

    AreaThresholdJudge AreaJudge(m_AreaThreshold);//建立函数符
    ContourPtSet.erase(std::remove_if(ContourPtSet.begin(), ContourPtSet.end(), AreaJudge), ContourPtSet.end());//面积滤波去除

    cv::Mat mask = cv::Mat::zeros(tempImg.size(), tempImg.type());//创建掩膜
    cv::drawContours(mask, ContourPtSet, -1, cv::Scalar(255), CV_FILLED);//这个函数本身就进行了处理，它修改了tempImg矩阵

    // 4 根据滤波的情况对原图像素进行修改
    InputImg.copyTo(tempImg, mask);

    // 5 效果验证，展示掩膜与处理后的效果
    //cv::namedWindow("mask", CV_WINDOW_NORMAL);
    //cv::imshow("mask", mask);//此处为测试掩膜代码
    //cv::namedWindow("ImgAfterProcess",CV_WINDOW_NORMAL);
    //imshow("ImgAfterProcess", tempImg);

    return tempImg;
}
