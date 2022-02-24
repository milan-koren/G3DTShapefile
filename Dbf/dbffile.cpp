/*!
 * *****************************************************************
 *                             G3DTShapefile
 * *****************************************************************
 * \file dbf.cpp
 *
 * \brief The Dbf class implementation.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include "dbffile.h"


/*!
 * \brief Standard constructor.
 */
DbfFile::DbfFile()
{
}


/*!
 * \brief Virtual destructor. Finishes open DBF file, closes file, and releases allocated memory.
 */
DbfFile::~DbfFile()
{
    close();
}


/*!
 * \brief Writes cache, closes open file, and releases allocated cache memory.
 */
void DbfFile::close()
{
    char c = char(DBF_FILE_END);

    writeCache();
    if (this->recordAppended && this->file.isOpen())
    {
        writeHeader();
        this->file.atEnd();
        this->file.write(&c, 1);
        this->recordAppended = false;
    }

    this->file.flush();
    this->file.close();
    if (this->cache != nullptr)
    {
        delete [] this->cache;
        this->cache = nullptr;
        this->cacheFirstRecord = -1;
        this->cacheLastRecord = -1;
        this->cacheNRecords = -1;
        this->cacheLength = -1;
        this->cacheChanged = false;
    }
    if (this->columnDsrs != nullptr)
    {
        delete [] columnDsrs;
        this->columnDsrs = nullptr;
        this->nColumns = 0;
    }
}


/*!
 * \brief Opens DBF file. Reads header and column descriptors, allocates cache memory.
 * \param fileName Full file name.
 * \param cacheNRecords Number of records in cache memory.
 * \param cacheOffset Offset of first record in cache. Used in ReadCache procedure.
 * \remark The values of cacheOffset and cacheNRecords will be automatically corrected, so that 0 <= cacheOffset; 0 <= cacheNRecords; cacheOffset < cacheNRecords.
 * \return True, if DBF is open and ready to use.
 */
bool DbfFile::open(QString fileName, qint64 cacheNRecords, qint64 cacheOffset)
{
    close();
    this->file.setFileName(fileName);
    if (this->file.open(QFile::ReadWrite))
    {
        if (cacheNRecords < 0)
            cacheNRecords = DBF_DEFAULT_CACHE_NRECORDS;
        if (cacheNRecords <= cacheOffset)
            cacheOffset = cacheNRecords - 1;
        if (cacheOffset < 0)
            cacheOffset = 0;

        if (!readHeader()) return false;
        this->cacheNRecords= cacheNRecords;
        this->cacheLength = cacheNRecords * this->fileHeader.recordLength;
        this->cache = new char[ulong(this->cacheLength)];
        this->cacheOffset = cacheOffset;
        this->cacheFirstRecord = -1;
        this->cacheLastRecord = -1;
        this->cacheChanged = false;
        this->recordAppended = false;
        return true;
    }
    return false;
}


/*!
 * \brief Checks if DBF is open.
 * \return If DBF is open returns true;
 */
inline bool DbfFile::isOpen()
{
    return this->file.isOpen();
}


/*!
 * \brief Writes DBF header (when new records were added or file was created).
 * \return
 */
bool DbfFile::writeHeader()
{
    if (this->file.isOpen())
    {
        this->file.seek(0);
        this->file.write(reinterpret_cast<char*>(&fileHeader), sizeof(DbfFileHeader));
        return true;
    }
    return false;
}


/*!
 * \brief Reads file header and column descriptors.
 * \return True, if file header was sucessfully read.
 */
bool DbfFile::readHeader()
{
    DbfFileColumnDescriptor fileColumndDsr;
    qint32 l = 0;

    if (this->file.isOpen())
    {
        this->file.seek(0);
        this->file.read(reinterpret_cast<char*>(&this->fileHeader), sizeof(DbfFileHeader));
        this->nColumns = (this->fileHeader.headerLength - qint32(sizeof(DbfFileHeader)) - 1) / qint32((sizeof(DbfFileColumnDescriptor)));
        this->columnDsrs = new DbfColumnDescriptor[ulong(this->nColumns)];
        for(qint32 i = 0; i < this->nColumns; i++)
        {
            this->file.read(reinterpret_cast<char*>(&fileColumndDsr), sizeof(DbfFileColumnDescriptor));
            l += fileColumndDsr.length;
            this->columnDsrs[i].name = QString(fileColumndDsr.name).trimmed();
            this->columnDsrs[i].type = fileColumndDsr.type;
            this->columnDsrs[i].length = fileColumndDsr.length;
            this->columnDsrs[i].precision = fileColumndDsr.precision;
            if (0 < i)
                this->columnDsrs[i].offset = this->columnDsrs[i-1].offset + this->columnDsrs[i-1].length;
            else
                this->columnDsrs[i].offset = 1;
        }
        return true;
    }
    return false;
}


