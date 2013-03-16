/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File codecreator.h
 * Version: 0.1
 * last modified: 2009-05-10
 *
 * License: GPL
 */

#ifndef CODECREATOR_H
#define CODECREATOR_H

#include <QObject>
#include <QStringList>

class CodeCreator : public QObject
{
    Q_OBJECT
public:
    CodeCreator();

    enum type {
        Microchip = 0x00,
        XGLCD = 0x01,
        glcd = 0x02
    };
    Q_DECLARE_FLAGS(OutputType, type)

    ~CodeCreator() {}
    void clear(void);
    void append(QByteArray ba, int w, int h, QString comment = "");
    QString code(void);
    void closeCode(QString s="");
    void startCode(QString s);
    void setOutputType(OutputType t) {outputType = t;}
    void setOutputType(QString type);
    QStringList availableTypes(void);
private:
    QString str_code;
    bool closedCode;
    OutputType outputType;
    QStringList slTypes;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(CodeCreator::OutputType)

#endif // CODECREATOR_H
