#include "shpmultipatch.h"

/*!
 * \brief Default constructor.
 */
ShpMultiPatch::ShpMultiPatch()
{
}


/*!
 * \brief Copy constructor.
 */
ShpMultiPatch::ShpMultiPatch(ShpMultiPatch &multiPatch)
{
    copyFrom(multiPatch);
}


/*!
 * \brief Virtual destructor.
 */
ShpMultiPatch::~ShpMultiPatch()
{
    clean();
}


/*!
 * \brief Copy assignment operator.
 */
ShpMultiPatch &ShpMultiPatch::operator=(ShpMultiPatch &multiPatch)
{
    copyFrom(multiPatch);
    return *this;
}


/*!
 * \brief Releases allocated memory and sets initial values to object's properties.
 */
void ShpMultiPatch::destroy()
{
    clean();
    ShpPolyLineZ::destroy();
}


/*!
 * \brief Deep copy of CShpMultiPatch.
 * \param multiPatch Source multi-patch.
 */
void ShpMultiPatch::copyFrom(ShpMultiPatch &multiPatch)
{
    clean();
    ShpPolyLineZ::copyFrom(multiPatch);
    if (0 < this->nParts && multiPatch.partTypes != nullptr)
    {
        this->partTypes = new int[quint64(nParts)];
        memcpy(reinterpret_cast<void*>(this->partTypes), reinterpret_cast<void*>(multiPatch.partTypes), quint64(nParts) * sizeof(qint32));
    }
}


/*!
 * \brief Returns the shape type.
 * \return Multi-patch type.
 */
inline qint32 ShpMultiPatch::getTypeId()
{
    return SHP_MULTIPATCH;
}


/*!
 * \brief Loads multi-patch from a shape-file.
 * \param shpFile Input shape file.
 * \param shpOffset Offset from shx-record.
 * \return True, if shape was loaded successfully.
 */
bool ShpMultiPatch::load(QFile &shpFile, qint64 shpOffset)
{
    qint32 type;
    qint64 size;

    destroy();
    if (!shpFile.seek(2 * shpOffset + 8)) return false;
    if (shpFile.read(reinterpret_cast<char*>(&type), sizeof(qint32)) != sizeof(qint32)) return false;
    if (type != getTypeId()) return false;
    if (shpFile.read(reinterpret_cast<char*>(&this->box), sizeof(ShapeBox)) != sizeof(ShapeBox)) return false;
    if (shpFile.read(reinterpret_cast<char*>(&this->nParts), sizeof(qint32)) != sizeof(qint32)) return false;
    if (shpFile.read(reinterpret_cast<char*>(&this->nPoints), sizeof(qint32)) != sizeof(qint32)) return false;
    if (0 < this->nParts)
    {
        this->parts = new qint32[quint64(this->nParts)];
        size = qint64(this->nParts) * qint64(sizeof(qint32));
        if (shpFile.read(reinterpret_cast<char*>(this->parts), size) != size) return false;
        this->partTypes = new qint32[quint64(this->nParts)];
        if (shpFile.read(reinterpret_cast<char*>(this->partTypes), size) != size) return false;
    }
    if (0 < this->nPoints)
    {
        this->points = new ShapePoint[uint(this->nPoints)];
        size = qint64(this->nPoints) * qint64(sizeof(ShapePoint));
        if (shpFile.read(reinterpret_cast<char*>(this->points), size) != size) return false;
    }
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
        this->m = new double[quint64(nPoints)];
        size = qint64(this->nPoints) * qint64(sizeof(double));
        if (shpFile.read(reinterpret_cast<char*>(this->m), size) != size) return false;
    }

    return true;
}

/*!
 * \brief Releases resources allocated by the sub-class.
 */
void ShpMultiPatch::clean()
{
    if (this->partTypes != nullptr)
    {
        delete [] this->partTypes;
        this->partTypes = nullptr;
    }
}
