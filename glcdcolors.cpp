/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File glcdcolors.cpp
 * Version: 0.1
 * last modified: 2009-05-10
 *
 * License: GPL
 */

#include "glcdcolors.h"

GLCDColors::GLCDColors()
{
    sl.clear();

    sl.append("red");
    sl.append("blue");
    sl.append("white");
    sl.append("green");
    sl.append("yellow");
    sl.append("brown");
}

QColor GLCDColors::color(QString name)
{
    QColor color;

    if (name == "red")
    {
        color.setRgb(255, 0, 0);
    }
    else if (name == "blue")
    {
        color.setRgb(0, 32, 255);
    }
    else if (name == "white")
    {
        color.setRgb(230, 230, 230);
    }
    else if (name == "green")
    {
        color.setRgb(32, 255, 32);
    }
    else if (name == "yellow")
        color.setRgb(255,255,0);
    else if (name == "brown")
        color.setRgb(128,64,0);
    else
    {
        color.setRgb(0, 32, 255);
    }

    return color;
}
