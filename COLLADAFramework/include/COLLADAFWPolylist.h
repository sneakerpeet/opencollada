/*
    Copyright (c) 2008 NetAllied Systems GmbH

	This file is part of COLLADAFramework.
	
    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADAFW_POLYLIST_H__
#define __COLLADAFW_POLYLIST_H__

#include "COLLADAFWPolyBase.h"
#include "COLLADAFWPrimitiveBase.h"


namespace COLLADAFW
{

    /**
    * The Polylist element provides the information needed to bind vertex attributes
    * together and  then organize those vertices into individual polygons. The
    * polygons described in Polylist can  contain arbitrary numbers of vertices.
    * Unlike the polygons element, the Polylist element cannot  contain polygons
    * with holes.
    */
    class Polylist : public PolyBase
    {

    public:

        /** The array of vertex counts per polygons. */
        typedef unsigned int* VCountArray;

    private:

        /**
        * The vcount element contains a array of integers describing the number 
        * of sides for each polygon  described by the Polylist element. 
        * The vcount element may occur once.
        */
        VCountArray mVCountArray;

        /** 
         * Contains the number of vcount elements in the @mVCountArray array. 
         */
        size_t mVCountArraySize;

        /**
        * Contains a array of integers that specify the vertex attributes
        * (indices) for an individual Polylist. (�p� stands for �primitive�.)
        * The p element may occur not or once. 
        */
        PElement mPElement;


    public:	

        /**
        * Constructor
        */
        Polylist () 
            : PolyBase ()
            , mVCountArray ( 0 )
            , mVCountArraySize ( 0 )
        {}

        /**
        * Destructor
        */
        virtual ~Polylist() 
        {
            delete[] mVCountArray;
        }

        /**
        * The vcount element contains a array of integers describing the number 
        * of sides for each polygon  described by the Polylist element. 
        * The vcount element may occur once.
        * @param vCountArraySize Parameter to set the size of the array.
        * @return An integer pointer to the vcount array.
        */
        const VCountArray& getVCountArray ( size_t& vCountArraySize ) const 
        {
            vCountArraySize = mVCountArraySize;
            return mVCountArray; 
        }

        /**
         * The vcount element contains a array of integers describing the number 
         * of sides for each polygon  described by the Polylist element. 
         * The vcount element may occur once.
         * @param vCountArraySize The size of the array.
         * @param vCountArray A pointer to the array of vcounts.
         */
        void setVCountArray ( const VCountArray& vCountArray, const size_t vCountArraySize ) 
        { 
            mVCountArraySize = vCountArraySize;
            mVCountArray = vCountArray; 
        }

        /**
        * Gets the p array array. The pArray contains a array of integers that specify the vertex 
        * attributes (indices) for an individual Polylist ("p" stands for "primitive").
        * @return A reference to the p element. See @mPElement
        */
        PElement& getPElement () 
        {
            return mPElement; 
        }

        /**
        * Gets the p array array. The pArray contains a array of integers that specify the vertex 
        * attributes (indices) for an individual Polylist ("p" stands for "primitive").
        * @return A reference to the p element. See @mPElement
        */
        const PElement& getPElement () const 
        {
            return mPElement; 
        }

        /**
        * Sets the p array. The pArray contains a array of integers that specify the vertex 
        * attributes (indices) for an individual Polylist ("p" stands for "primitive").
        * Occures not or just for one time.
        * @param pElement A reference to the p element. See @mPElement.
        */
        void setPElement ( const PElement& pElement ) 
        { 
            mPElement = pElement; 
        }

    };

    typedef Polylist* PolylistArray;

}

#endif // __COLLADAFW_POLYLIST_H__
