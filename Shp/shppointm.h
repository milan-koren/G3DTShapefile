#ifndef SHPPOINTM_H
#define SHPPOINTM_H

/*!
 * *****************************************************************
 *                            G3DTShapefile
 * *****************************************************************
 * \file shppointm.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "shppoint.h"


class G3DTSHAPEFILE_EXPORT ShpPointM : public ShpPoint
{
public:
    double m = 0.0;

public:
    ShpPointM();
    ShpPointM(ShpPointM &pointM);
    virtual ~ShpPointM() override;
    ShpPointM &operator=(ShpPointM &pointM);

    virtual void destroy() override;
    void copyFrom(ShpPointM &pointM);
    virtual qint32 getTypeId() override;

    virtual bool load(QFile &shpFile, qint64 shpOffset) override;

protected:
    void clean();
};

#endif // SHPPOINTM_H
