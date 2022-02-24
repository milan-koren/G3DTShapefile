#ifndef SHPMULTIPOINTM_H
#define SHPMULTIPOINTM_H

/*!
 * *****************************************************************
 *                            G3DTShapefile
 * *****************************************************************
 * \file shpmultipointm.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "shpmultipoint.h"


class G3DTSHAPEFILE_EXPORT ShpMultiPointM : public ShpMultiPoint
{
public:
    double m0 = DBL_MAX;
    double m1 = -DBL_MAX;
    double *m = nullptr;

public:
    ShpMultiPointM();
    ShpMultiPointM(ShpMultiPointM &multiPointM);
    virtual ~ShpMultiPointM() override;
    ShpMultiPointM &operator=(ShpMultiPointM &multiPointM);

    virtual void destroy() override;
    void copyFrom(ShpMultiPointM &multiPointM);
    virtual qint32 getTypeId() override;

    virtual bool load(QFile &shpFile, qint64 shpOffset) override;

protected:
    void clean();
};

#endif // SHPMULTIPOINTM_H
