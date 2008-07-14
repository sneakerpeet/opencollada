/*
    Copyright (c) 2008 NetAllied Systems GmbH
	
    Licensed under the MIT Open Source License, for details 
    please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADA_MAYA_STABLE_HEADERS_H__
#define __COLLADA_MAYA_STABLE_HEADERS_H__

//
// Precompiled Header
//

#define _CRT_SECURE_NO_DEPRECATE 1
#define _MGLFunctionTable_h_ // We don't want this one included by Maya 8.5

class MGLFunctionTable;

#ifdef MAC_TIGER
#include <maya/OpenMayaMac.h>
#endif

//STL
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <String>
#include <iostream>

// Maya SDK
#include <maya/MBoundingBox.h>
#include <maya/MColor.h>
#include <maya/MColorArray.h>
#include <maya/MDagPath.h>
#include <maya/MDagPathArray.h>
#include <maya/MDistance.h>
#include <maya/MEulerRotation.h>
#include <maya/MFloatArray.h>
#include <maya/MFloatPointArray.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MGlobal.h>
#include <maya/MIntArray.h>
#include <maya/MMatrix.h>
#include <maya/MObject.h>
#include <maya/MObjectArray.h>
#include <maya/MPlug.h>
#include <maya/MPlugArray.h>
#include <maya/MPoint.h>
#include <maya/MPointArray.h>
#include <maya/MPxData.h>
#include <maya/MQuaternion.h>
#include <maya/MFnSet.h>
#include <maya/MFnStringData.h>
#include <maya/MStatus.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>
#include <maya/MTime.h>
#include <maya/MTimeArray.h>
#include <maya/MVector.h>
#include <maya/MVectorArray.h>

#ifdef WIN32
#elif defined(MAC_PLUGIN)

#elif defined(LINUX)

#else
#error "Unsupported platform"
#endif //all platforms..

#ifndef UINT_MAX
#define UINT_MAX 0xFFFFFFFF
#endif

#ifndef INT_MAX
#define INT_MAX 0x7FFFFFFF
#endif

#endif //__COLLADA_MAYA_STABLE_HEADERS_H__