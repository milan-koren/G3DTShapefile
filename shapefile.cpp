#include <QtEndian>
#include "shapefile.h"

/*!
 * *****************************************************************
 *                             G3DTShapeFile
 * *****************************************************************
 * \file shapefile.cpp
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
ShapeFile::ShapeFile()
{
}


/*!
 * \brief Virtual destructor.
 */
ShapeFile::~ShapeFile()
{
    close();
}


/*!
 * \brief Closes open files (shp, shx, dbf) and releases allocated memory.
 */
void ShapeFile::close()
{
    this->shpFile.close();
    this->shxFile.close();
    if (this->shx != nullptr)
    {
        delete [] this->shx;
        this->shx = nullptr;
    }
    this->dbf.close();
}


/*!
 * \brief Opens shape-file in RW mode and reads shx records into memory.
 * \param fileName Shape-file full path.
 * \return True, if all files were sucessfully open.
 */
bool ShapeFile::open(QString fileName)
{
    close();
    this->shpFile.setFileName(changeFileExtension(fileName, SHP_SHPFILE_EXT));
    if (this->shpFile.open(QFile::ReadWrite))
    {
        this->shpFile.read(reinterpret_cast<char*>(&this->shpFileHeader), sizeof(ShpFileHeader));
        toLittleEndian(&this->shpFileHeader);
        this->dbf.open(changeFileExtension(fileName, DBF_FILE_EXT));
        return loadShx(fileName);
    }
    return false;
}


/*!
 * \brief Checks if shape-file is open.
 * \return If shape-file is open returns true;
 */
inline bool ShapeFile::isOpen()
{
    return this->dbf.isOpen() && this->shpFile.isOpen() && this->shxFile.isOpen();
}


/*!
 * \brief Number of all records (valid and deleted) in associated DBF.
 * \return Number of records.
 */
inline qint64 ShapeFile::countAllRecords()
{
    return this->dbf.countAllRecords();
}


/*!
 * \brief Number of deleted records in associated DBF.
 * \return Number of deleted records.
 */
inline qint64 ShapeFile::countDeletedRecords()
{
    return this->dbf.countDeletedRecords();
}


/*!
 * \brief Number of valid records in associated DBF.
 * \return Number of valid records.
 */
inline qint64 ShapeFile::countValidRecords()
{
    return this->dbf.countValidRecords();
}


/*!
 * \brief Number of columns in associated DBF.
 * \return Number of DBF columns.
 */
inline qint32 ShapeFile::countColumns()
{
    return this->dbf.countColumns();
}


/*!
 * \brief Returns the type of stored shapes. All shapes in file should be of the same type.
 * \return Type of stored shapes.
 */
inline int ShapeFile::getShapeType()
{
    if (this->shpFile.isOpen()) return this->shpFileHeader.shapeType;
    return SHP_NONE;
}


/*!
 * \brief Checks if a given record is valid.
 * \param recordIndex The index of record.
 * \return If record is valid returns true, false otherwise.
 */
inline bool ShapeFile::isValid(qint64 recordIndex)
{
    return this->dbf.isValid(recordIndex);
}


/*!
 * \brief Checks if a given record is deleted.
 * \param recordIndex The index of record.
 * \return If record is valid returns false, true otherwise.
 */
inline bool ShapeFile::isDeleted(qint64 recordIndex)
{
    return this->dbf.isDeleted(recordIndex);
}


/*!
 * \brief Creates shape object of shape-file type.
 * \return Pointer to created shape, or nullptr.
 */
ShpShape *ShapeFile::createShape()
{
    ShpShape *shp = nullptr;

    if (isOpen())
    {
        switch (getShapeType())
        {
            case SHP_POINT:
                shp = new ShpPoint();
                break;
            case SHP_POINTM:
                shp = new ShpPointM();
                break;
            case SHP_POINTZ:
                shp = new ShpPointZ();
                break;
            case SHP_MULTIPOINT:
                shp = new ShpMultiPoint();
                break;
            case SHP_MULTIPOINTM:
                shp = new ShpMultiPointM();
                break;
            case SHP_MULTIPOINTZ:
                shp = new ShpMultiPointZ();
                break;
            case SHP_POLYLINE:
                shp = new ShpPolyLine();
                break;
            case SHP_POLYLINEM:
                shp = new ShpPolyLineM();
                break;
            case SHP_POLYLINEZ:
                shp = new ShpPolyLineZ();
                break;
            case SHP_POLYGON:
                shp = new ShpPolygon();
                break;
            case SHP_POLYGONM:
                shp = new ShpPolygonM();
                break;
            case SHP_POLYGONZ:
                shp = new ShpPolygonZ();
                break;
            case SHP_MULTIPATCH:
                shp = new ShpMultiPatch();
                break;
            default:
                shp = nullptr;
        }
    }

    return shp;
}


