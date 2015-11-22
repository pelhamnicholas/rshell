#!/bin/bash

# This script tests the functionality of connectors in rshell to chain 
# multiple commands together.

#
# Tests semicolor connector
#
echo "Input: "
echo "ls ; cat makefile ; ls -l src ; exit"
sleep .5
echo "Output: "
echo "ls ; cat makefile ; ls -l src ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "badcommand ; ls -l ; exit"
sleep .5
echo "Output: "
echo "badcommand ; ls -l ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "ls -l ; badcommand ; exit"
sleep .5
echo "Output: "
echo "ls -l ; badcommand ; exit" | bin/rshell
echo ""
sleep .5

#
# Tests the or connector
#
echo "Input: "
echo "ls || cat makefile || ls -l src ; exit"
sleep .5
echo "Output: "
echo "ls || cat makefile || ls -l src ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "badcommand || ls -l ; exit"
sleep .5
echo "Output: "
echo "badcommand || ls -l ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "ls -l || badcommand ; exit"
sleep .5
echo "Output: "
echo "ls -l || badcommand ; exit" | bin/rshell
echo ""
sleep .5

#
# Tests the and connector
#
echo "Input: "
echo "ls && cat makefile && ls -l src ; exit"
sleep .5
echo "Output: "
echo "ls && cat makefile && ls -l src ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "badcommand && ls -l ; exit"
sleep .5
echo "Output: "
echo "badcommand && ls -l ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "ls -l && badcommand ; exit"
sleep .5
echo "Output: "
echo "ls -l && badcommand ; exit" | bin/rshell
echo ""
sleep .5
