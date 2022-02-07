#ifndef DBFFILE_H
#define DBFFILE_H

#include <QString>
#include <QtMath>
#include <QFile>
#include <QList>
#include <QVariant>
#include <float.h>
#include "g3dtshapefile_global.h"
#include "dbffilecolumndescriptor.h"
#include "dbffileheader.h"
#include "dbfcolumndescriptor.h"


/*!
 * *****************************************************************
 *                            G3DTShapeFile
 * *****************************************************************
 * \file dbf.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTLas
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */


#define DBF_FILE_EXT ".dbf"
#define DBF_CODEPAGE_FILE_EXT ".cpg"
#define DBF_VERSION (03)
#define DBF_HEADER_END (13)
#define DBF_FILE_END (26)
#define DBF_DEFAULT_CACHE_NRECORDS (1024)
#define DBF_DEFAULT_CACHE_OFFSET (0)

/*!
 * \class DbfFile
 * \todo Use code page to transform strings into locale.
 * \todo Include iterator for valid records.
 * \todo Return record values as QString-s.
 * \todo Return record values as QVariant-s.
 */
class G3DTSHAPEFILE_EXPORT DbfFile
{
protected:
    QFile file;
    DbfFileHeader fileHeader;
    qint32 nColumns = 0;
    DbfColumnDescriptor *columnDsrs = nullptr;

    qint64 cacheFirstRecord = -1; //!< index of the first record in cache memory
    qint64 cacheLastRecord = -1;  //!< index of the last record in cache
    qint64 cacheNRecords = 0;     //!< number of records stored in cache
    qint64 cacheLength = 0;       //!< the size of allocated cache in bytes (== cacheNRecords * recordLength)
    qint64 cacheOffset = 0;       //!< offset of the first requested record in cache, used in ReadCache
    char *cache = nullptr;        //!< pointer to cache
    bool cacheChanged = false;    //!< true, if cache changed and need to be saved
    bool recordAppended = false;  //!< true, if a new record was appended, chache and header have to be saved

    bool writeHeader();
    bool readHeader();

    bool writeCache();
    bool readCache(qint64 recordIndex);

public:
    DbfFile(void);
    virtual ~DbfFile(void);

    void close();
    bool open(QString fileName, qint64 cacheNRecords = DBF_DEFAULT_CACHE_NRECORDS, qint64 cacheOffset = DBF_DEFAULT_CACHE_OFFSET);
    bool isOpen();

    qint32 countColumns();
    QStringList getColumnNames();
    qint32 getColumnIndex(QString columnName);

    qint64 countAllRecords();
    qint64 countDeletedRecords();
    qint64 countValidRecords();
    bool isValid(qint64 recordIndex);
    bool isDeleted(qint64 recordIndex);

    QString getQString(qint64 recordIndex, qint32 columnIndex);
    QString getQString(qint64 recordIndex, QString columnName);

    double getDouble(qint64 recordIndex, qint32 columnIndex);
    double getDouble(qint64 recordIndex, QString columnName);

    qint64 getLong(qint64 recordIndex, qint32 columnIndex);
    qint64 getLong(qint64 recordIndex, QString columnName);
};

#endif // DBFFILE_H
