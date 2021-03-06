#ifndef DBFCOLUMNDESCRIPTOR_H
#define DBFCOLUMNDESCRIPTOR_H

/*!
 * *****************************************************************
 *                            G3DTShapefile
 * *****************************************************************
 * \file dbfcolumndescriptor.h
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include <QString>
#include "g3dtshapefile_global.h"


struct G3DTSHAPEFILE_EXPORT DbfColumnDescriptor
{
    QString name;
    quint16 type;
    quint16 length;
    quint16 precision;
    quint16 offset;
    QString format;
};

#endif // DBFCOLUMNDESCRIPTOR_H
