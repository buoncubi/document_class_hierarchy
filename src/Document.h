/**
 * @file Document.h
 * @author Buoncompagni Luca
 * @date Sep 14, 2016
 *
 * @brief The complete Document Hierarchy namespce specification.
 *
 * This is a test implementation of a Document class,
 * which contains an array of key words and a title and two derived classes.
 * A WebPage representation, with an url and an array of lines
 * contents (@see PointerArray), as well as a Spreadsheet,
 * with related number of column and raw.
 *
 * @see PointerArray
 */

#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <iostream>
#include <list>
#include "PointerArray.cpp"

/// This namespace is used to collect all the document hierarchy classes and types.
namespace docs{



	/*  ###########################################################################
		########################## INITIALISING DEFAULTS ##########################
		########################################################################### */

	/// The title, if not specified on Document construction.
	const std::string DEFAULT_DOCUMENT_TITLE = "Default Title";
	/// The size, of key words if not specified on Document construction.
	const int DEFAULT_DOCUMENT_KWSIZE = 3;

	/// The url, if not specified on WebPage construction.
	const std::string DEFAULT_WEBPAGE_URL = "www.defualt.com";
	/// The size of contents, if not specified on WebPage construction.
	const int DEFAULT_WEBPAGE_TEXTSIZE = 10;

	/// The number of columns, if not specified on Spreadsheet construction.
	const int DEFAULT_SPREADSHEET_COLCNT = 7;
	/// The number of rows, if not specified on Spreadsheet construction.
	const int DEFAULT_SPREADSHEET_ROWCNT = 2;

	/// The name of the DOCUMENT type values
	const std::string TYPE_NAME_DOCUMENT = "\"Document\"";
	/// The name of the WEB_PAGE type values
	const std::string TYPE_NAME_WEBPAGE = "\"Web Page\"";
	/// The name of the SPREADSHEET type values
	const std::string TYPE_NAME_SPREADSHEET = "\"Spreadsheet\"";

	/// Instances of document identifier values.
	enum Type {
		DOCUMENT, 		///< only Document objects will have this Document#getType() value
		WEB_PAGE, 		///< only WebPage objects will have this Document#getType() value
		SPREADSHEET		///< only Spreadsheet objects will have this Document#getType() value
	};

	/**
	 * Class containing a Type value.
	 * It allows to print the name of the of type of document and at
	 * the same time make an easy comparison or perhaps a searching rule.
	 */
	class DocType{
		public:
			/// constructors must provide a final type to be attached on document constructors.
			DocType( Type t) : t( t){}
			/// empty since all instances of this class are suppose to be constant.
			~DocType(){};

			/// returns the final type ID.
			const Type getType() const { return t;}

			/// returns the name of the type of the document and "Invalid Type" if unknown.
			const std::string getName() const{
				switch ( t) {
				case DOCUMENT: 		return TYPE_NAME_DOCUMENT;
				case WEB_PAGE: 		return TYPE_NAME_WEBPAGE;
				case SPREADSHEET:	return TYPE_NAME_SPREADSHEET;
				default:			return "Invalid type";
				}
			}
			/// prints the #getName() result.
			friend std::ostream& operator<<( std::ostream& st, const DocType& t){
				return st << t.getName();
			}
			/// return the comparison of #getName() methods.
			friend bool operator==( const DocType& c1, const DocType& c2){
				return c1.getName() == c2.getName();
			}
			/// return the negation of the comparison of #getName().
			friend bool operator!=( const DocType& c1, const DocType& c2){
				return !operator==( c1, c2);
			}

		private:
			const Type t; ///< the member type assign on constructor.
	};





	/* ###########################################################################
	   ########################### BASE DOCUMENT CLASS ###########################
	   ########################################################################### */

	/**
	 * This is the base class of the hierarchy and describes a generic document
	 * through: a Type, a title (string) and a keyword set (PointerArray).
	 * It implements default empty and copy constructors as well as basic
	 * operator overloading.
	 */
	class Document {
		public:

			/// construct by creating a new keyword list.
			Document( std::string title = DEFAULT_DOCUMENT_TITLE, int keyWordSize = DEFAULT_DOCUMENT_KWSIZE);
			/// construct by using a copy of a PointerArray of string.
			Document( const parray::StringPointerArray& kws, std::string title = DEFAULT_DOCUMENT_TITLE);
			/// #copy() constructor, to create an independent clone.
			Document( const Document& original);
			/// destructor, to clear the keywords list.
			virtual ~Document();

			/// to #copy() this object
			Document& operator=(const Document&);

			/// print the information of this object by listing all the data members.
			virtual const std::string toString() const;
			/// return the result of #toString().
			friend std::ostream& operator<<( std::ostream&, const Document&);

			/// check if all the data member are equals (type, title, keyWords).
			virtual bool const equals( const Document&) const;
			/// returns the result of #equals().
			friend bool operator== (const Document&, const Document&);
			/// returns the negation of #equals()
			friend bool operator!= (const Document&, const Document&);

			/// return the #title of this document
			virtual std::string getTitle() const;
			/// set a #title to this document.
			virtual void setTitle( const std::string);

			/// returns the manager of the #keyWords array of this document.
			virtual parray::StringPointerArray* getKeyWords() const;
			/// set a copy of the input #keyWords and overwrites the previous.
			virtual void setKeyWords( parray::StringPointerArray*);
			/// returns the dynamic array containing the #keyWords
			virtual const std::string* getKeyWordsArray() const;
			/// returns the #getKeyWordsArray() size
			virtual const int getKeyWordsSize() const;

