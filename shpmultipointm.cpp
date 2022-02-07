#include "shpmultipointm.h"

/*!
 * *****************************************************************
 *                             G3DTShapeFile
 * *****************************************************************
 * \file shpmultipointm.cpp
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
ShpMultiPointM::ShpMultiPointM()
{
}


/*!
 * \brief Copy constructor.
 */
ShpMultiPointM::ShpMultiPointM(ShpMultiPointM &multiPointM)
{
    copyFrom(multiPointM);
}


/*!
 * \brief Virtual destructor, calls Destroy().
 */
ShpMultiPointM::~ShpMultiPointM()
{
    clean();
}


/*!
 * \brief Copy assignment operator.
 */
ShpMultiPointM &ShpMultiPointM::operator=(ShpMultiPointM &multiPointM)
{
    copyFrom(multiPointM);
    return *this;
}


/*!
 * \brief Releases allocated memory.
 */
void ShpMultiPointM::destroy()
{
    clean();
    ShpMultiPoint::destroy();
}


/*!
 * \brief Deep copy of CShpMultiPointM.
 * \param point Source multi-point.
 */
void ShpMultiPointM::copyFrom(ShpMultiPointM &multiPointM)
{
    clean();
    ShpMultiPoint::copyFrom(multiPointM);
    this->m0 = multiPointM.m0;
    this->m1 = multiPointM.m1;
    if (0 < this->nPoints && multiPointM.m != nullptr)
    {
        this->m = new double[quint64(nPoints)];
        memcpy(reinterpret_cast<void*>(this->m), reinterpret_cast<void*>(multiPointM.m), quint64(nPoints) * sizeof(double));
    }
}


/*!
 * \brief Virtual function, returns shape type.
 * \return Measured multi-point type.
 */
inline qint32 ShpMultiPointM::getTypeId()
{
    return SHP_MULTIPOINTM;
}


/*!
 * \brief Loads measured multi-point from a shape-file.
 * \param shpFile Input file open for reading.
 * \param shpOffset Offset from shx-record.
 * \return True, if measured multi-point was sucessfully loaded from a file.
 */
bool ShpMultiPointM::load(QFile &shpFile, qint64 shpOffset)
{
    qint64 size;

    destroy();
    if (!ShpMultiPoint::load(shpFile, shpOffset)) return false;
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

void ShpMultiPointM::clean()
{
    this->m0 = DBL_MAX;
    this->m1 = -DBL_MAX;
    if (this->m != nullptr)
    {
        delete [] this->m;
        this->m = nullptr;
    }
}
