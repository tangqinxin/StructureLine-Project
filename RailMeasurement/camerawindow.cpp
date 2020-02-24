#include "camerawindow.h"
#include "ui_camerawindow.h"
#include <QWidget>
#include <QString>
#include "mainwindow.h"

//窗口构造函数
CameraWindow::CameraWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraWindow)
  //自定义参数的初始化
  ,ObjDevicePtr(NULL)
  ,ObjStreamPtr(NULL)
  ,ObjFeatureControlPtr(NULL)
  ,pCaptureEventHandler(NULL)
  ,m_pBitmap(NULL)
  ,m_bCheckSaveBmp(false)
  ,ImgWidth(0)
  ,ImgHeight(0)
  ,TimePushButton(0)
  ,TimeTakePhoto(0)
  ,CalibPhotoNums(0)
  ,m_bSetBaseLine(false)
  ,m_bMeasureOk(false)
  ,m_bUnDistort(false)
{
    ui->setupUi(this);
    LabelShowCurImg=ui->label_CurInput;
    LabelSingleImg=ui->label_SampleImg;//这两个指针的赋值务必放在setupUi的后面，否则前面没有对应的指针，就是空的
    LabelSingleImg->setScaledContents(true);//设置比例

    //下面为实时采集图部分
    pDrawWidget=ui->widget_CurInput;//用于绘制实时图的时候使用，使用drawimage来绘图
    pDrawWidget->SetSize();
    //LabelShowCurImg->hide();//使用label进行显示实时图时，将这段注释取消。

    ui->lineEdit_ExplosureTime->setText("20000");//设置默认曝光参数
    ui->lineEdit_FpsSet->setText("36");//设置默认帧率
    ui->lineEdit_FilePath->setText(".\\data");//设置默认保存路径，在当前目录下建立一个data文件夹
    ui->lineEdit_CamIndex->setText("1");//相机序号默认为1
    ui->lineEdit_FileName->setText("test.bmp");

    //标定部分
    ui->lineEdit_CalibrateData->setText("calibdata.txt");//标定数据出处
    ui->lineEdit_SquareSIze->setText("3");//设定标定板方格初始值为3mm
    ui->lineEdit_BoardWidth->setText("11");//设定标定板宽有11个角点
    ui->lineEdit_BoardHeight->setText("8");//设定标定板高有8个角点
    ui->lineEdit_CalibLaserPlaneData->setText("laserplanedata.txt");
    this->CameraIntrinsic=Mat::zeros(3,3,CV_32FC1);//相机内参初始化
    this->DisCoeffs=Mat::zeros(1,5,CV_32FC1);//相机畸变系数初始化
    this->LPlane.CleanCoeffs();//激光平面参数清空

    this->CamWinParamsSet(800,800,100,30);//设置界面窗口与部件宽高
    this->GeoSetWidgetCurInput(100,100,800,800);//设置实时窗口参数
    this->GeoSetWidgetSampleImg(1000,100,800,800);//设置采集窗口参数
    this->GeoSetFrameParamsSet(100,910,500,100,10,10);//设置参数框几何参数

    //初始化显示数据，用作测试
    /*
    std::ifstream inputx,inputy;
    inputx.open("x.txt");
    inputy.open("y.txt");
    for(int i=1;i<1050;i++){
        float inx,iny;
        inputx>>inx;
        inputy>>iny;
        MeasureResult_x.push_back(inx);
        MeasureResult_y.push_back(iny);
        if(i%100==0){
            qDebug()<<inx<<iny;
        }
    }
    */
}

CameraWindow::~CameraWindow()
{
    delete ui;
}


/* **************************************图形界面几何设计***********************************************/

