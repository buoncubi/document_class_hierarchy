/**
 * @file PointerArray.cpp
 * @author Buoncompagni Luca
 * @date Sep 14, 2016
 *
 * @brief The complete #parray (parray#PointerArray<T>) and #patch names paces specification and implementation.
 *
 * It describes a common templated method to convert an object into a string (patch#to_string()).
 * Also, it defines a templated manager to a dynamic array (parray#PointerArray) as well as a
 * specialisation that deal with arrays of string (parray#StringPointerArray).
 * For the last, also a static method for behavior testing is provided (StringPointerArray#tester()).
 */

#ifndef POINTER_ARRAY_H_
#define POINTER_ARRAY_H_

#include <iostream>
#include <sstream>
#include <string>


/// to emulate C++11 and get to_string translator
namespace patch{
	/// returns the description of the parameter by using << operator on a fresh std#ostringstream
	template < typename T > std::string to_string( const T& n ){
		std::ostringstream stm ;
		stm << n ;
		return stm.str() ;
	}
}

/// it specify the dynamic array manager for a generic data T and a std#string specialisation.
namespace parray{

	/// the debugging string to be appended on log head by this manager
	const std::string LOG_HEADER_INFO = " PointerArray: ";
	/// the debugging string to be appended on log head by the StringPointerArray#tester()
	const std::string LOG_HEADER_TEST = "\t[TEST] " + LOG_HEADER_INFO;


