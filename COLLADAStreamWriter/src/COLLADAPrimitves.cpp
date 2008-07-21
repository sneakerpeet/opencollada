/*
    Copyright (c) 2008 NetAllied Systems GmbH

	This file is part of COLLADAStreamWriter.
	
    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#include "COLLADAPrimitves.h"

namespace COLLADA
{
    //---------------------------------------------------------------
    void PrimitivesBase::prepareBaseToAppendValues ( bool openPolylistElement )
    {
        mPrimitiveCloser = mSW->openElement ( mPrimitiveName );

        if ( !mMaterial.empty() )
            mSW->appendAttribute ( CSWC::COLLADA_ATTRIBUTE_MATERIAL, mMaterial );

        mSW->appendAttribute ( CSWC::COLLADA_ATTRIBUTE_COUNT, mCount );

        mInputList.add();

        // write the vertex count list
        if ( !mVCountList.empty() )
        {
            mSW->openElement ( CSWC::COLLADA_ELEMENT_VCOUNT );
            mSW->appendValues ( mVCountList );
            mSW->closeElement();
        }

        if ( openPolylistElement )
            mSW->openElement ( CSWC::COLLADA_ELEMENT_P );
    }

    //---------------------------------------------------------------
    void PrimitivesBase::openPrimitiveElement ( )
    {
        mPrimitiveCloser = mSW->openElement ( mPrimitiveName );
    }

    //---------------------------------------------------------------
    void PrimitivesBase::appendMaterial ( const String &material )
    {
        mSW->appendAttribute ( CSWC::COLLADA_ATTRIBUTE_MATERIAL, material );
    }

    //---------------------------------------------------------------
    void PrimitivesBase::appendCount ( const unsigned int count )
    {
        mSW->appendAttribute ( CSWC::COLLADA_ATTRIBUTE_COUNT, count );
    }

    //---------------------------------------------------------------
    void PrimitivesBase::appendVertexCount( const unsigned long vCount )
    {
        mSW->appendValues ( vCount );
    }

    //---------------------------------------------------------------
    void PrimitivesBase::appendVertexCount( const VCountList& vCountList )
    {
        mSW->appendValues ( vCountList );
    }

    //---------------------------------------------------------------
    void PrimitivesBase::openVertexCountListElement()
    {
        mSW->openElement ( CSWC::COLLADA_ELEMENT_VCOUNT );
    }

    //---------------------------------------------------------------
    void PrimitivesBase::closeElement()
    {
        mSW->closeElement();
    }

    //---------------------------------------------------------------
    void PrimitivesBase::appendInputList ()
    {
        mInputList.add();
    }

    //---------------------------------------------------------------
    void PrimitivesBase::openPolylistElement ()
    {
        mSW->openElement ( CSWC::COLLADA_ELEMENT_P );
    }

    //---------------------------------------------------------------
    void PrimitivesBase::finish()
    {
        mPrimitiveCloser.close();
    }



} //namespace COLLADA

