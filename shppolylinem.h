#ifndef SHPPOLYLINEM_H
#define SHPPOLYLINEM_H

#include "shppolyline.h"

/*!
 * *****************************************************************
 *                            G3DTShapeFile
 * *****************************************************************
 * \file shppolylinem.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

class G3DTSHAPEFILE_EXPORT ShpPolyLineM : public ShpPolyLine
{
public:
    double m0 = DBL_MAX;
    double m1 = -DBL_MAX;
    double *m = nullptr;

public:   
    ShpPolyLineM();
    ShpPolyLineM(ShpPolyLineM &polyLineM);
    virtual ~ShpPolyLineM() override;
    ShpPolyLineM &operator=(ShpPolyLineM &polyLineM);

    virtual void destroy() override;
    void copyFrom(ShpPolyLineM &polyLineM);
    virtual qint32 getTypeId() override;

    virtual bool load(QFile &shpFile, qint64 shpOffset) override;

protected:
    void clean();
};

#endif // SHPPOLYLINEM_H
