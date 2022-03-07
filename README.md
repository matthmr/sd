# SD language repository

This is the main SD language git repository.

This contains the sources for the:

- plain-text & bytecode interpreter
- compiler

Besides the sources for the main `libsdlang.so` library for the entire language to function.

# Building

This uses a `Makefile` at root to compile. It has the following targets:

- help: show the options below
- install: makes **all** utilites (and install man documentation)
- man: makes [man](https://en.wikipedia.org/wiki/Man_page) documentation (but doesn't install it)
- parser: makes the plain-text & bytecode interpreter plus its dependencies
- compiler: makes the compiler plus its dependencies
- language: makes the SD language libraries (this is a dependency for most targets)
- clean: removes all compilation junk (`.o` and `.a` files, keeps `.so` and executables)

The `Makefile` also has a couple environment variables to pass through:

[FLAG]: [EXPLANATION] (DEFAULT)

- `CC`: the C compiler (GCC)
- `CCFLAG`: additional flags to pass to the compiler ()
- `BITS`: the machine memory address bit length (64)
- `INCLUDE`: additional include path to pass to the compiler (-I${PWD})
- `AR`: the `.a` archiver (ar)
- `ARFLAG`: the archiver flags (rc)
- `PREFIX`: the prefix for the installation (/usr/local)

Additionally for contributors, the `Makefile` also supports ctags with the `make tags` target.

It can be compiled with {G}CC or its windows equivalents.
After compilation, the results will be stored at `/bin` (with the repository as root).

# Documentation

Find the documentation at the [main website](https://matthmr.github.io/docs.sd).

# License

This repository is licensed under the [MIT License](https://opensource.org/licenses/MIT).
