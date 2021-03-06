[![Build Status](https://travis-ci.org/profan/yet-another-brainfuck-interpreter.svg?branch=master)](https://travis-ci.org/profan/yet-another-brainfuck-interpreter)

yet-another-brainfuck-interpreter
=================================

Just a simple brainfuck interpreter written in Portable C (ANSI).

Requirements
------------

* ANSI-C compatible compiler (Makefile uses system default C compiler).
  * Testing is done on gcc 4.6 and clang 3.4.
* GNU Make (only for build).


Building with GNU Make

		make

Running the test suite

		make test
		
Building without endline filtering, turning '\n' into 10 on input and 10 on output to '\n'...

		make nofilter
		
Cleaning up binaries and object files (required to build new binary without filtering/with filtering if already built)

		make clean

Downloading the source
------------

Either with git clone as below or by downloading a zipball of the [latest.](https://github.com/Profan/yet-another-brainfuck-interpreter/archive/master.zip).

		git clone https://github.com/Profan/yet-another-brainfuck-interpreter.git

Usage
------------
After building the interpreter, simply run it as such in your favorite terminal:

		usage: yabi <filename>

Details
------------
* Single header lib, just include lib/brain.h and you're set.
* Cleans up comments and no-op characters at parse-time.
* Turns consecutive ptrmov/arithmetic operations into single operations(>>> into {>, 3}, +++ into {+, 3})
* It uses char sized cells (usually a single byte).
* By default it has 65536 memory cells at its disposal.
* Max input size is also limited to 65536 characters (brain.h has defines).
* Converts newline characters to 10 on input and back to platform newline on output, if required.
    * Can be turned off by defining 'NO\_EOL\_FILTER' when compiling.
* Includes a special '#' character commonly implemented as debug printing of memory cells, once passed over in code it emits the content of the 16 first memory cells, space separated, ending with a newline.
* Returns BRAIN\_MEM\_OUT\_OF\_BOUNDS the memory pointer goes outside the range of the memory cells.
* Returns BRAIN\_PC\_OUT\_OF\_BOUNDS if the instruction pointer tries to reach outside of the range allocated. 

TODO
------------
- [ ] Add interactive input mode.
- [ ] Add debugging mode.
- [ ] More sophisticated optimizations?
- [x] Write tests(needs more).

Credits
------------
Many thanks to daniel b cristofani and his collection of brainfuck interpreters and programs at:
	http://www.hevanet.com/cristofd/brainfuck/

License
------------
See attached LICENSE file.
