yet-another-brainfuck-interpreter
=================================

Just a simple brainfuck interpreter written in Portable C (ANSI).

Requirements
------------

* ANSI-C compatible compiler (Makefile uses gcc by default).
* GNU Make (only for build).


Building with GNU Make

		make
		
Cleaning up binaries and object files

		make clean

Downloading the source
------------

Either with git clone as below or by downloading a zipball of the [latest.](https://github.com/Profan/yet-another-brainfuck-interpreter/archive/master.zip).

		git clone https://github.com/Profan/yet-another-brainfuck-interpreter.git

Usage
------------
After building the interpreter, simply run it as such in your favorite terminal:

		usage: yabi <filename> [<args>]

Details
------------
* It uses char sized cells (usually a single byte).
* By default it has 65536 memory cells at its disposal.
* Max input size is also limited to 65536 characters (brain.h has defines).
* Converts newline characters to 10 on input and back to platform newline on output, if required.
    * Can be turned off by defining 'NO_EOL_FILTER' when compiling.
* Includes a special '#' character commonly implemented as debug printing of memory cells, once passed over in code it emits the content of the 16 first memory cells, space separated, ending with a newline.
* Exits if the memory pointer goes outside the range of the memory cells.
* Exits if the instruction pointer tries to reach outside of the range allocated. 

Credits
------------
Many thanks to daniel b cristofani and his collection of brainfuck interpreters and programs at:
	http://www.hevanet.com/cristofd/brainfuck/
