#include "shppoint.h"

/*!
 * *****************************************************************
 *                             G3DTShapeFile
 * *****************************************************************
 * \file shppoint.cpp
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */


/*!
 * \brief Default constructor.
 */
ShpPoint::ShpPoint()
{
}

/*!
 * \brief Copy constructor.
 */
ShpPoint::ShpPoint(ShpPoint &point)
{
    copyFrom(point);
}


/*!
 * \brief Virtual destructor.
 */
ShpPoint::~ShpPoint()
{
    clean();
}


/*!
 * \brief Copy assignment operator.
 */
ShpPoint &ShpPoint::operator=(ShpPoint &point)
{
    copyFrom(point);
    return *this;
}


/*!
 * \brief Sets initial values to properties.
 */
void ShpPoint::destroy()
{
    clean();
    ShpShape::destroy();
}


/*!
 * \brief Deep copy of CShpPoint.
 * \param point Source point shape.
 */
void ShpPoint::copyFrom(ShpPoint &point)
{
    this->x = point.x;
    this->y = point.y;
}


/*!
 * \brief Virtual function, returns shape type.
 * \return Shape type.
 */
inline qint32 ShpPoint::getTypeId()
{
    return SHP_POINT;
}


/*!
 * \brief Loads point from a shape-file.
 * \param shpFile Input file open for reading.
 * \param shpOffset Offset from shx-record.
 * \return True, if point was sucessfully loaded from a file.
 */
bool ShpPoint::load(QFile &shpFile, qint64 shpOffset)
{
    qint32 type;

    if (!shpFile.seek(2 * shpOffset + 8)) return false;
    if (shpFile.read(reinterpret_cast<char*>(&type), sizeof(qint32)) != sizeof(qint32)) return false;
    if (type != getTypeId()) return false;
    if (shpFile.read(reinterpret_cast<char*>(&this->x), sizeof(double)) != sizeof(double)) return false;
    if (shpFile.read(reinterpret_cast<char*>(&this->y), sizeof(double)) != sizeof(double)) return false;
    return true;
}


/*!
 * \brief Set default values.
 */
void ShpPoint::clean()
{
    this->x = 0.0;
    this->y = 0.0;
}
