/**
 * @file main.cpp
 * @author Buoncompagni Luca
 * @date Sep 17, 2016
 *
 * \brief implements a main function to check the behavior of the #parray template and #docs hierarchy.
 *
 * @see StringPointerArray
 * @see plist
 * @see Document
 * @see SpreadSheet
 * @see WebPage
 * @see docs
 */

#include <iostream>
#include <list>
#include "Document.h"
#include "PointerArray.cpp"


/// function used to highlights debugging logs by printing a frame of '#'.
void logTest( std::string msg){
	std::cout << std::endl;
	std::cout << "\t ########################################################################################" << std::endl;
	std::cout << "\t ########################### " << msg << " ###########################" << std::endl;
	std::cout << "\t ########################################################################################" << std::endl;
	std::cout << std::endl;
}


/// the debugging string to be appended on log head by this manager
const std::string LOG_HEADER = " Main: ";
/// the debugging string to be appended on log head by the StringPointerArray#tester()
const std::string LOG_HEADER_TEST = "\t[TEST] " + LOG_HEADER;


/// the main function to check project consistency by console logging.
int main(){
	/// check the behavior of the template implementation (#parray) through the #parray::StringPointerArray::tester() function.
	logTest( "   STARTING PointerArray test   ");
	parray::StringPointerArray::tester();
	logTest( "     END PointerArray test      ");

	/// check the behavior of the Document hierarchy (#docs).
	logTest( "STARTING Document hierarchy test");

	/// define a document with given title and keywords.
	docs::Document d1( "MyTitle A");
	d1.getKeyWords()->setSize( 5);
	d1.getKeyWords()->add( "A-KW1");
	d1.getKeyWords()->add( "A-KW2");
	d1.getKeyWords()->add( "A-KW3");
	std::cout << LOG_HEADER_TEST << "Make a doc d1 = " << d1 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	/// define another document with given title and keywords.
	docs::Document d2( "MyTitle B", 2);
	d2.getKeyWords()->add( "B-KW1");
	d2.getKeyWords()->add( "B-KW2");
	d2.getKeyWords()->resize( 5);
	d2.getKeyWords()->add( "B-KW3");
	std::cout << LOG_HEADER_TEST << "Make a doc d2 = " << d2 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	/// make a copy of the second Document, augment title and change keywords.
	docs::Document d3(d2);
	std::cout << LOG_HEADER_TEST << "Make d3 as a copy of d2. Are d2 and d3 equal? " << ((d2 == d3) ? "Yes." : "No.") << std::endl;
	d3.setTitle( d3.getTitle() + " version 2");
	d3.getKeyWords()->remove( "B-KW1");
	d3.getKeyWords()->add( "C-KW1");
	d3.getKeyWords()->pack();
	std::cout << LOG_HEADER_TEST << "change key words and title of d3. d3 = " << d3 << std::endl;
	std::cout << LOG_HEADER_TEST << "Are now d2 and d3 equal? " << ((d2 == d3) ? "Yes." : "No.") << std::endl;
	std::cout <<  " ----------------------------------------------------------------------------------- " << std::endl;

	/// create a copy of the third Document. Overwrite the title and remove keywords.
	docs::Document d4 = d3;
	std::cout << LOG_HEADER_TEST << "Make d4 as another copy of d3. Are d4 and d3 equal? " << ((d4 == d3) ? "Yes." : "No.") << std::endl;
	d4.setTitle( "My Title C");
	d4.getKeyWords()->clear();
	std::cout << LOG_HEADER_TEST << "clear key words and change title of d4. d4 = " << d4 << std::endl;
	std::cout << LOG_HEADER_TEST << "Are now d3 and d4 equal? " << ((d3 == d4) ? "Yes." : "No.") << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	/// create a Document with a given set of keywords.
	docs::Document d5( *d1.getKeyWords(), "Document 5");
	std::cout << LOG_HEADER_TEST << "Make d5 from the same key words as d1.";
	d5.getKeyWords()->pack();
	std::cout << "Pack d5 key words. Are d5 and d1 key words equal? " << ((*d1.getKeyWords() == *d5.getKeyWords()) ? "Yes." : "No.") << std::endl;
	std::cout << LOG_HEADER_TEST << "d5 = " << d5 << std::endl;



	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;



	/// create a WebPage. Add keywords and contents.
	docs::WebPage w1( "MyWebTitle A");
	w1.getKeyWords()->setSize( 5);
	w1.getKeyWords()->add( "W-KW1");
	w1.getKeyWords()->add( "W-KW2");
	w1.getKeyWords()->add( "W-KW3");
	w1.getContents()->setSize( 3);
	w1.getContents()->add( "line 1");
	w1.getContents()->add( "line 2");
	w1.getContents()->add( "line 3");
	std::cout << LOG_HEADER_TEST << "Make a doc w1 = " << w1 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	/// make a new Web Page by specifying only the title and url.
	docs::WebPage ww1( "MyWebTitle AA", "www.myUrl.it");
	std::cout << LOG_HEADER_TEST << "Make a doc ww1 = " << ww1 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	/// make a new Web Page by specifying the title, the url, the contents and keywords.
	docs::WebPage w2( "MyWebTitle B", "www.myUrl2.it", 2);
	w2.getKeyWords()->add( "B-KW1");
	w2.getKeyWords()->add( "B-KW2");
	w2.getKeyWords()->resize( 5);
	w2.getKeyWords()->add( "B-KW3");
	w2.getContents()->add("text");
	std::cout << LOG_HEADER_TEST << "Make doc w2 with keywords = " << w2 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	/// make a copy of the second WebPage. Augment the title, remove a keyword and add a contents.
	docs::WebPage w3(w2);
	std::cout << LOG_HEADER_TEST << "Make w3 as a copy of w2. Are w2 and w3 equal? " << ((w2 == w3) ? "Yes." : "No.") << std::endl;
	w3.setTitle( w3.getTitle() + " version 2");
	w3.getKeyWords()->remove( "B-KW1");
	w3.getContents()->add( "contents");
	w3.getKeyWords()->pack();
	std::cout << LOG_HEADER_TEST << "change key words, title and text of w3. w3 = " << w3 << std::endl;
	std::cout << LOG_HEADER_TEST << "Are now w2 and w3 equal? " << ((w2 == w3) ? "Yes." : "No.") << std::endl;
	std::cout <<  " ----------------------------------------------------------------------------------- " << std::endl;

	/// Make a copy of the third WebPage. Set a new title and clear keywords.
	docs::WebPage w4 = w3;
	std::cout << LOG_HEADER_TEST << "Make w4 as another copy of w3. Are w4 and w3 equal? " << ((w4 == w3) ? "Yes." : "No.") << std::endl;
	w4.setTitle( "My Web Title C");
	w4.getKeyWords()->clear();
	std::cout << LOG_HEADER_TEST << "clear key words and change title of w4. w4 = " << w4 << std::endl;
	std::cout << LOG_HEADER_TEST << "Are now w3 and w4 equal? " << ((w3 == w4) ? "Yes." : "No.") << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	/// create a new WebPage with a given keywords set.
	docs::WebPage w5( *w1.getKeyWords());
	std::cout << LOG_HEADER_TEST << "Make w5 from the same key words as w1.";
	w5.getKeyWords()->pack();
	std::cout << "Pack w5 key words. Are w5 and w1 key words equal? " << ((*w1.getKeyWords() == *w5.getKeyWords()) ? "Yes." : "No.") << std::endl;
	std::cout << LOG_HEADER_TEST << "w5 = " << w5 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	/// create a new WebPage with a given keywords and contents sets. Set also its title.
	docs::WebPage w6( *w2.getKeyWords(), *w1.getContents(), "Web Document 5");
	std::cout << LOG_HEADER_TEST << "Make w6 with the same key worlds of w2 and text of w1. Are w6 and w1 texts equal? " << ((*w6.getContents() == *w1.getContents()) ? "Yes." : "No.") << std::endl;
	std::cout << LOG_HEADER_TEST << "w6 = " << w6 << std::endl;
	w6.setContents( w4.getContents());
	std::cout << LOG_HEADER_TEST << "Make w6 to have the same texts as w4. w6 = " << w6 << std::endl;
	w6.setContents( w2.getContents());
	std::cout << LOG_HEADER_TEST << "Make w6 to have the same texts as w4. w6 = " << w6 << std::endl;



	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;



	/// create a new default Spreadsheet.
	docs::Spreadsheet s7;
	std::cout << LOG_HEADER_TEST << " s7=" << s7 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	/// create a new Spreadsheet with given number of columns and rows.
	docs::Spreadsheet s8( 10, 20);
	std::cout << LOG_HEADER_TEST << " s8=" << s8 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	/// create a new Spreadsheet with a given key words set, a title, the number of row and columns.
	docs::Spreadsheet s9( *d1.getKeyWords(), "ttt", 1, 2);
	s9.setColoumnCnt( 0);
	std::cout << LOG_HEADER_TEST << " s9=" << s9 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	/// create a new SpreadSheet as the copy of the previous and set the title.
	docs::Spreadsheet s10( s9);
	s10.setTitle( "TTTT");
	std::cout << LOG_HEADER_TEST << " s10=" << s10 << std::endl;



	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;



	std::cout << LOG_HEADER_TEST << " construct a list of Documents ..." << std::endl;

	/// put all the created Document in a list and print its contents.
	std::list<docs::Document>* docList = new std::list<docs::Document>;
	int cnt = 1;
	docList->push_back( d1); cnt++;
	docList->push_back( d2); cnt++;
	docList->push_back( d3); cnt++;
	docList->push_back( d4); cnt++;

	int cnt1 = 1;
	docList->push_back( w1); cnt1++;
	docList->push_back( ww1);cnt1++;
	docList->push_back( w2); cnt1++;
	docList->push_back( w3); cnt1++;
	docList->push_back( w4); cnt1++;
	docList->push_back( w5); cnt1++;
	docList->push_back( w6); cnt1++;

	docList->push_back( s7);
	docList->push_back( s8);
	docList->push_back( s9);
	docList->push_back( s10);

	std::cout << LOG_HEADER_TEST << "Final document list:" << std::endl;
	int i = 1;
	for ( std::list<docs::Document>::const_iterator ci = docList->begin(); ci != docList->end(); ++ci){
		std::string tag = "d";
		if( i > cnt){
			if( i < cnt1)
				tag = "w";
			else tag = "s";
		}
		std::cout << "\t\t" << tag << i++ << " = " << *ci << std::endl;
	}

	// end and clear memory.
	logTest( "  END Document hierarchy test   ");
}




