/*
    Copyright (c) 2008-2009 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_WEIGHTGEOMETRYFILTER_H__
#define __MayaDM_WEIGHTGEOMETRYFILTER_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMGeometryFilter.h"
namespace MayaDM
{
class WeightGeometryFilter : public GeometryFilter
{
public:
	struct WeightList{
		float* weights;
		void write(FILE* file) const
		{
			size_t size = sizeof(weights)/sizeof(float);
			for(size_t i=0; i<size; ++i)
			{
				fprintf(file,"%f", weights[i]);
				if(i+1<size) fprintf(file," ");
			}
		}
	};
public:
	WeightGeometryFilter():GeometryFilter(){}
	WeightGeometryFilter(FILE* file,const std::string& name,const std::string& parent=""):GeometryFilter(file, name, parent, "weightGeometryFilter"){}
	virtual ~WeightGeometryFilter(){}
	void setWeightList(size_t wl_i,const WeightList& wl)
	{
		fprintf(mFile,"\tsetAttr \".wl[%i]\" ",wl_i);
		wl.write(mFile);
		fprintf(mFile,";\n");

	}
	void setWeights(size_t wl_i,size_t w_i,float w)
	{
		if(w == 1.0) return;
		fprintf(mFile,"\tsetAttr \".wl[%i].w[%i]\" %f;\n", wl_i,w_i,w);

	}
	void setWeights(size_t wl_i,size_t w_start,size_t w_end,float* w)
	{
		fprintf(mFile,"\tsetAttr \".wl[%i].w[%i:%i]\" ", wl_i,w_start,w_end);
		size_t size = (w_end-w_start)*1+1;
		for(size_t i=0;i<size;++i)
		{
			fprintf(mFile,"%f",w[i]);
			if(i+1<size) fprintf(mFile," ");
		}
		fprintf(mFile,";\n");

	}
	void startWeights(size_t wl_i,size_t w_start,size_t w_end)
	{
		fprintf(mFile,"\tsetAttr \".wl[%i].w[%i:%i]\"",wl_i,w_start,w_end);

	}
	void appendWeights(float w)
	{
		fprintf(mFile," %f",w);

	}
	void endWeights()
	{
		fprintf(mFile,";\n");

	}
	void getWeightList(size_t wl_i)
	{
		fprintf(mFile,"\"%s.wl[%i]\"",mName.c_str(),wl_i);

	}
	void getWeights(size_t wl_i,size_t w_i)
	{
		fprintf(mFile,"\"%s.wl[%i].w[%i]\"",mName.c_str(),wl_i,w_i);

	}
protected:
	WeightGeometryFilter(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType)
		:GeometryFilter(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_WEIGHTGEOMETRYFILTER_H__