			/// return the type identifier of this document assigned on custruction.
			const DocType getType() const;

		protected:
			/// the type ID assigned to this document on constructor.
			const DocType typeId;

			/// copy this object on a new memory location.
			virtual void copy( const Document&);

			/// The #Document( std::string, int) constructor to be use on derived class for specifying the document typeId ID.
			Document( const DocType typeId,
					const std::string title = DEFAULT_DOCUMENT_TITLE, const int keyWordSize = DEFAULT_DOCUMENT_KWSIZE);
			/// The #Document( const parray::StringPointerArray&, std::string) constructor to be use on derived class for specifying the document typeId ID.
			Document( const DocType typeId,
					const parray::StringPointerArray& kws, const std::string title = DEFAULT_DOCUMENT_TITLE);

		private:
			/// the title of this Document.
			std::string title;
			/// the key word array manager of this Document.
			parray::StringPointerArray* keyWords;
	};




	/* ###########################################################################
	   ########################### DOCUMENT DERIVATING ###########################
	   ########################################################################### */

	/**
	 * It describes a web page as a Document which have also an url and
	 * an array of contents (e.g., textual line).
	 */
	class WebPage : public Document{
	public:

		/// construct by creating a new contents list. It is based on #Document( const DocType typeId, std::string, int)
		WebPage( std::string title = DEFAULT_DOCUMENT_TITLE, std::string url = DEFAULT_WEBPAGE_URL,
				int keyWordSize = DEFAULT_DOCUMENT_KWSIZE, int textSize = DEFAULT_WEBPAGE_TEXTSIZE);
		/// construct by using a copy of a PointerArray of contents. It is based on #Document( const DocType typeId, const parray::StringPointerArray&, std::string title);
		WebPage( const parray::StringPointerArray& kws, const parray::StringPointerArray& tex=0,
				std::string title = DEFAULT_DOCUMENT_TITLE, std::string url = DEFAULT_WEBPAGE_URL);
		/// to #copy() this object
		WebPage( const WebPage& original);
		/// destructor, to clear the contents list.
		virtual ~WebPage();

		/// append to the result of Document#toString() the description of the url and contents.
		virtual const std::string toString() const;
		/// return true if Document#equals() is true as well as urls and contends are equals.
		virtual const bool equals( const WebPage&) const;

		/// returns the #url assign to this web page.
		virtual const  std::string getUrl() const;
		/// set the #url for this web page
		virtual void setUrl( const std::string);

		/// returns the manager of the #contents array of this document.
		virtual parray::StringPointerArray* getContents() const;
		/// set a copy of the input #contents and overwrites the previous.
		virtual void setContents( parray::StringPointerArray*);
		/// returns the dynamic array containing the #contents.
		virtual const std::string* getContentsArray() const;
		/// returns the #getContentsArray() size
		virtual const int getContentsSize() const;

	protected:
		/// copy this object on a new memory location. It relies on Document#copy(), which is also used on copy constructor and assign operator.
		virtual void copy( const WebPage&);

	private:
		/// The url of this WebPage
		std::string url;
		/// The contents of this WebPage
		parray::StringPointerArray* contents;

	};



	/**
	 * This describes a Document which has also a specified number of columns and rows.
	 */
	class Spreadsheet : public Document{
	public:

		/// Construct by creating a new Spreadsheet. It is based on #Document( const DocType typeId, std::string, int)
		Spreadsheet( int coloumnCnt = DEFAULT_SPREADSHEET_COLCNT, int rowCnt = DEFAULT_SPREADSHEET_ROWCNT,
				std::string title = DEFAULT_DOCUMENT_TITLE, int keyWordSize = DEFAULT_DOCUMENT_KWSIZE);
		/// Construct by creating a new Spreadsheet. It is based on #Document( const DocType typeId, const parray::StringPointerArray&, std::string title);
		Spreadsheet( const parray::StringPointerArray& kws, std::string title = DEFAULT_DOCUMENT_TITLE,
				int coloumnCnt = DEFAULT_SPREADSHEET_COLCNT, int rowCnt = DEFAULT_SPREADSHEET_ROWCNT);
		/// to #copy() this object
		Spreadsheet( const Spreadsheet& original); // COPY CONSTRUCTOR
		/// empty destructor,it relies on class hierarchy.
		virtual ~Spreadsheet();

		/// append to the result of Document#toString() the description of the number of columns and rows.
		virtual const std::string toString() const;
		/// return true if Document#equals() is true as well as the number of columns and rows are equals.
		virtual const bool equals( const Spreadsheet&) const;

		/// get the number of rows (#rowCnt) of this Spreadsheet.
		const int getRowCnt() const;
		/// set the number of rows (#rowCnt) of this Spreadsheet.
		void setRowCnt( const int);

		/// get the number of columns (#coloumnCnt) of this Spreadsheet.
		int getColoumnCnt() const;
		/// set the number of columns (#coloumnCnt) of this Spreadsheet.
		void setColoumnCnt( const int);

	protected:
		/// copy this object on a new memory location. It relies on Document#copy(), which is also used on copy constructor and assign operator.
		virtual void copy( const Spreadsheet&);

	private:
		int rowCnt;			///< the number of rows assigned to this Spreadsheet.
		int coloumnCnt;		///< the number of columns assigned to this Spreadsheet.
	};

}

#endif /* DOCUMENT_H_ */

