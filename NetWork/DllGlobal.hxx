#pragma once

#include <QtGlobal>

#if defined (NETWORK_LIBRARY)
#  define NETWORK_EXPORT Q_DECL_EXPORT
#else
#  define NETWORK_EXPORT Q_DECL_IMPORT
#endif

#ifndef GCM_BEGIN
#  define GCM_BEGIN namespace GCM {
#endif

#ifndef GCM_END
#  define GCM_END }
#endif
