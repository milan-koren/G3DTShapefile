#ifndef SHPPOLYLINE_H
#define SHPPOLYLINE_H

/*!
 * *****************************************************************
 *                            G3DTShapefile
 * *****************************************************************
 * \file shppolyline.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "shpshape.h"


class G3DTSHAPEFILE_EXPORT ShpPolyLine : public ShpShape
{
public:
    ShapeBox box;
    qint32 nParts = 0;
    qint32 nPoints = 0;
    qint32 *parts = nullptr;
    ShapePoint *points = nullptr;

public:
    ShpPolyLine();
    ShpPolyLine(ShpPolyLine &polyLine);
    virtual ~ShpPolyLine() override;
    ShpPolyLine &operator=(ShpPolyLine &polyLine);

    virtual void destroy() override;
    void copyFrom(ShpPolyLine &polyLine);
    virtual qint32 getTypeId() override;
    virtual double getLength() override;

    virtual bool load(QFile &shpFile, qint64 shpOffset) override;

protected:
    void clean();
};

#endif // SHPPOLYLINE_H
