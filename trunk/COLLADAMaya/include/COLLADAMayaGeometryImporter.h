/*
    Copyright (c) 2008-2009 NetAllied Systems GmbH

	This file is part of COLLADAMaya.

    Portions of the code are:
    Copyright (c) 2005-2007 Feeling Software Inc.
    Copyright (c) 2005-2007 Sony Computer Entertainment America
    Copyright (c) 2004-2005 Alias Systems Corp.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADA_MAYA_GEOMETRY_IMPORTER_H__
#define __COLLADA_MAYA_GEOMETRY_IMPORTER_H__

#include "COLLADAMayaStableHeaders.h"
#include "COLLADAMayaBaseImporter.h"
#include "COLLADAMayaNode.h"
#include "COLLADAMayaShadingBinding.h"

#include "COLLADAFWMesh.h"

#include "Math/COLLADABUMathVector3.h"

#include "MayaDMTypes.h"
#include "MayaDMMesh.h"
#include "MayaDMGroupId.h"

#include <vector>


namespace COLLADAMaya
{

    /** Declares the importer implementation to import the geometries. */
    class GeometryImporter : public BaseImporter
    {

    private:

        /** The standard name for geometry without name. */
        static const String GEOMETRY_NAME;

    public:

        /**
        * Assign the group to the unique geometry id, the transform node 
        * to the mesh instance and the index of the geometry's primitives.
        */
        class GroupAssignment
        {
        private:
            MayaDM::GroupId mGroupId;
            COLLADAFW::MaterialId mShadingEngineId;
            size_t mGeometryInstanceIndex;
            size_t mPrimitiveIndex;
        public:
            GroupAssignment () {}
            virtual ~GroupAssignment () {}

            const MayaDM::GroupId& getGroupId () const { return mGroupId; }
            void setGroupId ( MayaDM::GroupId& val ) { mGroupId = val; }

            const COLLADAFW::MaterialId& getShadingEngineId () const { return mShadingEngineId; }
            void setShadingEngineId ( const COLLADAFW::MaterialId& val ) { mShadingEngineId = val; }

            const size_t getGeometryInstanceIndex () const { return mGeometryInstanceIndex; }
            void setGeometryInstanceIndex ( const size_t val ) { mGeometryInstanceIndex = val; }

            const size_t getPrimitiveIndex () const { return mPrimitiveIndex; }
            void setPrimitiveIndex ( const size_t val ) { mPrimitiveIndex = val; }
        };

    private:

        /**
        * The list of the unique maya mesh node names.
        */
        COLLADABU::IDList mMeshNodeIdList;

        /** 
         * The map holds the unique ids of the geometry nodes to the maya specific nodes. 
         */
        UniqueIdMayaNodeMap mMayaMeshNodesMap;

        /** 
        * The map holds the unique ids of the geometry nodes to the maya controller mesh nodes. 
        */
        UniqueIdMayaDMMeshMap mMayaDMControllerMeshNodesMap;

        /** 
        * The map holds the unique ids of the geometry nodes to the specific nodes. 
        */
        UniqueIdMayaDMMeshMap mMayaDMMeshNodesMap;

        /** 
         * The map holds the number of primitive elements to the geometry id.
         */
        UniqueIdElementCountMap mGeometryIdPrimitivesCountMap;

        /**
         * The map holds for every geometry's shading engine a list of 
         * the index values of the geometry's primitives.
         */
        CombinedIdIndicesMap mShadingEnginePrimitivesMap;

        /**
         * Assign the group to the unique geometry id, the transform node 
         * to the mesh instance and the shading engine.
         */
        ShadingBindingGroupInfoMap mShadingBindingGroupMap;

        /**
         * The map holds the list of components of a mesh. Needed for the groupParts of a mesh's 
         * material, if the mesh element has a controller element (then the groups has to be 
         * organised in groupParts).
         */
        std::map<COLLADAFW::UniqueId, std::vector<MayaDM::componentList>> mMeshComponentLists;

    public:

        /** Constructor. */
        GeometryImporter ( DocumentImporter* documentImporter );

        /** Destructor. */
        virtual ~GeometryImporter ();

        /** Imports the geometry element. */
        void importGeometry ( const COLLADAFW::Geometry* geometry );

        /** 
        * The map holds the unique ids of the nodes to the maya specific nodes. 
        */
        const MayaNode* findMayaMeshNode ( const COLLADAFW::UniqueId& uniqueId ) const;

        /** 
        * The map holds the unique ids of the nodes to the maya specific nodes. 
        */
        MayaNode* findMayaMeshNode ( const COLLADAFW::UniqueId& uniqueId );

        /** 
        * The map holds the unique ids of the nodes to the  specific nodes. 
        */
        MayaDM::Mesh* findMayaDMMeshNode ( const COLLADAFW::UniqueId& uniqueId );

        /** 
        * The map holds the unique ids of the nodes to the  specific nodes. 
        */
        const MayaDM::Mesh* findMayaDMMeshNode ( const COLLADAFW::UniqueId& uniqueId ) const;

        /** 
        * The map holds the unique ids of the nodes to the  specific nodes. 
        */
        const MayaDM::Mesh* findMayaDMControllerMeshNode ( const COLLADAFW::UniqueId& uniqueId ) const;

        /** 
        * The map holds the number of primitive elements to the geometry id.
        */
        const size_t findPrimitivesCount ( const COLLADAFW::UniqueId& geometryId );

        /**
         * Returns a pointer to the vector of indices of the given geometry and shading engine.
         * The map holds for every geometry's shading engine a list of the index values of the 
         * geometry's primitives.
         */
        std::vector<size_t>* getShadingEnginePrimitiveIndices ( 
            const COLLADAFW::UniqueId& geometryId, 
            const COLLADAFW::MaterialId shadingEngineId );

        /**
        * Assign the group to the unique geometry id, the transform node 
        * to the mesh instance and the index of the geometry's primitives.
        */
        const ShadingBindingGroupInfoMap& getShadingBindingGroupMap () const { return mShadingBindingGroupMap; }

        /**
        * Get the groupId assignement data for the current geometry under the transform.
        */
        std::vector<GroupInfo>* findShadingBindingGroups ( 
            const COLLADAFW::UniqueId& geometryId, 
            const COLLADAFW::UniqueId& transformId, 
            const COLLADAFW::MaterialId& shadingEngineId );

        /**
        * Get the groupId assignement data for the current geometry under the transform.
        */
        std::vector<GroupInfo>* findShadingBindingGroups ( const ShadingBinding& shadingBinding );

        /**
        * The map holds the list of components of a mesh. Needed for the groupParts of a mesh's 
        * material, if the mesh element has a controller element (then the groups has to be 
        * organised in groupParts).
        */
        const std::vector<MayaDM::componentList>* findComponentLists ( const COLLADAFW::UniqueId& geometryId );

        /**
         * Writes the connection attributes into the maya ascii file. 
         * If there exist a controller for the current mesh, we also need to organize the groupIds 
         * of the mesh's primitive elements in groupParts (make the connections for this). 
         */
        void writeConnections ();

    private:

        /** 
        * Imports the data of the current mesh element. 
        */
        void importMesh ( const COLLADAFW::Mesh* mesh );

        /**
         * Make the mesh instances and import the mesh data.
         */
        void importMesh ( 
            const COLLADAFW::Mesh* mesh, 
            const UniqueIdVec* transformNodeIds,
            const bool isMeshController = false );

        /** 
        * Imports the data of the current mesh element. 
        */
        void importController ( const COLLADAFW::Mesh* mesh );

        /**
        * Writes the geometry of the current mesh.
        */
        void createMesh ( 
            const COLLADAFW::Mesh* mesh, 
            MayaNode* parentMayaNode, 
            const bool isMeshController = false );

        /**
         * Create maya group ids for every mesh primitive (if there is more than one).
         */
        void createGroupNodes ( 
            const COLLADAFW::Mesh* mesh, 
            const COLLADAFW::UniqueId& transformNodeId, 
            size_t& geometryInstanceIndex );

        /**
         * Create the object group instances and the object groups and write it into the maya file.
         */
        void writeObjectGroups ( 
            const COLLADAFW::Mesh* mesh, 
            MayaDM::Mesh &meshNode, 
            const COLLADAFW::UniqueId& transformNodeId );

        /**
         * Iterates over the mesh primitives and reads the edge indices.
         */
        void getEdgeIndices ( 
            const COLLADAFW::Mesh* mesh, 
            std::vector<COLLADAFW::Edge>& edgeIndices, 
            std::map<COLLADAFW::Edge,size_t>& edgeIndicesMap );

        /*
         *	Write the face informations into the maya file.
         */
        void writeFaces ( 
            const COLLADAFW::Mesh* mesh, 
            const std::map<COLLADAFW::Edge,size_t>& edgeIndicesMap, 
            MayaDM::Mesh &meshNode );

        /*
         *	Write the face values of the given primitive element into the maya file.
         */
        void appendPolygonPolyFaces ( 
            const COLLADAFW::Mesh* mesh, 
            const COLLADAFW::MeshPrimitive* primitiveElement, 
            const std::map<COLLADAFW::Edge,size_t>& edgeIndicesMap, 
            MayaDM::Mesh &meshNode,
            const size_t blockSize, 
            const size_t numGlobalFaces, 
            size_t& globalFaceIndex, 
            size_t& endPosition );

        /*
        *	Write the face values of the given primitive element into the maya file.
        */
        void appendTrifansPolyFaces (
            const COLLADAFW::Mesh* mesh, 
            const COLLADAFW::MeshPrimitive* primitiveElement, 
            const std::map<COLLADAFW::Edge,size_t>& edgeIndicesMap, 
            MayaDM::Mesh &meshNode,
            const size_t blockSize, 
            const size_t numGlobalFaces, 
            size_t& globalFaceIndex, 
            size_t& endPosition );

        /*
        *	Write the face values of the given primitive element into the maya file.
        */
        void appendTristripsPolyFaces (
            const COLLADAFW::Mesh* mesh, 
            const COLLADAFW::MeshPrimitive* primitiveElement, 
            const std::map<COLLADAFW::Edge,size_t>& edgeIndicesMap, 
            MayaDM::Mesh &meshNode,
            const size_t blockSize, 
            const size_t numGlobalFaces, 
            size_t& globalFaceIndex, 
            size_t& endPosition );

        /**
         * Set the face infos into the maya poly face element.
         */
        void setPolygonFaceInfos ( 
            const COLLADAFW::Mesh* mesh, 
            const COLLADAFW::MeshPrimitive* primitiveElement, 
            const std::map<COLLADAFW::Edge,size_t>& edgeIndicesMap, 
            MayaDM::polyFaces &polyFace, 
            int &numEdges, 
            size_t &positionIndex, 
            std::vector<COLLADABU::Math::Vector3*> &polygonPoints );

        void setPolygonHoleInfos ( 
            const COLLADAFW::Mesh* mesh, 
            const COLLADAFW::MeshPrimitive* primitiveElement, 
            const std::map<COLLADAFW::Edge,size_t>& edgeIndicesMap, 
            MayaDM::polyFaces &polyFace, 
            int &numEdges, 
            size_t &positionIndex, 
            std::vector<COLLADABU::Math::Vector3*> & polygonPoints );

        /**
         * Set the uv set infos into the maya poly face element.
         * Increments the initial value for the uv set indices index.
         */
        void setUVSetInfos ( 
            const COLLADAFW::Mesh* mesh, 
            const COLLADAFW::MeshPrimitive* primitiveElement, 
            MayaDM::polyFaces &polyFace, 
            size_t& uvSetIndicesIndex,
            const int numEdges );

        /**
        * Set the color infos into the maya poly face element.
        * Increments the initial value for the color indices index.
        */
        void setColorInfos ( 
            const COLLADAFW::Mesh* mesh, 
            const COLLADAFW::MeshPrimitive* primitiveElement, 
            MayaDM::polyFaces &polyFace, 
            size_t& colorIndicesIndex, 
            const int numEdges );

        /*
         *	Changes the orientation of a polyFace hole element.
         */
        void changePolyFaceHoleOrientation( MayaDM::polyFaces &polyFace );

        /*
         *	Returns true, if we have to change the orientation of the current hole.
         */
        bool changeHoleOrientation ( 
            std::vector<COLLADABU::Math::Vector3*>& polygonPoints, 
            std::vector<COLLADABU::Math::Vector3*>& holePoints );

        /*
         * Returns a class which stores the x, y and z values of the vertex point 
         * at the given index position.
         */
        COLLADABU::Math::Vector3* getVertexPosition ( 
            const COLLADAFW::Mesh* mesh, const size_t vertexIndex );

        /*
         *	Write the edges into the maya file.
         */
        void writeEdges ( 
            const COLLADAFW::Mesh* mesh, 
            const std::vector<COLLADAFW::Edge> &edgeIndices, 
            MayaDM::Mesh &meshNode );

        /*
         * Write the uv coordinates into the maya file.
         */
        void writeUVSets ( const COLLADAFW::Mesh* mesh, MayaDM::Mesh &meshNode );

        /*
        *	Write the uv coordinates into the maya file.
        */
        void writeColorSets ( const COLLADAFW::Mesh* mesh, MayaDM::Mesh &meshNode );

        /*
         *	Write the normals values into the maya file.
         */
        void writeNormals ( const COLLADAFW::Mesh* mesh, MayaDM::Mesh &meshNode );

        /*
         *	Write the vertex position values into the maya file.
         */
        void writeVertexPositions ( 
            const COLLADAFW::Mesh* mesh, 
            MayaDM::Mesh &meshNode );

        /*
         * Gets the index value of the current edge. 
         * Returns false, if the search for the index value was not sucessful.
         */
        bool getEdgeIndex ( 
            const COLLADAFW::Edge& edge, 
            const std::map<COLLADAFW::Edge,size_t>& edgeIndicesMap, 
            int& edgeIndex );

        /**
        * The map holds for every geometry's shading engine a list of 
        * the index values of the geometry's primitives.
        */
        void setShadingEnginePrimitiveIndex ( 
            const COLLADAFW::UniqueId& geometryId, 
            const COLLADAFW::MaterialId shadingEngineId, 
            const size_t primitiveIndex );

        /**
        * Fills the ShadingEnginePrimitivesMap. Used to create the connections between the 
        * shading engines and the geometries.
        * The map holds for every geometry's shading engine a list of the index values of the 
        * geometry's primitives.
        */
        void setMeshPrimitiveShadingEngines ( const COLLADAFW::Mesh* mesh );

    };

}

#endif // __COLLADA_MAYA_GEOMETRY_IMPORTER_H__