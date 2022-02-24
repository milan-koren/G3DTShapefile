#ifndef SHAPEPOINT_H
#define SHAPEPOINT_H

/*!
 * *****************************************************************
 *                            G3DTShapefile
 * *****************************************************************
 * \file shapepoint.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "g3dtshapefile_global.h"
#include "shapebox.h"

#pragma pack(2)

struct G3DTSHAPEFILE_EXPORT ShapePoint
{
    double x; //!< x-coordinate
    double y; //!< y-coordinate
};

#pragma pack()

#endif // SHAPEPOINT_H