	/**
	 * \brief This class describes a manager of a dynamic array of generic type T*.
	 *
	 * It manage manipulation, creation, copy and destruction, as well as basic operator overloading.
	 * In details, the array is specified by a pointer to the head, a size integer and a cnt meaning
	 * the number of elements currently in the array.
	 */
	template < class T> class PointerArray{
		public:
			/// does not initialise the set and invalidates the counter (generates also warning log to advertise the call of #setSize())
			PointerArray(){
				std::cout << "[WARNING]" << LOG_HEADER_INFO << "Contract empty object. First of all, call setSize(..)" << std::endl;
				set = 0;
				size = -1;
				cnt = -1;
			}
			/// create a new empty array of specified size
			PointerArray( const int length){
				std::cout << "[INFO]" << LOG_HEADER_INFO << "Contract a new array with size: " << length << std::endl;
				init( length);
			}
			/// #copy() constructors
			PointerArray( const PointerArray<T>& original){
				std::cout << "[INFO]" << LOG_HEADER_INFO << "Contract a copy of: " << original << std::endl;
				copy( original);
			}
			/// destructors, invalidate counter, pointer and clear memory. Logs:  "deleting", for debugging purposes.
			virtual ~PointerArray(){
				std::cout << "[INFO]" << LOG_HEADER_INFO << "deleting " << *this << std::endl;
				if( set != 0){
					delete [] set;
					set = 0;
					size = -1;
					cnt = -1;
				}
			}

			/// set the size of a new empty array on memory and delete the previous.
			void setSize( const int length){
				init( length);
			}
			/// returns the actual size of the array.
			int getSize() const{
				return size;
			}
			/// returns the actual number of elements in the array.
			int getCnt() const{
				return cnt;
			}

			/// returns the head to the memory managed by this class.
			const T* getArray() const{
				return set;
			}

			/// returns an element of the array by index.
			virtual const T& get( int idx) const{
				return set[ idx];
			}
			/** returns #get(). */
			const T& operator[]( size_t idx) const{
				return this->get( idx);
			}

			/// add an element into the array. Returns false if the array is full
			virtual bool add( const T toAdd){
				if( cnt < size){
					set[ cnt++] = toAdd;
					return true;
				} else {
					//cerr << LOG_HEADER_INFO << "array full, cannot add \"" << toAdd << "\"." << endl;
					return false;
				}
			}

			/// returns the index of an occurrence in the array. -1 if not found
			virtual const int find( const T toFind) const{
				for( int i = 0; i < size; i++)
					if( set[ i] == toFind)
						return i;
				return -1;
			}

			/// delete the array and create a new memory location of the same size.
			virtual void clear(){
				cnt = 0;
				newSet();
			}
			/// remove an element from the array (based on #find() and #remove(int)).
			virtual const bool remove( T toRemove){
				return remove( find( toRemove));
			}
			/// remove an element from the array by index.
			virtual const bool remove( int idx){
				if( idx >= 0 && idx < size){
					for( int i = idx; i < size - 1; i++)
						set[i] = set[i + 1];
					cnt -= 1;
					return true;
				}
				std::cerr << LOG_HEADER_INFO << "array out of index, cannot remove the (" << idx << ")-th element." << std::endl;
				return false;
			}

			/// replace the array with a new memory of the defined size. Possible old values are copied from start up to fill the array.
			virtual void resize( const int newLenght){
				if( newLenght == size)
					return;
				// make a copy
				T* copy = new T[ size];
				int copyCnt = cnt;
				for( int i = 0 ; i < copyCnt; i++)
					copy[ i] = set[ i];
				// reset list
				cnt = 0;
				size = newLenght;
				newSet();
				// get the new size
				int newCnt = copyCnt;
				if( newCnt > newLenght)
					newCnt = newLenght;
				// re-populate the new list
				for( int i = 0; i < newCnt; i++)
					add( copy[i]);
				// delete copy
				delete [] copy;
				copy = 0;
			}

			/// replace the array by removing empty cell on tail (size will be equal to cnt). Based on #resize().
			virtual void pack(){
				resize( cnt);
			}

			/// returns a description of the memory managed by this class
			virtual const std::string toString() const{
				std::string out = "(size=" + patch::to_string( size) + ", cnt=" + patch::to_string( cnt) + ", ";
				for( int i = 0; i < size; i++){
					if( i == 0)
						out += "[ " + set[ i];
					else {
						out += ", " + set[ i];
						if( i >= size - 1)
							out += "]";
					}
				}
				if( size == 1)
					out += "]";
				if( size == 0)
					out += "[]";
				out += ")";
				return out;
			}
			/// calls #toString() to describe the object.
			friend std::ostream& operator<<( std::ostream& strm, const PointerArray<T>& par){
				return strm << par.toString();
			}

			/// returns true if all the elements of this array are the only elements of the parameter.
			virtual bool equals( const PointerArray<T>& toCompare) const{
				if( cnt != toCompare.getCnt())
					return false;
				for( int i = 0; i < cnt; i++)
					if( set[ i] != toCompare.get( i))
						return false;
				return true;
			}
			/// calls #equals()
			friend bool operator== (const PointerArray<T>& c1, const PointerArray<T>& c2){
				return c1.equals( c2);
			}
			/// returns the negation of #equals()
			friend bool operator!= (const PointerArray<T>& c1, const PointerArray<T>& c2){
				return !operator==( c1, c2);
			}

			/// make a #copy() of this array.
			PointerArray<T>& operator= ( const PointerArray<T>& newCopy){
				this->copy( newCopy);
				return *this;
			}

			/// returns true if there are no elements in the array.
			virtual const bool isEmpty() const{
				if( cnt == 0)
					return true;
				return false;
			}
			/// returns #isEmpty().
			bool const operator! () const{
				return isEmpty();
			}

		private:
				int size;	///< the size of the dynamic array
				int cnt;	///< the number of elements in the array
				T* set;		///< the head of the array

			/// initialises a new array of given lenght (based on #newSet()).
			void init( int length){
				if( length >= 0){
					cnt = 0;
					size = length;
					set = 0;
					newSet();
				} else std::cerr << LOG_HEADER_INFO << "cannot instantiate an array with negative length" << std::endl;
			}

			/// allocate a new memory of this object size. Delete old memory if is not invalidated.
			void newSet(){
				if( set != 0)
					delete [] set;
				set = new T[ size];
			}

			/// make a new copy in memory (based on #newSet()).
			virtual void copy( const PointerArray<T>& original){
				this->size = original.getSize();
				this->cnt = original.getCnt();
				this->set = 0;
				newSet();
				for( int i = 0; i < cnt; i++)
					this->set[ i] = original.set[ i];
			}
	};




	/**
	 * It implements a dynamic array of (T=)string manager.
	 * @see PointerArray
	 */
	class StringPointerArray : public PointerArray< std::string>{
		public:

			/// empty constructor, based on PointerArray#PointerArray().
			StringPointerArray() : PointerArray() {}
			/// constructor a new array of given length, based on PointerArray#PointerArray( int).
			StringPointerArray( const int length) : PointerArray( length) {}
			/// PointerArray#copy() constructor, based on PointerArray#PointerArray( PointerArray).
			StringPointerArray( const StringPointerArray& original) : PointerArray( original) {}
			/// empty destructor, it relies on the base implementation.
			virtual ~StringPointerArray(){}

			/// overload the PointerArray#add() method by call #resize if the array is full (generate warning).
			virtual bool add( std::string toAdd){
				if( ! PointerArray< std::string>::add( toAdd)){
					resize( getSize() + 1);
					std::cout << "[WARNING] StringPointerArray: array resized in order to add a new element." << std::endl;
					add( toAdd);
				}
				return true;
			}