/*!
 * \brief Releases allocated memory and sets the pointer to nullptr.
 * \param shp Reference to a shape pointer.
 */
void ShapeFile::releaseShape(ShpShape **shp)
{
    if (*shp != nullptr)
    {
        delete *shp;
        *shp = nullptr;
    }
}


/*!
 * \brief Reads shape from a shape-file to an existing object. The type of object have to correspond shape-file type.
 * \param recordIndex Index of shape in input file.
 * \param shp Reference of object to be loaded with data.
 * \return True, if shape was loaded successfuly.
 */
bool ShapeFile::readShape(qint64 recordIndex, ShpShape &shp)
{
    if (0 <= recordIndex && recordIndex < countAllRecords())
    {
        if (shp.load(this->shpFile, this->shx[recordIndex].offset)) return true;
    }
    shp.destroy();
    return false;
}


/*!
 * \brief Returns the list of column names in associated DBF.
 * \return List of DBF column names.
 */
inline QStringList ShapeFile::getColumnNames()
{
    return this->dbf.getColumnNames();
}


/*!
 * \brief Changes file extension.
 * \param fileName Original file name, including full path and extension.
 * \param newExtension New extension, including dot.
 * \return File name with changed extension.
 */
QString ShapeFile::changeFileExtension(QString fileName, QString newExtension)
{
    qint32 i;

    i = qint32(fileName.lastIndexOf("."));
    if (0 < i)
    {
        fileName.truncate(i);
        return fileName + newExtension;
    }
    return fileName;
}


/*!
 * \brief Swaps shape-file header to little-endiands.
 * \param shpFileHeader Shape-file header.
 */
void ShapeFile::toLittleEndian(ShpFileHeader *shpFileHeader)
{
    shpFileHeader->fileCode = qFromBigEndian(shpFileHeader->fileCode);
    shpFileHeader->fileLength = qFromBigEndian(shpFileHeader->fileLength);
    for(qint32 i=0; i<5; i++)
        shpFileHeader->unused1[i]= qFromBigEndian(shpFileHeader->unused1[i]);
}

/*!
 * \brief Swaps shp-record header to little-endiands.
 * \param shpFileHeader Shp-record header.
 */
void ShapeFile::toLittleEndian(ShpRecordHeader *shpRecordHeader)
{
    shpRecordHeader->number = qFromBigEndian(shpRecordHeader->number);
    shpRecordHeader->length = qFromBigEndian(shpRecordHeader->length);
}


/*!
 * \brief Swaps shx-record header to little-endiands.
 * \param shpFileHeader Shx-record header.
 */
void ShapeFile::toLittleEndian(ShxRecord *shxRecord)
{
    shxRecord->offset = qFromBigEndian(shxRecord->offset);
    shxRecord->length = qFromBigEndian(shxRecord->length);
}


/*!
 * \brief Swaps all SHX records in memory into little-endians.
 */
void ShapeFile::shxToLittleEndian()
{
    if (this->shx != nullptr)
    {
        for(qint64 iRecord=0, nRecords = countAllRecords(); iRecord < nRecords; iRecord++)
            toLittleEndian(this->shx + iRecord);
    }
}


/*!
 * \brief Loads SHX file into memory.
 * \param fileName File name. Procedure sets correct file extension.
 * \return True if SHX records were sucessufully loaded.
 * \remark Input file must closed and shx deleted before procedure call.
 */
bool ShapeFile::loadShx(QString fileName)
{
    qint64 nRecords;

    this->shxFile.setFileName(changeFileExtension(fileName, SHP_SHXFILE_EXT));
    if (this->shxFile.open(QFile::ReadWrite))
    {
        this->shxFile.read(reinterpret_cast<char*>(&this->shxFileHeader), sizeof(ShpFileHeader));
        toLittleEndian(&this->shxFileHeader);
        nRecords = countAllRecords();
        this->shx = new ShxRecord[quint64(nRecords)];
        this->shxFile.read(reinterpret_cast<char*>(this->shx), nRecords * qint64(sizeof(ShxRecord)));
        shxToLittleEndian();
        return true;
    }
    return false;
}


/*!
 * \brief Private copy constructor.
 */
ShapeFile::ShapeFile(ShapeFile &)
{
}


/*!
 * \brief Private copy assignment operator.
 */
ShapeFile &ShapeFile::operator=(ShapeFile &)
{
    return *this;
}
