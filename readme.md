# Collin's C++ Additions

This is a collection of my C++ libraries that I use for personal projects. Feel free to use these at your own risk!

I find it fun to implement my own libraries, as C++ package management can be a pain. I've decided to do my own package management style with this set of libraries.

I use GNU Make to build. I've created template files to make creating a build file easier, and hopefully cross-platform in the future.

How my libraries are set up:
- Each library has its own folder. Some folders are named after C++ standard library headers. These are either up-and-coming C++ features that I want now, or things that I believe complement that header.
- In each library folder we have a `src` folder where all the C++ source files go.
- In each library folder we have a `tests` folder where all the C++ source files for testing goes
- When building a library, the `build` folder will be automatically created and will store all build artifacts
- When building an executable (such as a test driver), the `bin` folder will be automatically created and will store all executable artifacts

As you can see, there are no header files. Oh no! Lucky for you (or maybe not so lucky), I am using C++20 modules and all my source files will be module files, containing both declarations and implementations (just as a header-only library would behave). There is still a need for header files every now and then, and I will probably end up creating an `include` folder for that when it arises.

## Building

These libraries currently only build on Windows using MSVC. This is limited by the use of C++20 modules and standard library modules (std.core). Efforts to update the template with Linux or other platforms will come when I want to build on those platforms, given C++20 features are available to use.

To build you will need [Make](https://www.gnu.org/software/make/). Each Makefile requires knowing three external variables:
1. `LIBRARIES_PATH`
2. `TEMPLATE_BEGIN`
3. `TEMPLATE_END`

The `LIBRARIES_PATH` variable is where these libraries reside. This makes referencing other libraries much easier, as they all have the same format.

The `TEMPLATE_BEGIN` variable is the path to the Makefile_template_begin file containing useful macros in creating a build file. This is meant to be included into every Makefile at the top.

The `TEMPLATE_END` variables is the path to the Makefile_template_end file containing a few more useful macros meant to be included at the end of every build file.

The template files make creating a build file much easier and with less duplication.

## Output Files

The output of calling `make` inside of a library will generate the following items:
- A module file (.ifc) for each source file
- A static library (.lib) file containing all the object (.obj) files pertaining to the library

Calling `make` will always build the library's static library, which in turn also generates all the module and object files.

Calling `make tests` will always (if tests are available) build the `tests` executable and run it.

## Other Libraries

I have another [repository](https://github.com/mooncollin/C_plus_plus-Helpful-Libraries) that contains my original C++ libraries. This project attempts to convert those libraries into a standard format, and go fully C++20 modules. Eventually this repository will have everything from that other one, and I will deprecate it.

## Docs

Documentation is generate through a Python script located under the `docs` folder. I use Jinja to generate html files and use templates to help make the process easier. I find creating the docmentation separate from embedding comments into the code to be much easier to read the code and documentation. I try to mimic the look of [cppreference.com](https://en.cppreference.com/w/).

Current documentation can be checked out [here](https://mooncollin.github.io/CPPAdditions/).