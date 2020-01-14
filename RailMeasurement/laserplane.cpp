#include "laserplane.h"

LaserPlane::LaserPlane() {
    PCoeffs.a0 = 0;
    PCoeffs.a1 = 0;
    PCoeffs.a2 = 0;
    BaseLine.kx = 0;
    BaseLine.ky = 0;
    BaseLine.kz = 0;
    BaseLine.PassPt.x = 0;
    BaseLine.PassPt.y = 0;
    BaseLine.PassPt.z = 0;
}

LaserPlane::~LaserPlane() {}

// 利用三维点云集合进行拟合平面
// Z=a0*X+a1*Y+a2;
void LaserPlane::PlaneFitting(vector<Point3f> &PointsCameraCoordinate) {
    int NumOfPts = PointsCameraCoordinate.size();
    Mat A = Mat::ones(NumOfPts, 3, CV_64FC1);//[Xci,Yci,1]*[a0,a1,a2]'=[Zci]
    Mat b = Mat::zeros(NumOfPts, 1, CV_64FC1);

    for (int i = 0; i < NumOfPts; i++) {
        *A.ptr<double>(i, 0) = PointsCameraCoordinate[i].x;
        *A.ptr<double>(i, 1) = PointsCameraCoordinate[i].y;//A的第三列统一为1

        *b.ptr<double>(i, 0) = PointsCameraCoordinate[i].z;
    }
    Mat a_coefficient = (A.t()*A).inv()*(A.t()*b);
    for (int i = 0; i < 3; i++) {
        PCoeffs.a0 = a_coefficient.at<double>(0, 0);
        PCoeffs.a1 = a_coefficient.at<double>(1, 0);
        PCoeffs.a2 = a_coefficient.at<double>(2, 0);
    }
}

//清空激光平面的系数
void LaserPlane::CleanCoeffs() {
    PCoeffs.a0 = 0;
    PCoeffs.a1 = 0;
    PCoeffs.a2 = 0;
    BaseLine.kx = 0;
    BaseLine.ky = 0;
    BaseLine.kz = 0;
    BaseLine.PassPt.x = 0;
    BaseLine.PassPt.y = 0;
    BaseLine.PassPt.z = 0;
}

//输入相机内参，像素坐标点集，输出他们在相机坐标系下的三维坐标
/*
    a0*Xc+a1*Yc+a2=Zc;
    Zc*(a0*Xn+a1*Yn-1)=-a2;
    Zc=-a2/(a0*Xn+a1*Yn-1);
*/
void LaserPlane::ComputeImgPtOnPlane(Mat& M, vector<Point2f>& ImgPtSet, vector<Point3f>& PtsInCamera)
{
    int NumOfPts = ImgPtSet.size();
    //构建uvPoints矩阵
    Mat uvPts = Mat::ones(3, NumOfPts, CV_32FC1);
    for (int i = 0; i < NumOfPts; i++) {
        *uvPts.ptr<float>(0, i) = ImgPtSet[i].x;
        *uvPts.ptr<float>(1, i) = ImgPtSet[i].y;
    }

	// 构建齐次矩阵
	Mat tempMInverse = M.inv();
	if (M.type() == CV_64FC1) {
		tempMInverse.convertTo(tempMInverse, CV_32FC1);
	}
	Mat XnYnMat = tempMInverse*uvPts;

    // 构建结果矩阵
    vector<float> LineZc(NumOfPts, 0);
    vector<float> LineXc(NumOfPts, 0);
    vector<float> LineYc(NumOfPts, 0);
	float Xn;//临时变量
	float Yn;

    // 计算像素点在空间的坐标
    for (int i = 0; i < NumOfPts; i++) {
        Xn = *XnYnMat.ptr<float>(0, i);
        Yn = *XnYnMat.ptr<float>(1, i);
        LineZc[i] = (-1 * PCoeffs.a2) / (PCoeffs.a0*Xn + PCoeffs.a1*Yn - 1);
        LineXc[i] = Xn*LineZc[i];
        LineYc[i] = Yn*LineZc[i];
        Point3f tempPt;
        tempPt.x = LineXc[i];
        tempPt.y = LineYc[i];
        tempPt.z = LineZc[i];
        PtsInCamera.push_back(tempPt);
    }
}


