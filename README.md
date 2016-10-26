# document_class_hierarchy

--------------
The implementation of a simple document hierarchy in C++ (for an introductory PhD course).
--------------

The guide lines for the assignment can be found in: "./Doc/project assignment.pdf" while the documentation of this code is available, in pdf, at "./Doc/documentation.pdf" (also html format is available in the same location).

The code is composed by two main Namespacse:
- parray: which contains a generic template to a dinamic pointer array and an implementation for Strings list. This namespace is implemented into the file: "./src/PointerArray.cpp"
- docs: which contains all the implementation of the documents hierarchy. This namespace is defined into the file: "./src/Document.h". More in particular, the Document class is implemented in "./src/Document.cpp". While the implementation of the derived classes are in: "./src/WebPage.cpp", "./src/Spreadsheet.cpp".

Finally, testing and examples functions are implemented as well. In dettails see file: "./src/main.cpp".
