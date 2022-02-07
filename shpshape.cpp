#include "shpshape.h"

/*!
 * \brief Default constructor.
 */
ShpShape::ShpShape()
{
}

/*!
 * \brief Copy constructor.
 */
ShpShape::ShpShape(ShpShape &)
{
}

/*!
 * \brief Virtual destructor.
 */
ShpShape::~ShpShape()
{
}


/*!
 * \brief Copy assignment operator.
 */
ShpShape &ShpShape::operator=(ShpShape &)
{
    return *this;
}


/*!
 * \brief Virtual function. Releases allocated memory and sets initial values to object's properties.
 */
void ShpShape::destroy()
{
}


/*!
 * \brief Virtual function, returns the shape type.
 * \return Shape type.
 */
inline qint32 ShpShape::getTypeId()
{
    return SHP_NONE;
}

/*!
 * \brief Calculates and returns the length of the shape.
 * \return Shape length.
 */
double ShpShape::getLength()
{
    return 0.0;
}

/*!
 * \brief Calculates and returns the area of the shape.
 * \return Shape area.
 */
double ShpShape::getArea()
{
    return 0.0;
}

/*!
 * \brief Conversion to WKB format.
 * \return Shape in WKB format.
 */
char *ShpShape::toWKB()
{
    return nullptr;
}

/*!
 * \brief Loads shape from a shape-file.
 * \param shpFile Input shape file.
 * \param shpOffset Offset from shx-record.
 * \return True, if object was loaded successfully.
 */
bool ShpShape::load(QFile &, qint64)
{
    return false;
}

/*!
 * \brief Calculates polyline length or polygon perimeter.
 * \param nParts Number of parts.
 * \param nPoints Number of points.
 * \param parts Pointer to parts.
 * \param points Pointer to points.
 * \return Polyline length or polygon perimeter.
 */
double ShpShape::calculateLineLength(qint32 nParts, qint32 nPoints, qint32 *parts, ShapePoint *points)
{
    double l;
    qint32 partLastPoint;
    double dx, dy;

    l = 0.0;
    if (parts != nullptr && points != nullptr)
    {
        for(qint32 iPart=0; iPart < nParts; iPart++)
        {
            if (iPart == (nParts -1))
            {
                // last part
                partLastPoint = nPoints - 1;
            }
            else
            {
                partLastPoint = parts[iPart+1] - 1;
            }
            for(qint32 iPoint=parts[iPart]; iPoint < partLastPoint; iPoint++)
            {
                dx = points[iPoint].x - points[iPoint+1].x;
                dy = points[iPoint].y - points[iPoint+1].y;
                l += sqrt(dx*dx + dy*dy);
            }
        }
    }
    return l;
}

/*!
 * \brief Calculates and returns the area of the polygon.
 * \return Polygon area.
 * \remark It supposed, outter ring's vertices are stored clockwise, and inner ring's vertices are stored counter-clockwise.
 */
double ShpShape::calculatePolygonArea(qint32 nParts, qint32 nPoints, qint32 *parts, ShapePoint *points)
{
    double polygonArea;
    double partArea;
    qint32 lastPartPoint;

    polygonArea = 0.0;
    if (parts != nullptr && points != nullptr)
    {
        for(qint32 iPart=0; iPart < nParts; iPart++)
        {
            partArea = 0.0;
            if (iPart == (nParts -1))
            {
                // last part
                lastPartPoint = nPoints - 1;
            }
            else
            {
                lastPartPoint = parts[iPart+1] - 1;
            }
            for(qint32 iPoint=parts[iPart]; iPoint < lastPartPoint; iPoint++)
            {
                partArea += (points[iPoint].x * points[iPoint+1].y - points[iPoint+1].x * points[iPoint].y) / 2.0;
            }
            polygonArea += partArea;
        }
    }

    return fabs(polygonArea);
}
