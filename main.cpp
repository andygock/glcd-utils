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
 * Todo:
 *  - Offsets für Buchstaben separat speichern
 *  - Automatische Anpassung der Breite/Höhe
 *  - Verschieben der Toolbar klappt nicht immer an alle seiten
 *  - Performance probleme schriftartentool bei großem GLCD
 *  - QImage größe dem benötigten boundingRect des Chars anpassen
 */

#include <QtGui/QApplication>
#include <QPlastiqueStyle>
#include "mainwindow.h"
#include "codecreator.h"
#include "defines.h"

CodeCreator* cc;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStyle* style;

    cc = new CodeCreator();
    style = new QPlastiqueStyle();
    a.setStyle(style);

//    style->polish(&a);
    a.setPalette(style->standardPalette());

    MainWindow w;
    w.show();
    return a.exec();
}
