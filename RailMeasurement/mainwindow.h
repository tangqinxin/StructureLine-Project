#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QWidget>
#include <qcustomplot.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void MakeConnection(void* WinPtr);
    void LU_SubWinPlot(std::vector<float>& Resx,std::vector<float>& Resy);//LU窗口画出结果

signals:
    void SignalInMainWin_ShowSub1();
    void SignalInMainWin_StartMeasure();

private slots:
    //void PlotWidget();
    void MyCustomPlot();
    void on_pushButton_clicked();

    void on_pushButton_ChangeToCamWin1_clicked();

    void on_pushButton_Measure_clicked();

private:
    Ui::MainWindow *ui;
    int amplitude=1;
};

#endif // MAINWINDOW_H
