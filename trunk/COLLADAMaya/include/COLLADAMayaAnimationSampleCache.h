/*
    Copyright (c) 2008 Intel Corporation
    Copyright (c) 2005-2008 Sony Computer Entertainment America
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of COLLADAMaya.

    COLLADAMaya is free software; you can redistribute it and/or modify
    it under the terms of the MIT License as published by the
    Massachusetts Institute of Technology.

    COLLADAMaya is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    MIT License for more details.

    You should have received a copy of the MIT License along with
    COLLADAMaya; see the file COPYING. If not have a look here:
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADA_MAYA_ANIMATION_SAMPLE_CACHE_H__
#define __COLLADA_MAYA_ANIMATION_SAMPLE_CACHE_H__

#include "COLLADAMayaAnimationHelper.h"
#include <map>
#include <vector>

#include <maya/MObject.h>
#include <maya/MDagPath.h>
#include <maya/MPlug.h>
#include <maya/MTime.h>
#include <maya/MFloatArray.h>


namespace COLLADAMaya
{

    /**
     * This class caches all animations.
     */

    class AnimationSampleCache
    {

    private:

        struct CacheNode
        {
            /** The parts are the sample plugs of the current node */

            struct Part
            {
                MPlug plug;
                std::vector<float> values;
                bool isMatrix, isWanted, isAnimated;

                Part() : isMatrix ( false ), isWanted ( false ), isAnimated ( false ) {}

                Part ( const MPlug& plug ) : plug ( plug ), isMatrix ( false ), isWanted ( false ), isAnimated ( false ) {}
            };

            std::vector<Part> parts;

            MObject node;
            CacheNode ( const MObject& node ) : node ( node ) {}

            CacheNode& operator= ( const CacheNode &a )
            {
                node = a.node;
                parts = a.parts;
                return *this;
            }
        };

        /** Map for the cache nodes. */
        typedef std::map<String, CacheNode*> CacheNodeMap;
        typedef std::vector<CacheNode::Part> CachePartList;

        // list of nodes that require sampling
        CacheNodeMap nodes;
        CacheNode* nodeSearch;

    public:
        /** Constructor */
        AnimationSampleCache();

        /** Destructor */
        virtual ~AnimationSampleCache();

        /**
         * @todo documentation
         * @param plug
         * @param isMatrix
         */
        void cachePlug ( const MPlug& plug, bool isMatrix );

        /**
         * @todo documentation
         * @param plug
         * @return bool
         */
        bool markPlugWanted ( const MPlug& plug );

        /**
         * @todo documentation
         * @param node
         * @return bool
         */
        bool findCacheNode ( const MObject& node );

        /**
         * @todo documentation
         * @param plug
         * @param inputs
         * @param outputs
         * @return bool
         */
        bool findCachePlug ( const MPlug& plug, std::vector<float>*& inputs, std::vector<float>*& outputs );

        /**
         * @todo documentation
         * @param plug
         * @param isAnimated
         * @return bool
         */
        bool findCachePlug ( const MPlug& plug, bool& isAnimated );

        /**
         * @todo documentation
         * @param object
         */
        void sampleExpression ( const MObject& object );

        /**
         * @todo documentation
         * @param dagPath
         */
        void sampleConstraint ( const MDagPath& dagPath );

        /**
         * @todo documentation
         * @param dagPath
         */
        void sampleIKHandle ( const MDagPath& dagPath );

        /** Sample all the cached plugs */
        void samplePlugs();

    private:

        /**
         * @todo documentation
         * @param node
         */
        void cacheTransformNode ( const MObject& node );

    };

}

#endif  // __COLLADA_MAYA_ANIMATION_SAMPLE_CACHE_H__
