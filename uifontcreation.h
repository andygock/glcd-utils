/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File uifontcreation.h
 * Version: 0.1
 * last modified: 2009-05-15
 *
 * License: GPL
 */

#ifndef UIFONTCREATION_H
#define UIFONTCREATION_H

#include <QtGui/QWidget>
#include <QListWidgetItem>
#include <QtDebug>
#include "glcdfont.h"
#include "codecreator.h"
#include "uicodedisplay.h"
#include "glcdcolors.h"
#include "defines.h"

extern CodeCreator* cc;

namespace Ui {
    class UIFontCreation;
}

class UIFontCreation : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(UIFontCreation)
public:
    explicit UIFontCreation(QWidget *parent = 0);
    virtual ~UIFontCreation();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::UIFontCreation *m_ui;

    GLCDFont* glcdFont;
    GLCDColors glcdColors;
    uchar startChar, endChar;

//    QList<strctTransform> charTransform;

private slots:
    void selectedItem(QListWidgetItem* lwi);
    void updateFont(void);
    void updateGLCDSize(void);
    void updateGLCDHeight(int h);
    void updateGLCDZoom(double z);
    void receivedErrorMessage(QString s);
    void updateCharList(void);
    void setGLCDColor(void);

    void incOffsetX(void);
    void incOffsetY(void);
    void decOffsetX(void);
    void decOffsetY(void);
    void rotateCCW(void);
    void rotateCW(void);
    void resetPostion(void);

    void showCode(void);
    void autoArrange(void);
signals:
    void error(QString s);
};

#endif // UIFONTCREATION_H
