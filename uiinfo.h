/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File uiinfo.h
 * Version: 0.1
 * last modified: 2009-05-10
 *
 * License: GPL
 */

#ifndef UIINFO_H
#define UIINFO_H

#include <QtWidgets/QDialog>

namespace Ui {
    class UIInfo;
}

class UIInfo : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(UIInfo)
public:
    explicit UIInfo(QWidget *parent = 0);
    virtual ~UIInfo();
    void setVersion(QString version);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::UIInfo *m_ui;
};

#endif // UIINFO_H
