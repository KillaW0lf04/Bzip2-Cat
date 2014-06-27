Bzip2 Cat
=========

A utility similiar to the UNIX command "cat" that is able to display the content of text files compressed using either the bz2 or gzip compression algorithm.

Requirements
------------

The following need to be installed on a Ubuntu machine:

* gcc
* libbz2
* libbz2-dev
* zlib1g-dev

Building
--------

Simply build by running the `make` command

You can then view a compressed text file as follows:

    ./bcat sometextfile.txt.bz2

Move the `bcat` executable to a location in your path (like /usr/local/bin) to run it anywhere
