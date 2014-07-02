yet-another-brainfuck-interpreter
=================================

Just a simple brainfuck interpreter written in Portable C (ANSI).

To build run

		make

Usage
------------
After building the interpreter, simply run it as such in your favorite terminal:

		./yabi filename

Details
------------
* It uses byte sized cells.
* By default it has 65536 memory cells at disposal
* Max input size is also limited to 65536 characters (brain.h has defines).
* Converts EOF characters to 10 as per most brainfuck interpreters and back to EOF on the way out.
    * Can be turned off by defining 'NO_EOF_FILTER' when compiling.
* Exits if the memory pointer goes outside the range of the memory cells.
* Exits if the instruction pointer tries to reach outside of the range allocated. 

Credits
------------
Many thanks to daniel b cristofani and his collection of brainfuck interpreters and programs at:
	http://www.hevanet.com/cristofd/brainfuck/
