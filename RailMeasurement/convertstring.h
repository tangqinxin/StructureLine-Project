#ifndef CONVERTSTRING_H
#define CONVERTSTRING_H
// 该文件用于将String转换为WString，目的是为了能顺利调用大恒sdk来保存bmp图像
#include<vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include<string>
#include<Windows.h>//此处必须添加windows.h，否则无法识别CreateDirectory函数和LPCTSTR

//将string转换为wstring类，便于利用大恒接口写文件
std::wstring StringToWString( const std::string &s);

//创建文件夹，方便保存文件，
bool MakeMyDirectory(const std::string& strFilePathDirctory);

//从FileName文件中读取获得图像的地址DataArray
void ReadFileNameFromTxt(std::string FileName,std::vector<std::string>& DataArray);

#endif // CONVERTSTRING_H
