#include "shppolyline.h"

/*!
 * \brief Default constructor.
 */
ShpPolyLine::ShpPolyLine()
{
}


/*!
 * \brief Copy constructor.
 */
ShpPolyLine::ShpPolyLine(ShpPolyLine &polyLine)
{
    copyFrom(polyLine);
}


/*!
 * \brief Virtual destructor.
 */
ShpPolyLine::~ShpPolyLine()
{
    clean();
}


/*!
 * \brief Copy assignment operator.
 */
ShpPolyLine &ShpPolyLine::operator=(ShpPolyLine &polyLine)
{
    copyFrom(polyLine);
    return *this;
}


/*!
 * \brief Releases allocated memory and sets initial values to object's properties.
 */
void ShpPolyLine::destroy()
{
    clean();
    ShpShape::destroy();
}


/*!
 * \brief Deep copy of CShpPolyLine.
 * \param polyLine Source poly-line.
 */
void ShpPolyLine::copyFrom(ShpPolyLine &polyLine)
{
    clean();
    this->nParts = polyLine.nParts;
    if (0 < this->nParts && polyLine.parts != nullptr)
    {
        this->parts = new qint32[quint64(this->nParts)];
        memcpy(reinterpret_cast<void*>(this->parts), reinterpret_cast<void*>(polyLine.parts), quint64(this->nParts) * quint64(sizeof(qint32)));
    }
    this->nPoints = polyLine.nPoints;
    if (0 < this->nPoints && polyLine.points != nullptr)
    {
        this->points = new ShapePoint[quint64(this->nPoints)];
        memcpy(reinterpret_cast<void*>(this->points), reinterpret_cast<void*>(polyLine.points), quint64(this->nPoints) * quint64(sizeof(ShapePoint)));
    }
}


/*!
 * \brief Returns the shape type.
 * \return PolyLine type.
 */
inline qint32 ShpPolyLine::getTypeId()
{
    return SHP_POLYLINE;
}


/*!
 * \brief Calculates and returns the length of a poly-line. Also used to calculate polygon's perimeter.
 * \return Poly-line length.
 */
double ShpPolyLine::getLength()
{
    return calculateLineLength(this->nParts, this->nPoints, this->parts, this->points);
}


/*!
 * \brief Loads poly-line from a shape-file. Also used to load polygon from a shape-file.
 * \param shpFile Input shape file.
 * \param shpOffset Offset from shx-record.
 * \return True, if shape was loaded successfully.
 */
bool ShpPolyLine::load(QFile &shpFile, qint64 shpOffset)
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
    }
    if (0 < this->nPoints)
    {
        this->points = new ShapePoint[quint64(this->nPoints)];
        size = qint64(this->nPoints) * qint64(sizeof(ShapePoint));
        if (shpFile.read(reinterpret_cast<char*>(this->points), size) != size) return false;
    }
    return true;
}

void ShpPolyLine::clean()
{
    if (this->parts != nullptr)
    {
        delete [] this->parts;
        this->parts = nullptr;
        this->nParts = 0;
    }
    if (this->points != nullptr)
    {
        delete [] this->points;
        this->points = nullptr;
        this->nPoints = 0;
    }
}
