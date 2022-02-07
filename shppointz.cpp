#include "shppointz.h"

/*!
 * \brief Default constructor.
 */
ShpPointZ::ShpPointZ()
{
}


/*!
 * \brief Copy constructor.
 */
ShpPointZ::ShpPointZ(ShpPointZ &pointZ)
{
    copyFrom(pointZ);
}


/*!
 * \brief Virtual destructor.
 */
ShpPointZ::~ShpPointZ()
{
    clean();
}


/*!
 * \brief Copy assignment operator.
 */
ShpPointZ &ShpPointZ::operator=(ShpPointZ &pointZ)
{
    copyFrom(pointZ);
    return *this;
}


/*!
 * \brief Sets initial values to properties.
 */
void ShpPointZ::destroy()
{
    clean();
    ShpPointM::destroy();
}


/*!
 * \brief Deep copy of CShpPointZ.
 * \param pointZ Source z-point shape.
 */
void ShpPointZ::copyFrom(ShpPointZ &pointZ)
{
    ShpPointM::copyFrom(pointZ);
    z = pointZ.z;
}


/*!
 * \brief Returns z-point type.
 * \return PointZ type.
 */
inline qint32 ShpPointZ::getTypeId()
{
    return SHP_POINTZ;
}


/*!
 * \brief Loads z-point from a shape-file.
 * \param shpFile Input file open for reading.
 * \param shpOffset Offset from shx-record.
 * \return True, if z-point was sucessfully loaded from a file.
 * \remark Cannot call CShpPointM::Load, because of z and m order. z must be read first.
 */
bool ShpPointZ::load(QFile &shpFile, qint64 shpOffset)
{
    if (!ShpPoint::load(shpFile, shpOffset)) return false;
    if (shpFile.read(reinterpret_cast<char*>(&z), sizeof(double)) != sizeof(double)) return false;
    if (shpFile.read(reinterpret_cast<char*>(&m), sizeof(double)) != sizeof(double)) return false;
    return true;
}

void ShpPointZ::clean()
{
    z = 0.0;
}