//设置界面小部件的宽高参数
void CameraWindow::CamWinParamsSet(int _WidgetW,int _WidgetH,int _SmallPartW,int _SmallPartH)
{
    CwParas.WidgetWidth=_WidgetW;
    CwParas.WidgetHeight=_WidgetH;
    CwParas.LabelWidth=_SmallPartW;
    CwParas.LabelHeight=_SmallPartH;
    CwParas.LineeditWidth=_SmallPartW;
    CwParas.LineeditHeight=_SmallPartH;
    CwParas.ButtonWidth=_SmallPartW;
    CwParas.ButtonHeight=_SmallPartH;
}

//设置实时采集widget
void CameraWindow::GeoSetWidgetCurInput(int _x,int _y, int _width,int _height)
{

    //函数作用：设置相机窗口中的实时采集图像框的几何尺寸
    //输入：widget的起始位置x，y，以及widget的大小
    //设置对象：包含外框widget部分以及label部分的
    //设置变量：widget和label的位置和大小
    //设置要求：label和widget大小相同，起始位置也相同

    //设置widget
    ui->widget_CurInput->move(_x,_y);
    ui->widget_CurInput->resize(_width,_height);

    //设置label
    ui->label_CurInput->move(0,0);
    ui->label_CurInput->resize(_width,_height);
}

//设置单帧采集widget
void CameraWindow::GeoSetWidgetSampleImg(int _x,int _y, int _width,int _height)
{

    //函数作用：设置相机窗口中的单帧采集图像框的几何尺寸
    //输入：widget的起始位置x，y，以及widget的大小
    //设置对象：包含外框widget部分以及label部分的
    //设置变量：widget和label的位置和大小
    //设置要求：label和widget大小相同，起始位置也相同

    //设置widget
    ui->widget_SampleImg->move(_x,_y);
    ui->widget_SampleImg->resize(_width,_height);

    //设置label
    ui->label_SampleImg->move(0,0);
    ui->label_SampleImg->resize(_width,_height);
}

//设置参数框
void CameraWindow::GeoSetFrameParamsSet(int _x,int _y,int _width, int _height,int _dx,int _dy)
{
/*
    ui->frame_ParmsSet->move(_x,_y);
    ui->frame_ParmsSet->resize(_width,_height);

    ui->label_ExplosureTime->move(_dx,_dy);//框内第一行，第一列
    ui->label_ExplosureTime->resize(CwParas.LabelWidth,CwParas.LabelHeight);
    ui->label_FpsSet->move(_dx,2*_dy+CwParas.LabelHeight);//框内第二行，第一列
    ui->label_FpsSet->resize(CwParas.LabelWidth,CwParas.LabelHeight);

    ui->lineEdit_ExplosureTime->move(2*_dx+CwParas.LabelWidth,_dy);//框内第一行，第二列
    ui->lineEdit_ExplosureTime->resize(CwParas.LineeditWidth,CwParas.LineeditHeight);
    ui->lineEdit_FpsSet->move(2*_dx+CwParas.LabelWidth,2*_dy+CwParas.LabelHeight);//框内第二行，第二列
    ui->lineEdit_FpsSet->resize(CwParas.LineeditWidth,CwParas.LineeditHeight);

    ui->pushButton_ParamsSet->move(3*_dx+CwParas.LabelWidth+CwParas.LabelWidth,2*_dy+CwParas.LabelHeight);//框内第二行第三列
    ui->pushButton_ParamsSet->resize(CwParas.LineeditWidth,CwParas.LineeditHeight);
*/
}

//设置操作框
void CameraWindow::GeoSetFrameCamOperate()
{

}

//设置抬头框
void CameraWindow::GeoSetFrameWinInfo()
{

}




/* **************************************相机操作框内的函数设计***********************************************/

