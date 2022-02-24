#ifndef SHPPOLYGONZ_H
#define SHPPOLYGONZ_H

/*!
 * *****************************************************************
 *                            G3DTShapefile
 * *****************************************************************
 * \file shppolygonz.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "shppolylinez.h"

class G3DTSHAPEFILE_EXPORT ShpPolygonZ : public ShpPolyLineZ
{
public:
    ShpPolygonZ();
    ShpPolygonZ(ShpPolygonZ &polygonZ);
    virtual ~ShpPolygonZ() override;
    ShpPolygonZ &operator=(ShpPolygonZ &polygonZ);

    virtual void destroy() override;
    virtual qint32 getTypeId() override;
    virtual double getArea() override;
};

#endif // SHPPOLYGONZ_H
