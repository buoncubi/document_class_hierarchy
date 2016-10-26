/**
 * @file Spreadsheet.cpp
 * @author Buoncompagni Luca
 * @date Sep 14, 2016
 *
 * \brief implementation of the docs#Spreadsheet class.
 *
 * @see Spreadsheet
 * @see Document
 * @see docs
 */

#include "Document.h"

namespace docs{

	// ########################### CONSTRUCTORS ###########################
	Spreadsheet::Spreadsheet( int coloumnCnt, int rowCnt, std::string title, int keyWordSize)
					: Document::Document( SPREADSHEET, title, keyWordSize),
					  coloumnCnt( coloumnCnt), rowCnt( rowCnt)
					{}
	Spreadsheet::Spreadsheet( const parray::StringPointerArray& kws, std::string title, int coloumnCnt, int rowCnt)
					: Document::Document( SPREADSHEET, kws, title),
					  coloumnCnt( coloumnCnt), rowCnt( rowCnt)
					{}
	Spreadsheet::Spreadsheet( const Spreadsheet& original) : Document::Document( original.typeId) {
		copy( original);
	}
	Spreadsheet::~Spreadsheet(){} // ## DESTRUCTOR ########################


	// ########################### BASE INTERFACE #########################
	void Spreadsheet::copy( const Spreadsheet& original){

		Document::copy( original);
		rowCnt = original.getRowCnt();
		coloumnCnt = original.getColoumnCnt();
	}
	const std::string Spreadsheet::toString() const{
		std::string out = Document::toString();
		out += "\n\t\t\t(columns:" + patch::to_string( coloumnCnt) + ", rows:" + patch::to_string( rowCnt) + ")";
		return out;
	}
	const bool Spreadsheet::equals( const Spreadsheet& toCompare) const{
		if( Document::equals( toCompare))
			if( rowCnt == toCompare.rowCnt)
				if( coloumnCnt == toCompare.coloumnCnt)
					return true;
		return false;
	}


	// ########################## DOCUMENT ROW CNT ########################
	const int Spreadsheet::getRowCnt() const{
		return rowCnt;
	}
	void Spreadsheet::setRowCnt( const int r){
		rowCnt = r;
	}


	// ######################## DOCUMENT COLOUMN CNT ######################
	int Spreadsheet::getColoumnCnt() const{
		return coloumnCnt;
	}
	void Spreadsheet::setColoumnCnt( const int c){
		coloumnCnt = c;
	}

}

