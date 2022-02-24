#ifndef G3DTSHAPEFILE_GLOBAL_H
#define G3DTSHAPEFILE_GLOBAL_H

/*!
 * *****************************************************************
 *                            G3DTShapefile
 * *****************************************************************
 * \file g3dtshapefile_global.h
 *
 * \brief System generated include file.
 *
 * \author M. Koren, milan.koren3@gmail.com
 * Source: https:\\github.com/milan-koren/G3DTShapefile
 * Licence: EUPL v. 1.2
 * https://joinup.ec.europa.eu/collection/eupl
 * *****************************************************************
 */

#include <QtCore/qglobal.h>
#include <QtCore>

#if defined(G3DTSHAPEFILE_LIBRARY)
#  define G3DTSHAPEFILE_EXPORT Q_DECL_EXPORT
#else
#  define G3DTSHAPEFILE_EXPORT Q_DECL_IMPORT
#endif

#endif // G3DTSHAPEFILE_GLOBAL_H
