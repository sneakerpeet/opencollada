/*
    Copyright (c) 2008-2009 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_NONEXTENDEDLIGHTSHAPENODE_H__
#define __MayaDM_NONEXTENDEDLIGHTSHAPENODE_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMNonAmbientLightShapeNode.h"
namespace MayaDM
{
class NonExtendedLightShapeNode : public NonAmbientLightShapeNode
{
public:
public:
	NonExtendedLightShapeNode():NonAmbientLightShapeNode(){}
	NonExtendedLightShapeNode(FILE* file,const std::string& name,const std::string& parent=""):NonAmbientLightShapeNode(file, name, parent, "nonExtendedLightShapeNode"){}
	virtual ~NonExtendedLightShapeNode(){}
	void setLightRadius(float lr)
	{
		if(lr == 0.0) return;
		fprintf(mFile,"\tsetAttr \".lr\" %f;\n", lr);

	}
	void setCastSoftShadows(bool cw)
	{
		if(cw == false) return;
		fprintf(mFile,"\tsetAttr \".cw\" %i;\n", cw);

	}
	void setUseDepthMapShadows(bool dms)
	{
		if(dms == false) return;
		fprintf(mFile,"\tsetAttr \".dms\" %i;\n", dms);

	}
	void setReuseDmap(bool du)
	{
		if(du == false) return;
		fprintf(mFile,"\tsetAttr \".du\" %i;\n", du);

	}
	void setUseMidDistDmap(bool md)
	{
		if(md == true) return;
		fprintf(mFile,"\tsetAttr \".md\" %i;\n", md);

	}
	void setDmapFilterSize(short fs)
	{
		if(fs == 1) return;
		fprintf(mFile,"\tsetAttr \".fs\" %i;\n", fs);

	}
	void setDmapResolution(short dr)
	{
		if(dr == 512) return;
		fprintf(mFile,"\tsetAttr \".dr\" %i;\n", dr);

	}
	void setDmapBias(float db)
	{
		if(db == 0.001) return;
		fprintf(mFile,"\tsetAttr \".db\" %f;\n", db);

	}
	void setDmapFocus(float df)
	{
		if(df == 90.0) return;
		fprintf(mFile,"\tsetAttr \".df\" %f;\n", df);

	}
	void setDmapWidthFocus(float dw)
	{
		if(dw == 100.0) return;
		fprintf(mFile,"\tsetAttr \".dw\" %f;\n", dw);

	}
	void setUseDmapAutoFocus(bool af)
	{
		if(af == true) return;
		fprintf(mFile,"\tsetAttr \".af\" %i;\n", af);

	}
	void setVolumeShadowSamples(short nv)
	{
		if(nv == 20) return;
		fprintf(mFile,"\tsetAttr \".nv\" %i;\n", nv);

	}
	void setFogShadowIntensity(short fsi)
	{
		if(fsi == 1) return;
		fprintf(mFile,"\tsetAttr \".fsi\" %i;\n", fsi);

	}
	void setUseDmapAutoClipping(bool uc)
	{
		if(uc == true) return;
		fprintf(mFile,"\tsetAttr \".uc\" %i;\n", uc);

	}
	void setDmapNearClipPlane(float nc)
	{
		if(nc == 0.001) return;
		fprintf(mFile,"\tsetAttr \".nc\" %f;\n", nc);

	}
	void setDmapFarClipPlane(float fcp)
	{
		if(fcp == 10000.0) return;
		fprintf(mFile,"\tsetAttr \".fcp\" %f;\n", fcp);

	}
	void setUseOnlySingleDmap(bool us)
	{
		if(us == true) return;
		fprintf(mFile,"\tsetAttr \".us\" %i;\n", us);

	}
	void setUseXPositiveDmap(bool xp)
	{
		if(xp == true) return;
		fprintf(mFile,"\tsetAttr \".xp\" %i;\n", xp);

	}
	void setUseXNegativeDmap(bool xn)
	{
		if(xn == true) return;
		fprintf(mFile,"\tsetAttr \".xn\" %i;\n", xn);

	}
	void setUseYPositiveDmap(bool yp)
	{
		if(yp == true) return;
		fprintf(mFile,"\tsetAttr \".yp\" %i;\n", yp);

	}
	void setUseYNegativeDmap(bool yn)
	{
		if(yn == true) return;
		fprintf(mFile,"\tsetAttr \".yn\" %i;\n", yn);

	}
	void setUseZPositiveDmap(bool zp)
	{
		if(zp == true) return;
		fprintf(mFile,"\tsetAttr \".zp\" %i;\n", zp);

	}
	void setUseZNegativeDmap(bool zn)
	{
		if(zn == true) return;
		fprintf(mFile,"\tsetAttr \".zn\" %i;\n", zn);

	}
	void setDmapUseMacro(const string& dc)
	{
		if(dc == "NULL") return;
		fprintf(mFile,"\tsetAttr \".dc\" -type \"string\" ");
		dc.write(mFile);
		fprintf(mFile,";\n");

	}
	void setDmapName(const string& smn)
	{
		if(smn == "NULL") return;
		fprintf(mFile,"\tsetAttr \".smn\" -type \"string\" ");
		smn.write(mFile);
		fprintf(mFile,";\n");

	}
	void setDmapLightName(bool ul)
	{
		if(ul == true) return;
		fprintf(mFile,"\tsetAttr \".ul\" %i;\n", ul);

	}
	void setDmapSceneName(bool um)
	{
		if(um == false) return;
		fprintf(mFile,"\tsetAttr \".um\" %i;\n", um);

	}
	void setDmapFrameExt(bool uf)
	{
		if(uf == false) return;
		fprintf(mFile,"\tsetAttr \".uf\" %i;\n", uf);

	}
	void setWriteDmap(bool ws)
	{
		if(ws == false) return;
		fprintf(mFile,"\tsetAttr \".ws\" %i;\n", ws);

	}
	void setLastWrittenDmapAnimExtName(const string& lw)
	{
		if(lw == "NULL") return;
		fprintf(mFile,"\tsetAttr \".lw\" -type \"string\" ");
		lw.write(mFile);
		fprintf(mFile,";\n");

	}
	void setReceiveShadows(bool gs)
	{
		if(gs == true) return;
		fprintf(mFile,"\tsetAttr \".gs\" %i;\n", gs);

	}
	void getLightRadius()
	{
		fprintf(mFile,"\"%s.lr\"",mName.c_str());

	}
	void getCastSoftShadows()
	{
		fprintf(mFile,"\"%s.cw\"",mName.c_str());

	}
	void getUseDepthMapShadows()
	{
		fprintf(mFile,"\"%s.dms\"",mName.c_str());

	}
	void getReuseDmap()
	{
		fprintf(mFile,"\"%s.du\"",mName.c_str());

	}
	void getUseMidDistDmap()
	{
		fprintf(mFile,"\"%s.md\"",mName.c_str());

	}
	void getDmapFilterSize()
	{
		fprintf(mFile,"\"%s.fs\"",mName.c_str());

	}
	void getDmapResolution()
	{
		fprintf(mFile,"\"%s.dr\"",mName.c_str());

	}
	void getDmapBias()
	{
		fprintf(mFile,"\"%s.db\"",mName.c_str());

	}
	void getDmapFocus()
	{
		fprintf(mFile,"\"%s.df\"",mName.c_str());

	}
	void getDmapWidthFocus()
	{
		fprintf(mFile,"\"%s.dw\"",mName.c_str());

	}
	void getUseDmapAutoFocus()
	{
		fprintf(mFile,"\"%s.af\"",mName.c_str());

	}
	void getVolumeShadowSamples()
	{
		fprintf(mFile,"\"%s.nv\"",mName.c_str());

	}
	void getFogShadowIntensity()
	{
		fprintf(mFile,"\"%s.fsi\"",mName.c_str());

	}
	void getUseDmapAutoClipping()
	{
		fprintf(mFile,"\"%s.uc\"",mName.c_str());

	}
	void getDmapNearClipPlane()
	{
		fprintf(mFile,"\"%s.nc\"",mName.c_str());

	}
	void getDmapFarClipPlane()
	{
		fprintf(mFile,"\"%s.fcp\"",mName.c_str());

	}
	void getUseOnlySingleDmap()
	{
		fprintf(mFile,"\"%s.us\"",mName.c_str());

	}
	void getUseXPositiveDmap()
	{
		fprintf(mFile,"\"%s.xp\"",mName.c_str());

	}
	void getUseXNegativeDmap()
	{
		fprintf(mFile,"\"%s.xn\"",mName.c_str());

	}
	void getUseYPositiveDmap()
	{
		fprintf(mFile,"\"%s.yp\"",mName.c_str());

	}
	void getUseYNegativeDmap()
	{
		fprintf(mFile,"\"%s.yn\"",mName.c_str());

	}
	void getUseZPositiveDmap()
	{
		fprintf(mFile,"\"%s.zp\"",mName.c_str());

	}
	void getUseZNegativeDmap()
	{
		fprintf(mFile,"\"%s.zn\"",mName.c_str());

	}
	void getDmapUseMacro()
	{
		fprintf(mFile,"\"%s.dc\"",mName.c_str());

	}
	void getDmapName()
	{
		fprintf(mFile,"\"%s.smn\"",mName.c_str());

	}
	void getDmapLightName()
	{
		fprintf(mFile,"\"%s.ul\"",mName.c_str());

	}
	void getDmapSceneName()
	{
		fprintf(mFile,"\"%s.um\"",mName.c_str());

	}
	void getDmapFrameExt()
	{
		fprintf(mFile,"\"%s.uf\"",mName.c_str());

	}
	void getWriteDmap()
	{
		fprintf(mFile,"\"%s.ws\"",mName.c_str());

	}
	void getLastWrittenDmapAnimExtName()
	{
		fprintf(mFile,"\"%s.lw\"",mName.c_str());

	}
	void getReceiveShadows()
	{
		fprintf(mFile,"\"%s.gs\"",mName.c_str());

	}
protected:
	NonExtendedLightShapeNode(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType)
		:NonAmbientLightShapeNode(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_NONEXTENDEDLIGHTSHAPENODE_H__
