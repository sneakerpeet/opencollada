/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of COLLADADomHelper.

    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADA_EXCEPTION_H__
#define __COLLADA_EXCEPTION_H__

// Precompiler options
#include "COLLADADHStableHeaders.h"
#include "COLLADADHPrerequisites.h"

#include <exception>

// Backwards compatibility with old assert mode definitions
#if COLLADA_RELEASE_ASSERT == 1
#   define COLLADA_ASSERT_MODE 1
#endif

// Check for CPF assert mode

// RELEASE_EXCEPTIONS mode
#if COLLADA_ASSERT_MODE == 1
#   ifdef _DEBUG
#       define CPFAssert( a, b ) assert( (a) && (b) )

#   else
#       if COLLADA_COMP != COLLADA_COMPILER_BORL
#           define CPFAssert( a, b ) if( !(a) ) COLLADA_EXCEPT( CPF::Exception::ERR_RT_ASSERTION_FAILED, (b), "no function info")
#       else
#           define CPFAssert( a, b ) if( !(a) ) COLLADA_EXCEPT( CPF::Exception::ERR_RT_ASSERTION_FAILED, (b), __FUNC__ )
#       endif

#   endif

// EXCEPTIONS mode
#elif COLLADA_ASSERT_MODE == 2
#   if COLLADA_COMP != COLLADA_COMPILER_BORL
#       define CPFAssert( a, b ) if( !(a) ) COLLADA_EXCEPT( CPF::Exception::ERR_RT_ASSERTION_FAILED, (b), "no function info")
#   else
#       define CPFAssert( a, b ) if( !(a) ) COLLADA_EXCEPT( CPF::Exception::ERR_RT_ASSERTION_FAILED, (b), __FUNC__ )
#   endif

// STANDARD mode
#else
#   define CPFAssert( a, b ) assert( (a) && (b) )

#endif

namespace COLLADADH
{
    /** When thrown, provides information about an error that has occurred inside the engine.
        @remarks
            CPF never uses return values to indicate errors. Instead, if an
            error occurs, an exception is thrown, and this is the object that
            encapsulates the detail of the problem. The application using
            CPF should always ensure that the exceptions are caught, so all
            CPF engine functions should occur within a
            try{} catch(CPF::Exception& e) {} block.
        @par
            The user application should never create any instances of this
            object unless it wishes to unify its error handling using the
            same object.
        @todo Think about I18N for exceptions. Should that be done?
    */

    class Exception : public std::exception
    {

    protected:
        long mLine;
        int mNumber;
        String mTypeName;
        String mDescription;
        String mSource;
        String mFile;
        mutable String mFullDesc;

    public:
        /** Static definitions of error codes.
            @todo
                Add many more exception codes, since we want the user to be able
                to catch most of them.
        */
        enum ExceptionCodes {
            ERR_LOADING_FILE_FAILED,
            ERR_CANNOT_WRITE_TO_FILE,
            ERR_INVALID_STATE,
            ERR_INVALIDPARAMS,
            ERR_RENDERINGAPI_ERROR,
            ERR_DUPLICATE_ITEM,
            ERR_ITEM_NOT_FOUND,
            ERR_FILE_NOT_FOUND,
            ERR_INTERNAL_ERROR,
            ERR_RT_ASSERTION_FAILED,
            ERR_NOT_IMPLEMENTED,
            ERR_OUT_OF_MEM,
            ERR_COPY_FILE
        };

        /** Default constructor.
        */
        Exception( int number, const String& description, const String& source );

        /** Advanced constructor.
        */
        Exception( int number, const String& description, const String& source, const char* type, const char* file, long line );

        /** Copy constructor.
        */
        Exception( const Exception& rhs );

        /// Needed for  compatibility with std::exception
        ~Exception() throw()
        {}

        /** Assignment operator.
        */
        void operator = ( const Exception& rhs );

