QT -= gui

TEMPLATE = lib
DEFINES += G3DTSHAPEFILE_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Dbf/dbffile.cpp \
    Shp/shpmultipatch.cpp \
    Shp/shpmultipoint.cpp \
    Shp/shpmultipointm.cpp \
    Shp/shpmultipointz.cpp \
    Shp/shppoint.cpp \
    Shp/shppointm.cpp \
    Shp/shppointz.cpp \
    Shp/shppolygon.cpp \
    Shp/shppolygonm.cpp \
    Shp/shppolygonz.cpp \
    Shp/shppolyline.cpp \
    Shp/shppolylinem.cpp \
    Shp/shppolylinez.cpp \
    Shp/shpshape.cpp \
    shapefile.cpp

HEADERS += \
    Dbf/dbf.h \
    Dbf/dbfcolumndescriptor.h \
    Dbf/dbffile.h \
    Dbf/dbffilecolumndescriptor.h \
    Dbf/dbffileheader.h \
    Shp/shp.h \
    Shp/shpmultipatch.h \
    Shp/shpmultipoint.h \
    Shp/shpmultipointm.h \
    Shp/shpmultipointz.h \
    Shp/shppoint.h \
    Shp/shppointm.h \
    Shp/shppointz.h \
    Shp/shppolygon.h \
    Shp/shppolygonm.h \
    Shp/shppolygonz.h \
    Shp/shppolyline.h \
    Shp/shppolylinem.h \
    Shp/shppolylinez.h \
    Shp/shpshape.h \
    g3dtshapefile.h \
    g3dtshapefile_global.h \
    shapebox.h \
    shapefile.h \
    shapepoint.h

DISTFILES += \
    licence.txt

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
