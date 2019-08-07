
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl mesenger_idl
// ------------------------------
#ifndef MESENGER_IDL_EXPORT_H
#define MESENGER_IDL_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (MESENGER_IDL_HAS_DLL)
#  define MESENGER_IDL_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && MESENGER_IDL_HAS_DLL */

#if !defined (MESENGER_IDL_HAS_DLL)
#  define MESENGER_IDL_HAS_DLL 1
#endif /* ! MESENGER_IDL_HAS_DLL */

#if defined (MESENGER_IDL_HAS_DLL) && (MESENGER_IDL_HAS_DLL == 1)
#  if defined (MESENGER_IDL_BUILD_DLL)
#    define mesenger_idl_Export ACE_Proper_Export_Flag
#    define MESENGER_IDL_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define MESENGER_IDL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* MESENGER_IDL_BUILD_DLL */
#    define mesenger_idl_Export ACE_Proper_Import_Flag
#    define MESENGER_IDL_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define MESENGER_IDL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* MESENGER_IDL_BUILD_DLL */
#else /* MESENGER_IDL_HAS_DLL == 1 */
#  define mesenger_idl_Export
#  define MESENGER_IDL_SINGLETON_DECLARATION(T)
#  define MESENGER_IDL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* MESENGER_IDL_HAS_DLL == 1 */

// Set MESENGER_IDL_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (MESENGER_IDL_NTRACE)
#  if (ACE_NTRACE == 1)
#    define MESENGER_IDL_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define MESENGER_IDL_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !MESENGER_IDL_NTRACE */

#if (MESENGER_IDL_NTRACE == 1)
#  define MESENGER_IDL_TRACE(X)
#else /* (MESENGER_IDL_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define MESENGER_IDL_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (MESENGER_IDL_NTRACE == 1) */

#endif /* MESENGER_IDL_EXPORT_H */

// End of auto generated file.
