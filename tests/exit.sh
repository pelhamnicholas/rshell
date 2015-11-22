#!/bin/bash

# This bash script tests the functionality of the exit command built into
# rshell.
# Although connectors and comments are used in testing the exit command, they
# are not considered to be tested here.

#
# Basic exit test
#
echo "Input: "
echo "echo \"something before exit\" ; exit ; echo \"something after exit\""
sleep .5
echo "Output: "
echo "echo \"something before exit\" ; exit ; echo \"something after exit\"" | bin/rshell
echo ""
sleep .5

#
# Skipping exit with connectors
#
echo "Input: "
echo "echo \"something before exit\" || exit ; echo \"something after exit\" ; exit"
sleep .5
echo "Output: "
echo "echo \"something before exit\" || exit ; echo \"something after exit\" ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "notacommand && exit ; echo \"something after exit\" ; exit"
sleep .5
echo "Output: "
echo "notacommand && exit ; echo \"something after exit\" ; exit" | bin/rshell
echo  ""
sleep .5

#
# Exit in a comment
#
echo "Input: "
echo "echo \"Before a comment\" # exit"
echo "echo \"After a comment\" ; exit"
sleep .5
echo "Output: "
{   echo "echo \"Before a comment\" # exit" ;
    echo "echo \"After a comment\" ; exit" ;
} | bin/rshell
echo ""
sleep .5

#
# Exit inside an argument
#
echo "Input: "
echo "echo Argument with the word exit ; echo Didn't trigger exit ; exit"
sleep .5
echo "Output: "
echo "echo Argument with the word exit ; echo Didn't trigger exit ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "echo exit starts this argument ; echo Didn't trigger exit ; exit"
sleep .5
echo "Output: "
echo "echo exit starts this argument ; echo Didn't trigger exit ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "echo This argument has exit in it ; echo Didn't trigger exit ; exit"
sleep .5
echo "Output: "
echo "echo This argument has exit in it ; echo Didn't trigger exit ; exit" | bin/rshell
echo ""
sleep .5
