#ifndef SHPMULTIPOINTZ_H
#define SHPMULTIPOINTZ_H

/*!
 * *****************************************************************
 *                            G3DTShapefile
 * *****************************************************************
 * \file shpmultipointz.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "shpmultipointm.h"


class G3DTSHAPEFILE_EXPORT ShpMultiPointZ : public ShpMultiPointM
{
public:
    double z0 = DBL_MAX;
    double z1 = -DBL_MAX;
    double *z = nullptr;

public:
    ShpMultiPointZ();
    ShpMultiPointZ(ShpMultiPointZ &multiPointZ);
    virtual ~ShpMultiPointZ() override;
    ShpMultiPointZ &operator=(ShpMultiPointZ &multiPointZ);

    virtual void destroy() override;
    void copyFrom(ShpMultiPointZ &multiPointZ);
    virtual qint32 getTypeId() override;

    virtual bool load(QFile &shpFile, qint64 shpOffset) override;

protected:
    void clean();
};

#endif // SHPMULTIPOINTZ_H
