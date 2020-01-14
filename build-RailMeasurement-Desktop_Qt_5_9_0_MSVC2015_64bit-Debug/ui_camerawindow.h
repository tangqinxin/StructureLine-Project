/********************************************************************************
** Form generated from reading UI file 'camerawindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAWINDOW_H
#define UI_CAMERAWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <drawwidget.h>

QT_BEGIN_NAMESPACE

class Ui_CameraWindow
{
public:
    DrawWidget *widget_CurInput;
    QLabel *label_CurInput;
    QWidget *widget_SampleImg;
    QLabel *label_SampleImg;
    QFrame *frame_ParmsSet;
    QLabel *label_ExplosureTime;
    QLabel *label_FpsSet;
    QLineEdit *lineEdit_ExplosureTime;
    QLineEdit *lineEdit_FpsSet;
    QPushButton *pushButton_ParamsSet;
    QPushButton *pushButton_ShiftToMainWindow;
    QPushButton *pushButton_TestGetSingleImg_Take;
    QPushButton *pushButton_OutputBaseLine;
    QPushButton *pushButton_ReadBaseLineInfo;
    QFrame *frame_CamOperate;
    QPushButton *pushButton_OpenCam;
    QPushButton *pushButton_StartGrab;
    QPushButton *pushButton_StopGrab;
    QPushButton *pushButton_CloseCam;
    QPushButton *pushButton_ListDevice;
    QPushButton *pushButton_GetImg;
    QPushButton *pushButton_CalibCam;
    QPushButton *pushButton_PlaneFit;
    QPushButton *pushButton_ReadCalibParms;
    QPushButton *pushButton_ClearCalibParms;
    QPushButton *pushButton_MeasureSingleF;
    QPushButton *pushButton_MeasureContinuous;
    QPushButton *pushButton_SetBaseLine;
    QPushButton *pushButton_ShowCurParams;
    QFrame *frame_WinInfo;
    QLabel *label_NumOfCam;
    QLabel *label_CamIndex;
    QLineEdit *lineEdit_NumOfCam;
    QLineEdit *lineEdit_CamIndex;
    QLabel *label_FilePath;
    QLineEdit *lineEdit_FilePath;
    QLabel *label_FileName;
    QLineEdit *lineEdit_FileName;
    QLabel *label_CalibrateData;
    QLineEdit *lineEdit_CalibrateData;
    QLabel *label_BoardWidth;
    QLineEdit *lineEdit_BoardWidth;
    QLabel *label_BoardHeight;
    QLineEdit *lineEdit_BoardHeight;
    QLabel *label_SquareSize;
    QLineEdit *lineEdit_SquareSIze;
    QLabel *label_CalibrateDataNum;
    QLineEdit *lineEdit_CalibrateDataNum;
    QLabel *label_CalibLaserPlaneData;
    QLineEdit *lineEdit_CalibLaserPlaneData;

    void setupUi(QWidget *CameraWindow)
    {
        if (CameraWindow->objectName().isEmpty())
            CameraWindow->setObjectName(QStringLiteral("CameraWindow"));
        CameraWindow->resize(1920, 1080);
        CameraWindow->setMinimumSize(QSize(1920, 1080));
        CameraWindow->setMaximumSize(QSize(1920, 1080));
        widget_CurInput = new DrawWidget(CameraWindow);
        widget_CurInput->setObjectName(QStringLiteral("widget_CurInput"));
        widget_CurInput->setGeometry(QRect(100, 100, 800, 800));
        label_CurInput = new QLabel(widget_CurInput);
        label_CurInput->setObjectName(QStringLiteral("label_CurInput"));
        label_CurInput->setGeometry(QRect(0, 0, 800, 800));
        widget_SampleImg = new QWidget(CameraWindow);
        widget_SampleImg->setObjectName(QStringLiteral("widget_SampleImg"));
        widget_SampleImg->setGeometry(QRect(1000, 100, 800, 800));
        label_SampleImg = new QLabel(widget_SampleImg);
        label_SampleImg->setObjectName(QStringLiteral("label_SampleImg"));
        label_SampleImg->setGeometry(QRect(0, 0, 800, 800));
        frame_ParmsSet = new QFrame(CameraWindow);
        frame_ParmsSet->setObjectName(QStringLiteral("frame_ParmsSet"));
        frame_ParmsSet->setGeometry(QRect(100, 910, 800, 100));
        frame_ParmsSet->setFrameShape(QFrame::StyledPanel);
        frame_ParmsSet->setFrameShadow(QFrame::Raised);
        label_ExplosureTime = new QLabel(frame_ParmsSet);
        label_ExplosureTime->setObjectName(QStringLiteral("label_ExplosureTime"));
        label_ExplosureTime->setGeometry(QRect(10, 10, 100, 30));
        label_FpsSet = new QLabel(frame_ParmsSet);
        label_FpsSet->setObjectName(QStringLiteral("label_FpsSet"));
        label_FpsSet->setGeometry(QRect(10, 50, 100, 30));
        lineEdit_ExplosureTime = new QLineEdit(frame_ParmsSet);
        lineEdit_ExplosureTime->setObjectName(QStringLiteral("lineEdit_ExplosureTime"));
        lineEdit_ExplosureTime->setGeometry(QRect(120, 10, 100, 30));
        lineEdit_FpsSet = new QLineEdit(frame_ParmsSet);
        lineEdit_FpsSet->setObjectName(QStringLiteral("lineEdit_FpsSet"));
        lineEdit_FpsSet->setGeometry(QRect(120, 50, 100, 30));
        pushButton_ParamsSet = new QPushButton(frame_ParmsSet);
        pushButton_ParamsSet->setObjectName(QStringLiteral("pushButton_ParamsSet"));
        pushButton_ParamsSet->setGeometry(QRect(230, 50, 100, 30));
        pushButton_ShiftToMainWindow = new QPushButton(frame_ParmsSet);
        pushButton_ShiftToMainWindow->setObjectName(QStringLiteral("pushButton_ShiftToMainWindow"));
        pushButton_ShiftToMainWindow->setGeometry(QRect(340, 50, 100, 30));
        pushButton_TestGetSingleImg_Take = new QPushButton(frame_ParmsSet);
        pushButton_TestGetSingleImg_Take->setObjectName(QStringLiteral("pushButton_TestGetSingleImg_Take"));
        pushButton_TestGetSingleImg_Take->setGeometry(QRect(230, 10, 100, 30));
        pushButton_OutputBaseLine = new QPushButton(frame_ParmsSet);
        pushButton_OutputBaseLine->setObjectName(QStringLiteral("pushButton_OutputBaseLine"));
        pushButton_OutputBaseLine->setGeometry(QRect(340, 10, 100, 30));
        pushButton_ReadBaseLineInfo = new QPushButton(frame_ParmsSet);
        pushButton_ReadBaseLineInfo->setObjectName(QStringLiteral("pushButton_ReadBaseLineInfo"));
        pushButton_ReadBaseLineInfo->setGeometry(QRect(450, 50, 100, 30));
        frame_CamOperate = new QFrame(CameraWindow);
        frame_CamOperate->setObjectName(QStringLiteral("frame_CamOperate"));
        frame_CamOperate->setGeometry(QRect(1000, 910, 800, 100));
        frame_CamOperate->setFrameShape(QFrame::StyledPanel);
        frame_CamOperate->setFrameShadow(QFrame::Raised);
        pushButton_OpenCam = new QPushButton(frame_CamOperate);
        pushButton_OpenCam->setObjectName(QStringLiteral("pushButton_OpenCam"));
        pushButton_OpenCam->setGeometry(QRect(10, 10, 100, 30));
        pushButton_StartGrab = new QPushButton(frame_CamOperate);
        pushButton_StartGrab->setObjectName(QStringLiteral("pushButton_StartGrab"));
        pushButton_StartGrab->setGeometry(QRect(120, 10, 100, 30));
        pushButton_StopGrab = new QPushButton(frame_CamOperate);
        pushButton_StopGrab->setObjectName(QStringLiteral("pushButton_StopGrab"));
        pushButton_StopGrab->setGeometry(QRect(120, 50, 100, 30));
        pushButton_CloseCam = new QPushButton(frame_CamOperate);
        pushButton_CloseCam->setObjectName(QStringLiteral("pushButton_CloseCam"));
        pushButton_CloseCam->setGeometry(QRect(10, 50, 100, 30));
        pushButton_ListDevice = new QPushButton(frame_CamOperate);
        pushButton_ListDevice->setObjectName(QStringLiteral("pushButton_ListDevice"));
        pushButton_ListDevice->setGeometry(QRect(230, 10, 100, 30));
        pushButton_GetImg = new QPushButton(frame_CamOperate);
        pushButton_GetImg->setObjectName(QStringLiteral("pushButton_GetImg"));
        pushButton_GetImg->setGeometry(QRect(230, 50, 100, 30));
        pushButton_CalibCam = new QPushButton(frame_CamOperate);
        pushButton_CalibCam->setObjectName(QStringLiteral("pushButton_CalibCam"));
        pushButton_CalibCam->setGeometry(QRect(340, 10, 100, 30));
        pushButton_PlaneFit = new QPushButton(frame_CamOperate);
        pushButton_PlaneFit->setObjectName(QStringLiteral("pushButton_PlaneFit"));
        pushButton_PlaneFit->setGeometry(QRect(340, 50, 100, 30));
        pushButton_ReadCalibParms = new QPushButton(frame_CamOperate);
        pushButton_ReadCalibParms->setObjectName(QStringLiteral("pushButton_ReadCalibParms"));
        pushButton_ReadCalibParms->setGeometry(QRect(450, 10, 100, 30));
        pushButton_ClearCalibParms = new QPushButton(frame_CamOperate);
        pushButton_ClearCalibParms->setObjectName(QStringLiteral("pushButton_ClearCalibParms"));
        pushButton_ClearCalibParms->setGeometry(QRect(450, 50, 100, 30));
        pushButton_MeasureSingleF = new QPushButton(frame_CamOperate);
        pushButton_MeasureSingleF->setObjectName(QStringLiteral("pushButton_MeasureSingleF"));
        pushButton_MeasureSingleF->setGeometry(QRect(560, 10, 100, 30));
        pushButton_MeasureContinuous = new QPushButton(frame_CamOperate);
        pushButton_MeasureContinuous->setObjectName(QStringLiteral("pushButton_MeasureContinuous"));
        pushButton_MeasureContinuous->setGeometry(QRect(560, 50, 100, 30));
        pushButton_SetBaseLine = new QPushButton(frame_CamOperate);
        pushButton_SetBaseLine->setObjectName(QStringLiteral("pushButton_SetBaseLine"));
        pushButton_SetBaseLine->setGeometry(QRect(670, 10, 100, 30));
        pushButton_ShowCurParams = new QPushButton(frame_CamOperate);
        pushButton_ShowCurParams->setObjectName(QStringLiteral("pushButton_ShowCurParams"));
        pushButton_ShowCurParams->setGeometry(QRect(670, 50, 100, 30));
        frame_WinInfo = new QFrame(CameraWindow);
        frame_WinInfo->setObjectName(QStringLiteral("frame_WinInfo"));
        frame_WinInfo->setGeometry(QRect(100, 10, 1700, 80));
        frame_WinInfo->setFrameShape(QFrame::StyledPanel);
        frame_WinInfo->setFrameShadow(QFrame::Raised);
        label_NumOfCam = new QLabel(frame_WinInfo);
        label_NumOfCam->setObjectName(QStringLiteral("label_NumOfCam"));
        label_NumOfCam->setGeometry(QRect(10, 10, 100, 30));
        label_CamIndex = new QLabel(frame_WinInfo);
        label_CamIndex->setObjectName(QStringLiteral("label_CamIndex"));
        label_CamIndex->setGeometry(QRect(10, 50, 100, 30));
        lineEdit_NumOfCam = new QLineEdit(frame_WinInfo);
        lineEdit_NumOfCam->setObjectName(QStringLiteral("lineEdit_NumOfCam"));
        lineEdit_NumOfCam->setGeometry(QRect(120, 10, 100, 30));
        lineEdit_CamIndex = new QLineEdit(frame_WinInfo);
        lineEdit_CamIndex->setObjectName(QStringLiteral("lineEdit_CamIndex"));
        lineEdit_CamIndex->setGeometry(QRect(120, 50, 100, 30));
        label_FilePath = new QLabel(frame_WinInfo);
        label_FilePath->setObjectName(QStringLiteral("label_FilePath"));
        label_FilePath->setGeometry(QRect(230, 10, 100, 30));
        lineEdit_FilePath = new QLineEdit(frame_WinInfo);
        lineEdit_FilePath->setObjectName(QStringLiteral("lineEdit_FilePath"));
        lineEdit_FilePath->setGeometry(QRect(340, 10, 200, 30));
        label_FileName = new QLabel(frame_WinInfo);
        label_FileName->setObjectName(QStringLiteral("label_FileName"));
        label_FileName->setGeometry(QRect(230, 50, 100, 30));
        lineEdit_FileName = new QLineEdit(frame_WinInfo);
        lineEdit_FileName->setObjectName(QStringLiteral("lineEdit_FileName"));
        lineEdit_FileName->setGeometry(QRect(340, 50, 200, 30));
        label_CalibrateData = new QLabel(frame_WinInfo);
        label_CalibrateData->setObjectName(QStringLiteral("label_CalibrateData"));
        label_CalibrateData->setGeometry(QRect(550, 10, 100, 30));
        lineEdit_CalibrateData = new QLineEdit(frame_WinInfo);
        lineEdit_CalibrateData->setObjectName(QStringLiteral("lineEdit_CalibrateData"));
        lineEdit_CalibrateData->setGeometry(QRect(660, 10, 100, 30));
        label_BoardWidth = new QLabel(frame_WinInfo);
        label_BoardWidth->setObjectName(QStringLiteral("label_BoardWidth"));
        label_BoardWidth->setGeometry(QRect(900, 10, 100, 30));
        lineEdit_BoardWidth = new QLineEdit(frame_WinInfo);
        lineEdit_BoardWidth->setObjectName(QStringLiteral("lineEdit_BoardWidth"));
        lineEdit_BoardWidth->setGeometry(QRect(1010, 10, 100, 30));
        label_BoardHeight = new QLabel(frame_WinInfo);
        label_BoardHeight->setObjectName(QStringLiteral("label_BoardHeight"));
        label_BoardHeight->setGeometry(QRect(900, 40, 100, 30));
        lineEdit_BoardHeight = new QLineEdit(frame_WinInfo);
        lineEdit_BoardHeight->setObjectName(QStringLiteral("lineEdit_BoardHeight"));
        lineEdit_BoardHeight->setGeometry(QRect(1010, 50, 100, 30));
        label_SquareSize = new QLabel(frame_WinInfo);
        label_SquareSize->setObjectName(QStringLiteral("label_SquareSize"));
        label_SquareSize->setGeometry(QRect(1120, 10, 100, 30));
        lineEdit_SquareSIze = new QLineEdit(frame_WinInfo);
        lineEdit_SquareSIze->setObjectName(QStringLiteral("lineEdit_SquareSIze"));
        lineEdit_SquareSIze->setGeometry(QRect(1230, 10, 100, 30));
        label_CalibrateDataNum = new QLabel(frame_WinInfo);
        label_CalibrateDataNum->setObjectName(QStringLiteral("label_CalibrateDataNum"));
        label_CalibrateDataNum->setGeometry(QRect(550, 50, 100, 30));
        lineEdit_CalibrateDataNum = new QLineEdit(frame_WinInfo);
        lineEdit_CalibrateDataNum->setObjectName(QStringLiteral("lineEdit_CalibrateDataNum"));
        lineEdit_CalibrateDataNum->setGeometry(QRect(660, 50, 100, 30));
        label_CalibLaserPlaneData = new QLabel(frame_WinInfo);
        label_CalibLaserPlaneData->setObjectName(QStringLiteral("label_CalibLaserPlaneData"));
        label_CalibLaserPlaneData->setGeometry(QRect(1120, 50, 100, 30));
        lineEdit_CalibLaserPlaneData = new QLineEdit(frame_WinInfo);
        lineEdit_CalibLaserPlaneData->setObjectName(QStringLiteral("lineEdit_CalibLaserPlaneData"));
        lineEdit_CalibLaserPlaneData->setGeometry(QRect(1230, 50, 100, 30));

        retranslateUi(CameraWindow);

        QMetaObject::connectSlotsByName(CameraWindow);
    } // setupUi

    void retranslateUi(QWidget *CameraWindow)
    {
        CameraWindow->setWindowTitle(QApplication::translate("CameraWindow", "Form", Q_NULLPTR));
        label_CurInput->setText(QApplication::translate("CameraWindow", "TextLabel", Q_NULLPTR));
        label_SampleImg->setText(QApplication::translate("CameraWindow", "TextLabel", Q_NULLPTR));
        label_ExplosureTime->setText(QApplication::translate("CameraWindow", "\346\233\235\345\205\211\346\227\266\351\227\264\357\274\210us\357\274\211", Q_NULLPTR));
        label_FpsSet->setText(QApplication::translate("CameraWindow", "\345\270\247\346\225\260\357\274\210fps\357\274\211", Q_NULLPTR));
        pushButton_ParamsSet->setText(QApplication::translate("CameraWindow", "\350\256\276\347\275\256\345\217\202\346\225\260", Q_NULLPTR));
        pushButton_ShiftToMainWindow->setText(QApplication::translate("CameraWindow", "\345\210\207\346\215\242\345\210\260\344\270\273\347\225\214\351\235\242", Q_NULLPTR));
        pushButton_TestGetSingleImg_Take->setText(QApplication::translate("CameraWindow", "\351\207\207\345\215\225\345\270\247", Q_NULLPTR));
        pushButton_OutputBaseLine->setText(QApplication::translate("CameraWindow", "\350\276\223\345\207\272\345\237\272\347\272\277\344\277\241\346\201\257", Q_NULLPTR));
        pushButton_ReadBaseLineInfo->setText(QApplication::translate("CameraWindow", "\350\257\273\345\217\226\345\237\272\347\272\277\344\277\241\346\201\257", Q_NULLPTR));
        pushButton_OpenCam->setText(QApplication::translate("CameraWindow", "\346\211\223\345\274\200\347\233\270\346\234\272", Q_NULLPTR));
        pushButton_StartGrab->setText(QApplication::translate("CameraWindow", "\345\274\200\345\247\213\351\207\207\351\233\206", Q_NULLPTR));
        pushButton_StopGrab->setText(QApplication::translate("CameraWindow", "\345\201\234\346\255\242\351\207\207\351\233\206", Q_NULLPTR));
        pushButton_CloseCam->setText(QApplication::translate("CameraWindow", "\345\205\263\351\227\255\347\233\270\346\234\272", Q_NULLPTR));
        pushButton_ListDevice->setText(QApplication::translate("CameraWindow", "\346\236\232\344\270\276\350\256\276\345\244\207", Q_NULLPTR));
        pushButton_GetImg->setText(QApplication::translate("CameraWindow", "\345\215\225\345\270\247\345\233\276\347\211\207\351\207\207\351\233\206", Q_NULLPTR));
        pushButton_CalibCam->setText(QApplication::translate("CameraWindow", "\347\233\270\346\234\272\344\270\200\351\224\256\346\240\207\345\256\232", Q_NULLPTR));
        pushButton_PlaneFit->setText(QApplication::translate("CameraWindow", "\346\277\200\345\205\211\345\271\263\351\235\242\346\240\207\345\256\232", Q_NULLPTR));
        pushButton_ReadCalibParms->setText(QApplication::translate("CameraWindow", "\350\257\273\345\217\226\346\240\207\345\256\232\345\217\202\346\225\260", Q_NULLPTR));
        pushButton_ClearCalibParms->setText(QApplication::translate("CameraWindow", "\346\270\205\347\251\272\346\240\207\345\256\232\345\217\202\346\225\260", Q_NULLPTR));
        pushButton_MeasureSingleF->setText(QApplication::translate("CameraWindow", "\345\215\225\345\270\247\346\265\213\351\207\217", Q_NULLPTR));
        pushButton_MeasureContinuous->setText(QApplication::translate("CameraWindow", "\350\277\236\347\273\255\346\265\213\351\207\217", Q_NULLPTR));
        pushButton_SetBaseLine->setText(QApplication::translate("CameraWindow", "\350\256\276\345\256\232\345\237\272\345\207\206\347\272\277", Q_NULLPTR));
        pushButton_ShowCurParams->setText(QApplication::translate("CameraWindow", "\346\230\276\347\244\272\345\275\223\345\211\215\345\217\202\346\225\260", Q_NULLPTR));
        label_NumOfCam->setText(QApplication::translate("CameraWindow", "\345\267\262\350\277\236\346\216\245\347\233\270\346\234\272\346\225\260", Q_NULLPTR));
        label_CamIndex->setText(QApplication::translate("CameraWindow", "\345\275\223\345\211\215\347\233\270\346\234\272\345\272\217\345\217\267", Q_NULLPTR));
        label_FilePath->setText(QApplication::translate("CameraWindow", "\346\226\207\344\273\266\345\255\230\345\202\250\344\275\215\347\275\256", Q_NULLPTR));
        label_FileName->setText(QApplication::translate("CameraWindow", "\346\226\207\344\273\266\344\277\235\345\255\230\345\220\215\347\247\260", Q_NULLPTR));
        label_CalibrateData->setText(QApplication::translate("CameraWindow", "\346\240\207\345\256\232\346\226\207\344\273\266\347\233\256\345\275\225", Q_NULLPTR));
        label_BoardWidth->setText(QApplication::translate("CameraWindow", "\346\240\207\345\256\232\346\235\277\345\256\275\350\247\222\347\202\271", Q_NULLPTR));
        label_BoardHeight->setText(QApplication::translate("CameraWindow", "\346\240\207\345\256\232\346\235\277\351\253\230\350\247\222\347\202\271", Q_NULLPTR));
        label_SquareSize->setText(QApplication::translate("CameraWindow", "\346\240\207\345\256\232\346\226\271\346\240\274\345\244\247\345\260\217", Q_NULLPTR));
        label_CalibrateDataNum->setText(QApplication::translate("CameraWindow", "\346\240\207\345\256\232\346\226\207\344\273\266\346\225\260\351\207\217", Q_NULLPTR));
        label_CalibLaserPlaneData->setText(QApplication::translate("CameraWindow", "\346\277\200\345\205\211\346\240\207\345\256\232\346\226\207\344\273\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CameraWindow: public Ui_CameraWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAWINDOW_H