//枚举设备按钮
void CameraWindow::on_pushButton_ListDevice_clicked()
{
    try{
    IGXFactory::GetInstance().Init();//初始化
    IGXFactory::GetInstance().UpdateDeviceList(1000, this->vectorDeviceInfo);//更新设备列表
    ui->lineEdit_NumOfCam->setText(QString::number(vectorDeviceInfo.size()));//更新现有设备数，并在窗口显示
    }
    catch (CGalaxyException)
    {
     QMessageBox::information(this,"提示","枚举相机按钮报错，请重启程序后，重新枚举设备");
    }
}
//打开相机按钮
void CameraWindow::on_pushButton_OpenCam_clicked()
{
    try{
    int IndexOfCam=(ui->lineEdit_CamIndex->text()).toInt();//得到打开相机的序号
    if(vectorDeviceInfo.size()>0&&vectorDeviceInfo.size()>=IndexOfCam&&IndexOfCam>=1){
        GxIAPICPP::gxstring strSN = vectorDeviceInfo[IndexOfCam-1].GetSN();
        ObjDevicePtr = IGXFactory::GetInstance().OpenDeviceBySN(strSN, GX_ACCESS_EXCLUSIVE);
        ObjStreamPtr = ObjDevicePtr->OpenStream(IndexOfCam-1);//连接流采集通道
        ObjFeatureControlPtr = ObjDevicePtr->GetRemoteFeatureControl();//获取远端设备控制器，可用于调节相机参数
        AllocateRoomForMatCurImgPtr();//为Mat矩阵开辟空间

		//判断图像对象是否为空
		if (m_pBitmap != NULL)
		{
			delete m_pBitmap;
			m_pBitmap = NULL;
		}
		//为画图对象分配内存
		m_pBitmap = new CGXBitmap(ObjDevicePtr);//为单帧采集开辟空间
    }
    }
    catch (CGalaxyException)
    {
     QMessageBox::information(this,"提示","打开相机按钮报错，请先枚举设备，再打开相机");
    }
}

//关闭相机按钮，使用了try来防止报错
void CameraWindow::on_pushButton_CloseCam_clicked()
{
    try{
    ObjStreamPtr->Close();
    ObjDevicePtr->Close();//关闭相机，释放资源

		if (m_pBitmap != NULL)//释放图片内存空间
		{
		delete m_pBitmap;
		m_pBitmap = NULL;
		}
	}
    catch (CGalaxyException)
    {
     QMessageBox::information(this,"提示","关闭按钮报错，请先枚举设备，再打开相机");
    }
}
//开始采集按钮
void CameraWindow::on_pushButton_StartGrab_clicked()
{
    try{
    //进行注册回调采集函数，后期关闭相机自动释放资源
    pCaptureEventHandler = new CSampleCaptureEventHandler();
    ObjStreamPtr->RegisterCaptureCallback(pCaptureEventHandler,this);//将整个界面作为参数进行传递
    //开启流通道采集
    ObjStreamPtr->StartGrab();

    //给设备发送开采命令
    ObjFeatureControlPtr->GetCommandFeature("AcquisitionStart")->Execute();
    }
    catch (CGalaxyException)
    {
     QMessageBox::information(this,"提示","开始采集按钮报错，请先枚举设备，再打开相机");
    }
}

//停止采集按钮,使用了try来防止报错
void CameraWindow::on_pushButton_StopGrab_clicked()
{
    try{
    ObjFeatureControlPtr->GetCommandFeature("AcquisitionStop")->Execute();
    ObjStreamPtr->StopGrab();
    //注销采集回调
    ObjStreamPtr->UnregisterCaptureCallback();
    }
    catch (CGalaxyException)
    {
     QMessageBox::information(this,"提示","停止采集按钮报错，请先枚举设备，再打开相机");
    }
}
//单帧采集按钮
void CameraWindow::on_pushButton_GetImg_clicked()
{
    m_bCheckSaveBmp=true;
    TimePushButton=clock();//开始计时

    /* 这个功能可以另外扩展为一个触发功能
    CImageDataPointer ImageDataPtr;//定义一个数据指针
    ImageDataPtr = ObjStreamPtr->GetImage(500);//采集单帧数据，超时时间使用500ms，用户可以自行设定

    if (ImageDataPtr->GetStatus() == GX_FRAME_STATUS_SUCCESS)
    {
    //采图成功而且是完整帧，将数据保存为bmp格式，注意保存的文件名和路径根据窗口来设定
    BOOL bRet = CreateDirectory((LPCWSTR)strFilePath.c_str(),NULL);//创建文件夹
    m_pBitmap->SaveBmp(ImageDataPtr,strFileName);
    }
    */
}

