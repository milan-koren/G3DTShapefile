#ifndef SHAPEBOX_H
#define SHAPEBOX_H

/*!
 * *****************************************************************
 *                            G3DTShapefile
 * *****************************************************************
 * \file shapebox.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "g3dtshapefile_global.h"

#pragma pack(2)

struct G3DTSHAPEFILE_EXPORT ShapeBox
{
    double x0;          //!< little-endian, minimal x-coordinate
    double y0;          //!< little-endian, minimal y-coordinate
    double x1;          //!< little-endian, maximal x-coordinate
    double y1;          //!< little-endian, maximal y-coordinate
};

#pragma pack()

#endif // SHAPEBOX_H
