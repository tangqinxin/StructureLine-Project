#include"convertstring.h"
std::wstring StringToWString( const std::string &s)
{
    std::wstring wsTmp(s.begin(), s.end());
    return wsTmp;
}

bool MakeMyDirectory(const std::string &strFilePathDirctory)
{
    std::wstring wDirectoryName = StringToWString(strFilePathDirctory);
    LPCTSTR lpwdir = wDirectoryName.c_str();
    return CreateDirectory(lpwdir, NULL);
}

void ReadFileNameFromTxt(std::string FileName,std::vector<std::string> &DataArray)
{
   std::fstream fin;
   fin.open(FileName);
   std::string PhotoName;
    while(std::getline(fin,PhotoName)){
        DataArray.push_back(PhotoName);//读取照片信息加入到队列尾部
    }
}
