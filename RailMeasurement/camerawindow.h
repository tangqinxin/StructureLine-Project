#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H
#include "GalaxyIncludes.h"
#include <QDebug>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "mat2qtformatmethod.h"
#include <QPixmap>
#include <QImage>
#include <QLabel>
#include <QMessageBox>
#include <string>
#include "cgxbitmap.h"
#include "convertstring.h"
#include <time.h>
#include <QPainter>
#include "drawwidget.h"
#include "cameracalib.h"
#include "laserplane.h"
#include "matio.h"
#include "pointstocamera.h"
#include "pointstoworld.h"
#include "imgprofun.h"
#include <fstream>

struct CameraWindowGeoParams{
    int WidgetWidth;
    int WidgetHeight;
    int LabelWidth;
    int LabelHeight;
    int LineeditWidth;
    int LineeditHeight;
    int ButtonWidth;
    int ButtonHeight;
};
struct MyUserParam{
    cv::Mat CurImgMat;
    QLabel* LabelShowImgPtr;
};



#include <QWidget>

namespace Ui {
class CameraWindow;
struct CameraWindowGeoParams;
//class CSampleCaptureEventHandler;
}

class CameraWindow : public QWidget
{
    Q_OBJECT

private:
    //回调采集事件类
    class CSampleCaptureEventHandler : public ICaptureEventHandler
     {
    public:

       void DoOnImageCaptured(CImageDataPointer& objImageDataPointer, void* pUserParam)
       {

           if (objImageDataPointer->GetStatus() == GX_FRAME_STATUS_SUCCESS)
           {                  
               CameraWindow* CamUiPtr=(CameraWindow*)pUserParam;
               //以下为连续采集部分的显示
               void* pRaw8Buffer = NULL;
               pRaw8Buffer = objImageDataPointer->ConvertToRaw8(GX_BIT_0_7);
               std::memcpy(CamUiPtr->CurImgMat.data, pRaw8Buffer, (objImageDataPointer->GetHeight())*(objImageDataPointer->GetWidth()));

               //判定是否去除畸变
               if(CamUiPtr->m_bUnDistort==true){

               }

               //调用自定义绘图函数进行绘制实时采集图像
               CamUiPtr->ShowCurImgInLabel(CamUiPtr->LabelShowCurImg,CamUiPtr->CurImgMat);

               //重新调整图像大小以适应窗口,并且此处进行了数据更新，这样才能使用update()函数
               //使用drawimage进行绘图的代码
               //先得到一张完整的qimage,然后根据窗口进行修改qimage的大小，最后再进行更新。更行时需要对窗口进行提升，使用自定义窗口。
               //使用update进行画图有更好的连续性效果
               //CamUiPtr->CurImgQimg=CV2QTFORMAT::cvMatToQImage(CamUiPtr->CurImgMat);
               //CamUiPtr->pDrawWidget->ReSizeImg(CamUiPtr->CurImgQimg);
               //CamUiPtr->pDrawWidget->update();

               //单帧采集
               if(CamUiPtr->m_bCheckSaveBmp==true){
                   MakeMyDirectory(CamUiPtr->strFilePath);//创建文件夹
                   std::string PathAndName=CamUiPtr->strFilePath+"\\"+CamUiPtr->strFileName;
                   CamUiPtr->m_pBitmap->SaveBmp(objImageDataPointer,PathAndName);//保存单帧图像
                   CamUiPtr->m_bCheckSaveBmp=false;

                   //通过读取的方式画出单帧图像
                   QString LoadImgName=QString::fromStdString(PathAndName);
                   CamUiPtr->SingleImgPixMap.load(LoadImgName,nullptr,Qt::AutoColor);
                   CamUiPtr->LabelSingleImg->setPixmap(CamUiPtr->SingleImgPixMap);

                   //仅仅在激发采集的时候是有意义的
                   CamUiPtr->TimeTakePhoto=clock();
                   qDebug()<<(double)(CamUiPtr->TimeTakePhoto-CamUiPtr->TimePushButton);
                   CamUiPtr->TimePushButton=0;
                   CamUiPtr->TimeTakePhoto=0;
               }

               //是否连续进行测量
               if(CamUiPtr->m_bMeasureOk==true){
                    CamUiPtr->SingleFrameMeasureFunction();
               }
            }
       }
     };


public:
    explicit CameraWindow(QWidget *parent = 0);
    ~CameraWindow();

