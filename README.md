Bzip2 Cat
=========

A utility similiar to the UNIX command "cat" that is able to display the content of text files compressed using the bz2 compression algorithm.

Requirements
------------

The following need to be installed on a Ubuntu machine:

* gcc
* libbz2
* libbz2-dev

Building
--------

Simply build by running the `make` command

You can then view a compressed text file as follows:

    bcat sometextfile.txt.bz2
