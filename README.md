# document_class_hierarchy

--------------
The implementation of a simple document hierarchy in C++ (for an introductory PhD course).
--------------

The guide lines for the assignment can be found in: *"./Doc/project assignment.pdf"* while the documentation of this code is available, in pdf, at *"./Doc/documentation.pdf"* (also html format is available in the same location).

The code is composed by two main Namespaces:
- **parray**: which contains a generic template to a dynamic pointer array and an implementation for Strings list. This namespace is implemented into the file: *"./src/PointerArray.cpp"*
- **docs**: which contains all the implementation of the documents hierarchy and depends on **parray**. This namespace is defined into the file: *"./src/Document.h"*. Where, the Document class is implemented in *"./src/Document.cpp"*, while the the derived classes are in: *"./src/WebPage.cpp"* and *"./src/Spreadsheet.cpp"*.

Finally, testing and examples functions are implemented as well, for details see the *"./src/main.cpp"* file.

**Remark**: the developing of this project is aimed in experience C++ features. So, its implementation may use not optimised functions and libraries but, on the other hands, it explore the usage of templates, operators, class hierarchy etc.
