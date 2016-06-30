# libforth
An experiment of using Forth as a debug tool. 
Proof-of-concept custom C function calling from forth REPL.  

Well, it's a wrapper that turns pforth to a shared library and extends it with a Forth word that can execute any defined function in the debugged target (there's no need to call it explicitly) with custom signature. It can also be run on embedded systems since pforth has nice API for them.

<img src="http://i.imgur.com/RhxwDgc.gif"/> 

*Notes*: 
* It requires libffi to be installed.
* Current build has some dirty hacks that let pforth to be built into a shared library. It's better to stop using submodule and just make a fork of pforth. It'll be much cleaner.
* Currently, strucures are not supported, but I have a good idea how to fix it.
* Unit-tests and CI are also needed.

WORK IN PROGRESS.
