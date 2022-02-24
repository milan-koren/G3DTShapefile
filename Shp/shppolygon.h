#ifndef SHPPOLYGON_H
#define SHPPOLYGON_H

/*!
 * *****************************************************************
 *                            G3DTShapefile
 * *****************************************************************
 * \file shppolygon.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "shppolyline.h"


class G3DTSHAPEFILE_EXPORT ShpPolygon : public ShpPolyLine
{
public:
    ShpPolygon();
    ShpPolygon(ShpPolygon &polygon);
    virtual ~ShpPolygon() override;
    ShpPolygon &operator=(ShpPolygon &polygon);

    virtual qint32 getTypeId() override;
    virtual double getArea() override;
};

#endif // SHPPOLYGON_H
