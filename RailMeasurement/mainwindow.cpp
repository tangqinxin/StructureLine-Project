#include "mainwindow.h"
#include "camerawindow.h"
#include <QtCharts>
#include"convertstring.h"
QT_CHARTS_USE_NAMESPACE

#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->PlotWidget();
    //this->MyCustomPlot();
    this->LUWinPlot();//LU窗口画图
    this->LDWinPlot();//LD窗口画图
    this->DWinPlot();//Down窗口画图
    this->RDWinPlot();//RD窗口画图
    this->RUWinPlot();//RU窗口画图
}

MainWindow::~MainWindow()
{
    delete ui;
}



//使用Qchart来画图，暂时舍弃
//void MainWindow::PlotWidget()
//{
//    QChart* chart = new QChart();
//    QLineSeries *series = new QLineSeries();
//
//    for (quint32 i = 0; i < 100; i++) {
//        series->append(i, this->amplitude*sin(0.6f*i));
//    }
//    chart->addSeries(series);
//    chart->createDefaultAxes();        // 基于已添加到图表的 series 来创建默认的坐标轴
//   ui->widget_Plot->setChart(chart);
//    ui->widget_Plot->resize(500,500);
//}

//void MainWindow::MyCustomPlot()
//{
    //QVector<double> x(101), y(101); // initialize with entries 0..100
    //for (int i=0; i<101; ++i)
    //{
    //  x[i] = i/50.0 - 1; // x goes from -1 to 1
    //  y[i] = x[i]*x[i]; // let's plot a quadratic function
    //}
    // create graph and assign data to it:
    //ui->widget_customPlot->addGraph();
    //ui->widget_customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    //ui->widget_customPlot->xAxis->setLabel("x");
    //ui->widget_customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    //ui->widget_customPlot->xAxis->setRange(-1, 1);
    //ui->widget_customPlot->yAxis->setRange(0, 1);
    //ui->widget_customPlot->replot();
//}

void MainWindow::on_pushButton_clicked()
{
    this->amplitude=this->amplitude*10;
}

void MainWindow::on_pushButton_ChangeToCamWin1_clicked()
{
    //隐藏主界面，发出信号显示子界面
    this->hide();
    emit SignalInMainWin_ShowSub1();
}

//建立槽之间的连接，用于切换界面，这个函数是用于子窗口控制主窗口的
void MainWindow::MakeConnection(void *WinPtr)
{
    CameraWindow* ptr=(CameraWindow*)WinPtr;
    connect(ptr,&CameraWindow::SignalInSub1_ShowMainWin,this,&MainWindow::show);
    connect(ptr,&CameraWindow::Signal_LUResToMainWin,this,&MainWindow::LU_SubWinPlot);
}

//发出测量信号给子窗口
void MainWindow::on_pushButton_Measure_clicked()
{
    emit SignalInMainWin_StartMeasure();
}


//在左上窗口指针中进行画图
void MainWindow::LU_SubWinPlot(std::vector<float> &Resx, std::vector<float> &Resy)
{

    QVector<double> FigX,FigY;
    for(int i=0;i<Resx.size();i++){
        FigX.append(Resx[i]);
        FigY.append(Resy[i]);
    }
    ui->widget_LUArrowFig->addGraph();
    ui->widget_LUArrowFig->graph(0)->setData(FigX,FigY);
    ui->widget_LUArrowFig->xAxis->setLabel("测量水平距离(mm)");
    ui->widget_LUArrowFig->yAxis->setLabel("到基准线距离(mm)");
    ui->widget_LUArrowFig->rescaleAxes(true);//如果不用这个语句，可能无法看到画图的结果
    ui->widget_LUArrowFig->replot();
}

/*项目验收截图展示效果
 * 窗口LU
 */
