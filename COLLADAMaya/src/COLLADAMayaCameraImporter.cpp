/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of COLLADAFramework.

    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADAMayaStableHeaders.h"
#include "COLLADAMayaCameraImporter.h"
#include "COLLADAMayaVisualSceneImporter.h"

#include "COLLADAFWCamera.h"

#include <MayaDMCommands.h>


namespace COLLADAMaya
{

    const String CameraImporter::CAMERA_NAME = "Camera";


    //------------------------------
	CameraImporter::CameraImporter ( DocumentImporter* documentImporter ) 
        : BaseImporter ( documentImporter )
	{
	}
	
    //------------------------------
	CameraImporter::~CameraImporter()
	{
	}

    //------------------------------
    void CameraImporter::importCamera ( const COLLADAFW::Camera* camera )
    {
        // Get the parent transform node, which reference this camera.
        const COLLADAFW::UniqueId& cameraId = camera->getUniqueId ();
        VisualSceneImporter* visualSceneImporter = getDocumentImporter ()->getVisualSceneImporter ();

        // Check if the camera is already imported.
        if ( findMayaCameraNode ( cameraId ) != 0 ) return;

        // Get the transform nodes, which work with this camera instance.
        const UniqueIdVec* transformNodes = visualSceneImporter->findCameraTransformIds ( cameraId );
        if ( transformNodes == 0 )
        {
            MGlobal::displayError ( "No camera node which implements this camera!" );
            std::cerr << "No camera node which implements this camera!" << endl;
        }
        size_t numNodeInstances = transformNodes->size ();

        // The index value of the current geometry instance.
        size_t geometryInstanceIndex = 0;

        UniqueIdVec::const_iterator nodesIter = transformNodes->begin ();
        while ( nodesIter != transformNodes->end () )
        {
            // Get the maya node of the current transform node.
            const COLLADAFW::UniqueId& transformNodeId = *nodesIter;
            MayaNode* mayaTransformNode = visualSceneImporter->findMayaTransformNode ( transformNodeId );
            String transformNodeName = mayaTransformNode->getName ();

            // Get the path to the parent transform node.
            String transformNodePath = mayaTransformNode->getNodePath ();

            // The first reference is a direct one, the others are instances.
            if ( nodesIter == transformNodes->begin() )
            {
                // Create the current mesh node.
                createCamera ( camera, mayaTransformNode, numNodeInstances );
            }
            else
            {
                // Get the path to the mesh.
                MayaNode* mayaCameraNode = findMayaCameraNode ( cameraId );
                String cameraNodePath = mayaCameraNode->getNodePath ();

                // parent -shape -noConnections -relative -addObject "|pCube1|pCubeShape1" "pCube2";
                FILE* file = getDocumentImporter ()->getFile ();
                MayaDM::parentShape ( file, cameraNodePath, transformNodePath, false, true, true, true );
            }

            ++nodesIter;
        }
    }

    //------------------------------
    void CameraImporter::createCamera ( 
        const COLLADAFW::Camera* camera,  
        MayaNode* mayaTransformNode, 
        size_t numNodeInstances )
    {
        // Create a unique name.
        String cameraName = camera->getName ();
        if ( COLLADABU::Utils::equals ( cameraName, "" ) ) 
            cameraName = CAMERA_NAME;
        cameraName = mCameraIdList.addId ( cameraName );

        // Create a maya node object of the current node and push it into the map.
        const COLLADAFW::UniqueId& cameraId = camera->getUniqueId ();
        MayaNode mayaMeshNode ( cameraId, cameraName, mayaTransformNode );
        mMayaCameraNodesMap [ cameraId ] = mayaMeshNode;

        // Create the maya camera object and write it into the maya ascii file.
        FILE* file = getDocumentImporter ()->getFile ();
        MayaDM::Camera mayaCamera ( file, cameraName, mayaTransformNode->getNodePath () );

        const COLLADAFW::Camera::CameraType& cameraType = camera->getCameraType ();
        switch ( cameraType )
        {
        case COLLADAFW::Camera::ORTHOGRAPHIC:
            setOrthographicCameraAttributes ( camera, mayaCamera );
            break;
        case COLLADAFW::Camera::PERSPECTIVE:
            setPerspectiveCameraAttributes ( camera, mayaCamera );
            break;
        default:
            std::cerr << "Unknown camera type!" << endl;
            MGlobal::displayError ( "Unknown camera type!" );
            break;
        }

    }