/* **************************************拍照参数函数设计***********************************************/
//相机参数设计
void CameraWindow::on_pushButton_ParamsSet_clicked()
{
    try{
    //设置曝光时间
    float ParmsExposureTime=(ui->lineEdit_ExplosureTime->text()).toFloat();
    ParmsExposureTime=ParmsExposureTime>20?ParmsExposureTime:20;
    ObjFeatureControlPtr->GetFloatFeature("ExposureTime")->SetValue(ParmsExposureTime);

    //设置采集帧率
    float ParmsFps=(ui->lineEdit_FpsSet->text()).toFloat();
    ParmsFps=ParmsFps>0.1?ParmsFps:0.1;
    ObjFeatureControlPtr->GetFloatFeature("AcquisitionFrameRate")->SetValue(ParmsFps);

    //设置采集路径
    strFilePath = ui->lineEdit_FilePath->text().toStdString();
    //设置保存文件名
    strFileName = ui->lineEdit_FileName->text().toStdString();
    }
    catch (CGalaxyException)
    {
     QMessageBox::information(this,"提示","参数设置按钮报错，请先枚举设备，再打开相机");
    }
}




/* **************************************Opencv函数设计***********************************************/
//打开相机时调用此函数获得图片基本信息
void CameraWindow::AllocateRoomForMatCurImgPtr()
{
    ObjFeatureControlPtr= ObjDevicePtr->GetRemoteFeatureControl();
    CIntFeaturePointer ObjIntPtrWidth = ObjFeatureControlPtr->GetIntFeature("AAROIWidth");
    CIntFeaturePointer ObjIntPtrHeight = ObjFeatureControlPtr->GetIntFeature("AAROIHeight");
    ImgWidth=ObjIntPtrWidth->GetValue();//获取图片宽
    ImgHeight=ObjIntPtrHeight->GetValue();//获取图片高
    CurImgMat.create(ImgHeight,ImgWidth,CV_8UC1);//为Mat矩阵开辟空间
}

//连续采集绘图设备
void CameraWindow::ShowCurImgInLabel(QLabel *ptrLabelToShow, cv::Mat &CVMat)
{
    //获取要显示图片的label的大小
    QSize LabelSize=ptrLabelToShow->size();
    QImage QSrcImg=CV2QTFORMAT::cvMatToQImage(CVMat);//获取一个QImage
    QImage QSrcImgRatio=QSrcImg.scaled(LabelSize,Qt::IgnoreAspectRatio);//重新调整图像大小以适应窗口
    ptrLabelToShow->setPixmap(QPixmap::fromImage(QSrcImgRatio));//显示
}

/*
 * ************************
 * 相机与激光平面标定
 * ************************
*/

//相机一键标定
//该函数仅仅输出相机内参标定结果，并不改变当前测量的参数，还需要人为的读取参数
void CameraWindow::on_pushButton_CalibCam_clicked()
{
    std::string CalibFileTxtName=ui->lineEdit_CalibrateData->text().toStdString();
    int BoardWidth=ui->lineEdit_BoardWidth->text().toInt();
    int BoardHeight=ui->lineEdit_BoardHeight->text().toInt();
    float BoardSquareSize=ui->lineEdit_SquareSIze->text().toFloat();
    CalibPhotoNums=CalibWithButton(CalibFileTxtName,BoardWidth,BoardHeight,BoardSquareSize);
    ui->lineEdit_CalibrateDataNum->setText(QString::number(CalibPhotoNums));
    QMessageBox::information(this,"提示","标定结束");

}