/*!
 * \brief Writes cache, if records in cache have been changed.
 * \return True, if cache was successfully written into file.
 */
bool DbfFile::writeCache()
{
    qint64 nRecords;

    if (this->cache != nullptr && this->cacheChanged && 0 <= this->cacheFirstRecord && 0 < this->fileHeader.records)
    {
        this->file.seek(this->fileHeader.headerLength + this->cacheFirstRecord * this->fileHeader.recordLength);
        nRecords = this->cacheLastRecord - this->cacheFirstRecord + 1;
        file.write(this->cache, nRecords * this->fileHeader.recordLength);
        this->cacheChanged = false;
    }
    return true;
}


/*!
 * \brief Reads records into the cache memory. The cacheOffset is used to locate the first record in cache.
 * \param recordIndex Index of required record.
 * \return True, if successful.
 */
bool DbfFile::readCache(qint64 recordIndex)
{
    qint64 nRecords;

    if (0 <= recordIndex && recordIndex < this->fileHeader.records)
    {
        if (writeCache())
        {
            this->cacheFirstRecord = recordIndex - this->cacheOffset;
            if (this->cacheFirstRecord < 0) this->cacheFirstRecord = 0;
            this->cacheLastRecord = this->cacheFirstRecord + this->cacheNRecords - 1;
            if (this->fileHeader.records <= this->cacheLastRecord)
            {
                this->cacheLastRecord = this->fileHeader.records - 1;
                this->cacheFirstRecord = this->cacheLastRecord - this->cacheNRecords + 1;
                if (this->cacheFirstRecord < 0) this->cacheFirstRecord = 0;
            }
            if (this->cacheFirstRecord <= recordIndex && recordIndex <= this->cacheLastRecord)
            {
                this->file.seek(this->fileHeader.headerLength + this->cacheFirstRecord * this->fileHeader.recordLength);
                nRecords = this->cacheLastRecord - this->cacheFirstRecord + 1;
                file.read(this->cache, nRecords * this->fileHeader.recordLength);
                this->cacheChanged = false;
            }
            else
            {
                this->cacheFirstRecord = -1;
                this->cacheLastRecord = -1;
                return false;
            }
        }
    }
    return true;
}


/*!
 * \brief Returns number of columns in DBF (value is stored in internal variable).
 * \return Number of columns.
 */
qint32 DbfFile::countColumns()
{
    if (this->file.isOpen()) return nColumns;
    return 0;
}


/*!
 * \brief Returns the list of column names.
 * \return List of column names.
 */
QStringList DbfFile::getColumnNames()
{
    QStringList lst;

    for(qint32 iColumn=0; iColumn< this->nColumns; iColumn++)
    {
        lst.append(this->columnDsrs[iColumn].name);
    }

    return lst;
}


/*!
 * \brief Returns the names of text columns.
 * \return List of text column names.
 */

QStringList DbfFile::getTextColumnNames()
{
    QStringList lst;

    for(qint32 iColumn=0; iColumn< this->nColumns; iColumn++)
    {
        if (this->columnDsrs[iColumn].type == toascii('C'))
            lst.append(this->columnDsrs[iColumn].name);
    }

    return lst;
}


/*!
 * \brief Finds the index of a givne column.
 * \param columnName Name of a column.
 * \return Index of the column with a given name. -1 if column does not exist.
 */
qint32 DbfFile::getColumnIndex(QString columnName)
{
    for(qint32 columnIndex = 0; columnIndex < this->nColumns; columnIndex++)
    {
        if (this->columnDsrs[ulong(columnIndex)].name == columnName) return columnIndex;
    }
    return -1;
}


/*!
 * \brief Returns number of all records in DBF file.
 * \return Number of all (valid and deleted) records.
 */
inline qint64 DbfFile::countAllRecords()
{
    if (this->file.isOpen()) return this->fileHeader.records;
    return 0;
}


/*!
 * \brief Counts number of deleted records in DBF.
 * \return Number of deleted records.
 */
qint64 DbfFile::countDeletedRecords()
{
    qint64 nRecords, iRecord;
    qint64 deletedRecords = 0;

    if (file.isOpen())
    {
        nRecords = countAllRecords();
        for(iRecord=0; iRecord < nRecords; iRecord++)
            if (isDeleted(iRecord)) deletedRecords++;
    }

    return deletedRecords;
}


