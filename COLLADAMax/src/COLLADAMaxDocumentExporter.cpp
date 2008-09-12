/*
    Copyright (c) 2008 NetAllied Systems GmbH

	This file is part of COLLADAMax.

    Portions of the code are:
    Copyright (c) 2005-2007 Feeling Software Inc.
    Copyright (c) 2005-2007 Sony Computer Entertainment America
    
    Based on the 3dsMax COLLADA Tools:
    Copyright (c) 2005-2006 Autodesk Media Entertainment
	
    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/


#include "ColladaMaxStableHeaders.h"

#include "COLLADAMaxDocumentExporter.h"
#include "COLLADAMaxGeometryExporter.h"
#include "COLLADAMaxControllerExporter.h"
#include "COLLADAMaxVisualSceneExporter.h"
#include "COLLADAMaxEffectExporter.h"
#include "COLLADAMaxAnimationExporter.h"
#include "COLLADAMaxMaterialExporter.h"
#include "COLLADAMaxImageExporter.h"
#include "COLLADAMaxCameraExporter.h"
#include "COLLADAMaxLightExporter.h"

#include "COLLADAAsset.h"
#include "COLLADAScene.h"
#include "COLLADASWC.h"

#include <max.h>

namespace COLLADAMax
{

    const String DocumentExporter::SCENE_ID = "MaxScene";

    //---------------------------------------------------------------
    DocumentExporter::DocumentExporter ( Interface * i, const String &filepath )
            : 
			mOptions(i),
			mMaxInterface ( i ),
            mStreamWriter ( filepath ),
			mOutputFileUri ( filepath ),
            mExportSceneGraph ( new ExportSceneGraph(mMaxInterface->GetRootNode()) ),
			mDeleteExportSceneGraph(true)
    {
		String dir, baseName, extension;
		mOutputFileUri.pathComponents(mOutputDir, baseName, extension);
		mOutputFileName = baseName + "." + extension;
	}


	//---------------------------------------------------------------
	DocumentExporter::DocumentExporter ( Interface * i, ExportSceneGraph* exportSceneGraph, const String &filepath, const Options& options )
		: 
		mOptions( options ),
		mMaxInterface ( i ),
		mStreamWriter ( filepath ),
		mOutputFileUri ( filepath ),
		mExportSceneGraph ( exportSceneGraph ),
		mDeleteExportSceneGraph(false)
	{
		String dir, baseName, extension;
		mOutputFileUri.pathComponents(mOutputDir, baseName, extension);
		mOutputFileName = baseName + "." + extension;
	}

	//---------------------------------------------------------------
	DocumentExporter::~DocumentExporter()
	{
		if ( mDeleteExportSceneGraph )
			delete mExportSceneGraph;
	}


	//---------------------------------------------------------------
	void DocumentExporter::exportRootMaxScene()
	{
		if ( createExportSceneGraph() )
			exportMaxScene();
	}

    //---------------------------------------------------------------
    void DocumentExporter::exportMaxScene()
    {
        mStreamWriter.startDocument();

		createExporters();

		exportAsset();
		exportEffects();
		exportMaterials();
		exportGeometries();
		exportControllers();
		exportCameras();
		exportLights();
		exportImages();
		exportVisualScenes();
		if ( mOptions.getExportAnimations() )
			exportAnimations();
		exportScene();

		deleteExporters();

        mStreamWriter.endDocument();

		const ExportSceneGraph::XRefSceneGraphList& sceneGraphList = mExportSceneGraph->getXRefSceneGraphList();

		for ( ExportSceneGraph::XRefSceneGraphList::const_iterator it = sceneGraphList.begin(); it!=sceneGraphList.end(); ++it )
		{
			String outputFileName = getXRefOutputPath(it->exportFileURI);
			DocumentExporter document(mMaxInterface, it->exportSceneGraph, outputFileName, mOptions);
			document.exportMaxScene();
		}
    }

    //---------------------------------------------------------------
    bool DocumentExporter::createExportSceneGraph()
    {
        return mExportSceneGraph->create ( mOptions.getExportSelected() );
    }

    //---------------------------------------------------------------
    void DocumentExporter::createExporters()
    {
		mAnimationExporter = new AnimationExporter ( &mStreamWriter, this );
        mEffectExporter = new EffectExporter ( &mStreamWriter, mExportSceneGraph, this );
        mMaterialExporter = new MaterialExporter ( &mStreamWriter, this );

    }

    //---------------------------------------------------------------
    void DocumentExporter::exportAsset()
    {
        COLLADA::Asset asset ( &mStreamWriter );

        // Add contributor information
        // Set the author
        String userName = getEnvironmentVariable ( "USERNAME" );

        if ( userName.empty() )
            userName = getEnvironmentVariable ( "USER" );

        if ( !userName.empty() )
            asset.getContributor().mAuthor = String ( userName );

        const TSTR& filename = getMaxInterface() ->GetCurFilePath();

        asset.getContributor().mSourceData = COLLADA::Utils::FILE_PROTOCOL + COLLADA::Utils::UriEncode ( String ( filename.data() ) );

        asset.getContributor().mAuthoringTool = "COLLADAMax";


        // set *system* unit information
        int systemUnitType;

        float systemUnitScale;

        GetMasterUnitInfo ( &systemUnitType, &systemUnitScale );

        switch ( systemUnitType )
        {

        case UNITS_INCHES:
            asset.setUnit ( "inch", systemUnitScale * 0.0254f );
            break;

        case UNITS_FEET:
            asset.setUnit ( "feet", systemUnitScale * 0.3048f );
            break;

        case UNITS_MILES:
            asset.setUnit ( "mile", systemUnitScale * 1609.344f );
            break;

        case UNITS_MILLIMETERS:
            asset.setUnit ( "millimeter", systemUnitScale * 0.001f );
            break;

        case UNITS_CENTIMETERS:
            asset.setUnit ( "centimeter", systemUnitScale * 0.01f );
            break;

        case UNITS_METERS:
            asset.setUnit ( "meter", systemUnitScale );
            break;

        case UNITS_KILOMETERS:
            asset.setUnit ( "kilometer", systemUnitScale * 1000.0f );
            break;

        default:
            break;
        }

        asset.setUpAxisType ( COLLADA::Asset::Z_UP );

        asset.add();
    }

    //---------------------------------------------------------------
    void DocumentExporter::exportGeometries()
    {
        GeometriesExporter geometriesExporter ( &mStreamWriter, mExportSceneGraph, this );
        geometriesExporter.doExport();
    }

	//---------------------------------------------------------------
	void DocumentExporter::exportControllers()
	{
		ControllerExporter controllerExporter ( &mStreamWriter, mExportSceneGraph, this  );
		controllerExporter.doExport();
	}

	//---------------------------------------------------------------
	void DocumentExporter::exportCameras()
	{
		CameraExporter cameraExporter(&mStreamWriter, mExportSceneGraph, this);
		cameraExporter.doExport();
	}

	//---------------------------------------------------------------
	void DocumentExporter::exportLights()
	{
		LightExporter lightExporter(&mStreamWriter, mExportSceneGraph, this);
		lightExporter.doExport();
	}

    //---------------------------------------------------------------
    void DocumentExporter::exportEffects()
    {
        mEffectExporter->doExport();
    }

    //---------------------------------------------------------------
    void DocumentExporter::exportMaterials()
    {
        mMaterialExporter->doExport();
    }

    //---------------------------------------------------------------
    void DocumentExporter::exportImages()
    {
        ImageExporter imageExporter ( &mStreamWriter, this );
        imageExporter.doExport();
    }

    //---------------------------------------------------------------
    void DocumentExporter::exportVisualScenes()
    {
        VisualSceneExporter visualSceneExporter ( &mStreamWriter, mExportSceneGraph, SCENE_ID, this );
        visualSceneExporter.doExport();
    }

    //---------------------------------------------------------------
    void DocumentExporter::exportAnimations()
    {
        mAnimationExporter->doExport();
    }

    //---------------------------------------------------------------
    void DocumentExporter::exportScene()
    {
        COLLADA::Scene scene ( &mStreamWriter, COLLADA::URI ( "", SCENE_ID ) );
        scene.add();
    }

    //---------------------------------------------------------------
    void DocumentExporter::deleteExporters()
    {
        delete mEffectExporter;
        mEffectExporter = 0;

        delete mMaterialExporter;
        mMaterialExporter = 0;

        delete mAnimationExporter;
        mAnimationExporter = 0;
    }

    //---------------------------------------------------------------
    String DocumentExporter::getEnvironmentVariable ( const String & variableName )
    {
        char * buffer;
        size_t numberOfElements;
        errno_t error = _dupenv_s ( &buffer, &numberOfElements, variableName.c_str() );

        if ( error != 0 )
        {
            free ( buffer );
            return String();
        }

        String variableValue ( buffer, numberOfElements-1 );

        free ( buffer );
        return variableValue;
    }


	//---------------------------------------------------------------
	bool DocumentExporter::showExportOptions(bool suppressPrompts)
	{
		if (!suppressPrompts) 
		{
			// Prompt the user with our dialogbox, and get all the options.
			// The user may cancel the export at this point.
			if (!mOptions.ShowDialog()) 
				return false;
		}
		else if (!mOptions.getSampleAnimation())
		{
			Interval animRange = GetCOREInterface()->GetAnimRange();
			int sceneStart = animRange.Start();
			int sceneEnd = animRange.End();
			mOptions.setAnimBounds(sceneStart, sceneEnd);
		}

		// Set relative/absolute export
	//	colladaDocument->GetFileManager()->SetForceAbsoluteFlag(!options->ExportRelativePaths());

		return true;
	}

	//---------------------------------------------------------------
	bool DocumentExporter::isExportedObject( ObjectIdentifier& object )
	{
		return mExportedObjects.find(object) != mExportedObjects.end();
	}

	//---------------------------------------------------------------
	void DocumentExporter::insertExportedObject( ObjectIdentifier& object, ExportNode* objectExportNode )
	{
		mExportedObjects[object] = objectExportNode;
	}

	//---------------------------------------------------------------
	ExportNode* DocumentExporter::getExportedObjectExportNode( ObjectIdentifier& object )
	{
		ObjectExportNodeMap::const_iterator it = mExportedObjects.find(object);
		if ( it != mExportedObjects.end() )
			return it->second;
		else
			return 0;
	}

	COLLADAMax::String DocumentExporter::getXRefOutputPath( const COLLADA::URI& sourceFile ) const
	{
		const String& xRefOutputFileDir = getOptions().getXRefOutputDir();
		if ( xRefOutputFileDir.empty() )
			return getOutputDir() + "\\" + sourceFile.getPathFileBase() + ".dae"; 
		else
			return xRefOutputFileDir + "\\" + sourceFile.getPathFileBase() + ".dae"; 
	}

	//---------------------------------------------------------------
	bool ObjectIdentifier::operator<( const ObjectIdentifier& other ) const
	{
		if ( mObject < other.mObject )
			return true;
		if ( mObject > other.mObject )
			return false;

		if ( mIdentificationNumber < other.mIdentificationNumber )
			return true;
		if ( mIdentificationNumber > other.mIdentificationNumber )
			return false;

		return false;
	}
}
