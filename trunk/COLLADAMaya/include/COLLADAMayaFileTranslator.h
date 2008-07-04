/*
    Copyright (c) 2008 NetAllied Systems GmbH
	
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#ifndef __COLLADA_MAYA_FILE_TRANSLATOR_H__
#define __COLLADA_MAYA_FILE_TRANSLATOR_H__

#include "COLLADAMayaDocumentNode.h"
// #include "vld.h"
// #include "vldapi.h"

#ifndef _MPxFileTranslator
#include <maya/MPxFileTranslator.h>
#endif // _MPxFileTranslator

namespace COLLADAMaya
{
    /**
     * The main class for the maya plug-in.
     */

    class FileTranslator : public MPxFileTranslator
    {

    private:

        /** Name of the current scene. */
        MString sceneName;

        /** Flag, if just the selection should be exported. */
        bool exportSelection;

        /** Flag, if we do an import. */
        bool isImporter;

        static uint readDepth;

    public:

        /**
         * Constructor
         * @param isImporter True, if we want to import.
         */
        FileTranslator ( bool isImporter );
        virtual ~FileTranslator();

        /**
         * Create a new instance of the translator
         * This method is registered to Maya's plugin module in the initializePlugin function.
         */
        static void* createImporter();

        /**
         * Create a new instance of the translator
         * This method is registered to Maya's plugin module in the initializePlugin function.
         */
        static void* createExporter();

        /**
         * The reader() method reads each line of the file and returns a
         * MS::kFailure if it cannot be opened by the translator. If a file type
         * cannot be recognized by the translator, the method creates a new
         * object via MEL to support the data in that file.
         * @param & The file object
         * @param optionsString String with the options
         * @param mode Mode of file access
         * @return MStatus Returns a MS::kFailure if it cannot be opened by the translator
         */
        virtual MStatus reader ( const MFileObject &,
                                 const MString &optionsString,
                                 MPxFileTranslator::FileAccessMode mode );

        /**
         * The writer() method provides a message through the script editor and
         * returns a status to indicate the results.
         * In this example, only �export all� and �export selection� options are
         * allowed when trying to save data. Other options will result in the
         * display of a failure message through the script editor and returns a
         * MS:kFailure, which indicates that the file type cannot be understood
         * by the translator.
         * @param & The file object
         * @param optionsString String with the options
         * @param mode Mode of file access
         * @return MStatus Returns a MS:kFailure, which indicates that the file type
         *   cannot be understood by the translator.
         */
        virtual MStatus writer ( const MFileObject &,
                                 const MString &optionsString,
                                 MPxFileTranslator::FileAccessMode mode );

        /**
         * The haveReadMethod() method checks if the translator provides a read
         * method. In the LepTranslator class, the method returns true because
         * the reader() method exists.
         * @return bool True, if it is an importer.
         */
        virtual bool haveReadMethod() const
        {
            return isImporter;
        }

        /**
         * The haveWriteMethod() method checks if the translator has a write
         * method. In the polyExporter class, the method returns true because
         * the writer() method is implemented.
         * @return bool True, if it is an exporter.
         */
        virtual bool haveWriteMethod() const
        {
            return !isImporter;
        }

        /**
         * Return the default extension for COLLADA files.
         * @return MString Default extension for COLLADA files
         */
        MString defaultExtension() const;

        /**
         * Returns valid file extension.
         * @return MString Valid file extensions.
         */
        MString filter() const;

        /**
         * Check the given file to see if it is COLLADA data
         * @param fileObject The file object.
         * @param buffer File buffer
         * @param size File size
         * @return MFileKind Kind of file.
         */
        virtual MFileKind identifyFile ( const MFileObject &fileObject, const char *buffer, short size ) const;

    private:
        /**
         * Parses the Maya DAG/DG graphs and writes out a COLLADA document.
         * @param filename Name of the collada file.
         * @return MStatus Status of export.
         */
        MStatus exportIntoFile ( const MString& filename, const bool selectionOnly );

        /**
         * @todo documentation
         * @param filename
         * @return MStatus
         */
        MStatus import ( const MString& filename );

    };

}

#endif //__COLLADA_MAYA_FILE_TRANSLATOR_H__
