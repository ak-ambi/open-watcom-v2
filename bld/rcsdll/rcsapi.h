/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  SCM interface definitions.
*
****************************************************************************/


#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined( _RCSDLL_ )
    #define RCSDLLENTRY    __declspec(dllexport)
#elif defined( __NT__ )
    #define RCSDLLENTRY    __declspec(dllimport)
#else
    #define RCSDLLENTRY
#endif

#if defined( __NT__ )
    #include <windows.h>
    typedef const char *rcsstring;
    typedef void *rcsdata;
    #define RCSAPI  WINAPI
#elif defined( __WINDOWS__ )
    #include <windows.h>
    typedef const char __far *rcsstring;
    typedef void __far *rcsdata;
    #define RCSAPI WINAPI
#elif defined( __OS2__ )
    #include <os2.h>
    typedef const char *rcsstring;
    typedef void *rcsdata;
  #if !defined( __WATCOMC__ )
    #define RCSAPI
  #else
    #define RCSAPI APIENTRY
  #endif
#elif defined( __DOS__ )
    typedef const char *rcsstring;
    typedef void *rcsdata;
    #define RCSAPI
#elif defined( __UNIX__ )
    typedef const char *rcsstring;
    typedef void *rcsdata;
    #define RCSAPI
#else
    #error Unsupported OS
    #define RCSAPI
#endif

/* parms to RCSSetSystem, retvals from RCSQuerySystem */
#define NO_RCS   0
#define MKS_RCS  1
#define MKS_SI   2
#define PVCS     3
#define GENERIC  4
#define O_CYCLE  5
#define PERFORCE 6
#define WPROJ    7
#define MAX_RCS_TYPE    7

#define RCS_DLL_VER     1

typedef int RCSAPI      BatchCallback( rcsstring str, void *cookie );
typedef int RCSAPI      MessageBoxCallback( rcsstring text, rcsstring title, char *buffer, int len, void *cookie );

typedef int RCSAPI      RCSGetVersionFn( void );
typedef rcsdata RCSAPI  RCSInitFn( unsigned long, char *cfg_dir );
typedef int RCSAPI      RCSCheckoutFn( rcsdata, rcsstring, rcsstring, rcsstring );
typedef int RCSAPI      RCSCheckinFn( rcsdata, rcsstring, rcsstring, rcsstring );
typedef int RCSAPI      RCSHasShellFn( rcsdata );
typedef int RCSAPI      RCSRunShellFn( rcsdata );
typedef int RCSAPI      RCSSetSystemFn( rcsdata, int );
typedef int RCSAPI      RCSQuerySystemFn( rcsdata );
typedef int RCSAPI      RCSRegBatchCbFn( rcsdata, BatchCallback *, void * );
typedef int RCSAPI      RCSRegMsgBoxCbFn( rcsdata, MessageBoxCallback *, void * );
typedef void RCSAPI     RCSSetPauseFn( rcsdata, int );
typedef void RCSAPI     RCSFiniFn( rcsdata );

#ifdef __cplusplus
};
#endif
