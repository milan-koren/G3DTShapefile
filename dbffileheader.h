#ifndef DBFFILEHEADER_H
#define DBFFILEHEADER_H

#include "g3dtshapefile_global.h"


/*!
 * *****************************************************************
 *                            G3DTShapeFile
 * *****************************************************************
 * \file dbffileheader.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */


#pragma pack(1)

struct G3DTSHAPEFILE_EXPORT DbfFileHeader
{
    quint8 version;
    quint8 year, month, day;
    quint32 records;
    quint16 headerLength;
    quint16 recordLength;
    quint8 reserved1[3];
    quint8 multiUserReserved[13];
    quint8 reserved2[4];
    // description of columns
    // 0x0D
};

#pragma pack()

#endif // DBFFILEHEADER_H