//读取相机标定参数以及激光平面标定参数
void CameraWindow::on_pushButton_ReadCalibParms_clicked()
{
    //定义文件流
    std::string CamIntrinsicFilePath=".\\CameraCalibrate\\";
    std::string CamMFileName="CamIntrinsicMat.txt";
    std::string DisCoeffsFileName="distCoeffs.txt";
    ReadMatFromFileName(CamIntrinsicFilePath+CamMFileName,CameraIntrinsic,1);//读取内参矩阵
    ReadMatFromFileName(CamIntrinsicFilePath+DisCoeffsFileName,DisCoeffs,1);//读取畸变系数
    m_bUnDistort=true;//可以进行畸变矫正

    //下面是激光平面信息
    std::string PlaneInfoFilePath=".\\PlaneCalibrate\\";
    std::fstream PlaneCoeffsStream,PlaneBaseLineStream;
    std::string CoeffsFileName="PlaneCoeffs.txt";
    std::string BaseLineFileName="BaseLineInfo.txt";
    PlaneCoeffsStream.open(PlaneInfoFilePath+CoeffsFileName);
    PlaneBaseLineStream.open(PlaneInfoFilePath+BaseLineFileName);

    //定义变量
    double m_kx,m_ky,m_kz,m_a0,m_a1,m_a2;//平面系数a0,a1,a2
    Point3f ReadPassPt;

    //读取参数
    PlaneCoeffsStream>>m_a0>>m_a1>>m_a2;
    PlaneBaseLineStream>>m_kx>>m_ky>>m_kz>>ReadPassPt.x>>ReadPassPt.y>>ReadPassPt.z;

    //设置参数
    LPlane.SetBaseLineParams(m_kx,m_ky,m_kz,ReadPassPt);
    LPlane.SetPCoeffs(m_a0,m_a1,m_a2);
    QMessageBox::information(this,"Information","Read Parameters Complete!");
}

//清空标定参数
void CameraWindow::on_pushButton_ClearCalibParms_clicked()
{
    LPlane.CleanCoeffs();
    CameraIntrinsic=Mat::zeros(3,3,CV_32FC1);
    DisCoeffs=Mat::zeros(1,5,CV_32FC1);
    m_bUnDistort=false;//不再进行畸变矫正
}

//激光平面标定
void CameraWindow::on_pushButton_PlaneFit_clicked()
{
    std::string CalibPlaneFileTxtName=ui->lineEdit_CalibLaserPlaneData->text().toStdString();
    vector<string> PhotoDataArray;//暗场照片数据
    ReadFileNameFromTxt(CalibPlaneFileTxtName,PhotoDataArray);//获取暗场照片数据
    vector<Point2f> CenterLinePtsPerImg;//中心条纹图像坐标
    ReadMatFromFileName(".\\CameraCalibrate\\CamIntrinsicMat.txt",CameraIntrinsic,1);//读取内参
    ReadMatFromFileName(".\\CameraCalibrate\\distCoeffs.txt",DisCoeffs,1);//畸变系数
    Mat RotMati=Mat::zeros(3,3,CV_32FC1);//第i张图旋转矩阵
    Mat TranslationVeci=Mat::zeros(3,1,CV_32FC1);//第i张图平移矩阵
    vector<Point3f> PtsInWPerImg;//每张图片的世界坐标系坐标
    vector<Point3f> PtsInCPerImg;//每张图的相机坐标系坐标
    vector<float> PtsToWorldError;//每张图的误差
    vector<Point3f> PtsInCTOFitPlane;//用于拟合平面的点集合容器

    //对每张图片提取中心条纹
    for(int i=0;i<PhotoDataArray.size();i++){
        Mat CalibPlaneSrcImg=imread(PhotoDataArray[i],IMREAD_GRAYSCALE);//读取图片

        CenterLinePtsPerImg=StegerLine(CalibPlaneSrcImg);//提取中心线
        ReadMatFromFileName(".\\CameraCalibrate\\RMat.txt",RotMati,i);//读取对应的R
        ReadMatFromFileName(".\\CameraCalibrate\\tvec.txt",TranslationVeci,i);//读取对应的t

        PointsToWorld(CameraIntrinsic,RotMati,TranslationVeci,CenterLinePtsPerImg,PtsInWPerImg,PtsToWorldError);//投影点到棋盘坐标系
        PointsToCamera(PtsInWPerImg,RotMati,TranslationVeci,PtsInCPerImg);//投影到相机坐标系

        //将点云压入拟合容器中
        for(int j=0;j<PtsInCPerImg.size();j++){
            PtsInCTOFitPlane.push_back(PtsInCPerImg[j]);
        }

        //清空容器
        PtsInWPerImg.clear();
        PtsInCPerImg.clear();
    }

    this->LPlane.PlaneFitting(PtsInCTOFitPlane);
    this->LPlane.SavePlaneParams();//保存平面标定参数
    QMessageBox::information(this,"Information","PlaneFitting Complete!");
}

