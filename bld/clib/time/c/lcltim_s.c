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
* Description:  Implementation of localtime_s() - bounds-checking localtime().
*               Wrapper for _localtime().
*
****************************************************************************/


#include "variety.h"
#include "saferlib.h"
#include <time.h>
#include "rtdata.h"
#include "timedata.h"


_WCRTLINK struct tm *localtime_s( const time_t * __restrict timer,
                                  struct tm * __restrict t )
/****************************************************************/
{
    char    *msg = NULL;

    // Verify runtime-constraints
    // timer   not NULL
    // t  not NULL
    if( __check_constraint_nullptr_msg( msg, timer ) &&
        __check_constraint_nullptr_msg( msg, t ) ) {

        // Parameters checked, now call plain old _localtime
        return( _localtime( timer, t ) );
    }

    // Runtime-constraint violated, call the handler
    __rtct_fail( __func__, msg, NULL );
    return( NULL );
}
