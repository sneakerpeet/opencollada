/*
    Copyright (c) 2008-2009 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_POINTMATRIXMULT_H__
#define __MayaDM_POINTMATRIXMULT_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMDependNode.h"
namespace MayaDM
{
class PointMatrixMult : public DependNode
{
public:
public:
	PointMatrixMult():DependNode(){}
	PointMatrixMult(FILE* file,const std::string& name,const std::string& parent=""):DependNode(file, name, parent, "pointMatrixMult"){}
	virtual ~PointMatrixMult(){}
	void setInPoint(const double3& ip)
	{
		fprintf(mFile,"\tsetAttr \".ip\" -type \"double3\" ");
		ip.write(mFile);
		fprintf(mFile,";\n");

	}
	void setInPointX(double ipx)
	{
		if(ipx == 0) return;
		fprintf(mFile,"\tsetAttr \".ip.ipx\" %f;\n", ipx);

	}
	void setInPointY(double ipy)
	{
		if(ipy == 0) return;
		fprintf(mFile,"\tsetAttr \".ip.ipy\" %f;\n", ipy);

	}
	void setInPointZ(double ipz)
	{
		if(ipz == 0) return;
		fprintf(mFile,"\tsetAttr \".ip.ipz\" %f;\n", ipz);

	}
	void setInMatrix(const matrix& im)
	{
		if(im == identity) return;
		fprintf(mFile,"\tsetAttr \".im\" -type \"matrix\" ");
		im.write(mFile);
		fprintf(mFile,";\n");

	}
	void setVectorMultiply(bool vm)
	{
		if(vm == false) return;
		fprintf(mFile,"\tsetAttr \".vm\" %i;\n", vm);

	}
	void getInPoint()
	{
		fprintf(mFile,"\"%s.ip\"",mName.c_str());

	}
	void getInPointX()
	{
		fprintf(mFile,"\"%s.ip.ipx\"",mName.c_str());

	}
	void getInPointY()
	{
		fprintf(mFile,"\"%s.ip.ipy\"",mName.c_str());

	}
	void getInPointZ()
	{
		fprintf(mFile,"\"%s.ip.ipz\"",mName.c_str());

	}
	void getInMatrix()
	{
		fprintf(mFile,"\"%s.im\"",mName.c_str());

	}
	void getVectorMultiply()
	{
		fprintf(mFile,"\"%s.vm\"",mName.c_str());

	}
	void getOutput()
	{
		fprintf(mFile,"\"%s.o\"",mName.c_str());

	}
	void getOutputX()
	{
		fprintf(mFile,"\"%s.o.ox\"",mName.c_str());

	}
	void getOutputY()
	{
		fprintf(mFile,"\"%s.o.oy\"",mName.c_str());

	}
	void getOutputZ()
	{
		fprintf(mFile,"\"%s.o.oz\"",mName.c_str());

	}
protected:
	PointMatrixMult(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType)
		:DependNode(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_POINTMATRIXMULT_H__
