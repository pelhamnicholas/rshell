#!/bin/bash

# This bash script tests the functionality of comments in rshell.
# Although connectors are used they are not considered to be tested here.

#
# Test of basic comments
#
echo "Input: "
echo "# This is a commented line"
echo "exit"
sleep .5
echo "Output: "
{   echo "# This is a commented line" ;
    echo "exit" ;
} | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "#This is a commented line"
echo "exit"
sleep .5
echo "Output: "
{   echo "#This is a commented line" ;
    echo "exit" ;
} | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "echo Something before # a commented line"
echo "exit"
sleep .5
echo "Output: "
{   echo "echo Something before # a commented line" ;
    echo "exit" ;
} | bin/rshell
echo ""
sleep .5

#
# Testing comments inside quotations
#
echo "Input: "
echo "echo \"# This is a commented line\""
echo "exit"
sleep .5
echo "Output: "
{   echo "echo \"# This is a commented line\"" ;
    echo "exit" ;
} | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "echo \"#This is a commented line\""
echo "exit"
sleep .5
echo "Output: "
{   echo "echo \"#This is a commented line\"" ;
    echo "exit" ;
} | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "echo \"Something before # a commented line\""
echo "exit"
sleep .5
echo "Output: "
{   echo "echo \"Something before # a commented line\"" ;
    echo "exit" ;
} | bin/rshell
echo ""
sleep .5

#
# Testing escaped comments
#
echo "Input: "
echo "\# This is a commented line"
echo "exit"
sleep .5
echo "Output: "
{   echo "\# This is a commented line" ;
    echo "exit" ;
} | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "\#This is a commented line"
echo "exit"
sleep .5
echo "Output: "
{   echo "\#This is a commented line" ;
    echo "exit" ;
} | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "echo Something before \# a commented line"
echo "exit"
sleep .5
echo "Output: "
{   echo "echo Something before \# a commented line" ;
    echo "exit" ;
} | bin/rshell
echo ""
sleep .5
