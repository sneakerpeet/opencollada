#include "COLLADAMaxStableHeaders.h"
#include "COLLADAMaxCOLLADAPlugin.h"

#include "COLLADAMaxVersionInfo.h"

namespace COLLADAMax
{

	const String COLLADAPlugin::EXTENSIONNAME = "dae";
	const String COLLADAPlugin::LONGDESCRIPTION = "New COLLADA Document";
	const String COLLADAPlugin::SHORTDESCRIPTION = "COLLADA NextGen";
	const String COLLADAPlugin::AUTHORNAME = "NetAllied Systems GmbH";
	const String COLLADAPlugin::COPYRIGHTMESSAGE = "Copyright 2008-2009 NetAllied Systems GmbH. Copyright 2006 Feeling Software. Based on Autodesk' 3dsMax COLLADASW Tools.";
	const String COLLADAPlugin::OTHERMESSAGE1 = "";
	const String COLLADAPlugin::OTHERMESSAGE2 = "";

	const String COLLADAPlugin::PLUGIN_VERSION_STRING = String("Version: 0.9.4");
	const String COLLADAPlugin::REVISION_STRING = (CURRENT_REVISION.empty() ? "" : String("Revision: ") + CURRENT_REVISION);
	const String COLLADAPlugin::PLATFORM_STRING = String("Platform: ") + CURRENT_PLATFORM;
	const String COLLADAPlugin::CONFIGURATION_STRING = String("Configuration: ") + CURRENT_CONFIGURATION;


	const String COLLADAPlugin::FATALERROR = "Fatal Error: exception caught.";

	const unsigned int COLLADAPlugin::PLUGINVERSION = 503;


	//--------------------------------------------------------------------
	COLLADAPlugin::COLLADAPlugin()
	{
	}
	
	//--------------------------------------------------------------------
	COLLADAPlugin::~COLLADAPlugin()
	{
	}

} // namespace COLLADAMax
