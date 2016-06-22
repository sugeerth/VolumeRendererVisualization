#-------------------------------------------------
#
# Project created by QtCreator 2014-09-03T21:03:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

CONFIG += c++11

TARGET = VolumeRayCasting
TEMPLATE = app


SOURCES += main.cpp\
    GLWidget.cpp \
    GLShaderProgram.cpp \
    GLArrayBuffer.cpp \
    GLFramebuffer.cpp \
    GLTexture.cpp \
    GLVertexArray.cpp \
    transparencysliders.cpp \
    transfer.cpp

HEADERS  += GLWidget.h \
    Mat.h \
    MathUtil.h \
    Vec.h \
    GLShaderProgram.h \
    GLArrayBuffer.h \
    GLConfig.h \
    GLFramebuffer.h \
    GLTexture.h \
    GLVertexArray.h \
    transparencysliders.h \
    transfer.h

OTHER_FILES += \
    VolumeRayCasting.frag \
    VolumeRayCasting.vert \
    SampleVolume.raw \
    PreIntVertex.vert \
    PreIntFrag.frag \
    ambientOcclusion.vert \
    ambientOcclusion.frag

Data.files += $$OTHER_FILES

macx {
    Data.path = Contents/MacOS
    QMAKE_BUNDLE_DATA += Data
    QMAKE_MAC_SDK = macosx10.9
}

win32 {
    Data.path = $$OUT_PWD
    INSTALLS += Data
    LIBS += -L$$PWD/glew/ -lglew32
    INCLUDEPATH += $$PWD/glew
    DEPENDPATH += $$PWD/glew
    PRE_TARGETDEPS += $$PWD/glew/glew32.lib
    DESTDIR = $$OUT_PWD
}

unix:!macx {
    Data.path = $$OUT_PWD
    INSTALLS += Data
    LIBS += -lGLEW
}

FORMS += \
    transparencysliders.ui \
    transfer.ui
