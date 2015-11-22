#!/bin/bash

# This script tests the functionality of single commands in rshell
# Although some connectors are used to exit the shell, connectors are
# not considered to be tested here.

#
# Tests known functionality of the ls command
#
echo "Input: "
echo "ls ; exit"
sleep .5
echo "Output:"
echo "ls ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "ls -l ; exit"
sleep .5
echo "ls -l ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "ls -a -l ; exit"
sleep .5
echo "Output: "
echo "ls -a -l ; exit" | bin/rshell
echo ""
sleep .5

#
# Tests failed commands
#
echo "Input: "
echo "notacommand ; exit"
sleep .5
echo "Output: "
echo "notacommand ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "ls notadirectory ; exit"
sleep .5
echo "Output: "
echo "ls notadirectory ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "\"ls inquotes\" ; exit"
sleep .5
echo "Output: "
echo "\"ls inquotes\" ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "ls \"arguments in quotes\" ; exit"
sleep .5
echo "ls \"arguments in quotes\" ; exit"
echo ""
sleep .5

echo "Input: "
echo "mkdir \"directory with spaces\" ; exit"
sleep .5
echo "Output: "
echo "mkdir \"directory with spaces\" ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "touch directory\ with\ spaces/file1 ; exit"
sleep .5
echo "Output: "
echo "touch directory\ with\ spaces/file1 ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "touch \"directory with spaces/file2\" ; exit"
sleep .5
echo "Output: "
echo "touch \"directory with spaces/file2\" ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "mkdir directory\ with\ spaces/dir ; exit"
sleep .5
echo "mkdir directory\ with\ spaces/dir ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "ls -la \"directory with spaces\" ; exit"
sleep .5
echo "Output: "
echo "ls -la \"directory with spaces\" ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "rm -r directory\ with\ spaces ; exit"
sleep .5
echo "Output: "
echo "rm -r directory\ with\ spaces ; exit" | bin/rshell
echo ""
sleep .5

