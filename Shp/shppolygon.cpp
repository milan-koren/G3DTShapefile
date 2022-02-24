/*!
 * *****************************************************************
 *                             G3DTShapefile
 * *****************************************************************
 * \file shppolygon.cpp
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "shppolygon.h"


/*!
 * \brief Default constructor.
 */
ShpPolygon::ShpPolygon()
{
}


/*!
 * \brief Copy constructor.
 */
ShpPolygon::ShpPolygon(ShpPolygon &polygon)
{
    copyFrom(polygon);
}


/*!
 * \brief Virtual destructor.
 */
ShpPolygon::~ShpPolygon()
{
}


/*!
 * \brief Copy assignment operator.
 */
ShpPolygon &ShpPolygon::operator=(ShpPolygon &polygon)
{
    copyFrom(polygon);
    return *this;
}


/*!
 * \brief Returns the shape type.
 * \return Polygon type.
 */
inline qint32 ShpPolygon::getTypeId()
{
    return SHP_POLYGON;
}


/*!
 * \brief Calculates and returns the area of the polygon.
 * \return Polygon area.
 */
inline double ShpPolygon::getArea()
{
    return calculatePolygonArea(this->nParts, this->nPoints, this->parts, this->points);
}
