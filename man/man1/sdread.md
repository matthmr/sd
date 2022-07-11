# sdread - The default SD language interpreter

## SYNOPSIS
**sdread** [ *-i*, *--int* ]
       [ [ *-b*, *--byte* ] <*file*...> ]
       [ [ *-m*, *--mod* ] <*module*...>]
       [ [ *-e*, *--expr* ] <*expr*...> ]
       <*file*...>

## DESCRIPTION
**sdread** is the default plain-text & bytecode interpreter for the SD language.
It is linked through the **sd** symbolic link to become the default parser for SD,
but there also exists **libsdcore.so**, which is a small runtime library to run SD bytecode
embbed in a binary file. **sdread** wraps arround two implementations of the SD parser,
one for SD plain-text source code, and another one for SD bytecode.

## OPTIONS
|                       |                                                                     |
|-----------------------|---------------------------------------------------------------------|
| *-*                   | streams a file from **STDIN**. Only one of these flags can be passed|
| *-b*, *--byte*        | streams a bytecode file.                                            |
| *-s*, *--source*      | streams a plain-text file. Used to override *--byte*.               |
| *-m*, *--mod*         | runs the `main` procedure of a given module.                        |
| *-i*, *--int*         | runs in interactive mode; can be combined with *-s* and *-m*        |
| *-e*, *--expr*        | parses `expr` and executes it **after** parsing the file.           |
| *-E*, *--Expr*        | parses `expr` and executes it **before** parsing the file.          |
| *-h*, *--help*        | displays a help message, then exits.                                |
| *-v*, *--version*     | displays the current version, then exits.                           |

## COMPOUND FLAGS
**sdread** can make use of compounds flags. The default will be set in parentheses.

|                       |                                                                     |
|-----------------------|---------------------------------------------------------------------|
| *-o{,no}color*        | {en,dis}ables color display through ANSI escape sequences. (-ocolor)|


## EXPRESSIONS
**sdread** can be run with an optional expression passed as a string. SD will parse its
contents asynchronously from the main files being passed in and will synchronize them once
the main file has been fully loaded **or**, if passed the **-E** flag, it will parse the expression
and execute it first, then those of the files.

Regardless of the parse time, its resultant objects are appended (or prepended)
to the main module root. If parsing a single file, the main module root is that
file's object code. If parsing multiple files, the main module root is a bundle
of the files. If executing a single module or multiple modules, the main module
root is a bundle of the modules.

## NOTES
- Byte default, typeless <file> is of type "**source**", aka plain-text.
- If **sdread** is called without any file parameters, it will assume that a
  pipe has been opened. Don't run `sdread` by itself if you want an interactive
  shell.

## SEE ALSO
	sdc(1), sdapi(3)

## DEVELOPERS
	mH (https://github.com/matthmr)

## VERSION
**SD** is at version *v0.4.2* as of July 2022.