    //------------------------------
    void CameraImporter::setPerspectiveCameraAttributes ( 
        const COLLADAFW::Camera* camera,
        MayaDM::Camera& mayaCamera )
    {
        mayaCamera.setOrthographic ( false );

        double nearClipPlane = camera->getNearClippingPlane ();
        nearClipPlane = toLinearUnit ( nearClipPlane );
        mayaCamera.setNearClipPlane ( nearClipPlane );

        double farClipPlane = camera->getFarClippingPlane ();
        farClipPlane = toLinearUnit ( farClipPlane );
        mayaCamera.setFarClipPlane ( farClipPlane );

        FILE* file = getDocumentImporter ()->getFile ();

        if ( camera->getHasAspectRatio () )
        {
            double aspectRatio = camera->getAspectRatio ();
            MayaDM::editCameraAspectRatio ( file, mayaCamera.getName (), aspectRatio );
        }
        else
        {
            double aspectRatio = camera->getXFov () / camera->getYFov ();
            MayaDM::editCameraAspectRatio ( file, mayaCamera.getName (), aspectRatio );
        }

        if ( camera->getHasYFovOrYMag () )
        {
            double verticalFieldOfView = camera->getYFov ();
            MayaDM::editCameraVerticalFieldOfView ( file, mayaCamera.getName (), verticalFieldOfView );
        }

        if ( camera->getHasXFovOrXMag () )
        {
            double horizontalFieldOfView = camera->getXFov ();
            MayaDM::editCameraHorizontalFieldOfView ( file, mayaCamera.getName (), horizontalFieldOfView );
        }
    }

    //------------------------------
    void CameraImporter::setOrthographicCameraAttributes ( 
        const COLLADAFW::Camera* camera, 
        MayaDM::Camera& mayaCamera )
    {
        mayaCamera.setOrthographic ( true );

        double nearClipPlane = camera->getNearClippingPlane ();
        nearClipPlane = toLinearUnit ( nearClipPlane );
        mayaCamera.setNearClipPlane ( nearClipPlane );

        double farClipPlane = camera->getFarClippingPlane ();
        farClipPlane = toLinearUnit ( farClipPlane );
        mayaCamera.setFarClipPlane ( farClipPlane );

        FILE* file = getDocumentImporter ()->getFile ();

        if ( camera->getHasAspectRatio () )
        {
            double aspectRatio = camera->getAspectRatio ();
            MayaDM::editCameraAspectRatio ( file, mayaCamera.getName (), aspectRatio );
        }
        else
        {
            double aspectRatio = camera->getXMag () / camera->getYMag ();
            MayaDM::editCameraAspectRatio ( file, mayaCamera.getName (), aspectRatio );
        }

        if ( camera->getHasYFovOrYMag () )
        {
            double orthographicHeight = camera->getYMag () / 2;
            MayaDM::editCameraOrthographicHeight ( file, mayaCamera.getName (), orthographicHeight );
        }

        if ( camera->getHasXFovOrXMag () )
        {
            double orthographicWidth = camera->getXMag () / 2;
            MayaDM::editCameraOrthographicWidth ( file, mayaCamera.getName (), orthographicWidth );
        }
    }

    // --------------------------------------------
    MayaNode* CameraImporter::findMayaCameraNode ( const COLLADAFW::UniqueId& cameraId ) 
    {
        UniqueIdMayaNodesMap::iterator it = mMayaCameraNodesMap.find ( cameraId );
        if ( it != mMayaCameraNodesMap.end () )
            return &(*it).second;

        return NULL;
    }

} // namespace COLLADAMaya
