/**
 * @file main.cpp
 * @author Buoncompagni Luca
 * @date Sep 17, 2016
 *
 * \brief implements a main function to check the behavior of the #plist template class and #docs hierarchy.
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

void logTest( std::string msg){
	std::cout << std::endl;
	std::cout << "\t #################################################################################" << std::endl;
	std::cout << "\t ########################### " << msg << " ##########################" << std::endl;
	std::cout << "\t #################################################################################" << std::endl;
	std::cout << std::endl;
}

/// the main function to check project consistency by console logging
int main(){
	/// check the behavior of the template implementation (#parray) trhough the #plist::StringPointerArray::tester() function
	logTest( "starting PointerArray test");
	parray::StringPointerArray::tester();
	logTest( "   end PointerArray test  ");

	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;
/*
	docs::Document d1( "MyTitle A");
	d1.getKeyWords()->setSize( 5);
	d1.getKeyWords()->add( "A-KW1");
	d1.getKeyWords()->add( "A-KW2");
	d1.getKeyWords()->add( "A-KW3");
	std::cout << "Make a doc d1 = " << d1 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	docs::Document d2( "MyTitle B", 2);
	d2.getKeyWords()->add( "B-KW1");
	d2.getKeyWords()->add( "B-KW2");
	d2.getKeyWords()->resize( 5);
	d2.getKeyWords()->add( "B-KW3");
	std::cout << "Make a doc d2 = " << d2 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	docs::Document d3(d2);
	std::cout << "Make d3 as a copy of d2. Are d2 and d3 equal? " << ((d2 == d3) ? "Yes." : "No.") << std::endl;
	d3.setTitle( d3.getTitle() + " version 2");
	d3.getKeyWords()->remove( "B-KW1");
	d3.getKeyWords()->add( "C-KW1");
	d3.getKeyWords()->pack();
	std::cout << "change key words and title of d3. d3 = " << d3 << std::endl;
	std::cout << "Are now d2 and d3 equal? " << ((d2 == d3) ? "Yes." : "No.") << std::endl;
	std::cout <<  " ----------------------------------------------------------------------------------- " << std::endl;

	docs::Document d4 = d3;
	std::cout << "Make d4 as another copy of d3. Are d4 and d3 equal? " << ((d4 == d3) ? "Yes." : "No.") << std::endl;
	d4.setTitle( "My Title C");
	d4.getKeyWords()->clear();
	std::cout << "clear key words and change title of d4. d4 = " << d4 << std::endl;
	std::cout << "Are now d3 and d4 equal? " << ((d3 == d4) ? "Yes." : "No.") << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	docs::Document d5( *d1.getKeyWords(), "Document 5");
	std::cout << "Make d5 from the same key words as d1.";
	d5.getKeyWords()->pack();
	std::cout << "Pack d5 key words. Are d5 and d1 key words equal? " << ((*d1.getKeyWords() == *d5.getKeyWords()) ? "Yes." : "No.") << std::endl;
	std::cout << "d5 = " << d5 << std::endl;

	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	docs::WebPage w1( "MyWebTitle A");
	w1.getKeyWords()->setSize( 5);
	w1.getKeyWords()->add( "W-KW1");
	w1.getKeyWords()->add( "W-KW2");
	w1.getKeyWords()->add( "W-KW3");
	w1.getContents()->setSize( 3);
	w1.getContents()->add( "line 1");
	w1.getContents()->add( "line 2");
	w1.getContents()->add( "line 3");
	std::cout << "Make a doc w1 = " << w1 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	docs::WebPage ww1( "MyWebTitle AA", "www.myUrl.it");
	std::cout << "Make a doc ww1 = " << ww1 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	docs::WebPage w2( "MyWebTitle B", "www.myUrl2.it", 2);
	w2.getKeyWords()->add( "B-KW1");
	w2.getKeyWords()->add( "B-KW2");
	w2.getKeyWords()->resize( 5);
	w2.getKeyWords()->add( "B-KW3");
	w2.getContents()->add("text");
	std::cout << "Make doc w2 with keywords = " << w2 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	docs::WebPage w3(w2);
	std::cout << "Make w3 as a copy of w2. Are w2 and w3 equal? " << ((w2 == w3) ? "Yes." : "No.") << std::endl;
	w3.setTitle( w3.getTitle() + " version 2");
	w3.getKeyWords()->remove( "B-KW1");
	w3.getContents()->add( "contents");
	w3.getKeyWords()->pack();
	std::cout << "change key words, title and text of w3. w3 = " << w3 << std::endl;
	std::cout << "Are now w2 and w3 equal? " << ((w2 == w3) ? "Yes." : "No.") << std::endl;
	std::cout <<  " ----------------------------------------------------------------------------------- " << std::endl;

	docs::WebPage w4 = w3;
	std::cout << "Make w4 as another copy of w3. Are w4 and w3 equal? " << ((w4 == w3) ? "Yes." : "No.") << std::endl;
	w4.setTitle( "My Web Title C");
	w4.getKeyWords()->clear();
	std::cout << "clear key words and change title of w4. w4 = " << w4 << std::endl;
	std::cout << "Are now w3 and w4 equal? " << ((w3 == w4) ? "Yes." : "No.") << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	docs::WebPage w5( *w1.getKeyWords());
	std::cout << "Make w5 from the same key words as w1.";
	w5.getKeyWords()->pack();
	std::cout << "Pack w5 key words. Are w5 and w1 key words equal? " << ((*w1.getKeyWords() == *w5.getKeyWords()) ? "Yes." : "No.") << std::endl;
	std::cout << "w5 = " << w5 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	docs::WebPage w6( *w2.getKeyWords(), *w1.getContents(), "Web Document 5");
	std::cout << "Make w6 with the same key worlds of w2 and text of w1. Are w6 and w1 texts equal? " << ((*w6.getContents() == *w1.getContents()) ? "Yes." : "No.") << std::endl;
	std::cout << "w6 = " << w6 << std::endl;
	w6.setContents( w4.getContents());
	std::cout << "Make w6 to have the same texts as w4. w6 = " << w6 << std::endl;
	w6.setContents( w2.getContents());
	std::cout << "Make w6 to have the same texts as w4. w6 = " << w6 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	docs::Spreadsheet s7;
	std::cout << " s7=" << s7 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	docs::Spreadsheet s8( 10, 20);
	std::cout << " s8=" << s8 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	docs::Spreadsheet s9( *d1.getKeyWords(), "ttt", 1, 2);
	s9.setColoumnCnt( 0);
	std::cout << " s9=" << s9 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	docs::Spreadsheet s10( s9);
	s10.setTitle( "TTTT");
	std::cout << " s10=" << s10 << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;


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

	std::cout << "Add all the document in a list:" << std::endl;
	int i = 1;
	for ( std::list<docs::Document>::const_iterator ci = docList->begin(); ci != docList->end(); ++ci){
		std::string tag = "d";
		if( i > cnt){
			if( i < cnt1)
				tag = "w";
			else tag = "s";
		}
		std::cout << "\t" << tag << i++ << " = " << *ci << std::endl;
	}
	std::cout << " ----------------------------------------------------------------------------------- " << std::endl;

*/
}




