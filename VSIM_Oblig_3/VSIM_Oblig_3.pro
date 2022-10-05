QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17
TARGET      = 3D-programmering

SOURCES += main.cpp \
    logger.cpp \
    mainwindow.cpp \
    renderwindow.cpp \
    rollingball.cpp \
    shader.cpp \
    camera.cpp \
    objmesh.cpp \
    surfacemesh.cpp \
    texture.cpp \
    vector3d.cpp \
    vertex.cpp \
    visualobject.cpp \
    visualpoint.cpp

HEADERS += \
    logger.h \
    mainwindow.h \
    renderwindow.h \
    rollingball.h \
    shader.h \
    camera.h \
    objmesh.h \
    surfacemesh.h \
    texture.h \
    vector3d.h \
    vertex.h \
    visualobject.h \
    visualpoint.h
FORMS += \
    mainwindow.ui

DISTFILES += \
    plainshader.frag \
    plainshader.vert \
    heightshader.frag\
    heightshader.vert\
    textureshader.frag \
    textureshsder.vert \
    lightshader.frag \
    lightshader.vert