//设定一条基准线作为参考坐标
void LaserPlane::SetBaseLine(Mat& M, vector<Point2f>& BaseLineImgPtSet) {
    //预设一个容器装baseline的point3f
    vector<Point3f> PtsInCamera;

    //计算baseline的point3f
    ComputeImgPtOnPlane(M, BaseLineImgPtSet, PtsInCamera);

    //利用空间点云进行设置基线
    SetBaseLineWith3DPts(PtsInCamera);
}


//利用空间中的点云进行设置基线
void LaserPlane::SetBaseLineWith3DPts(vector<Point3f>& PtsInCamera)
{
    int NumOfPts = PtsInCamera.size();
    Mat A1 = Mat::ones(NumOfPts, 2,CV_64FC1);
    Mat b1 = Mat::zeros(NumOfPts, 1, CV_64FC1);
    Mat A2 = Mat::ones(NumOfPts, 2, CV_64FC1);
    Mat b2 = Mat::zeros(NumOfPts, 1, CV_64FC1);

    // 设置A1，b1,A2,b2
    for (int i = 0; i < NumOfPts; i++) {
        *A1.ptr<double>(i, 0) = PtsInCamera[i].z;
        *A2.ptr<double>(i, 0) = PtsInCamera[i].z;
        *b1.ptr<double>(i, 0) = PtsInCamera[i].x;
        *b2.ptr<double>(i, 0) = PtsInCamera[i].y;
    }

    Mat k1b1 = (A1.t()*A1).inv()*(A1.t()*b1);
    Mat k2b2 = (A2.t()*A2).inv()*(A2.t()*b2);
    BaseLine.kx = *k1b1.ptr<double>(0, 0);
    BaseLine.ky = *k2b2.ptr<double>(0, 0);
    BaseLine.kz = 1;
    // 将方向向量单位化
    double VecLen = sqrt(BaseLine.kx*BaseLine.kx + BaseLine.ky*BaseLine.ky + BaseLine.kz*BaseLine.kz);
    BaseLine.kx = BaseLine.kx/VecLen;
    BaseLine.ky = BaseLine.ky/VecLen;
    BaseLine.kz = BaseLine.kz/VecLen;

    BaseLine.PassPt.x= *k1b1.ptr<double>(1, 0);
    BaseLine.PassPt.y = *k2b2.ptr<double>(1, 0);
    BaseLine.PassPt.z = 0;
}

// Pt为基线外一点M1，基线过M0，方向向量为[kx,ky,kz]
float LaserPlane::PointToBaseLine(Point3f & Pt)
{
    float SingleDist = 0;
    Point3f VecM0ToM1;

    Point3f DirUnitVec;
    DirUnitVec.x = BaseLine.kx;
    DirUnitVec.y = BaseLine.ky;
    DirUnitVec.z = BaseLine.kz;

    //设定基线外一点
    VecM0ToM1 = Pt - BaseLine.PassPt;

    //计算投影向量
    Point3f ProjVecM0ToM1 = VecM0ToM1.ddot(DirUnitVec)*DirUnitVec;

    //计算垂直向量
    Point3f PerpendicularVecOfM0ToM1 = VecM0ToM1 - ProjVecM0ToM1;

    //计算垂直距离
    SingleDist = NormPoint3f(PerpendicularVecOfM0ToM1);
    return SingleDist;
}

