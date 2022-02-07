#include "shppolylinez.h"

/*!
 * *****************************************************************
 *                             G3DTShapeFile
 * *****************************************************************
 * \file shppolylinez.cpp
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
ShpPolyLineZ::ShpPolyLineZ()
{
}


/*!
 * \brief Copy assignment operator.
 */
ShpPolyLineZ::ShpPolyLineZ(ShpPolyLineZ &polyLineZ)
{
    copyFrom(polyLineZ);
}


/*!
 * \brief Virtual destructor, calls Destroy().
 */
ShpPolyLineZ::~ShpPolyLineZ()
{
    clean();
}


/*!
 * \brief Copy assignment operator.
 */
ShpPolyLineZ &ShpPolyLineZ::operator=(ShpPolyLineZ &polyLineZ)
{
    copyFrom(polyLineZ);
    return *this;
}


/*!
 * \brief Releases allocated memory.
 */
void ShpPolyLineZ::destroy()
{
    clean();
    ShpPolyLineM::destroy();
}


/*!
 * \brief Deep copy of CShpPolyLineZ.
 * \param polyLineM Source poly-line.
 */
void ShpPolyLineZ::copyFrom(ShpPolyLineZ &polyLineZ)
{
    clean();
    ShpPolyLineM::copyFrom(polyLineZ);
    this->z0 = polyLineZ.z0;
    this->z1 = polyLineZ.z1;
    if (0 < this->nPoints && polyLineZ.z != nullptr)
    {
        this->z = new double[quint64(this->nPoints)];
        memcpy(reinterpret_cast<void*>(this->z), reinterpret_cast<void*>(polyLineZ.z), quint64(this->nPoints) * sizeof(double));
    }
}


/*!
 * \brief Virtual function, returns shape type.
 * \return Measured poly-line type.
 */
inline qint32 ShpPolyLineZ::getTypeId()
{
    return SHP_POLYLINEZ;
}


/*!
 * \brief Loads measured z-poly-line from a shape-file.
 * \param shpFile Input file open for reading.
 * \param shpOffset Offset from shx-record.
 * \return True, if measured z-poly-line was sucessfully loaded from a file.
 */
bool ShpPolyLineZ::load(QFile &shpFile, qint64 shpOffset)
{
    qint64 size;

    destroy();
    if (!ShpPolyLineM::load(shpFile, shpOffset)) return false;
    if (shpFile.read(reinterpret_cast<char*>(&this->z0), sizeof(double)) != sizeof(double)) return false;
    if (shpFile.read(reinterpret_cast<char*>(&this->z1), sizeof(double)) != sizeof(double)) return false;
    if (0 < this->nPoints)
    {
        this->z = new double[quint64(this->nPoints)];
        size = qint64(this->nPoints) * qint64(sizeof(double));
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

void ShpPolyLineZ::clean()
{
    this->z0 = DBL_MAX;
    this->z1 = -DBL_MAX;
    if (this->z != nullptr)
    {
        delete [] this->z;
        this->z = nullptr;
    }
}
