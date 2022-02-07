#ifndef SHPPOLYGONM_H
#define SHPPOLYGONM_H

#include "shppolygon.h"
#include "shppolylinem.h"

/*!
 * *****************************************************************
 *                            G3DTShapeFile
 * *****************************************************************
 * \file shppolygonm.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

class G3DTSHAPEFILE_EXPORT ShpPolygonM : public ShpPolyLineM
{
public:
    ShpPolygonM();
    ShpPolygonM(ShpPolygonM &polygonM);
    virtual ~ShpPolygonM() override;
    ShpPolygonM &operator=(ShpPolygonM &polygonM);

    virtual void destroy() override;
    virtual qint32 getTypeId() override;
    virtual double getArea() override;
};

#endif // SHPPOLYGONM_H
