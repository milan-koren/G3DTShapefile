/*!
 * *****************************************************************
 *                             G3DTShapefile
 * *****************************************************************
 * \file shppolygonz.cpp
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "shppolygonz.h"


/*!
 * \brief Default constructor.
 */
ShpPolygonZ::ShpPolygonZ()
{
}


/*!
 * \brief Copy constructor.
 */
ShpPolygonZ::ShpPolygonZ(ShpPolygonZ &polygonZ)
{
    ShpPolyLineZ::copyFrom(polygonZ);
}


/*!
 * \brief Virtual destructor, calls Destroy().
 */
ShpPolygonZ::~ShpPolygonZ()
{
}


/*!
 * \brief Copy assignment operator.
 */
ShpPolygonZ &ShpPolygonZ::operator=(ShpPolygonZ &polygonZ)
{
    ShpPolyLineZ::copyFrom(polygonZ);
    return *this;
}


/*!
 * \brief Releases allocated memory.
 */
void ShpPolygonZ::destroy()
{
    ShpPolyLineZ::destroy();
}


/*!
 * \brief Virtual function, returns shape type.
 * \return Measured polygon type.
 */
inline qint32 ShpPolygonZ::getTypeId()
{
    return SHP_POLYGONZ;
}


/*!
 * \brief Calculates and returns the area of the polygon.
 * \return Polygon area.
 */
double ShpPolygonZ::getArea()
{
    return calculatePolygonArea(this->nParts, this->nPoints, this->parts, this->points);
}

