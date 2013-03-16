/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File uifontcreation.cpp
 * Version: 0.2
 * last modified: 2009-05-15
 *
 * License: GPL
 */

#include "mainwindow.h"
#include "uifontcreation.h"
#include "ui_uifontcreation.h"

UIFontCreation::UIFontCreation(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::UIFontCreation)
{
    glcdFont = new GLCDFont(this);

    m_ui->setupUi(this);

    m_ui->glcdColor->clear();
    m_ui->glcdColor->addItems(glcdColors.colors());
    updateCharList();

    glcdFont->setPixelSize(m_ui->glcdWidth->value(), m_ui->glcdHeight->value());
    updateFont();

    m_ui->scrollArea->setWidget(glcdFont->glcdWidget());

    connect(m_ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectedItem(QListWidgetItem*)));

    connect(glcdFont, SIGNAL(error(QString)), this, SLOT(receivedErrorMessage(QString)));

    setGLCDColor();
}

UIFontCreation::~UIFontCreation()
{
    delete m_ui;
}

void UIFontCreation::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void UIFontCreation::selectedItem(QListWidgetItem* lwi)
{
    QString s;

    s = lwi->text();

    glcdFont->setCharacter(s.toLocal8Bit().at(0));
    glcdFont->updateGLCD();
    qDebug() << "bounding rect: " << glcdFont->boundingRect();
    qDebug() << "Selected '" << s << "'";
}


void UIFontCreation::updateFont(void)
{
    QFont f;

    f = m_ui->fontComboBox->currentFont();
    f.setBold(false);
    f.setItalic(false);

    if (Qt::Checked == m_ui->cbBold->checkState())    f.setBold(true);
    if (Qt::Checked == m_ui->cbItalic->checkState())  f.setItalic(true);

    f.setPointSize(m_ui->fontSize->value());

    glcdFont->setFont(f);
}

void UIFontCreation::updateGLCDSize(void)
{
    glcdFont->setPixelSize(m_ui->glcdWidth->value(), m_ui->glcdHeight->value());
}

void UIFontCreation::updateGLCDHeight(int h)
{
}

void UIFontCreation::updateGLCDZoom(double z)
{
    glcdFont->glcdWidget()->setZoomFactor(z);
}

void UIFontCreation::receivedErrorMessage(QString s)
{
    emit error(s);
}

void UIFontCreation::incOffsetX(void)
{
    glcdFont->incOffsetX();
}

void UIFontCreation::incOffsetY(void)
{
    glcdFont->incOffsetY();
}

void UIFontCreation::decOffsetX(void)
{
    glcdFont->decOffsetX();
}

void UIFontCreation::decOffsetY(void)
{
    glcdFont->decOffsetY();
}

void UIFontCreation::rotateCCW(void)
{
    glcdFont->rotateCCW();
}

void UIFontCreation::rotateCW(void)
{
    glcdFont->rotateCW();
}

void UIFontCreation::showCode(void)
{
//    CodeCreator cc;
    UICodeDisplay* cd;
//    CodeCreator* cc;
//
//    cc = parent->cc;

    cc->clear();
    cc->startCode(QString("//size: %1x%2\nunsigned char font%3[] = {\n")
                 .arg(m_ui->glcdWidth->value())
                 .arg(m_ui->glcdHeight->value())
                 .arg(m_ui->fontComboBox->currentText().replace(" ", "")));

    m_ui->progressBar->setMaximum(endChar-startChar);
    m_ui->progressBar->setValue(0);

    for (uchar c=startChar; c<=endChar; c++)
    {
        glcdFont->setCharacter(c);
        cc->append(glcdFont->data(), m_ui->glcdWidth->value(), m_ui->glcdHeight->value(), QString("Char %1").arg(QString(c)));
        m_ui->progressBar->setValue(c-startChar);
    }
    cc->closeCode("};");
    cd = new UICodeDisplay(this);
    cd->setText(cc->code());
    cd->show();
}

void UIFontCreation::updateCharList(void)
{
    m_ui->listWidget->clear();
    startChar = (uchar)m_ui->sbStartChar->value();
    endChar = (uchar)m_ui->sbEndChar->value();

    for (uchar c=startChar; c<=endChar; c++)
        m_ui->listWidget->addItem(
                QString("%1 (%2)").arg(QChar(c).toLatin1())
                                    .arg((uchar)c,2,10,QChar('0'))
                );
}

void UIFontCreation::resetPostion(void)
{
    glcdFont->resetPosition();
}

void UIFontCreation::setGLCDColor(void)
{
    QString c;
    QColor color;

    c = m_ui->glcdColor->currentText();

    glcdFont->setGLCDColor(glcdColors.color(c));
}

void UIFontCreation::autoArrange(void)
{
    int minX, minY, maxX, maxY;
    int currentWidth, currentHeight;
    QRect r;

    glcdFont->setOffsetX(0);
    glcdFont->setOffsetY(0);

    m_ui->progressBar->setMaximum(endChar-startChar);
    m_ui->progressBar->setValue(0);

    currentHeight = m_ui->glcdHeight->value();
    currentWidth  = m_ui->glcdWidth->value();

    minX = minY = 999;
    maxX = maxY = 0;
    for (uchar c=startChar; c<=endChar; c++)
    {
        glcdFont->setCharacter(QChar(c));
//        glcdFont->updateGLCD();
        r = glcdFont->boundingRect();

        if (r.x() < minX)    minX = r.x();
        if (r.y() < minY)    minY = r.y();

        if ((r.width() + r.x()) > maxX)     maxX = (r.width() + r.x());
        if ((r.height() + r.y()) > maxY)    maxY = (r.height() + r.y());

        m_ui->progressBar->setValue(c-startChar);
    }

    qDebug() << "offX:" << minX << ";offY:"<< minY<< ";maxX:"<< maxX << ";maxY:"<<maxY;
    qDebug() << "current height: " << m_ui->glcdHeight->value();
    qDebug() << "Setting y offset to " << m_ui->glcdHeight->value() - maxY;

    switch(glcdFont->getRotation())
    {
        case 0:
            glcdFont->setOffsetX(0 - minX);
            glcdFont->setOffsetY(0 - minY);
        break;

        case 90:
            glcdFont->setOffsetX(0);
            glcdFont->setOffsetY(0);
        break;

        case 180:
            glcdFont->setOffsetX(0);
            glcdFont->setOffsetY(0);
        break;

        case 270:
            glcdFont->setOffsetX(0 - minX);
            glcdFont->setOffsetY(currentHeight - maxY);
        break;

        default: break;

    }

//    glcdFont->setPixelSize((maxX-minX), (maxY-minY));
    m_ui->glcdHeight->setValue((maxY-minY));
    m_ui->glcdWidth->setValue((maxX-minX));

    glcdFont->updateChar();
}