// 将当前图片的激光条纹设定为基准直线
void CameraWindow::on_pushButton_SetBaseLine_clicked()
{
    vector<Point2f> BLineCenterImgPts=StegerLine(CurImgMat);//对当前图片提取中心条纹
    LPlane.SetBaseLine(CameraIntrinsic,BLineCenterImgPts);//利用内参结合中心条纹设定基准线
    LPlane.SaveBaseLineParams();//设置基准线的时候，自动保存基准线信息
}

// 当前参数显示
void CameraWindow::on_pushButton_ShowCurParams_clicked()
{
    std::string tempStr="CurrentParams.txt";
    fstream fout;
    fout.open(tempStr,ios::out|ios::trunc);
    fout.close();
    fout.open(tempStr,ios::app);
    float Pbaselinekx,Pbaselineky,Pbaselinekz;
    Point3f Ppasspt;
    double PCoeffsa0,PCoeffsa1,PCoeffsa2;
    LPlane.SendPlaneParams(Pbaselinekx,Pbaselineky,Pbaselinekz,Ppasspt,PCoeffsa0,PCoeffsa1,PCoeffsa2);
    fout<<"PlaneParams:"<<std::endl;
    fout<<"baseline:"<<"kx: "<<Pbaselinekx<<" ky: "<<Pbaselineky<<" kz: "<<Pbaselinekz<<std::endl;
    fout<<"baseline:"<<"Passpt: "<<Ppasspt<<std::endl;
    fout<<"Plane Coeffs:"<<std::endl;
    fout<<"a0: "<<PCoeffsa0<<" a1: "<<PCoeffsa1<<" a2: "<<PCoeffsa2<<std::endl;

    fout<<"M:"<<std::endl;
    fout<<CameraIntrinsic<<std::endl;
    fout<<"discoeffs"<<std::endl;
    fout<<DisCoeffs<<std::endl;
    QMessageBox::information(this,"提示","输出参数完成");
}

// 单帧测量
void CameraWindow::on_pushButton_MeasureSingleF_clicked()
{
    SingleFrameMeasureFunction();
    //vector<Point2f> CurCenterLinePtSet;
    //vector<Point3f> CurMeasurePtsIn3D;
    //vector<float> MeasureRes;
    //CurCenterLinePtSet=StegerLine(CurImgMat);//提取中心线
    //LPlane.ComputeImgPtOnPlane(CameraIntrinsic,CurCenterLinePtSet,CurMeasurePtsIn3D);//中心线转换到三维坐标系
    //LPlane.ComputePtDistToBaseLine(CurMeasurePtsIn3D,MeasureRes);//计算三维点集到基准直线的距离
    m_bMeasureOk=false;//将原本的设置为false
}

