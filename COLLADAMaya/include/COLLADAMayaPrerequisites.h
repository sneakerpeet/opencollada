/*
    Copyright (c) 2008 NetAllied Systems GmbH
	
    Licensed under the MIT Open Source License, for details 
    please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADA_MAYA_PREREQUISITES_H__
#define __COLLADA_MAYA_PREREQUISITES_H__

/**< Removes a piece of code during the pre-process.
This macro is useful for these pesky unused variable warnings. */
#define UNUSED(a)

#include <string>

namespace COLLADAMaya
{
    typedef std::string String;

#ifndef uint
    typedef unsigned int uint;
#endif

#ifndef NULL
    typedef 0 NULL
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
}

#endif // __COLLADA_MAYA_PREREQUISITES_H__