/*
    Copyright (c) 2008-2009 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_POSTPROCESSLIST_H__
#define __MayaDM_POSTPROCESSLIST_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMDependNode.h"
namespace MayaDM
{
class PostProcessList : public DependNode
{
public:
public:
	PostProcessList():DependNode(){}
	PostProcessList(FILE* file,const std::string& name,const std::string& parent=""):DependNode(file, name, parent, "postProcessList"){}
	virtual ~PostProcessList(){}
	void getPostProcesses(size_t p_i)
	{
		fprintf(mFile,"\"%s.p[%i]\"",mName.c_str(),p_i);

	}
protected:
	PostProcessList(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType)
		:DependNode(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_POSTPROCESSLIST_H__
