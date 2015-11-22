#rshell

##Overview

rshell is a simple shell program that serves as an interface between a user 
and their operating system. It allows a user to chain commands together with 
specified connectors. The commands entered are run by default in left to 
right precedence, but can be run in any other precedence by including 
parentheses.

* `<cmd1> && <cmd2>` - Executes the second command only if the first command
executes successfully
* `<cmd1> || <cmd2>` - Executes the second command only if the first command
fails to execute
* `<cmd1> ; <cmd2>`  - Executes both commands regardless of the success or 
failure of the other

##Design
Commands utilize a composite pattern in their inheritance structure. Adding a 
new command can be done by creating a new class for it inherited from the 
`Instruction` class and overwriting its pure virtual method `int execute()`. 
For each command added this way, a new case must be created in the 
`InstructionTree::makeTree()` method.

Connectors are all handled inside `class Connector`. New connectors should be 
added to `const char * const Connector::CONNECTOR` in connector.cpp, 
`NUMCONNECTORS` should be incremented in connector.h, and a new case should 
be added to `int Connector::execute()`.

Additional precedence delimiters can be added by including them appropriatley 
to both `const char InstructionTree::openParen[]` and `const char 
InstructionTree::closeParen[]` in instructiontree.cpp, and incrementing
`NUMPARENS` in instructiontree.h.

##Tests
Bash scripts are included in this repository to automate the testing of 
various functionality of rshell.
###test_command
Bash shell script to test the functionality of the test command in rshell
###precedence_test
Bash shell script to test the functionality of precedence operators in rshell

##Known Bugs
* Including parentheses in command arguments can result in unexpected behavior
    * Leading parentheses are removed if they are the first characters in the
    argument
    * Trailing parentheses are removed if they make up the last characters of
    the argument
* Certain commands expected of a shell program do not work. These commands
include, but are not limited to:
    * cd
    * alias
    * logout
* All output from rshell is monocolored. Any colors expected in shell output
are not displayed

##Contributors
Nicholas Pelham : [website](http://pelhamnicholas.wordpress.com)
