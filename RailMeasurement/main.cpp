#include "mainwindow.h"
#include "camerawindow.h"
#include <QApplication>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    CameraWindow Cam;
    w.show();
    //Cam.show();
    w.MakeConnection(&Cam);
    Cam.MakeConnection(&w);
    return a.exec();
}
