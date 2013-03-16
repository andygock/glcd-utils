/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File mainwindow.h
 * Version: 0.1
 * last modified: 2009-05-10
 *
 * License: GPL
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "glcdfont.h"
#include "uifontcreation.h"
#include "uibitmapconversion.h"
#include "uiinfo.h"
#include "codecreator.h"
#include "defines.h"
extern CodeCreator* cc;

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    UIFontCreation* uiFontCreation;
    UIBitmapConversion* uiBitmapConversion;
    UIInfo* uiInfo;

    bool bitmapConversionActive;
    bool fontCreationActive;

private slots:
//    void showMainWindow(void);
    void showBitmapConversion(void);
    void showFontCreation(void);
    void showMessage(QString s);
    void showInfo(void);
    void outputTypeChanged(QString s);
};

#endif // MAINWINDOW_H
