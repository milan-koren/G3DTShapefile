/*!
 * *****************************************************************
 *                             G3DTShapefile
 * *****************************************************************
 * \file shppointm.cpp
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "shppointm.h"


/*!
 * \brief Default constructor.
 */
ShpPointM::ShpPointM()
{
}


/*!
 * \brief Copy constructor.
 */
ShpPointM::ShpPointM(ShpPointM &pointM)
{
    copyFrom(pointM);
}


/*!
 * \brief Virtual destructor.
 */
ShpPointM::~ShpPointM()
{
    clean();
}


/*!
 * \brief Copy assignment operator.
 */
ShpPointM &ShpPointM::operator=(ShpPointM &pointM)
{
    copyFrom(pointM);
    return *this;
}


/*!
 * \brief Sets initial values to properties.
 */
void ShpPointM::destroy()
{
    clean();
    ShpPoint::destroy();
}


/*!
 * \brief Deep copy of CShpPointM.
 * \param pointM Source m-point shape.
 */
void ShpPointM::copyFrom(ShpPointM &pointM)
{
    ShpPoint::copyFrom(pointM);
    this->m = pointM.m;
}


/*!
 * \brief Returns measured point type.
 * \return PointM type.
 */
inline qint32 ShpPointM::getTypeId()
{
    return SHP_POINTM;
}


/*!
 * \brief Loads measured point from a shape-file.
 * \param shpFile Input file open for reading.
 * \param shpOffset Offset from shx-record.
 * \return True, if measured point was sucessfully loaded from a file.
 */
bool ShpPointM::load(QFile &shpFile, qint64 shpOffset)
{
    if (!ShpPoint::load(shpFile, shpOffset)) return false;
    if (shpFile.read(reinterpret_cast<char*>(&this->m), sizeof(double)) != sizeof(double)) return false;
    return true;
}

void ShpPointM::clean()
{
    this->m = 0.0;
}