void MainWindow::LUWinPlot(){
    vector<double> Resx, Resy;
    ReadDataFromTxt("UpLeft.txt", Resx, Resy);

    QVector<double> FigX,FigY;
    for(int i=0;i<Resx.size();i++){
        FigX.append(Resx[i]);
        FigY.append(Resy[i]);
    }
    ui->widget_LUArrowFig->addGraph();
    ui->widget_LUArrowFig->graph(0)->setData(FigX,FigY);
    ui->widget_LUArrowFig->xAxis->setLabel("测量水平距离(mm)");
    ui->widget_LUArrowFig->yAxis->setLabel("到基准线距离(mm)");
    ui->widget_LUArrowFig->rescaleAxes(true);//如果不用这个语句，可能无法看到画图的结果
    ui->widget_LUArrowFig->replot();
}

//窗口LD
void MainWindow::LDWinPlot(){
    vector<double> Resx, Resy;
    ReadDataFromTxt("DownLeft.txt", Resx, Resy);

    QVector<double> FigX,FigY;
    for(int i=0;i<Resx.size();i++){
        FigX.append(Resx[i]);
        FigY.append(Resy[i]);
    }
    ui->widget_LDArrowFig->addGraph();
    ui->widget_LDArrowFig->graph(0)->setData(FigX,FigY);
    ui->widget_LDArrowFig->xAxis->setLabel("测量水平距离(mm)");
    ui->widget_LDArrowFig->yAxis->setLabel("到基准线距离(mm)");
    ui->widget_LDArrowFig->rescaleAxes(true);//如果不用这个语句，可能无法看到画图的结果
    ui->widget_LDArrowFig->replot();
}

void MainWindow::RUWinPlot()
{
    vector<double> Resx, Resy;
    ReadDataFromTxt("UpRight.txt", Resx, Resy);

    QVector<double> FigX,FigY;
    for(int i=0;i<Resx.size();i++){
        FigX.append(Resx[i]);
        FigY.append(Resy[i]);
    }
    ui->widget_RUArrowFig->addGraph();
    ui->widget_RUArrowFig->graph(0)->setData(FigX,FigY);
    ui->widget_RUArrowFig->xAxis->setLabel("测量水平距离(mm)");
    ui->widget_RUArrowFig->yAxis->setLabel("到基准线距离(mm)");
    ui->widget_RUArrowFig->rescaleAxes(true);//如果不用这个语句，可能无法看到画图的结果
    ui->widget_RUArrowFig->replot();
}

//窗口Down
void MainWindow::DWinPlot(){
    vector<double> Resx, Resy;
    ReadDataFromTxt("Down.txt", Resx, Resy);

    QVector<double> FigX,FigY;
    for(int i=0;i<Resx.size();i++){
        FigX.append(Resx[i]);
        FigY.append(Resy[i]);
    }
    ui->widget_DownArrowFig->addGraph();
    ui->widget_DownArrowFig->graph(0)->setData(FigX,FigY);
    ui->widget_DownArrowFig->xAxis->setLabel("测量水平距离(mm)");
    ui->widget_DownArrowFig->yAxis->setLabel("到基准线距离(mm)");
    ui->widget_DownArrowFig->rescaleAxes(true);//如果不用这个语句，可能无法看到画图的结果
    ui->widget_DownArrowFig->replot();
}

//窗口RightDown
void MainWindow::RDWinPlot(){
    vector<double> Resx, Resy;
    ReadDataFromTxt("DownRight.txt", Resx, Resy);

    QVector<double> FigX,FigY;
    for(int i=0;i<Resx.size();i++){
        FigX.append(Resx[i]);
        FigY.append(Resy[i]);
    }
    ui->widget_RDArrowFig->addGraph();
    ui->widget_RDArrowFig->graph(0)->setData(FigX,FigY);
    ui->widget_RDArrowFig->xAxis->setLabel("测量水平距离(mm)");
    ui->widget_RDArrowFig->yAxis->setLabel("到基准线距离(mm)");
    ui->widget_RDArrowFig->rescaleAxes(true);//如果不用这个语句，可能无法看到画图的结果
    ui->widget_RDArrowFig->replot();
}
