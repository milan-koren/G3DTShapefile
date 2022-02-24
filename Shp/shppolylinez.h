#ifndef SHPPOLYLINEZ_H
#define SHPPOLYLINEZ_H

/*!
 * *****************************************************************
 *                            G3DTShapefile
 * *****************************************************************
 * \file shppolylinez.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "shppolylinem.h"


class G3DTSHAPEFILE_EXPORT ShpPolyLineZ : public ShpPolyLineM
{
public:
    double z0 = DBL_MAX;
    double z1 = -DBL_MAX;
    double *z = nullptr;

public:
    ShpPolyLineZ();
    ShpPolyLineZ(ShpPolyLineZ &polyLineM);
    virtual ~ShpPolyLineZ() override;
    ShpPolyLineZ &operator=(ShpPolyLineZ &polyLineZ);

    virtual void destroy() override;
    void copyFrom(ShpPolyLineZ &polyLineZ);
    virtual qint32 getTypeId() override;

    virtual bool load(QFile &shpFile, qint64 shpOffset) override;

protected:
    void clean();
};

#endif // SHPPOLYLINEZ_H
