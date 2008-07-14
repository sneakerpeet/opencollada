/*
    Copyright (c) 2008 NetAllied Systems GmbH
	
    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/


#ifndef __COLLADASTREAMWRITER_VERTEX_H__
#define __COLLADASTREAMWRITER_VERTEX_H__

#include "COLLADAPrerequisites.h"
#include "COLLADAElementWriter.h"
#include "COLLADAInputList.h"

namespace COLLADA
{

    class Vertices : public ElementWriter
    {

    public:
        Vertices ( StreamWriter* streamWriter )
                : ElementWriter ( streamWriter ),
                mInputList ( streamWriter ),
                mNodeId ( "" ),
                mNodeName ( "" )
        {}

        /** Returns a reference to the id of the vertex element*/
        const String& getId() const
        {
            return mNodeId;
        }

        /** Sets the id of the vertex element*/
        void setId ( const String& id )
        {
            mNodeId = id;
        }

        /** Returns a reference to the name of the vertex element*/
        const String& getNodeName() const
        {
            return mNodeName;
        }

        /** Sets the id of the vertex element*/
        void setNodeName ( const String& nodeName )
        {
            mNodeName = nodeName;
        }

        /** Returns a reference to the inputlist */
        InputList& getInputList()
        {
            return mInputList;
        }

        /** Adds the vertex to the stream*/
        void add();

    private:
        /** The id of the vertex element*/
        String mNodeId;

        /** The name of the vertex node*/
        String mNodeName;

        /** List of all the inputs*/
        InputList mInputList;

    };


} //namespace COLLADA


#endif //__COLLADASTREAMWRITER_VERTEX_H__
