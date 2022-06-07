# SD language repository

This is the main SD language git repository.

This contains the sources for the:

- plain-text & bytecode interpreter
- bytecode compiler

Besides the sources for the main `libsd.so` library for the entire language to function.

# Building

This uses a **Makefile** and a **configure** file at root to compile.
The Makefile has the following final targets:

- help: show the options below
- install: makes **all** utilites (and install man documentation)
- man: compresses [man](https://en.wikipedia.org/wiki/Man_page) documentation (but doesn't install it)
- ctags: makes [ctags](https://ctags.io) tag file for the source repository
- interpreter: makes the plain-text & bytecode interpreter plus its dependencies
- compiler: makes the compiler plus its dependencies
- language: makes the SD language libraries (this is a dependency for most targets)
- docs: makes [doxygen](https://www.doxygen.nl/) HTML documentation (if `doxygen` is available).
- clean: removes all compilation junk (`.o` and `.a` files, keeps `.so` and executables)

The default for `make` being run alone is `make install`.

The 'configure' script also has a couple options to pass through:

- `CC`: the C compiler (cc)
- `CFLAGS`: additional flags to pass to the compiler (-Wall)
- `AR`: the ar archiver (ar)
- `ARFLAGS`: the archiver flags (rc)
- `C_INCLUDE_PATH`: additional include path to pass to the compiler (.)
- `BITS`: the machine memory address bit length (64)
- `PREFIX`: the prefix for the installation (/usr/local)

and a couple booleans:

- `DOCS`: install doxygen documentation (no)
- `SRCDOCS`: install source code documentation (no)
- `TEST`: run test suite before installing (yes)

that can also be overwriten at `make` time if passed as `make` variables, but it is encouraged
to pass them as options to the `./configure` script.

To fully compile the SD suite, run `./configure && make install`. 'configure' *must* be run first
as it will autogenerate make targets in the `Sources.mk` file. This project *does not* use the
GNU autotools, the *configure-make* scheme is only used for convenience.

It can be compiled with any modern C compiler (gcc, clang, ...). After compilation, the results
will be stored at `bin` and `lib`. For more info, run `make help` & `./configure --help`.

# Documentation

Find the language syntax documentation at the [main website](https://matthmr.github.io/docs.sd),
source code documentation at [docs.sd/source](https://matthmr.github.io/docs.sd/source)
and the parser stack documentation at the [/docs directory](https://github.com/matthmr/sd/blob/master/docs).

# License

This repository is licensed under the [MIT License](https://opensource.org/licenses/MIT).
