# SD language repository

This is the main SD language git repository.

This contains the sources for the:

- plain-text & bytecode interpreter
- bytecode compiler

Besides the sources for the main `libsd.so` library for the entire language to function.

# Building

This uses a Makefile at root to compile. It has the following targets:

- help: show the options below
- install: makes **all** utilites (and install man documentation)
- man: compresses [man](https://en.wikipedia.org/wiki/Man_page) documentation (but doesn't install it)
- interpreter: makes the plain-text & bytecode interpreter plus its dependencies
- compiler: makes the compiler plus its dependencies
- language: makes the SD language libraries (this is a dependency for most targets)
- docs: makes [doxygen](https://www.doxygen.nl/) HTML documentation (if `doxygen` is available). An older pre-compiled version of this can be found at [docs.sd/source](https://matthmr.github.io/docs.sd/source).
- clean: removes all compilation junk (`.o` and `.a` files, keeps `.so` and executables)
- clean-docs: removes all documentation junk (man's `.gz` pages and doxygen's `docs/html` output)

The default for `make` being run alone is `make install`.

The Makefile also has a couple environment variables to pass through:

- `CC`: the C compiler (cc)
- `CCFLAGS`: additional flags to pass to the compiler (-Wall)
- `AR`: the ar archiver (ar)
- `ARFLAGS`: the archiver flags (rc)
- `C_INCLUDE_PATH`: additional include path to pass to the compiler (${PWD})
- `BITS`: the machine memory address bit length (`getconf LONG_BIT`)
- `PREFIX`: the prefix for the installation (/usr/local)

Additionally for contributors, the Makefile also supports ctags with the `make tags` target.

It can be compiled with any modern C compiler.
After compilation, the results will be stored at `bin`.

# Documentation

Find the language syntax documentation at the [main website](https://matthmr.github.io/docs.sd),
source code documentation at [docs.sd/source](https://matthmr.github.io/docs.sd/source)
and the parser stack documentation at the [/docs directory](https://github.com/matthmr/sd/blob/master/docs).

# License

This repository is licensed under the [MIT License](https://opensource.org/licenses/MIT).
