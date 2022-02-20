QT -= gui

TEMPLATE = lib
DEFINES += G3DTSHAPEFILE_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbffile.cpp \
    shapefile.cpp \
    shpmultipatch.cpp \
    shpmultipoint.cpp \
    shpmultipointm.cpp \
    shpmultipointz.cpp \
    shppoint.cpp \
    shppointm.cpp \
    shppointz.cpp \
    shppolygon.cpp \
    shppolygonm.cpp \
    shppolygonz.cpp \
    shppolyline.cpp \
    shppolylinem.cpp \
    shppolylinez.cpp \
    shpshape.cpp

HEADERS += \
    dbfcolumndescriptor.h \
    dbffile.h \
    dbffilecolumndescriptor.h \
    dbffileheader.h \
    g3dtshapefile.h \
    g3dtshapefile_global.h \
    shapebox.h \
    shapefile.h \
    shapepoint.h \
    shpmultipatch.h \
    shpmultipoint.h \
    shpmultipointm.h \
    shpmultipointz.h \
    shppoint.h \
    shppointm.h \
    shppointz.h \
    shppolygon.h \
    shppolygonm.h \
    shppolygonz.h \
    shppolyline.h \
    shppolylinem.h \
    shppolylinez.h \
    shpshape.h

DISTFILES += \
    licence.txt

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
