# Collin's C++ Additions

This is a collection of my C++ libraries that I use for personal projects. Feel free to use these at your own risk!

I find it fun to implement my own libraries, as C++ package management can be a pain. I've decided to do my own package management style with this set of libraries.

I use GNU Make to build. I've created template files to make creating a build file easier, and hopefully cross-platform in the future.

How my libraries are set up:
- Each library has its own folder. Some folders are named after C++ standard library headers. These are either up-and-coming C++ features that I want now, or things that I believe complement the standard.
- In each library folder we have a `src` folder where all the C++ source files go.
- In each library folder we have a `tests` folder where all the C++ source files for testing goes
- When building a library, the `build` folder will be automatically created and will store all build artifacts
- When building an executable (such as a test driver), the `bin` folder will be automatically created (for that library) and will store all executable artifacts

As you can see, there are no header files. Oh no! Lucky for you (or maybe not so lucky), I am using C++20 modules and all my source files will be module files, containing both declarations and implementations (just as a header-only library would behave).

## Building

These libraries currently only build on Windows using MSVC. This is limited by the use of C++20 modules and standard library modules (std.core). Efforts to update the template with Linux or other platforms will come when I want to build on those platforms, given C++20 features are available to use.

To build you will need [Make](https://www.gnu.org/software/make/). There is a Makefile in the root folder, which will build all release-ready libraries into a single .lib file. This Makefile calls down to other Makefiles in each folder, compiling that libraries' code.

## Output Files

The output of calling `make` inside of a library will generate the following items in the root build folder:
- A module file (.ifc) for each source file
- A static library (.lib) file containing all the object (.obj) files pertaining to the library

Calling `make` will always build the library's static library, which in turn also generates all the module and object files.

Calling `make tests` will always (if tests are available) build the `tests` executable for that library and run it.

To consume my library, call `make` on the root folder, and that will build my release-ready libraries (some libraries are WIP) into a single .lib and a whole bunch of module files. I haven't yet figured out how to combine module files, but compilers will just let you give a directory and it will lookup modules automatically. So all you need to do is point your module path and linker at the root build folder.

## Other Libraries

I have another [repository](https://github.com/mooncollin/C_plus_plus-Helpful-Libraries) that contains my original C++ libraries. This project attempts to convert those libraries into a standard format, and go fully C++20 modules. Eventually this repository will have everything from that other one, and I will deprecate it.

## Docs

Documentation is generate through a Python script located under the `docs` folder. I use Jinja to generate html files and use templates to help make the process easier. I find creating the docmentation separate from embedding comments into the code to be much easier to read the code and documentation. I try to mimic the look of [cppreference.com](https://en.cppreference.com/w/).

Current documentation can be checked out [here](https://mooncollin.github.io/CPPAdditions/).