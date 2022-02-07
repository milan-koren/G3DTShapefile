#include "shpmultipointz.h"

/*!
 * *****************************************************************
 *                             G3DTShapeFile
 * *****************************************************************
 * \file shpmultipointz.cpp
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
ShpMultiPointZ::ShpMultiPointZ()
{
}


/*!
 * \brief Copy constructor.
 */
ShpMultiPointZ::ShpMultiPointZ(ShpMultiPointZ &multiPointZ)
{
    copyFrom(multiPointZ);
}


/*!
 * \brief Virtual destructor, calls Destroy().
 */
ShpMultiPointZ::~ShpMultiPointZ()
{
    clean();
}


/*!
 * \brief Copy assignment operator.
 */
ShpMultiPointZ &ShpMultiPointZ::operator=(ShpMultiPointZ &multiPointZ)
{
    copyFrom(multiPointZ);
    return *this;
}


/*!
 * \brief Releases allocated memory.
 */
void ShpMultiPointZ::destroy()
{
    clean();
    ShpMultiPointM::destroy();
}


/*!
 * \brief Deep copy of CShpMultiPointZ.
 * \param point Source multi-point.
 */
void ShpMultiPointZ::copyFrom(ShpMultiPointZ &multiPointZ)
{
    clean();
    ShpMultiPointM::copyFrom(multiPointZ);
    this->z0 = multiPointZ.z0;
    this->z1 = multiPointZ.z1;
    if (0 < this->nPoints && multiPointZ.z != nullptr)
    {
        z = new double[quint64(this->nPoints)];
        memcpy(reinterpret_cast<void*>(z), reinterpret_cast<void*>(multiPointZ.z), quint64(this->nPoints) * sizeof(double));
    }
}


/*!
 * \brief Virtual function, returns shape type.
 * \return MultiPointZ type.
 */
inline qint32 ShpMultiPointZ::getTypeId()
{
    return SHP_MULTIPOINTZ;
}


/*!
 * \brief Loads measured z-multi-point from a shape-file.
 * \param shpFile Input file open for reading.
 * \param shpOffset Offset from shx-record.
 * \return True, if measured z-multi-point was sucessfully loaded from a file.
 * \remark Cannot call CShpMultiPointM::Load, because of z and m order. z must be read first.
 */
bool ShpMultiPointZ::load(QFile &shpFile, qint64 shpOffset)
{
    qint64 size;

    destroy();
    if (!ShpMultiPoint::load(shpFile, shpOffset)) return false;
    if (shpFile.read(reinterpret_cast<char*>(&this->z0), sizeof(double)) != sizeof(double)) return false;
    if (shpFile.read(reinterpret_cast<char*>(&this->z1), sizeof(double)) != sizeof(double)) return false;
    if (0 < this->nPoints)
    {
        z = new double[quint64(nPoints)];
        size = qint64(nPoints) * qint64(sizeof(double));
        if (shpFile.read(reinterpret_cast<char*>(this->z), size) != size) return false;
    }
    if (shpFile.read(reinterpret_cast<char*>(&this->m0), sizeof(double)) != sizeof(double)) return false;
    if (shpFile.read(reinterpret_cast<char*>(&this->m1), sizeof(double)) != sizeof(double)) return false;
    if (0 < this->nPoints)
    {
        this->m = new double[quint64(this->nPoints)];
        size = qint64(this->nPoints) * qint64(sizeof(double));
        if (shpFile.read(reinterpret_cast<char*>(this->m), size) != size) return false;
    }
    return true;
}

void ShpMultiPointZ::clean()
{
    this->z0 = DBL_MAX;
    this->z1 = -DBL_MAX;
    if (this->z != nullptr)
    {
        delete [] this->z;
        this->z = nullptr;
    }
}
