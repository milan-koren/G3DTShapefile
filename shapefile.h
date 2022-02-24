#ifndef SHAPEFILE_H
#define SHAPEFILE_H

/*!
 * *****************************************************************
 *                            G3DTShapefile
 * *****************************************************************
 * \file shpfile.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 *
 * ESRI Shapefile Technical Specification
 * http://www.esri.com/library/whitepapers/pdfs/shapefile.pdf
 * *****************************************************************
 */

#include <QString>
#include <QFile>
#include "g3dtshapefile_global.h"
#include "Dbf/dbf.h"
#include "Shp/shp.h"

#define SHP_SHPFILE_EXT ".shp"
#define SHP_SHXFILE_EXT ".shx"

#define SHP_FILECODE (9994)
#define SHP_VERSION  (1000)


#pragma pack(2)

struct G3DTSHAPEFILE_EXPORT ShxRecord
{
    qint32 offset;		// big-endian       0
    qint32 length;		// big-endian       4
};

struct G3DTSHAPEFILE_EXPORT ShpRecordHeader
{
    qint32 number;		// big-endian       0
    qint32 length;		// big-endian       4
};

struct G3DTSHAPEFILE_EXPORT ShpFileHeader
{
    qint32 fileCode;	// big-endian		 0 (9994)
    qint32 unused1[5];	// big-endian		 4 (0)
    qint32 fileLength;	// big-endian		24 (words, not bytes!)
    qint32 version;		// little-endian	28 (1000}
    qint32 shapeType;	// little-endian	32
    ShapeBox box;       // little-endian	36
    double z0;          // little-endian    68
    double z1;          // little-endian    76
    double m0;          // little-endian    84
    double m1;          // little-endian    92
};

#pragma pack()


class G3DTSHAPEFILE_EXPORT ShapeFile
{
protected:
    QFile shpFile;
    QFile shxFile;
    ShpFileHeader shpFileHeader;
    ShpFileHeader shxFileHeader;
    DbfFile dbf;
    ShxRecord *shx = nullptr;

public:
    ShapeFile();
    virtual ~ShapeFile();

    void close();
    bool open(QString fileName);
    bool isOpen();

    qint64 countAllRecords();
    qint64 countDeletedRecords();
    qint64 countValidRecords();
    qint32 countColumns();
    int getShapeType();

    bool isValid(qint64 recordIndex);
    bool isDeleted(qint64 recordIndex);

    ShpShape *createShape();
    void releaseShape(ShpShape **shp);

    bool readShape(qint64 recordIndex, ShpShape &shp);

    QStringList getColumnNames();
    QStringList getTextColumnNames();

protected:
    QString changeFileExtension(QString fileName, QString newExtension);
    void toLittleEndian(ShpFileHeader *shpFileHeader);
    void toLittleEndian(ShpRecordHeader *shpRecordHeader);
    void toLittleEndian(ShxRecord *shxRecord);
    void shxToLittleEndian(void);
    bool loadShx(QString fileName);

private:
    ShapeFile(ShapeFile &shpFile);
    ShapeFile &operator=(ShapeFile &shpFile);
};

#endif // SHAPEFILE_H
