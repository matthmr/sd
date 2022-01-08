# SD language repository

This is the main SD language git repository.

This contains the sources for the:

- plain-text interpreter
- bytecode interpreter
- compiler
- linker

Besides the sources for the main `libsdlang.so` library for the entire language to function.

# Building

This uses a `Makefile` at root to compile. It has the following targets:

- install: make **all** utilites
- parser: make the plain-text interpreter plus its dependencies
- binary-parser: make the bytecode interpreter plus its dependencies
- linker: make the linker plus its dependencies
- compiler: make the compiler plus its dependencies
- language: make the SD language libraries (this is a dependency for most targets)
- clean: removes all compilation junk (`.o` and `.a` files)

The `Makefile` also has a couple environment variables to pass through:

- `CC`: the C compiler (GCC)
- `CCFLAG`: additional flags to pass to the compiler ()
- `AR`: the `.a` archiver (ar)
- `ARFLAG`: the archiver flags (cqv)
- `PREFIX`: the prefix for the installation (/usr/local)

Additionally for contributors, the `Makefile` also supports ctags with the `make tags` target.

It can be compiled with GCC, Clang12 or its windows equivalents.

# Documentation

Find the documentation at the [main website](https://matthmr.github.io/sd/index.html).

# License

This repository is licensed under the [MIT License](https://opensource.org/licenses/MIT).
