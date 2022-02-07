#include "shppolylinem.h"

/*!
 * \brief Default constructor.
 */
ShpPolyLineM::ShpPolyLineM()
{
}


/*!
 * \brief Copy assignment operator.
 */
ShpPolyLineM::ShpPolyLineM(ShpPolyLineM &polyLineM)
{
    copyFrom(polyLineM);
}


/*!
 * \brief Virtual destructor, calls Destroy().
 */
ShpPolyLineM::~ShpPolyLineM()
{
    clean();
}


/*!
 * \brief Copy assignment operator.
 */
ShpPolyLineM &ShpPolyLineM::operator=(ShpPolyLineM &polyLineM)
{
    copyFrom(polyLineM);
    return *this;
}


/*!
 * \brief Releases allocated memory.
 */
void ShpPolyLineM::destroy()
{
    clean();
    ShpPolyLine::destroy();
}


/*!
 * \brief Deep copy of CShpPolyLineM.
 * \param polyLineM Source poly-line.
 */
void ShpPolyLineM::copyFrom(ShpPolyLineM &polyLineM)
{
    clean();
    ShpPolyLine::copyFrom(polyLineM);
    this->m0 = polyLineM.m0;
    this->m1 = polyLineM.m1;
    if (0 < nPoints && polyLineM.m != nullptr)
    {
        this->m = new double[quint64(this->nPoints)];
        memcpy(reinterpret_cast<void*>(this->m), reinterpret_cast<void*>(polyLineM.m), quint64(this->nPoints) * sizeof(double));
    }
}


/*!
 * \brief Virtual function, returns shape type.
 * \return Measured poly-line type.
 */
inline qint32 ShpPolyLineM::getTypeId()
{
    return SHP_POLYLINEM;
}


/*!
 * \brief Loads measured poly-line from a shape-file.
 * \param shpFile Input file open for reading.
 * \param shpOffset Offset from shx-record.
 * \return True, if measured poly-line was sucessfully loaded from a file.
 */
bool ShpPolyLineM::load(QFile &shpFile, qint64 shpOffset)
{
    qint64 size;

    destroy();
    if (!ShpPolyLine::load(shpFile, shpOffset)) return false;
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

void ShpPolyLineM::clean()
{
    this->m0 = DBL_MAX;
    this->m1 = -DBL_MAX;
    if (this->m != nullptr)
    {
        delete [] this->m;
        this->m = nullptr;
    }
}
