#ifndef CAMERACALIB_H
#define CAMERACALIB_H

#include<string>
#include <opencv2\imgproc.hpp>
#include <opencv2\calib3d.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <QDebug>
#include <QMessageBox>
#include "matio.h"
#include"convertstring.h"

using namespace std;
using namespace cv;

// 将标定程序写成了一个函数
// 棋盘角点的排列m_width X m_height - I
// 棋盘每个格子的边长m_square_size - I
// 读取照片的信息txt文件strFileName - I
int CalibWithButton(std::string strFileName, int m_width, int m_height, float m_square_size);//从StrFileName里面去读取要标定的参数的文件名

#endif // CAMERACALIB_H
