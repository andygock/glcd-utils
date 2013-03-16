/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File uiinfo.cpp
 * Version: 0.1
 * last modified: 2009-05-10
 *
 * License: GPL
 */

#include "uiinfo.h"
#include "ui_uiinfo.h"

UIInfo::UIInfo(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::UIInfo)
{
    m_ui->setupUi(this);
}

UIInfo::~UIInfo()
{
    delete m_ui;
}

void UIInfo::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void UIInfo::setVersion(QString version)
{
    QString tmp;

    tmp = m_ui->label->text();

    tmp.replace("%VERSION%", version);
    m_ui->label->setText(tmp);
}
