# Documentation

This directory contains three types of documentation:

1. html/
2. txt/
3. lang/

The first one refers to Doxygen's generated html from
the language source. It is empty by default but
`make docs DOCS=yes` can generate it.

The second one refers to complementary documentation
for the first one. It is written in plain text employing
a pseudo-markup language (read the [README](txt/README)).

The third one refers to the `docs.sd` git submodule
(which won't be present if this repository is cloned as
`git clone --depth=1`). It is written in markdown and
can be compiled to html using [cmark](https://commonmark.org/) or any other
markdown-to-html converter that supports inlined html,
although because the server itself uses html, it is mostly
precompiled already.
