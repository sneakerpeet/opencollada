/*
    Copyright (c) 2008-2009 NetAllied Systems GmbH

    This file is part of COLLADASaxFrameworkLoader.

    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADA_LOADER_H__
#define __COLLADA_LOADER_H__

#include "COLLADASaxFWLPrerequisites.h"
#include "COLLADASaxFWLGeometryMaterialIdInfo.h"
#include "COLLADASaxFWLSidTreeNode.h"
#include "COLLADASaxFWLKinematicsIntermediateData.h"

#include "COLLADAFWILoader.h"
#include "COLLADAFWLoaderUtils.h"
#include "COLLADAFWUniqueId.h"
#include "COLLADAFWTypes.h"
#include "COLLADAFWSkinController.h"

#include "COLLADABUHashMap.h"
#include "COLLADABUHashFunctions.h"
#include "COLLADABUURI.h"


namespace COLLADAFW
{
	class IWriter;
	class VisualScene;
	class LibraryNodes;
	class Effect;
	class Light;
	class Camera;
	class Formula;
	class AnimationList;
	class MorphController;
}


namespace COLLADASaxFWL
{

	class IErrorHandler;
	class DocumentProcessor;
	class PostProcessor;


	typedef std::list<String> StringList;

	typedef std::list<COLLADABU::URI> URIList;

	static StringList EMPTY_STRING_LIST = StringList();



	/** Loader to a COLLADA document and all the documents that are referenced it.*/
	class Loader : public COLLADAFW::ILoader 
	{
	public:
		/** Maps the unique id of each geometry to the corresponding ColladaSymbolMaterialIdMap.*/
		typedef std::map<COLLADAFW::UniqueId, GeometryMaterialIdInfo> UniqueIdMeshMaterialIdInfoMap;

		typedef std::map<String, COLLADAFW::TextureMapId> StringTextureMapIdMap;

		/** Flags for each type of object that are passed by the IWriter interface. */
		enum ObjectFlags
		{
			NO_FLAG                    = 0,
			ASSET_FLAG                 = 1<< 0,
			SCENE_FLAG                 = 1<< 1,
			VISUAL_SCENES_FLAG         = 1<< 2,
			LIBRARY_NODES_FLAG         = 1<< 3,
			GEOMETRY_FLAG              = 1<< 4,
			MATERIAL_FLAG              = 1<< 5,
			EFFECT_FLAG                = 1<< 6,
			CAMERA_FLAG                = 1<< 7,
			IMAGE_FLAG                 = 1<< 8,
			LIGHT_FLAG                 = 1<< 9,
			ANIMATION_FLAG             = 1<<10,
			ANIMATION_LIST_FLAG        = 1<<11,
			SKIN_CONTROLLER_DATA_FLAG  = 1<<12,
			CONTROLLER_FLAG            = 1<<13,
			FORMULA_FLAG               = 1<<14,
			KINEMATICS_FLAG            = 1<<15,

			ALL_OBJECTS_MASK           = (1<<16) - 1,
		};

	public:
		typedef COLLADABU::HashMap<COLLADABU::URI, COLLADAFW::UniqueId, unsigned long, COLLADABU::calculateHash> URIUniqueIdMap;

		typedef COLLADABU::HashMap<COLLADABU::URI, COLLADAFW::FileId, unsigned long, COLLADABU::calculateHash> URIFileIdMap;

		/** Maps file id to uri.*/
		typedef std::map<COLLADAFW::FileId, COLLADABU::URI> FileIdURIMap;

		/** Maps the id of a collada element to the corresponding sit tree node.*/
		typedef std::map<String /*id*/, SidTreeNode*> IdStringSidTreeNodeMap;

		/** Maps unique ids of animation list to the corresponding animation list.*/
		typedef std::map< COLLADAFW::UniqueId , COLLADAFW::AnimationList* > UniqueIdAnimationListMap;

		/** List of visual scenes.*/
		typedef std::vector<COLLADAFW::VisualScene*> VisualSceneList;

		/** List of library nodes.*/
		typedef std::vector<COLLADAFW::LibraryNodes*> LibraryNodesList;

		/** List of effects.*/
		typedef std::vector<COLLADAFW::Effect*> EffectList;

		/** List of lights.*/
		typedef std::vector<COLLADAFW::Light*> LightList;

		/** List of cameras.*/
		typedef std::vector<COLLADAFW::Camera*> CameraList;

		/** List of morph controller.*/
		typedef std::vector<COLLADAFW::MorphController*> MorphControllerList;

		/** Maps unique ids of skin data to the sids of the joints of this skin controller.*/
		typedef std::map< COLLADAFW::UniqueId, StringList> SkinDataJointSidsMap;

		/** Maps unique ids of skin data to the source uri string.*/
		typedef std::map< COLLADAFW::UniqueId/*skin controller data*/, COLLADABU::URI/*source uri string*/> SkinDataSkinSourceMap;

		/** Set of SkinControllers.*/
		typedef std::set< COLLADAFW::SkinController, bool(*)(const COLLADAFW::SkinController& lhs, const COLLADAFW::SkinController& rhs)> SkinControllerSet;

		/** Data that needs to be store, intermediately, to assign controllers. One struct for each 
		instance controller.*/
		struct InstanceControllerData
		{
			/** List of URIs of the skeleton roots, ie the uris in the COLLADA skeleton element.*/
			URIList skeletonRoots;

			/** The instance controller that instantiates the controller.*/
			COLLADAFW::InstanceController* instanceController;
		};

		/** List of all instance controllers that reference the same controller, ie share the same skin 
		data for skin controllers.*/
		typedef std::list<InstanceControllerData> InstanceControllerDataList;

		/** Maps each controller data unique id to the list of nodes instantiating it.*/
		typedef std::map<COLLADAFW::UniqueId,InstanceControllerDataList> InstanceControllerDataListMap;


		/** List of formulas.*/
		typedef std::vector<COLLADAFW::Formula*> FormulaList;

	public:
		const static InstanceControllerDataList EMPTY_INSTANCE_CONTROLLER_DATALIST;

	private:
		/** The version of the collada document.*/
		COLLADAVersion mCOLLADAVersion;

		/** Loader utils that will help us to fill the model.*/
		COLLADAFW::LoaderUtils mLoaderUtil;

		/** The writer that will be fed by this loader.*/
		COLLADAFW::IWriter* mWriter;

		/** Maps each already processed dae element to its COLLADAFW::UniqueId. */
		URIUniqueIdMap mURIUniqueIdMap;

		/** Maps each uri to the file id assigned to it. The Uris need to have empty fragments.*/
		URIFileIdMap mURIFileIdMap;

		/** Maps each file id, already assigned to an uri, to that uri.*/
		FileIdURIMap mFileIdURIMap;

		/** The file id that will be used for the next file.*/
		COLLADAFW::FileId mNextFileId;

		/** The file id of the file currently being loaded.*/
		COLLADAFW::FileId mCurrentFileId;

		/** Maps the unique id of each geometry to the corresponding GeometryMaterialIdInfo.*/
		UniqueIdMeshMaterialIdInfoMap mGeometryMeshMaterialIdInfoMapMap;

		/** The error handler to pass the errors to.*/
		IErrorHandler* mErrorHandler;

		/** The TextureMapId that will be assigned to the next unknown texture map semantic.*/
		COLLADAFW::TextureMapId mNextTextureMapId;

		/** Maps the semantic name of a texture map to the TextureMapId used in the framework.*/
		StringTextureMapIdMap mTextureMapSemanticTextureMapIdMap;

		/** A combination of ObjectFlags, indicating which objects should be parsed during the 
		parse process.*/
		int mObjectFlags;

		/** A combination of ObjectFlags, indicating which objects have be parsed already.*/
		int mParsedObjectFlags;

		/** The root node of the sid tree. This tree is used to resolve sids.*/
		SidTreeNode *mSidTreeRoot;

		/** Maps the id of a collada element to the corresponding sit tree node.*/
		IdStringSidTreeNodeMap mIdStringSidTreeNodeMap;

		/** List of all visual scenes in the file. They are send to the writer and deleted, when the file has 
		completely been parsed.*/
		VisualSceneList mVisualScenes;

		/** List of all library nodes in the file. They are send to the writer and deleted, when the file has 
		completely been parsed.*/
		LibraryNodesList mLibraryNodes;

		/** List of all effects in the file. They are send to the writer and deleted, when the file has 
		completely been parsed.*/
		EffectList mEffects;

		/** List of all lights in the file. They are send to the writer and deleted, when the file has 
		completely been parsed.*/
		LightList mLights;

		/** List of all cameras in the file. They are send to the writer and deleted, when the file has 
		completely been parsed.*/
		CameraList mCameras;

		/** List of all effects in the file. They are send to the writer and deleted, when the file has 
		completely been parsed. This is required to assign animations of the morph weights.*/
		MorphControllerList mMorphControllerList;

		/** Maps unique ids of skin data to the sids of the joints of this skin controller.*/
		SkinDataJointSidsMap mSkinDataJointSidsMap;

		/** Maps the Unique generated from the id of the COLLADA controller element to the 
		InstanceControllerDataList containing all instance controllers that reference the same controller.*/
		InstanceControllerDataListMap mInstanceControllerDataListMap;

		/** Maps unique ids of skin data to the source uri string.*/
		SkinDataSkinSourceMap mSkinDataSkinSourceMap;

		/** Set of all SkinController already created and written.*/
		SkinControllerSet mSkinControllerSet;


		/** Maps unique ids of animation list to the corresponding animation list. All animation list in this map 
		will be deleted by the FileLoader.*/
		UniqueIdAnimationListMap mUniqueIdAnimationListMap;

		/** Intermediate data to build up the kinematics after the COLLADA file has been parsed.*/
		KinematicsIntermediateData mKinematicsIntermediateData;

		/** List of all formulas in the file. They are send to the writer and deleted, when the file has 
		completely been parsed. This is required to resolve referenced elements like parameters and other formulas.*/
		FormulaList mFormulas;

	public:

        /** Constructor. */
		Loader( IErrorHandler* errorHandler = 0 );

        /** Destructor. */
		virtual ~Loader();

		/** The version of the collada document.*/
		COLLADAVersion getCOLLADAVersion() const { return mCOLLADAVersion; }

        /** Starts loading the model and feeds the writer with data.
		@param fileName The name of the fills that should be loaded.
		@param writer The writer that should be fed with data.
		@param objectFlags The flags indicating which objects should be loaded
		@return True, if loading succeeded, false otherwise.*/
		virtual bool loadDocument(const String& fileName, COLLADAFW::IWriter* writer );

		/** Sets the flags indicating which objects should be loaded.
		@param objectFlags The flags indicating which objects should be loaded.*/
		void setObjectFlags( int objectFlags ) { mObjectFlags = objectFlags; }

	private:
		friend class IFilePartLoader;
		friend class FileLoader;
		friend class PostProcessor;
		friend class DocumentProcessor;

		/** The version of the collada document.*/
		void setCOLLADAVersion(COLLADAVersion cOLLADAVersion) { mCOLLADAVersion = cOLLADAVersion; }

		/** The error handler to pass the errors to.*/
		IErrorHandler* getErrorHandler() {return mErrorHandler;}

		/** Returns the COLLADAFW::UniqueId of the element with uri @a uri. If the uri has been 
		passed to this method before, the same 	COLLADAFW::UniqueId will be returned, if not, a 
		new one is created.
		@param uri The uri of the element to get the COLLADAFW::UniqueId for
		@param classId The COLLADAFW::ClassId of the object that will be created for @a element.
		@return The elements COLLADAFW::UniqueId */
		const COLLADAFW::UniqueId& getUniqueId(const COLLADABU::URI& uri, COLLADAFW::ClassId classId);

		/** Returns the COLLADAFW::UniqueId of the element with uri @a uri. If the uri has been 
		passed to this method before, the same 	COLLADAFW::UniqueId will be returned, if not, an 
		invalid unique id will be returned.
		@param uri The uri of the element to get the COLLADAFW::UniqueId for
		@return The elements COLLADAFW::UniqueId or COLLADAFW::UniqueId::INVALID*/
		const COLLADAFW::UniqueId& getUniqueId(const COLLADABU::URI& uri);

		/** Returns the COLLADAFW::UniqueId of an element with no uri.  At each call a new 
		COLLADAFW::UniqueId will be created and returned. Use this member for collada elements that
		do not have an id.
		@param classId The COLLADAFW::ClassId of the object that will be created for @a element.
		@return The elements COLLADAFW::UniqueId */
		COLLADAFW::UniqueId getUniqueId(COLLADAFW::ClassId classId);

		/** Returns the file id of the file pointed to by the path in @a uri. If @a uri is relative, 
		the file id of the current file is returned. If the an uri with the same path has been passed to 
		this method before, the same file id is returned, if not a new one is created.*/
		COLLADAFW::FileId getFileId(const COLLADABU::URI& uri);

		/** Returns the Uri the file id @a fileId was assigned to by getFileId(). If @a fileId has not been 
		assigned to any Uri, an invalid uri is returned.*/
		const COLLADABU::URI& getFileUri( COLLADAFW::FileId fileId );

		/** Add the pair of @a fileId and @a uri to mURIFileIdMap and mFileIdURIMap. It is assumed, neither 
		@a fileId nor @a uri have been passed to that method before.*/
		void addFileIdUriPair( COLLADAFW::FileId fileId, const COLLADABU::URI& uri );

		/** Returns the GeometryMaterialIdInfo object of the geometry with @a uniqueId. If this method has 
		not been called before with the same uniqueId, an empty GeometryMaterialIdInfo is created, added to
		the map and returned.*/
		GeometryMaterialIdInfo& getMeshMaterialIdInfo( const COLLADAFW::UniqueId& uniqueId);

		/** Returns TextureMapId for @a semantic. Successive call with same semantic return the same TextureMapId.*/
		COLLADAFW::TextureMapId getTextureMapIdBySematic( const String& semantic );

		/** The root node of the sid tree. This tree is used to resolve sids.*/
		SidTreeNode * getSidTreeRoot() { return mSidTreeRoot; }

		/** Maps the id of a collada element to the corresponding sit tree node.*/
		IdStringSidTreeNodeMap& getIdStringSidTreeNodeMap() { return mIdStringSidTreeNodeMap; }

		/** List of all visual scenes in the file. They are send to the writer and deleted, when the file has 
		completely been parsed.*/
		VisualSceneList& getVisualScenes() { return mVisualScenes; }

		/** List of all library nodes in the file. They are send to the writer and deleted, when the file has 
		completely been parsed.*/
		LibraryNodesList& getLibraryNodes() { return mLibraryNodes; }

		/** List of all effects in the file. They are send to the writer and deleted, when the file has 
		completely been parsed.*/
		EffectList& getEffects() { return mEffects; }

		/** List of all lights in the file. They are send to the writer and deleted, when the file has 
		completely been parsed.*/
		LightList& getLights() { return mLights; }

		/** List of all cameras in the file. They are send to the writer and deleted, when the file has 
		completely been parsed.*/
		CameraList& getCameras() { return mCameras; }

		/** Returns the intermediate data to build up the kinematics after the COLLADA file has been parsed.*/
		KinematicsIntermediateData& getKinematicsIntermediateData() { return mKinematicsIntermediateData; }

		/** List of all formulas in the file. They are send to the writer and deleted, when the file has 
		completely been parsed. This is required to resolve referenced elements like parameters and other formulas.*/
		FormulaList& getFormulaList() { return mFormulas; }

		/** Maps unique ids of animation list to the corresponding animation list. All animation list in this map 
		will be deleted by the FileLoader.*/
		UniqueIdAnimationListMap& getUniqueIdAnimationListMap() { return mUniqueIdAnimationListMap; }

		/** List of all effects in the file. They are send to the writer and deleted, when the file has 
		completely been parsed. This is required to assign animations of the morph weights.*/
		MorphControllerList& getMorphControllerList() { return mMorphControllerList; }

		/** Maps unique ids of skin data to the sids of the joints of this skin controller.*/
		SkinDataJointSidsMap& getSkinDataJointSidsMap() { return mSkinDataJointSidsMap; }
		
		/** Maps the Unique generated from the id of the COLLADA controller element to the 
		InstanceControllerDataList containing all instance controllers that reference the same controller.*/
		InstanceControllerDataListMap& getInstanceControllerDataListMap() { return mInstanceControllerDataListMap; }

		/** Maps unique ids of skin data to the source uri string.*/
		SkinDataSkinSourceMap& getSkinDataSkinSourceMap() { 
			return mSkinDataSkinSourceMap; 
		}

		/** Set of all SkinController already created and written.*/
		SkinControllerSet& getSkinControllerSet() { return mSkinControllerSet; }

		/** Compares to SkinControllers. The comparison is suitable for using SkinController as key in stl
		containers but has no deeper meaning. The unique id of the SkinControllers themselves is not
		taken into account. Is basically compares if two SkinControllers describe exactly the same skin controller
		i.e. have the same source, joints and SkinControllerData.*/
		static bool compare( const COLLADAFW::SkinController& lhs, const COLLADAFW::SkinController& rhs);

		/** Returns the writer the data will be written to.*/
		COLLADAFW::IWriter* writer(){ return mWriter; }


        /** Disable default copy ctor. */
		Loader( const Loader& pre );

        /** Disable default assignment operator. */
		const Loader& operator= ( const Loader& pre );


	};

} // namespace COLLADA

#endif // __COLLADA_LOADER_H__
