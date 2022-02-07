#ifndef SHPPOINTZ_H
#define SHPPOINTZ_H

#include "shppointm.h"

/*!
 * *****************************************************************
 *                           G3DTShapeFile
 * *****************************************************************
 * \file shppointz.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

class G3DTSHAPEFILE_EXPORT ShpPointZ : public ShpPointM
{
public:
    double z = 0.0;

public:
    ShpPointZ();
    ShpPointZ(ShpPointZ &pointZ);
    virtual ~ShpPointZ() override;
    ShpPointZ &operator=(ShpPointZ &pointZ);

    virtual void destroy() override;
    void copyFrom(ShpPointZ &pointZ);
    virtual qint32 getTypeId() override;

    virtual bool load(QFile &shpFile, qint64 shpOffset) override;

protected:
    void clean();
};

#endif // SHPPOINTZ_H