        /** Returns a string with the full description of this error.
            @remarks
                The description contains the error number, the description
                supplied by the thrower, what routine threw the exception,
                and will also supply extra platform-specific information
                where applicable. For example - in the case of a rendering
                library error, the description of the error will include both
                the place in which CPF found the problem, and a text
                description from the 3D rendering library, if available.
        */
        virtual const String& getFullDescription( void ) const;

        /** Gets the error code.
        */
        virtual int getNumber( void ) const throw();

        /** Gets the source function.
        */
        virtual const String &getSource() const
        {
            return mSource;
        }

        /** Gets source file name.
        */
        virtual const String &getFile() const
        {
            return mFile;
        }

        /** Gets line number.
        */
        virtual long getLine() const
        {
            return mLine;
        }

        /** Returns a string with only the 'description' field of this exception. Use
         getFullDescriptionto get a full description of the error including line number,
         error number and what function threw the exception.
              */
        virtual const String &getDescription( void ) const
        {
            return mDescription;
        }

        /** Override std::exception::what.
        @remarks
        The new created C string is converted from unicode and will be not deleted
        by this implementation. The reciepient is responsible to free the memory of
        the returned string. Use delete [].
        */
        const char* what() const throw();

    };


    /** Template struct which creates a distinct type for each exception code.
    @note
    This is useful because it allows us to create an overloaded method
    for returning different exception types by value without ambiguity. 
    From 'Modern C++ Design' (Alexandrescu 2001).
    */

    template <int num>

    struct ExceptionCodeType
    {
        enum { number = num };
    };

    // Specialised exceptions allowing each to be caught specifically
    // backwards-compatible since exception codes still used

    class UnimplementedException : public Exception
    {

    public:
        UnimplementedException( int number, const String& description, const String& source, const char* file, long line )
                : Exception( number, description, source, "UnimplementedException", file, line )
        {}

    }

    ;

    class FileNotFoundException : public Exception
    {

    public:
        FileNotFoundException( int number, const String& description, const String& source, const char* file, long line )
                : Exception( number, description, source, "FileNotFoundException", file, line )
        {}

    }

    ;

    class IOException : public Exception
    {

    public:
        IOException( int number, const String& description, const String& source, const char* file, long line )
                : Exception( number, description, source, "IOException", file, line )
        {}

    }

    ;

    class InvalidStateException : public Exception
    {

    public:
        InvalidStateException( int number, const String& description, const String& source, const char* file, long line )
                : Exception( number, description, source, "InvalidStateException", file, line )
        {}

    }

    ;

    class InvalidParametersException : public Exception
    {

    public:
        InvalidParametersException( int number, const String& description, const String& source, const char* file, long line )
                : Exception( number, description, source, "InvalidParametersException", file, line )
        {}

    }

    ;

    class ItemIdentityException : public Exception
    {

    public:
        ItemIdentityException( int number, const String& description, const String& source, const char* file, long line )
                : Exception( number, description, source, "ItemIdentityException", file, line )
        {}

    }

    ;

    class InternalErrorException : public Exception
    {

    public:
        InternalErrorException( int number, const String& description, const String& source, const char* file, long line )
                : Exception( number, description, source, "InternalErrorException", file, line )
        {}

    }

    ;

    class RenderingAPIException : public Exception
    {

    public:
        RenderingAPIException( int number, const String& description, const String& source, const char* file, long line )
                : Exception( number, description, source, "RenderingAPIException", file, line )
        {}

    }

    ;

    class RuntimeAssertionException : public Exception
    {

    public:
        RuntimeAssertionException( int number, const String& description, const String& source, const char* file, long line )
                : Exception( number, description, source, "RuntimeAssertionException", file, line )
        {}

    }

    ;

    class OutOfMemoryException : public Exception
    {

    public:
        OutOfMemoryException( int number, const String& description, const String& source, const char* file, long line )
                : Exception( number, description, source, "OutOfMemoryException", file, line )
        {}

    }

