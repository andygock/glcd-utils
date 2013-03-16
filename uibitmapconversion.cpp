/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File uibitmapconversion.cpp
 * Version: 0.1
 * last modified: 2009-05-10
 *
 * License: GPL
 */

#include "mainwindow.h"
#include "uibitmapconversion.h"
#include "ui_uibitmapconversion.h"

UIBitmapConversion::UIBitmapConversion(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::UIBitmapConversion)
{
    m_ui->setupUi(this);

    m_ui->cbColors->clear();
    m_ui->cbColors->addItems(glcdColors.colors());

    m_ui->glcdPreview->setGLCDSize(128,64);
    m_ui->glcdPreview->setGLCDColor(QColor(230, 230, 230));
}

UIBitmapConversion::~UIBitmapConversion()
{
    delete m_ui;
}

void UIBitmapConversion::changeEvent(QEvent *e)
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

void UIBitmapConversion::pickInputFile(void)
{
        QString vFileName, str;
        QFile file;
        QImage* img;
        QFileDialog fd;
        vFileName = QFileDialog::getOpenFileName(this, tr("Open File"), m_ui->leInputFilename->displayText(), tr("Windows Bitmap (*.bmp)"));

        if (vFileName != "")
        {
                m_ui->leInputFilename->setText(vFileName);

                img = &image;
                img->load(vFileName);
                m_ui->imagePreview->setPixmap(QPixmap::fromImage(image));
//                btnStart->setEnabled(true);

                bmpColWidth = (int)floor(img->width() / 8);
                bmpPageHeight = (int)ceil(img->height()  / 8);
                bmpSizeX = img->width();
                bmpSizeY = img->height();
        }
    }

unsigned char UIBitmapConversion::getbits(unsigned int x, int p, int n)
{
        return (x >> (p+1-n)) & 0x01;// & n;
}

void UIBitmapConversion::convert2GLCD(void)
{
        BMP imageIn, imageOutput;
        int targetWidth, targetHeight, bitDepth;
//	double coeff;
//	ifstream test;

        SetEasyBMPwarningsOn();
        targetWidth = bmpSizeX;
        targetHeight = bmpSizeY;

        imageIn.ReadFromFile(m_ui->leInputFilename->text().toLatin1().data());
        bitDepth = imageIn.TellBitDepth();
        if (bitDepth != 1)
        {
            imageOutput.SetSize( targetWidth , targetHeight );
            RangedPixelToPixelCopy( imageIn, 0, targetWidth-1, targetHeight-1, 0, imageOutput, 0,0);
            imageOutput.SetBitDepth( 1 );
            CreateGrayscaleColorTable( imageOutput );
            //	imageOutput.ReadFromFile(leInputFilename->text().toLatin1().data());

            createByteArray(imageOutput);
        }
        else
        {
            imageIn.SetBitDepth( 1 );
            CreateGrayscaleColorTable( imageIn );
            createByteArray(imageIn);
        }
        //createCCode(imageIn);
//        outputConvertedImage();
}

void UIBitmapConversion::showCCode(void)
{
//    CodeCreator cc;
    UICodeDisplay* cd;

    // Make sure image ist converted
    convert2GLCD();

    cc->clear();
    cc->startCode(QString("//size: %1x%2\nunsigned char icon[] = {\n")
             .arg(bmpSizeX)
             .arg(bmpSizeY)
             );

    cc->append(arrayGLCD, bmpSizeX, bmpSizeY);

    cc->closeCode("};");

    cd = new UICodeDisplay(this);
    cd->setText(cc->code());
    cd->show();
}

void UIBitmapConversion::createByteArray(BMP &image)
{
    int pages, single_lines, j, i, count;
    quint8 byte, bi;
    QString code,s;

    arrayGLCD.clear();

    pages=(int)image.TellHeight()/8;
    single_lines=image.TellHeight()-pages*8;
    j=0;
    count=bmpSizeX*(pages+single_lines);
    s.setNum(bmpSizeX);

    //whole pages
    while(j<pages)
    {
        i=0;
        while(i<image.TellWidth())
        {
            byte=0x00;
            for(bi=0;bi<8;bi++)
            {
                if((int)(image(i,j*8+bi)->Green)==0)
                { //pixel is black RGB=(0,0,0)
                    byte |= (1<<bi);
                }
            }
            arrayGLCD.append(byte);

            i++;
        }
        j++;
    }

    m_ui->glcdPreview->setGLCDSize(image.TellWidth(), image.TellHeight());
    m_ui->glcdPreview->setData(&arrayGLCD);
}

void UIBitmapConversion::setGLCDColor(QString c)
{
    m_ui->glcdPreview->setGLCDColor(glcdColors.color(c));
    m_ui->glcdPreview->update();
}