    void CamWinParamsSet(int _WidgetW, int _WidgetH, int _SmallPartW, int _SmallPartH);
    void MakeConnection(void* MainWinPtr);//建立窗口间的联系，这个函数是用于让主窗口控制子窗口的
    void SendResSignalToMainWin();
    void SingleFrameMeasureFunction();//用于在单帧采集中使用，连续采集也可调用该函数，该函数会根据CurImgMat改变窗口的measure_y变量的值

signals:
    void SignalInSub1_ShowMainWin();
    void Signal_LUResToMainWin(vector<float>& m_resx,vector<float>& m_resy);

private slots:
    void on_pushButton_ListDevice_clicked();

    void on_pushButton_OpenCam_clicked();

    void on_pushButton_CloseCam_clicked();

    void on_pushButton_StartGrab_clicked();

    void on_pushButton_StopGrab_clicked();

    void on_pushButton_GetImg_clicked();
    
    void on_pushButton_ParamsSet_clicked();
    
    void on_pushButton_CalibCam_clicked();

    void on_pushButton_ReadCalibParms_clicked();

    void on_pushButton_ClearCalibParms_clicked();

    void on_pushButton_PlaneFit_clicked();

    void on_pushButton_SetBaseLine_clicked();

    void on_pushButton_ShowCurParams_clicked();
    
    void on_pushButton_MeasureSingleF_clicked();

    void on_pushButton_MeasureContinuous_clicked();

    void on_pushButton_ShiftToMainWindow_clicked();

    void on_pushButton_TestGetSingleImg_Take_clicked();

    void on_pushButton_OutputBaseLine_clicked();

    void on_pushButton_ReadBaseLineInfo_clicked();

private:
    Ui::CameraWindow *ui;
    CameraWindowGeoParams CwParas;
    //相机库
    GxIAPICPP::gxdeviceinfo_vector vectorDeviceInfo;//枚举设备结果
    CGXDevicePointer ObjDevicePtr;//当前界面操作的相机指针
    CGXStreamPointer ObjStreamPtr;//流采集指针
    CGXFeatureControlPointer ObjFeatureControlPtr;//远端设备控制器
    ICaptureEventHandler* pCaptureEventHandler;//注册回调事件指针

    //Opencv参数
    cv::Mat CurImgMat;//实时窗口的Mat
    void AllocateRoomForMatCurImgPtr();//为实时采集窗口指针分配空间

    //这里使用string，然后使用自定义函数进行转换，放弃了MFC的CString类
    std::string strFilePath;//保存路径
    std::string strFileName;//文件名称

    // 保存图像为BMP格式
    CGXBitmap*  m_pBitmap;// 保存图像指针
    bool m_bCheckSaveBmp;// 是否保存图片
    int ImgWidth;//记录图片的宽度
    int ImgHeight;//记录图片的高度

    //展示窗口指针
    QLabel* LabelShowCurImg;
    QLabel* LabelSingleImg;
    QPixmap SingleImgPixMap;
    QPixmap CurImgPixMap;//画一个当前的图
    DrawWidget* pDrawWidget;//提升窗口指针，使用drawqimage显示实时图像

    //使用Painter事件来绘图drawQimg
    QImage CurImgQimg;
    QSize LableSize;

    //计时函数
    clock_t TimePushButton;
    clock_t TimeTakePhoto;
    double DelayTime;//用于后期设定延时时间

    //窗口几何参数设计
    void GeoSetWidgetCurInput(int _x, int _y, int _width, int _height);//设置实时采集框几何尺寸
    void GeoSetWidgetSampleImg(int _x, int _y, int _width, int _height);//设置单帧采集几何尺寸
    void GeoSetFrameParamsSet(int _x, int _y, int _width, int _height, int _dx, int _dy);//设置参数框几何尺寸
    void GeoSetFrameCamOperate();//设置操作框几何尺寸
    void GeoSetFrameWinInfo();//设置抬头框几何尺寸

    //绘制实时采集图像成比例
    void ShowCurImgInLabel(QLabel* ptrLabelToShow,cv::Mat& CVMat);

    //标定相机参数
    cv::Mat CameraIntrinsic;//相机内参
    cv::Mat DisCoeffs;//相机畸变系数
    int CalibPhotoNums;//标定图片数量
    bool m_bUnDistort;//根据是否已经有畸变参数判定是否需要去畸变
    //激光平面
    LaserPlane LPlane;
    bool m_bSetBaseLine;//是否将当前图设置为基准
    bool m_bMeasureOk;//是否开始测量
    vector<float> MeasureResult_x;//测量结果参数传递
    vector<float> MeasureResult_y;
};

#endif // CAMERAWINDOW_H
