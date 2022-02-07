#ifndef SHPMULTIPATCH_H
#define SHPMULTIPATCH_H

#include "shppolylinez.h"

/*!
 * *****************************************************************
 *                            G3DTShapeFile
 * *****************************************************************
 * \file shpmultipatch.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

class G3DTSHAPEFILE_EXPORT ShpMultiPatch : public ShpPolyLineZ
{
    qint32 *partTypes = nullptr;

public:
    ShpMultiPatch();
    ShpMultiPatch(ShpMultiPatch &multiPatch);
    virtual ~ShpMultiPatch() override;
    ShpMultiPatch &operator=(ShpMultiPatch &multiPatch);

    virtual void destroy() override;
    void copyFrom(ShpMultiPatch &multiPatch);
    virtual qint32 getTypeId() override;

    virtual bool load(QFile &shpFile, qint64 shpOffset) override;

protected:
    void clean();
};

#endif // SHPMULTIPATCH_H
