/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File mainwindow.cpp
 * Version: 0.1
 * last modified: 2009-05-10
 *
 * License: GPL
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    QByteArray ba, ret;

    for (int i=0; i<(128*8); i++)
        ba.append(i);

    ui->setupUi(this);
    ui->cbCodeOuputType->clear();
    ui->cbCodeOuputType->addItems(cc->availableTypes());

    cc->setOutputType(ui->cbCodeOuputType->currentText());

    uiFontCreation = new UIFontCreation(this);
    uiFontCreation->hide();

    uiBitmapConversion = new UIBitmapConversion(this);
    uiBitmapConversion->hide();

    uiInfo = new UIInfo(this);
    uiInfo->setVersion(QString("%1.%2%3")
                       .arg(MAJOR_PROGRAM_VERSION)
                       .arg(MINOR_PROGRAM_VERSION)
                       .arg(ADDITIONAL_PROGRAM_VERSION)
                       );
    uiInfo->hide();

    bitmapConversionActive = false;
    fontCreationActive = false;

    connect(uiFontCreation, SIGNAL(error(QString)), this, SLOT(showMessage(QString)));
    connect(ui->actionInfo, SIGNAL(triggered()), this, SLOT(showInfo()));
//    ui->widget->setData(&ba);
//
//    ret = ui->widget->data();
//
//    ui->widget->setData(&ret);

//    gf = new GLCDFont(this);
//    gf->setFont(QFont("System", 6, QFont::Normal, false));
//    gf->setPixelSize(8, 16);
//    gf->setCharacter(QChar('0'));
//
//    ret.append(gf->data());
//    gf->setCharacter(0x31);
//    ret.append(gf->data());
//
//    ui->widget->setData(&ret);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showBitmapConversion(void)
{
    if (fontCreationActive)
    {
        ui->gridLayout->removeWidget(uiFontCreation);
        uiFontCreation->hide();
        fontCreationActive = false;
    }
    
    ui->gridLayout->addWidget(uiBitmapConversion,0,0,1,1);
    uiBitmapConversion->show();
    bitmapConversionActive = true;
}

void MainWindow::showFontCreation(void)
{
    if (bitmapConversionActive)
    {
        ui->gridLayout->removeWidget(uiBitmapConversion);
        uiBitmapConversion->hide();
        bitmapConversionActive = false;
    }

    ui->gridLayout->addWidget(uiFontCreation,0,0,1,1);
    uiFontCreation->show();
    fontCreationActive = true;
}

void MainWindow::showMessage(QString s)
{
    ui->statusBar->showMessage(s, 2000);
}

void MainWindow::showInfo(void)
{
    uiInfo->show();
}

void MainWindow::outputTypeChanged(QString s)
{
    QByteArray ba;
    const char sample[] = {0x00,0x01,0x04,0x01,0x00,0x08,0x20,0x02,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00};
    ba.append(sample,20);

    cc->setOutputType(s);
    cc->clear();
    cc->startCode("Output:\n");
    cc->append(ba,10,10,"");
    cc->closeCode("");

    // Load according image
    qDebug() << ":/Icons/CC"+s+".png";
    ui->imgCodeOutputType->setPixmap(QPixmap(QString(":/Icons/CC"+s+".png")));
    ui->ccOutputSample->clear();
    ui->ccOutputSample->setText(cc->code());
}