//单帧测量的回调函数获取测量结果
void CameraWindow::SingleFrameMeasureFunction(){
	MeasureResult_x.clear();
	MeasureResult_y.clear();//清空原有的结果
    vector<Point2f> CurCenterLinePtSet;
    vector<Point3f> CurMeasurePtsIn3D;
    vector<float> MeasureRes;
    CurCenterLinePtSet=StegerLine(CurImgMat);//提取中心线
    LPlane.ComputeImgPtOnPlane(CameraIntrinsic,CurCenterLinePtSet,CurMeasurePtsIn3D);//中心线转换到三维坐标系
    LPlane.ComputePtDistToBaseLine(CurMeasurePtsIn3D,MeasureRes);//计算三维点集到基准直线的距离
    for(int i=0;i<MeasureRes.size();i++){
		MeasureResult_x.push_back(i);
        MeasureResult_y.push_back(MeasureRes[i]);//将结果传递给主窗口，此处是没有空间的，必须使用push_back
    }
}

// 连续测量
void CameraWindow::on_pushButton_MeasureContinuous_clicked()
{
    m_bMeasureOk=true;
}

//切换到主界面
void CameraWindow::on_pushButton_ShiftToMainWindow_clicked()
{
    this->hide();
    emit SignalInSub1_ShowMainWin();
}

//建立窗口间的联系，这个函数是用于让主窗口控制子窗口的
void CameraWindow::MakeConnection(void *MainWinPtr)
{
    MainWindow* ptr=(MainWindow*)MainWinPtr;
    connect(ptr,&MainWindow::SignalInMainWin_ShowSub1,this,&CameraWindow::show);
    connect(ptr,&MainWindow::SignalInMainWin_StartMeasure,this,&CameraWindow::SendResSignalToMainWin);//子窗口接收到信号后，将结果返回给主窗口
}

//向主窗口发送结果信号,在主窗口中绘图
void CameraWindow::SendResSignalToMainWin(){
    SingleFrameMeasureFunction();//直接调用函数根据curMat修改结果
    emit Signal_LUResToMainWin(MeasureResult_x,MeasureResult_y);
}

//采集单帧
void CameraWindow::on_pushButton_TestGetSingleImg_Take_clicked()
{
    ObjStreamPtr->StartGrab();

    //给设备发送开采命令
    ObjFeatureControlPtr->GetCommandFeature("AcquisitionStart")->Execute();
    CImageDataPointer objImageDataPtr;
    objImageDataPtr = ObjStreamPtr->GetImage(500);//超时时间使用500ms，用户可以自行设定

    if (objImageDataPtr->GetStatus() == GX_FRAME_STATUS_SUCCESS)
    {
      //采图成功而且是完整帧，可以进行图像处理...
      void* pRaw8Buffer = NULL;
      pRaw8Buffer = objImageDataPtr->ConvertToRaw8(GX_BIT_0_7);
      memcpy(this->CurImgMat.data, pRaw8Buffer, (objImageDataPtr->GetHeight())*(objImageDataPtr->GetWidth()));
      if(m_bUnDistort==true){

      }
    }
    //采集完之后要显示

    this->ShowCurImgInLabel(LabelSingleImg,CurImgMat);
    ObjFeatureControlPtr->GetCommandFeature("AcquisitionStop")->Execute();
    ObjStreamPtr->StopGrab();
}

//仅仅保存基线信息
void CameraWindow::on_pushButton_OutputBaseLine_clicked()
{
    LPlane.SaveBaseLineParams();
}

//读取基线信息
void CameraWindow::on_pushButton_ReadBaseLineInfo_clicked()
{
    //下面是基线信息
    std::string PlaneInfoFilePath=".\\PlaneCalibrate\\";
    std::fstream PlaneBaseLineStream;

    std::string BaseLineFileName="BaseLineInfo.txt";

    PlaneBaseLineStream.open(PlaneInfoFilePath+BaseLineFileName);

    //定义变量
    double m_kx,m_ky,m_kz;//平面系数a0,a1,a2
    Point3f ReadPassPt;

    //读取参数
    PlaneBaseLineStream>>m_kx>>m_ky>>m_kz>>ReadPassPt.x>>ReadPassPt.y>>ReadPassPt.z;

    //设置参数
    LPlane.SetBaseLineParams(m_kx,m_ky,m_kz,ReadPassPt);
    QMessageBox::information(this,"Information","Read BaseLine Parameters Complete!");
}
