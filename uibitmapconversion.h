/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File uibitmapconversion.h
 * Version: 0.1
 * last modified: 2009-05-10
 *
 * License: GPL
 */

#ifndef UIBITMAPCONVERSION_H
#define UIBITMAPCONVERSION_H

#include <QtGui/QWidget>
#include <QFile>
#include <QFileDialog>
#include "EasyBMP/EasyBMP.h"
#include "codecreator.h"
#include "uicodedisplay.h"
#include "glcdcolors.h"
#include "defines.h"

extern CodeCreator* cc;

namespace Ui {
    class UIBitmapConversion;
}

class UIBitmapConversion : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(UIBitmapConversion)
public:
    explicit UIBitmapConversion(QWidget *parent = 0);
    virtual ~UIBitmapConversion();

        QImage image;
        unsigned char getbits(unsigned int x, int p, int n);
        char count, arrayLCD[1024];

        QByteArray arrayBmp, arrayGLCD;
        int bmpColWidth, bmpPageHeight;
        int bmpSizeX, bmpSizeY;
        //
        void createByteArray(BMP &image);
        void outputConvertedImage(void);


private slots:
        void pickInputFile();
        void convert2GLCD(void);
        void showCCode(void);
        void setGLCDColor(QString c);
//        void setGLCDPreviewColor(QString c);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::UIBitmapConversion *m_ui;
    GLCDColors glcdColors;
};

#endif // UIBITMAPCONVERSION_H
