/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of GeneratedSaxParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "GeneratedSaxParserLibxmlSaxParser.h"
#include "GeneratedSaxParserParser.h"
#include "GeneratedSaxParserIErrorHandler.h"

#include <libxml/parserInternals.h> // for xmlCreateFileParserCtxt


namespace GeneratedSaxParser
{

	xmlSAXHandler LibxmlSaxParser::SAXHANDLER =
	{
		0,                 		           //internalSubsetSAXFunc internalSubset;
		0,                 		           //isStandaloneSAXFunc isStandalone;
		0,                 		           //hasInternalSubsetSAXFunc hasInternalSubset;
		0,                 		           //hasExternalSubsetSAXFunc hasExternalSubset;
		0,                 		           //resolveEntitySAXFunc resolveEntity;
		0,                 		           //getEntitySAXFunc getEntity;
		0,                 		           //entityDeclSAXFunc entityDecl;
		0,                 		           //notationDeclSAXFunc notationDecl;
		0,                 		           //attributeDeclSAXFunc attributeDecl;
		0,                 		           //elementDeclSAXFunc elementDecl;
		0,                 		           //unparsedEntityDeclSAXFunc unparsedEntityDecl;
		0,                 		           //setDocumentLocatorSAXFunc setDocumentLocator;
		0,                 		           //startDocumentSAXFunc startDocument;
		0,                      		   //endDocumentSAXFunc endDocument;
		&LibxmlSaxParser::startElement,    //startElementSAXFunc startElement;
		&LibxmlSaxParser::endElement,	   //endElementSAXFunc endElement;
		0,                 		           //referenceSAXFunc reference;
		&LibxmlSaxParser::characters,	   //charactersSAXFunc characters;
		0,                 		           //ignorableWhitespaceSAXFunc ignorableWhitespace;
		0,                 		           //processingInstructionSAXFunc processingInstruction;
		0,                 		           //commentSAXFunc comment;
		0,                 		           //warningSAXFunc warning;
		&LibxmlSaxParser::errorFunction,   //errorSAXFunc error;
		&LibxmlSaxParser::errorFunction    //fatalErrorSAXFunc fatalError;

	};


	//--------------------------------------------------------------------
	LibxmlSaxParser::LibxmlSaxParser(Parser* parser)
		: SaxParser(parser),
		mParserContext(0)
	{
	}

	//--------------------------------------------------------------------
	LibxmlSaxParser::~LibxmlSaxParser()
	{
	}

	bool LibxmlSaxParser::parseFile( const char* fileName )
	{
			mParserContext = xmlCreateFileParserCtxt(fileName);

			if ( !mParserContext )
			{
				ParserError error(ParserError::SEVERITY_CRITICAL,
						ParserError::ERROR_COULD_NOT_OPEN_FILE,
						0,
						0,
						0,
						0,
						fileName);
				getParser()->getErrorHandler()->handleError(error);
				return false;
			}

			if (mParserContext->sax != (xmlSAXHandlerPtr) &xmlDefaultSAXHandler)
			{
				xmlFree(mParserContext->sax);
			}

			mParserContext->sax = &SAXHANDLER;
			mParserContext->userData = (void*)this;

			initializeParserContext();
			xmlParseDocument(mParserContext);

			mParserContext->sax = 0;

			if ( mParserContext->myDoc )
			{
				xmlFreeDoc(mParserContext->myDoc);
				mParserContext->myDoc = 0;
			}

			xmlFreeParserCtxt(mParserContext);
			mParserContext = 0;

			return true;
	}

	void LibxmlSaxParser::initializeParserContext()
	{
		mParserContext->linenumbers = true;
		mParserContext->validate = false;
	}


	void LibxmlSaxParser::startElement( void* user_data, const ::xmlChar* name, const ::xmlChar** attrs )
	{
		LibxmlSaxParser* thisObject = (LibxmlSaxParser*)user_data;
		Parser* parser = thisObject->getParser();
		if ( !parser->elementBegin((const ParserChar*)name, (const ParserChar**)attrs) )
			thisObject->abortParsing();
	}

	void LibxmlSaxParser::endElement( void* user_data, const ::xmlChar* name)
	{
		LibxmlSaxParser* thisObject = (LibxmlSaxParser*)user_data;
		Parser* parser = thisObject->getParser();
		if ( !parser->elementEnd((const ParserChar*)name) )
			thisObject->abortParsing();
	}


	void LibxmlSaxParser::characters( void* user_data, const ::xmlChar* name, int length )
	{
		LibxmlSaxParser* thisObject = (LibxmlSaxParser*)user_data;
		Parser* parser = thisObject->getParser();
		if ( !parser->textData((const ParserChar*)name, (size_t)length) )
			thisObject->abortParsing();
	}

	void LibxmlSaxParser::abortParsing()
	{
		xmlStopParser(mParserContext);
	}

	size_t LibxmlSaxParser::getLineNumer() const
	{
		return (size_t)xmlSAX2GetLineNumber(mParserContext);
	}

	size_t LibxmlSaxParser::getColumnNumer() const
	{
		return (size_t)xmlSAX2GetColumnNumber(mParserContext);
	}

	void LibxmlSaxParser::errorFunction( void *ctx, const char *msg, ... )
	{
		xmlParserCtxtPtr context = (xmlParserCtxtPtr)ctx;
		LibxmlSaxParser* thisObject = (LibxmlSaxParser*)(context->userData);
		ParserError error(ParserError::SEVERITY_CRITICAL,
					ParserError::ERROR_XML_PERSER_ERROR,
					0,
					0,
					0,
					0,
					msg);
		thisObject->getParser()->getErrorHandler()->handleError(error);
	}

} // namespace GeneratedSaxParser