// 计算点集到基线坐标，点集的坐标是相机坐标系下的坐标
// 假设要求的线外一点为M1,基线过M0,方向向量为[kx,ky,kz]
void LaserPlane::ComputePtDistToBaseLine(vector<Point3f>& PtSet, vector<float>& DistIn3D) {
    int NumOfPts = PtSet.size();
    float SingleDist=0;
    Point3f VecM0ToM1;

    Point3f DirUnitVec;
    DirUnitVec.x = BaseLine.kx;
    DirUnitVec.y = BaseLine.ky;
    DirUnitVec.z = BaseLine.kz;

    for (int i = 0; i < NumOfPts; i++) {
        VecM0ToM1 = PtSet[i] - BaseLine.PassPt;
        //计算投影向量
        Point3f ProjVecM0ToM1 = VecM0ToM1.ddot(DirUnitVec)*DirUnitVec;

        //计算垂直向量
        Point3f PerpendicularVecOfM0ToM1 = VecM0ToM1 - ProjVecM0ToM1;

        //计算垂直距离
        SingleDist = NormPoint3f(PerpendicularVecOfM0ToM1);
        DistIn3D.push_back(SingleDist);
    }
}

//打印平面参数
void LaserPlane::DisplayCoeffs()
{
    std::cout << "a0= "<<PCoeffs.a0 << std::endl;
    std::cout << "a1= " << PCoeffs.a1 << std::endl;
    std::cout << "a2= " << PCoeffs.a2 << std::endl;
}

//打印基线信息
void LaserPlane::DisplayBaseLine()
{
    std::cout << "法向量为" << std::endl;
    std::cout << "kx=" << BaseLine.kx << std::endl;
    std::cout << "ky=" << BaseLine.ky << std::endl;
    std::cout << "kz=" << BaseLine.kz << std::endl;
    std::cout << "通过的点坐标" << std::endl;
    std::cout << BaseLine.PassPt<< std::endl;
}

// 三维向量的norm
float LaserPlane::NormPoint3f(Point3f & vec)
{
    double Norm = sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
    return Norm;
}

// 自己设定基准线的参数
void LaserPlane::SetBaseLineParams(float _kx, float _ky, float _kz, Point3f & pt)
{
    BaseLine.kx = _kx;
    BaseLine.ky = _ky;
    BaseLine.kz = _kz;
    BaseLine.PassPt = pt;
}

// 保存平面参数
void LaserPlane::SavePlaneParams()
{
    
    std::string FilePath = ".\\PlaneCalibrate";
	MakeMyDirectory(FilePath);
    std::string FileName1 = FilePath + "\\" +"PlaneCoeffs.txt";//保存平面系数a0，a1，a2
    std::string FileName2 = FilePath + "\\" +"BaseLineInfo.txt";//保存基线参数kx，ky，kz，PassPt
    std::fstream PlaneParamStream;
    std::fstream PlaneBaseLineStream;

    PlaneParamStream.open(FileName1,ios::out | ios::trunc);
    PlaneBaseLineStream.open(FileName2,ios::out | ios::trunc);
    PlaneBaseLineStream.close();
    PlaneParamStream.close();
    PlaneParamStream.open(FileName1,ios::app);
    PlaneBaseLineStream.open(FileName2,ios::app);

    PlaneParamStream << PCoeffs.a0 << " " << PCoeffs.a1 << " " << PCoeffs.a2 << std::endl;
    PlaneBaseLineStream << BaseLine.kx << std::endl;
    PlaneBaseLineStream << BaseLine.ky << std::endl;
    PlaneBaseLineStream << BaseLine.kz << std::endl;
    PlaneBaseLineStream << BaseLine.PassPt.x << " " << BaseLine.PassPt.y << " " << BaseLine.PassPt.z << std::endl;
}

// 人为设定平面参数a0,a1,a2
void LaserPlane::SetPCoeffs(double m_a0, double m_a1, double m_a2)
{
    PCoeffs.a0=m_a0;
    PCoeffs.a1=m_a1;
    PCoeffs.a2=m_a2;
}

//向外界传递参数
void LaserPlane::SendPlaneParams(float &_kx, float &_ky, float &_kz, Point3f &m_pt, double &_a0, double &_a1, double &_a2)
{
    _kx=BaseLine.kx;
    _ky=BaseLine.ky;
    _kz=BaseLine.kz;
    m_pt=BaseLine.PassPt;
    _a0=PCoeffs.a0;
    _a1=PCoeffs.a1;
    _a2=PCoeffs.a2;
}
