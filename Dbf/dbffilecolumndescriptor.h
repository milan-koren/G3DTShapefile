#ifndef DBFFILECOLUMNDESCRIPTOR_H
#define DBFFILECOLUMNDESCRIPTOR_H

/*!
 * *****************************************************************
 *                            G3DTShapefile
 * *****************************************************************
 * \file dbffilecolumndescriptor.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 *
 * DBF field descriptor
 * https://www.dbase.com/Knowledgebase/INT/db7_file_fmt.htm
 * *****************************************************************
 */

#include "g3dtshapefile_global.h"

#define DBF_MAX_COLUMN_NAME_LENGTH (11)

#pragma pack(1)

struct G3DTSHAPEFILE_EXPORT DbfFileColumnDescriptor
{
    char name[DBF_MAX_COLUMN_NAME_LENGTH];
    quint8 type;                            //!<  ASCII (B, C, D, N, L, M, @, I, +, F, 0, G)
    quint16 address;
    quint16 reserved0;
    quint8 length;
    quint8 precision;
    quint16 reservedForMultiUser1;
    quint8 id;
    quint16 reservedForMultiUser2;
    quint8 setLabel;
    quint8 reserved[8];
};

#pragma pack()

#endif // DBFFILECOLUMNDESCRIPTOR_H
