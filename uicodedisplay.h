/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File uicodedisplay.h
 * Version: 0.1
 * last modified: 2009-05-10
 *
 * License: GPL
 */

#ifndef UICODEDISPLAY_H
#define UICODEDISPLAY_H

#include <QtWidgets/QDialog>

namespace Ui {
    class UICodeDisplay;
}

class UICodeDisplay : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(UICodeDisplay)
public:
    explicit UICodeDisplay(QWidget *parent = 0);
    virtual ~UICodeDisplay();
    void setText(QString s);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::UICodeDisplay *m_ui;
};

#endif // UICODEDISPLAY_H
