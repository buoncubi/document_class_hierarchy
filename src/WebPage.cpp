/**
 * @file WebPage.cpp
 * @author Buoncompagni Luca
 * @date Sep 14, 2016
 *
 * \brief implementation of the WebBase (extending) Document class.
 *
 * @see WebPage
 * @see Document
 * @see docs
 */

#include "Document.h"

namespace docs{

	// ########################### CONSTRUCTORS ###########################
	WebPage::WebPage( std::string docTitle, std::string url, int keyWordSize, int textSize)
			: Document::Document( WEB_PAGE, docTitle, keyWordSize),
			  url( url), contents( new parray::StringPointerArray( textSize))
			{}
	WebPage::WebPage( const parray::StringPointerArray& kws, const parray::StringPointerArray& text, std::string docTitle, std::string url)
			: Document::Document( WEB_PAGE, kws, docTitle),
			  url( url), contents(new parray::StringPointerArray( text))
			{}

	WebPage::WebPage( const WebPage& original) : Document::Document( original.typeId) {
		contents = 0;
		copy( original);
	}


	// ############################ DESTRUCTOR ############################
	WebPage::~WebPage(){
		std::cout << this << " -> " << typeId << " delete texts container.";
		if( contents != 0)
			delete contents;
		contents = 0;
	}


	// ########################### BASE INTERFACE #########################
	void WebPage::copy( const WebPage& original){
		Document::copy( original);
		this->url = original.url;
		if( contents != 0)
			delete contents;
		this->contents = new parray::StringPointerArray( *original.contents);
	}
	const std::string WebPage::toString() const{
		std::string out = Document::toString();
		out += "\n\t\t\t(url:" + url + ")(texts:" + contents->toString();
		return out;
	}
	const bool WebPage::equals( const WebPage& toCompare) const{
		if( Document::equals( toCompare))
			if( ! url.compare( toCompare.url))
				if( *contents == *toCompare.contents)
					return true;
		return false;
	}


	// ############################ DOCUMENT URL ##########################
	const std::string WebPage::getUrl()const{
		return url;
	}
	void WebPage::setUrl( const std::string newUrl){
		url = newUrl;
	}


	// ######################### DOCUMENT CONTENTS ########################
	parray::StringPointerArray* WebPage::getContents() const{
		return contents;
	}
	void WebPage::setContents( parray::StringPointerArray* t){
		if( contents != 0)
			delete contents;
		contents = new parray::StringPointerArray( *t);
	}

	const std::string* WebPage::getContentsArray() const{
		return contents->getArray();
	}
	const int WebPage::getContentsSize() const{
		return contents->getCnt();
	}
}

