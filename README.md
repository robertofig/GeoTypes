# GeoTypes

Library for manipulating geometric objects, and providing easy IO for common GIS data types in C++ code.

The [geotypes-base.h](src/geotypes-base.h) header provides basic geometric types and querying/editing for them. Currently in experimental state, should not be used in production software.

The data types available currently are:

* [Shapefile](src/geotypes-shp.h): full read and write support.
* [WKB](src/geotypes-wkb.h): full read and write support.

The reason for this library, when other libraries for reading and manipulating GIS are available, is to provide a lightweight and straightforward way of adding such capabilities to C++ code. No dependency hell, no hidden memory allocation, no exception handling - just add the desired header file to the project and start using it.

## How to use?

The header files contain the struct and function declarations, and the .c files contain the implementations.

The library files can be moved in whole to the project directory, in which case the header files will include the .c files in the translation unit. They have very short compile times, which makes this approach feasible.

Alternatively, one can build these into objects or static library, in which case passing `GEOTYPES_STATIC_LINKING` as a preprocessing symbol when compiling the project will prevent the header files from including the implementation files.

## Dependencies

This library currently builds on top of [TinyBase](https://github.com/robertofig/TinyBase). The `Base` and `WKB` modules make use of tinybase-types, and the `Shapefile` module makes use of tinybase-strings and tinybase-platform for generating necessary DBF info.

## Tests

Unit tests are provided in the /tests subfolder for most functionalities in the libraries, though they need expanding. The sub-folder /tests/data provide sample files for supporting the tests.

To build the tests, edit the `build.bat` file located in /tests and add the path to the TinyBase library, then run. A /build folder will be created (if not already), and the test executables will be placed there, along with debug symbols.

## License

MIT open source license.
