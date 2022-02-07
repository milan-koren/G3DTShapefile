#ifndef SHPMULTIPOINT_H
#define SHPMULTIPOINT_H

#include "shpshape.h"

/*!
 * *****************************************************************
 *                            G3DTShapeFile
 * *****************************************************************
 * \file shpmultipoint.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

class G3DTSHAPEFILE_EXPORT ShpMultiPoint : public ShpShape
{
public:
    ShapeBox box;
    qint32 nPoints = 0;
    ShapePoint *points = nullptr;

public:
    ShpMultiPoint();
    ShpMultiPoint(ShpMultiPoint &multiPoint);
    virtual ~ShpMultiPoint() override;
    ShpMultiPoint &operator=(ShpMultiPoint &multiPoint);

    virtual void destroy() override;
    void copyFrom(ShpMultiPoint &multiPoint);
    virtual qint32 getTypeId() override;

    virtual bool load(QFile &shpFile, qint64 shpOffset) override;

protected:
    void clean();
};

#endif // SHPMULTIPOINT_H
