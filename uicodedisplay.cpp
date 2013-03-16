/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File uicodedisplay.cpp
 * Version: 0.1
 * last modified: 2009-05-10
 *
 * License: GPL
 */

#include "uicodedisplay.h"
#include "ui_uicodedisplay.h"

UICodeDisplay::UICodeDisplay(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::UICodeDisplay)
{
    m_ui->setupUi(this);
}

UICodeDisplay::~UICodeDisplay()
{
    delete m_ui;
}

void UICodeDisplay::changeEvent(QEvent *e)
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

void UICodeDisplay::setText(QString s)
{
    m_ui->textBrowser->setText(s);
}
