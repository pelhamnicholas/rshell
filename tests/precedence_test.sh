#!/bin/bash

# This script tests various functionality of precedence operators in
# rshell.
# Although the echo command and connectors are used, they are not 
# considered to be tested here.

#
# test basic functionality
#
echo "Input: "
echo "echo A && echo B || echo C && echo D ; exit"
sleep .5
echo "Output: "
echo "echo A && echo B || echo C && echo D ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "( echo A && echo B ) || ( echo C && echo D ) ; exit"
sleep .5
echo "Output: "
echo "( echo A && echo B ) || ( echo C && echo D ) ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "echo A && ( echo B || echo C ) && echo D ; exit"
sleep .5
echo "Output: "
echo "echo A && ( echo B || echo C ) && echo D ; exit" | bin/rshell
echo ""
sleep .5

#
# test nested parentheses
# 
echo "Input: "
echo "( echo A && ( echo B || ( echo C && echo D ) ) ) ; exit"
sleep .5
echo "Output: "
echo "( echo A && ( echo B || ( echo C && echo D ) ) ) ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "( echo A && ( echo B || echo C ) && echo D ) ; exit"
sleep .5
echo "Output: "
echo "( echo A && ( echo B || echo C ) && echo D ) ; exit" | bin/rshell
sleep .5
echo ""

echo "Input: "
echo "( ( ( echo A && echo B ) || echo C ) && echo D ) ; exit"
sleep .5
echo "Output: "
echo "( ( ( echo A && echo B ) || echo C ) && echo D ) ; exit" | bin/rshell
echo ""
sleep .5

#
# test invalid parentheses structure
# 
echo "Input: "
echo "( echo A && ( echo B || ( echo C && echo D ) ; exit"
sleep .5
echo "Output: "
{ 
    echo "( echo A && ( echo B || ( echo C && echo D )" 
    sleep .5 
    echo "exit" 
} | bin/rshell
echo ""
sleep .5

#
# test unspaced parentheses
#
echo "Input: "
echo "(echo A && echo B) || (echo C && echo D) ; exit"
sleep .5
echo "Output: "
echo "(echo A && echo B) || (echo C && echo D) ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "((echo A && echo B) || (echo C && echo D)) ; exit"
sleep .5
echo "Output: "
echo "((echo A && echo B) || (echo C && echo D)) ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "(((echo A && echo B) || echo C) && echo D) ; exit"
sleep .5
echo "Output: "
echo "(((echo A && echo B) || echo C) && echo D) ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "(echo A && (echo B || (echo C && echo D))) ; exit"
sleep .5
echo "(echo A && (echo B || (echo C && echo D))) ; exit" | bin/rshell
echo ""
sleep .5

#
# test individual commands in parentheses
#
echo "Input: "
echo "(echo A) ; exit"
sleep .5
echo "(echo A) ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "((echo A)) ; exit"
sleep .5
echo "((echo A)) ; exit" | bin/rshell
echo ""
sleep .5

echo "Input: "
echo "(((echo A))) ; exit"
sleep .5
echo "(((echo A))) ; exit" | bin/rshell
echo ""
sleep .5
