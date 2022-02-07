#include "shppolygonm.h"

/*!
 * \brief Default constructor.
 */
ShpPolygonM::ShpPolygonM()
{
}


/*!
 * \brief Copy constructor.
 */
ShpPolygonM::ShpPolygonM(ShpPolygonM &polygonM)
{
    ShpPolyLineM::copyFrom(polygonM);
}


/*!
 * \brief Virtual destructor, calls Destroy().
 */
ShpPolygonM::~ShpPolygonM()
{
}


/*!
 * \brief Copy assignment operator.
 */
ShpPolygonM &ShpPolygonM::operator=(ShpPolygonM &polygonM)
{
    ShpPolyLineM::copyFrom(polygonM);
    return *this;
}


/*!
 * \brief Releases allocated memory.
 */
void ShpPolygonM::destroy()
{
    ShpPolyLineM::destroy();
}


/*!
 * \brief Virtual function, returns shape type.
 * \return Measured polygon type.
 */
inline qint32 ShpPolygonM::getTypeId()
{
    return SHP_POLYGONM;
}


/*!
 * \brief Calculates and returns the area of the polygon.
 * \return Polygon area.
 */
double ShpPolygonM::getArea()
{
    return calculatePolygonArea(this->nParts, this->nPoints, this->parts, this->points);
}