    ;

    /** Class implementing dispatch methods in order to construct by-value
        exceptions of a derived type based just on an exception code.
       @remarks
        This nicely handles construction of derived Exceptions by value (needed
        for throwing) without suffering from ambiguity - each code is turned into
        a distinct type so that methods can be overloaded. This allows COLLADA_EXCEPT
        to stay small in implementation (desirable since it is embedded) whilst
        still performing rich code-to-type mapping. 
       */

    class ExceptionFactory
    {

    private:
        /// Private constructor, no construction
        ExceptionFactory()
        {}

    public:
        static UnimplementedException create(
            ExceptionCodeType<Exception::ERR_NOT_IMPLEMENTED> code,
            const String& desc,
            const String& src, const char* file, long line )
        {
            return UnimplementedException( code.number, desc, src, file, line );
        }

        static FileNotFoundException create(
            ExceptionCodeType<Exception::ERR_FILE_NOT_FOUND> code,
            const String& desc,
            const String& src, const char* file, long line )
        {
            return FileNotFoundException( code.number, desc, src, file, line );
        }

        static IOException create(
            ExceptionCodeType<Exception::ERR_CANNOT_WRITE_TO_FILE> code,
            const String& desc,
            const String& src, const char* file, long line )
        {
            return IOException( code.number, desc, src, file, line );
        }

        static InvalidStateException create(
            ExceptionCodeType<Exception::ERR_INVALID_STATE> code,
            const String& desc,
            const String& src, const char* file, long line )
        {
            return InvalidStateException( code.number, desc, src, file, line );
        }

        static InvalidParametersException create(
            ExceptionCodeType<Exception::ERR_INVALIDPARAMS> code,
            const String& desc,
            const String& src, const char* file, long line )
        {
            return InvalidParametersException( code.number, desc, src, file, line );
        }

        static ItemIdentityException create(
            ExceptionCodeType<Exception::ERR_ITEM_NOT_FOUND> code,
            const String& desc,
            const String& src, const char* file, long line )
        {
            return ItemIdentityException( code.number, desc, src, file, line );
        }

        static ItemIdentityException create(
            ExceptionCodeType<Exception::ERR_DUPLICATE_ITEM> code,
            const String& desc,
            const String& src, const char* file, long line )
        {
            return ItemIdentityException( code.number, desc, src, file, line );
        }

        static InternalErrorException create(
            ExceptionCodeType<Exception::ERR_INTERNAL_ERROR> code,
            const String& desc,
            const String& src, const char* file, long line )
        {
            return InternalErrorException( code.number, desc, src, file, line );
        }

        static RenderingAPIException create(
            ExceptionCodeType<Exception::ERR_RENDERINGAPI_ERROR> code,
            const String& desc,
            const String& src, const char* file, long line )
        {
            return RenderingAPIException( code.number, desc, src, file, line );
        }

        static RuntimeAssertionException create(
            ExceptionCodeType<Exception::ERR_RT_ASSERTION_FAILED> code,
            const String& desc,
            const String& src, const char* file, long line )
        {
            return RuntimeAssertionException( code.number, desc, src, file, line );
        }

        static OutOfMemoryException create(
            ExceptionCodeType<Exception::ERR_OUT_OF_MEM> code,
            const String& desc,
            const String& src, const char* file, long line )
        {
            return OutOfMemoryException( code.number, desc, src, file, line );
        }

    };



#ifdef COLLADA_DEBUG_MODE
# define COLLADA_EXCEPT(num, desc, src) throw COLLADADH::ExceptionFactory::create( \
   COLLADADH::ExceptionCodeType<num>(), desc, src, __FILE__, __LINE__ );
#else
# define COLLADA_EXCEPT(num, desc, src) throw COLLADADH::ExceptionFactory::create( \
   COLLADADH::ExceptionCodeType<num>(), desc, src, "", 0 );
#endif

} // Namespace COLLADA

#endif
