# -------------------------------------------------
# Project created by QtCreator 2009-05-05T21:17:08
# -------------------------------------------------
TARGET = GLCDTools
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    glcdpreview.cpp \
    EasyBMP/EasyBMP.cpp \
    uibitmapconversion.cpp \
    uifontcreation.cpp \
    glcdfont.cpp \
    uicodedisplay.cpp \
    codecreator.cpp \
    glcdcolors.cpp \
    uiinfo.cpp
HEADERS += mainwindow.h \
    glcdpreview.h \
    EasyBMP/EasyBMP_VariousBMPutilities.h \
    EasyBMP/EasyBMP_DataStructures.h \
    EasyBMP/EasyBMP_BMP.h \
    EasyBMP/EasyBMP.h \
    uibitmapconversion.h \
    uifontcreation.h \
    glcdfont.h \
    uicodedisplay.h \
    codecreator.h \
    glcdcolors.h \
    uiinfo.h \
    defines.h
FORMS += mainwindow.ui \
    uibitmapconversion.ui \
    uifontcreation.ui \
    uicodedisplay.ui \
    uiinfo.ui
RESOURCES += resources.qrc
RC_FILE = glcdtools.rc
