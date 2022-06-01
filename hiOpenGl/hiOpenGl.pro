#TEMPLATE = app
CONFIG += console c++11
#CONFIG -= app_bundle
#CONFIG -= qt

INCLUDEPATH += $$PWD/FuckingGlad/include
DEPENDPATH += $$PWD/FuckingGlad/include

INCLUDEPATH += $$PWD/glm
DEPENDPATH += $$PWD/glm

LIBS += -lopengl32 -lglu32 -lgdi32

QT += opengl
QT += core

SOURCES += \
        main.cpp\
        $$PWD/FuckingGlad/glad.c \
        stb_image.cpp


INCLUDEPATH += $$PWD/../../glfw-3.3.2.bin.WIN64/include/GLFW

HEADERS += \
    ../../glfw-3.3.2.bin.WIN64/include/GLFW/glfw3.h \
    ../../glfw-3.3.2.bin.WIN64/include/GLFW/glfw3native.h \
    ShaderClass.h\
    camera.h \
    stb_image.h


win32: LIBS += -L$$PWD/../../glfw-3.3.2.bin.WIN64/lib-mingw-w64/ -lglfw3 -lglfw3dll -lgdi32

INCLUDEPATH += $$PWD/../../glfw-3.3.2.bin.WIN64/lib-mingw-w64
DEPENDPATH += $$PWD/../../glfw-3.3.2.bin.WIN64/lib-mingw-w64

#win32: LIBS += -L$$PWD/../../glfw-3.3.2.bin.WIN64/lib-mingw-w64/ -lglfw3dll

#INCLUDEPATH += $$PWD/../../glfw-3.3.2.bin.WIN64/lib-mingw-w64
#DEPENDPATH += $$PWD/../../glfw-3.3.2.bin.WIN64/lib-mingw-w64

#win32: LIBS += -L$$PWD/../../Ot/Tools/mingw810_64/x86_64-w64-mingw32/lib/ -lgdi32

#INCLUDEPATH += $$PWD/../../Ot/Tools/mingw810_64/x86_64-w64-mingw32/include
#DEPENDPATH += $$PWD/../../Ot/Tools/mingw810_64/x86_64-w64-mingw32/include

RESOURCES += \
    Shaders.qrc

