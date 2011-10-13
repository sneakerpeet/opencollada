/*
    Copyright (c) 2008-2009 NetAllied Systems GmbH

	This file is part of COLLADAMax.

    Portions of the code are:
    Copyright (c) 2005-2007 Feeling Software Inc.
    Copyright (c) 2005-2007 Sony Computer Entertainment America
    
    Based on the 3dsMax COLLADASW Tools:
    Copyright (c) 2005-2006 Autodesk Media Entertainment
	
    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/


#ifndef __COLLADAMAX_TYPES_H__
#define __COLLADAMAX_TYPES_H__

#include "COLLADAMaxPrerequisites.h"

#include "COLLADABUURI.h"

#include <vector>
#include <map>
#include <set>

class INode;

namespace COLLADAMax
{

	class ExportNode;

	typedef std::vector<String> StringList;

	struct EffectIdAndName
	{
		EffectIdAndName( const String& _effectId, const String& _effectName ) 
			: effectId(_effectId)
			, effectName(_effectName)
		{}

		String effectId;
		String effectName;
	};


    /** A list of ids of effects that are exported*/
    typedef std::vector<EffectIdAndName> ExportedEffectIdAndNameList;

    /** A list of wire frame colors that are exported*/
    typedef std::vector<DWORD> WireFrameColorEffectList;

    /** Maps material pointers to effect ids*/
    typedef std::map<Mtl*, String> EffectMap;

	struct ImageInfo
	{
		/** The id of the image element in the COLLADA file.*/
		String imageId;

		/** The location of the image to reference in the COLLADA image element.*/
		COLLADABU::URI fileLocation;
	};

    /**map<filename(original max absolute file location),imageID>*/
	typedef std::map<COLLADABU::URI, ImageInfo> ExportedImageMap;

	/** List of INodes*/
	typedef std::vector<INode*> INodeList;

	/** List of ImpNodes*/
	typedef std::vector<ImpNode*> ImpNodeList;

	typedef std::set<ExportNode*> ExportNodeSet;

	typedef std::vector<float> FloatList;


	typedef std::map<Object*, String> ObjectStringMap;

}


#endif //__COLLADAMAX_TYPES_H__