/*!
 * \brief Counts number of valid records in DBF.
 * \return Number of valid records.
 */
inline qint64 DbfFile::countValidRecords()
{
    return (countAllRecords() - countDeletedRecords());
}


/*!
 * \brief Checks if a given record is valid.
 * \param recordIndex The index of record.
 * \return If record is valid returns true, false otherwise.
 */
bool DbfFile::isValid(qint64 recordIndex)
{
    if (recordIndex < this->cacheFirstRecord || this->cacheLastRecord < recordIndex) readCache(recordIndex);
    if (this->cacheFirstRecord <= recordIndex && recordIndex <= this->cacheLastRecord)
        return (this->cache[(recordIndex - this->cacheFirstRecord) * this->fileHeader.recordLength] == 0);
    return false;
}


/*!
 * \brief Checks if a given record is deleted.
 * \param recordIndex The index of record.
 * \return If record is valid returns false, true otherwise.
 */
inline bool DbfFile::isDeleted(qint64 recordIndex)
{
    return !isValid(recordIndex);
}


/*!
 * \brief Reads column value as a string.
 * \param recordIndex Record index in a DBF.
 * \param columnIndex Column index.
 * \return Trimmed string, or QString::none if conversion was not successful.
 */
QString DbfFile::getQString(qint64 recordIndex, qint32 columnIndex)
{
    qint64 columnOffset;

    if (0 <= recordIndex && recordIndex < this->fileHeader.records)
    {
        if (0 <= columnIndex && columnIndex < this->nColumns)
        {
            if (recordIndex < this->cacheFirstRecord || this->cacheLastRecord < recordIndex) readCache(recordIndex);
            if (this->cacheFirstRecord <= recordIndex && recordIndex <= this->cacheLastRecord)
            {
                columnOffset = (recordIndex - this->cacheFirstRecord) * this->fileHeader.recordLength + this->columnDsrs[columnIndex].offset;
                return QString::fromLocal8Bit(this->cache + columnOffset, this->columnDsrs[columnIndex].length).trimmed();
            }
        }
    }

    return "";
}


/*!
 * \brief Reads column value as a string.
 * \param recordIndex Record index.
 * \param columnName Column name.
 * \return String value, QString::none if conversion was not successful.
 */
inline QString DbfFile::getQString(qint64 recordIndex, QString columnName)
{
    return getQString(recordIndex, getColumnIndex(columnName));
}


/*!
 * \brief Reads double value from a given field.
 * \param recordIndex The index of a record.
 * \param columnsIndex The index of a field to be read.
 * \return Double value stored in the field, -DBL_MAX if conversion was unsuccessful.
 * \remark The function does not handle thousands group separator.
 */
double DbfFile::getDouble(qint64 recordIndex, qint32 columnIndex)
{
    QString sval;
    bool ok;
    double dval = -DBL_MAX;

    sval = getQString(recordIndex, columnIndex);
    if (!sval.isNull())
    {
        dval = sval.toDouble(&ok);
        if (!ok)
        {
            // coversion was not successful
            // try to change decimal point to decimal comma and vice versa
            if (sval.contains("."))
            {
                sval = sval.replace(".", ",");
            }
            else
                sval = sval.replace(",", ".");
            dval = sval.toDouble(&ok);
            if (!ok) dval = -DBL_MAX;
        }
    }

    return dval;
}


/*!
 * \brief Reads double value from field with a given name.
 * \param recordIndex Record index.
 * \param columnName Field name.
 * \return Double value, -DBL_MAX if conversion was unsuccessful.
 */
inline double DbfFile::getDouble(qint64 recordIndex, QString columnName)
{
    return getDouble(recordIndex, getColumnIndex(columnName));
}


/*!
 * \brief Reads long value from a given field.
 * \param recordIndex The index of a record.
 * \param fieldIndex The index of a field to be read.
 * \return Value stored in the field.
 */
qint64 DbfFile::getLong(qint64 recordIndex, qint32 fieldIndex)
{
    QString sval;
    bool ok;
    qint64 ival = 0;

    sval = getQString(recordIndex, fieldIndex);
    if (!sval.isNull())
    {
        ival = sval.toLongLong(&ok);
        if (!ok) ival = 0;
    }

    return ival;
}


/*!
 * \brief Reads integer value from field with a given name.
 * \param recordIndex Record index.
 * \param columnName Field name.
 * \return Long value.
 */
qint64 DbfFile::getLong(qint64 recordIndex, QString columnName)
{
    return getLong(recordIndex, getColumnIndex(columnName));
}