			/// static method to test the behavior of a PointerArray of strings.
			static void tester(){
				int n0 = 10;
				int cnt0 = 5;

				/// Creates (pa0) new parray#StringPointArray( const int) and populate with letters.
				StringPointerArray pa0( n0);
				for( int i = 0; i < cnt0; i++)
					pa0.add( std::string( 1, 'A' + i)); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				std::cout << LOG_HEADER_TEST << "create an array of size " << n0 << " with " << cnt0 << " elements: \t\t pa0 = " << pa0 << std::endl;
				printTestDelitator(); // "----------------------------"

				/// StringPointerArray#remove( T) an element from pa0 and access the first char (StringPointerArray#operator[]()) after the manipulation.
				std::cout << LOG_HEADER_TEST << "remove the first element: \t\t\t\t pa0 = ";
				pa0.remove( std::string( 1, 'A'));
				std::cout << pa0 << std::endl;
				std::cout << LOG_HEADER_TEST << "so the first element of pa0 now is: " << pa0[0] << std::endl;
				printTestDelitator(); // "----------------------------"

				/// Creates (pa1) a new #StringPointArray() and set is size to be smaller than pa0.
				std::cout << LOG_HEADER_TEST << "create an array of unknown size..." << std::endl;
				StringPointerArray pa1;
				int n1 = n0 - 3;
				int cnt1 = cnt0 - 1;
				pa1.setSize( n1);
				std::cout << LOG_HEADER_TEST << "set the size to " << n1 << " with " << cnt1 << " elements: \t\t\t pa1 = ";
				/// Populate (StringPointerArray::add()) pa1 with some elements.
				for( int i = 0; i < cnt1; i++)
					pa1.add( std::string( 1, 'B' + i));
				std::cout << pa1 << std::endl;
				printTestDelitator(); // "----------------------------"

				/// Make a comparison (StringPointerArray#operator==()) between two #StringPointerArray (pa0 == pa1)
				bool comparison1 = ( pa0 == pa1);
				std::cout << LOG_HEADER_TEST << "are pa0 and pa1 equal? " << ( comparison1 ? "Yes." : "No.") << std::endl;
				printTestDelitator(); // "----------------------------"

				/// Creates (pa2) a copy (StringPointerArray#copy() and StringPointerArray(StringPointerArray)) of pa1.
				StringPointerArray pa2;
				pa2 = pa1; //pa2.copy( pa1);
				std::cout << LOG_HEADER_TEST << "copy pa1 in pa2 \t\t\t\t\t pa2 = " << pa2 << std::endl;
				/// StringPointerArray#remove() all its elements and makes a comparison.
				pa2.clear();
				std::cout << LOG_HEADER_TEST << "clear pa2 \t\t\t\t\t\t pa2 = " << pa2 << std::endl;
				std::cout << LOG_HEADER_TEST << "is pa2 empty? " << ( !pa2 ? "Yes." : "No.") << " Is pa1 empty? " << ( !pa1 ? "Yes." : "No.") << " (pa1 = " << pa1 << ")"<< std::endl;
				printTestDelitator(); // "----------------------------"

				/// Adds two strings to pa2.
				pa2.add( "hi");
				pa2.add( "there");
				std::cout << LOG_HEADER_TEST << "add something to pa2 \t\t\t\t\t pa2 = " << pa2 << std::endl;
				/// Creates (pa3) a #copy() of pa2 and remove the first element.
				StringPointerArray pa3( pa2);
				pa3.remove( 0);
				std::cout << LOG_HEADER_TEST << "copy constructor on pa2 and remove \"" << pa3[0] << "\" \t\t pa3 = " << pa3 << std::endl;
				/// Makes a comparison (pa3 == pa2) and #pack() pa2.
				bool comparison2 = ( pa3 == pa2);
				std::cout << LOG_HEADER_TEST << "Are pa3 and pa2 equal? " << ( comparison2 ? "Yes." : "No.") << std::endl;
				pa2.pack();
				std::cout << LOG_HEADER_TEST << "Pack pa2. \t\t\t\t\t\t pa2 = " << pa2 << std::endl;
				printTestDelitator(); // "----------------------------"

				/// #resize() pa1 to be bigger and smaller.
				int res1 = 20;
				pa1.resize( res1);
				std::cout << LOG_HEADER_TEST << "resize pa1 to " << res1 << " \t\t\t\t\t pa1 = " << pa1 << std::endl;
				int res2 = 2;
				pa1.resize( res2);
				std::cout << LOG_HEADER_TEST << "resize pa1 to " << res2 << " \t\t\t\t\t pa1 = " << pa1 << std::endl;
			}

		private:
			/// prints a line to separe different tests used in #tester() function
			static void printTestDelitator(){
				std::cout << " -------------------------------------------------------------------------------------------------------------------------------------------------- " << std::endl;
			}
	};

}
#endif /* POINTERARRAY_H_ */
