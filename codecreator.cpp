/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File codecreator.cpp
 * Version: 0.1
 * last modified: 2009-05-10
 *
 * License: GPL
 */

#include "codecreator.h"

CodeCreator::CodeCreator()
{
    str_code = "";
    closedCode = false;

    // these are older alternatives, but we don't use them
    //slTypes << "Microchip" << "XGLCD";
    //slTypes << "Microchip" << "XGLCD" << "glcd";
    //slTypes << "glcd" << "glcd_avr";

    slTypes << "glcd";

    outputType = CodeCreator::glcd;
}

void CodeCreator::append(QByteArray ba, int w, int h, QString comment)
{
    QString s;

    switch(outputType)
    {
        case CodeCreator::glcd:
            s.append(QString("\t"));
            for (int i=0; i<ba.size(); i++)
                s.append(QString("0x%1, ").arg((uchar)ba.at(i),2,16,QChar('0')));

            s.append(QString("  //%1 \n").arg(comment));
            str_code.append(s);
        break;

        case CodeCreator::glcd_avr:
            // not used
            for (int i=0; i<ba.size(); i++)
                s.append(QString("0x%1, ").arg((uchar)ba.at(i),2,16,QChar('0')));

            s.append(QString("  //%1 \n").arg(comment));
            str_code.append(s);
        break;

        default:
            str_code.append("//Sorry this output type isn't supported (yet)\n");
        break;
    }
}

void CodeCreator::clear(void)
{
    str_code = "";
}

QString CodeCreator::code()
{
    if (!closedCode) closeCode();

    return str_code;
}

void CodeCreator::closeCode(QString s)
{
    int li;

    li = str_code.lastIndexOf(",");

    str_code.remove(li,1);  // Remove last ","
    str_code.append(s);

    closedCode = true;
}

void CodeCreator::startCode(QString s)
{
    str_code.append(s);
}

void CodeCreator::setOutputType(QString type)
{
    setOutputType((CodeCreator::OutputType) slTypes.indexOf(type));
}

QStringList CodeCreator::availableTypes(void)
{
    return slTypes;
}
