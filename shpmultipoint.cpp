#include "shpmultipoint.h"

/*!
 * *****************************************************************
 *                             G3DTShapeFile
 * *****************************************************************
 * \file shpmultipoint.cpp
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
ShpMultiPoint::ShpMultiPoint()
{
}


/*!
 * \brief Copy constructor.
 */
ShpMultiPoint::ShpMultiPoint(ShpMultiPoint &multiPoint)
{
    copyFrom(multiPoint);
}


/*!
 * \brief Virtual destructor, calls Destroy().
 */
ShpMultiPoint::~ShpMultiPoint()
{
    clean();
}


/*!
 * \brief Copy assignment operator.
 */
ShpMultiPoint &ShpMultiPoint::operator=(ShpMultiPoint &multiPoint)
{
    copyFrom(multiPoint);
    return *this;
}


/*!
 * \brief Releases allocated memory.
 */
void ShpMultiPoint::destroy()
{
    clean();
    ShpShape::destroy();
}


/*!
 * \brief Deep copy of CShpMultiPoint.
 * \param point Source multi-point.
 */
void ShpMultiPoint::copyFrom(ShpMultiPoint &multiPoint)
{
    clean();
    if (0 < multiPoint.nPoints && multiPoint.points != nullptr)
    {
        this->nPoints = multiPoint.nPoints;
        this->points = new ShapePoint[quint64(nPoints)];
        memcpy(reinterpret_cast<void*>(this->points), reinterpret_cast<void*>(multiPoint.points), quint64(this->nPoints) * sizeof(ShapePoint));
    }
}


/*!
 * \brief Virtual function, returns shape type.
 * \return Multi-point type.
 */
inline qint32 ShpMultiPoint::getTypeId()
{
    return SHP_MULTIPOINT;
}


/*!
 * \brief Loads multi-point from a shape-file.
 * \param shpFile Input file open for reading.
 * \param shpOffset Offset from shx-record.
 * \return True, if multi-point was sucessfully loaded from a file.
 */
bool ShpMultiPoint::load(QFile &shpFile, qint64 shpOffset)
{
    qint32 type;
    qint64 size;

    destroy();
    if (!shpFile.seek(2 * shpOffset + 8)) return false;
    if (shpFile.read(reinterpret_cast<char*>(&type), sizeof(qint32)) != sizeof(qint32)) return false;
    if (type != getTypeId()) return false;
    if (shpFile.read(reinterpret_cast<char*>(&this->box), sizeof(ShapeBox)) != sizeof(ShapeBox)) return false;
    if (shpFile.read(reinterpret_cast<char*>(&this->nPoints), sizeof(qint32)) != sizeof(qint32)) return false;
    if (0 < this->nPoints)
    {
        this->points = new ShapePoint[quint64(this->nPoints)];
        size = qint64(nPoints) * qint64(sizeof(ShapePoint));
        if (shpFile.read(reinterpret_cast<char*>(this->points), size) != size) return false;
    }
    return true;
}

void ShpMultiPoint::clean()
{
    if (this->points != nullptr)
    {
        delete [] this->points;
        this->points = nullptr;
        this->nPoints = 0;
    }
}
