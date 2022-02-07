#ifndef SHPSHAPE_H
#define SHPSHAPE_H

#include <g3dtshapefile_global.h>
#include <QtCore>
#include <QFile>

/*!
 * *****************************************************************
 *                            G3DTShapeFile
 * *****************************************************************
 * \file shpshape.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */


#define SHP_NONE		(0)
#define SHP_POINT		(1)
#define SHP_POINTZ		(11)
#define SHP_POINTM		(21)
#define SHP_MULTIPOINT	(8)
#define SHP_MULTIPOINTZ	(18)
#define SHP_MULTIPOINTM	(28)
#define SHP_POLYLINE	(3)
#define SHP_POLYLINEZ	(13)
#define SHP_POLYLINEM	(23)
#define SHP_POLYGON		(5)
#define SHP_POLYGONZ	(15)
#define SHP_POLYGONM	(25)
#define SHP_MULTIPATCH	(31)


#pragma pack(2)

struct G3DTSHAPEFILE_EXPORT ShapeBox
{
    double x0;          //!< little-endian, minimal x-coordinate
    double y0;          //!< little-endian, minimal y-coordinate
    double x1;          //!< little-endian, maximal x-coordinate
    double y1;          //!< little-endian, maximal y-coordinate
};

struct G3DTSHAPEFILE_EXPORT ShapePoint
{
    double x; //!< x-coordinate
    double y; //!< y-coordinate
};

#pragma pack()


class G3DTSHAPEFILE_EXPORT ShpShape
{
public:
    ShpShape();
    ShpShape(ShpShape &shp);
    virtual ~ShpShape();
    ShpShape &operator=(ShpShape &shp);

    virtual void destroy();
    virtual qint32 getTypeId();
    virtual double getLength();
    virtual double getArea();
    virtual char *toWKB();
    virtual bool load(QFile &shpFile, qint64 shpOffset);

protected:
    double calculateLineLength(qint32 nParts, qint32 nPoints, qint32 *parts, ShapePoint *points);
    double calculatePolygonArea(qint32 nParts, qint32 nPoints, qint32 *parts, ShapePoint *points);
};

#endif // SHPSHAPE_H
