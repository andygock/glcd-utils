/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File main.cpp
 * Version: 0.1
 * last modified: 2009-05-10
 *
 * License: GPL
 *
 */

#include "mainwindow.h"
#include "codecreator.h"
#include "defines.h"
#include <QtWidgets/QApplication>
//#include <QFusionStyle>

CodeCreator* cc;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    //QStyle* style;

    cc = new CodeCreator();
    //style = new QFusionStyle();
    //a.setStyle(style);

	//style->polish(&a);
    //a.setPalette(style->standardPalette());

    MainWindow w;
    w.show();
    return a.exec();
}
