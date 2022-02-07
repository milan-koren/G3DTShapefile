#ifndef SHPPOINT_H
#define SHPPOINT_H

#include "shpshape.h"

/*!
 * *****************************************************************
 *                            G3DTShapeFile
 * *****************************************************************
 * \file shppoint.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

class G3DTSHAPEFILE_EXPORT ShpPoint : public ShpShape
{
public:
    double x = 0.0;
    double y = 0.0;

public:
    ShpPoint();
    ShpPoint(ShpPoint &point);
    virtual ~ShpPoint() override;
    ShpPoint &operator=(ShpPoint &point);

    virtual void destroy() override;
    void copyFrom(ShpPoint &point);
    virtual qint32 getTypeId() override;

    virtual bool load(QFile &shpFile, qint64 shpOffset) override;

protected:
    void clean();
};

#endif // SHPPOINT_H
