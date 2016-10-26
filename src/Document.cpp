/**
 * @file Document.cpp
 * @author Buoncompagni Luca
 * @date Sep 14, 2016
 *
 * \brief implementation of the Document base class.
 *
 * @see Document
 * @see docs
 */

#include "Document.h"

namespace docs{

	// ########################### CONSTRUCTORS ###########################
	Document::Document( std::string title, int keyWordSize)
			: typeId( DOCUMENT),  title( title),
			  keyWords(new parray::StringPointerArray( keyWordSize)){
		std::cout << LOG_HEADER_INFO << "Constructing doc: " << typeId << std::endl;
	}
	Document::Document( const DocType type, std::string title, int keyWordSize)
			: typeId( type), title( title),
			  keyWords( new parray::StringPointerArray( keyWordSize)) {
		std::cout << LOG_HEADER_INFO << "Constructing doc: " << type << std::endl;
	}

	Document::Document( const parray::StringPointerArray& kw, std::string title)
			: typeId( DOCUMENT), title( title),
			  keyWords( new parray::StringPointerArray( kw)){
		std::cout << LOG_HEADER_INFO << "Constructing doc: " << typeId << std::endl;
	}
	Document::Document( const DocType type, const parray::StringPointerArray& kw, std::string title)
				: typeId( type), title( title),
				  keyWords( new parray::StringPointerArray( kw)){
		std::cout << LOG_HEADER_INFO << "Constructing doc: " << type << std::endl;
	}

	Document::Document( const Document& original)
			: typeId( original.typeId) {
		std::cout << LOG_HEADER_INFO << "Construct a copy of: " << original << std::endl;
		keyWords = 0;
		copy( original);
	}


	// ############################ DESTRUCTOR ############################
	Document::~Document() {
		std::cout << this << " -> " << typeId << " delete key words container..." << std::endl << "\t\t...";
		if( keyWords != 0)
			delete keyWords;
		keyWords = 0;
	}


	// ########################### BASE INTERFACE #########################
	const std::string Document::toString() const{
		return "[" + typeId.getName() + "] (title:" + title + ")(key words: " + keyWords->toString() + ")";
	}
	/** it returns 'strm << doc.toString()'. This method should not be implemented on derived classes. */
	std::ostream& operator<<( std::ostream& strm, const Document& doc) {
		return strm << doc.toString();
	}

	void Document::copy( const Document& doc){
		this->title = doc.title;
		if( keyWords != 0)
			delete keyWords;
		keyWords = new parray::StringPointerArray( *doc.keyWords);
	}
	Document& Document::operator=(const Document& doc){
		copy( doc);
		return *this;
	}

	const bool Document::equals( const Document& toCompare) const{
		if( ! typeId.getName().compare( toCompare.typeId.getName()))
			if( ! title.compare( toCompare.title))
				if( *keyWords == *toCompare.keyWords)
					return true;
		return false;
	}
	/** it returns 'c1.equals( c2)'. This method should not be implemented on derived classes. */
	bool operator== (const Document &c1, const Document &c2){
		return c1.equals( c2);
	}
	/** it returns '!c1.equals( c2)'. This method should not be implemented on derived classes. */
	bool operator!= (const Document &c1, const Document &c2){
		return !operator==( c1, c2);
	}


	// ########################### DOCUMENT TYPE ##########################
	const DocType Document::getType() const{
		return typeId;
	}


	// ########################## DOCUMENT TITLE ##########################
	std::string Document::getTitle()const{
		return title;
	}
	void Document::setTitle( const std::string newTitle){
		title = newTitle;
	}


	// ######################### DOCUMENT KEYWORDS ########################
	parray::StringPointerArray* Document::getKeyWords() const{
		return keyWords;
	}
	void Document::setKeyWords( parray::StringPointerArray* kw){
		if( keyWords != 0)
			delete keyWords;
		keyWords = new parray::StringPointerArray( *kw);
	}

	const std::string* Document::getKeyWordsArray() const{
		return keyWords->getArray();
	}
	const int Document::getKeyWordsSize() const{
		return keyWords->getCnt();
	}
}
