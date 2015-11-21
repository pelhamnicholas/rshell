#!/bin/bash

# This script tests various functionality of the test command in rshell
# Although precedence operators are used to display the results of the test command,
# they are not considered to be tested here.

# make a file for testing purposes
touch "has spaces in its name"

# list of files used in tests
declare -a test_files=("README.md" "src" "nonexistant.file" "makefile" "tests/test_command.sh" "has\ spaces\ in\ its\ name")

#
# tests basic functionality on an assortment of files
#
for FILE in "${test_files[@]}"
do
# test -e on $FILE
    echo "Input Line: ";
    echo "test -e $FILE && echo \"$FILE exists\" || echo \"$FILE does not exist\" ; exit" ;
    sleep .5;
    echo "test -e $FILE && echo \"$FILE exists\" || echo \"$FILE does not exist\" ; exit" | bin/rshell
    echo "" ;
    sleep .5;

# test -f on $FILE
    echo "Input Line: ";
    echo "( ( test -f $FILE && echo \"$FILE exists and is a regular file\" ) || ( test -e $FILE && echo \"$FILE exists but is not a regular file\" ) ) || echo \"$FILE does not exist\" ; exit" ;
    sleep .5;
    echo "( ( test -f $FILE && echo \"$FILE exists and is a regular file\" ) || ( test -e $FILE && echo \"$FILE exists but is not a regular file\" ) ) || echo \"$FILE does not exist\" ; exit" | bin/rshell
    echo "" ;
    sleep .5;

# test -d on $FILE
    echo "Input Line: "
    echo "( ( test -d $FILE && echo \"$FILE exists and is a directory\" ) || ( test -e $FILE && echo \"$FILE exists but is not a directory\" ) ) || echo \"$FILE does not exist\" ; exit" ;
    sleep .5;
    echo "( ( test -d $FILE && echo \"$FILE exists and is a directory\" ) || ( test -e $FILE && echo \"$FILE exists but is not a directory\" ) ) || echo \"$FILE does not exist\" ; exit" | bin/rshell
    echo "" ;
    sleep .5;
done

#
# tests basic symbolic functionality on an assortment of files
#
for FILE in "${test_files[@]}"
do
#test -e on #file
    echo "Input Line: " ;
    echo "[ -e $FILE ] && echo \"$FILE exists\" || echo \"$FILE does not exist\" ; exit" ;
    sleep .5;
    echo "[ -e $FILE ] && echo \"$FILE exists\" || echo \"$FILE does not exist\" ; exit" | bin/rshell
    echo "" ;
    sleep .5;

# test -f on #file
    echo "Input Line: " ;
    echo "( ( [ -f $FILE ] && echo \"$FILE exists and is a regular file\" ) || ( [ -e $FILE ] && echo \"$FILE exists but is not a regular file\" ) ) || echo \"$FILE does not exist\" ; exit" ;
    sleep .5;
    echo "( ( [ -f $FILE ] && echo \"$FILE exists and is a regular file\" ) || ( [ -e $FILE ] && echo \"$FILE exists but is not a regular file\" ) ) || echo \"$FILE does not exist\" ; exit" | bin/rshell
    echo "" ;
    sleep .5;

# test -d on #file
    echo "Input Line: " ;
    echo "( ( [ -d $FILE ] && echo \"$FILE exists and is a regular file\" ) || ( [ -e $FILE ] && echo \"$FILE exists but is not a directory\" ) ) || echo \"$FILE does not exist\" ; exit" ;
    sleep .5;
    echo "( ( [ -f $FILE ] && echo \"$FILE exists and is a regular file\" ) || ( [ -e $FILE ] && echo \"$FILE exists but is not a directory\" ) ) || echo \"$FILE does not exist\" ; exit" | bin/rshell
    echo "" ;
    sleep .5;
done

#
# tests default method of using the symbolic functionality on an assortment of files
#
for FILE in "${test_files[@]}"
do
    echo "Input Line: " ;
    echo "[ $FILE ] && echo \"$FILE exists\" ; exit" ;
    sleep .5 ;
    echo "[ $FILE ] && echo \"$FILE exists\" ; exit" | bin/rshell
    echo "" ;
done

#
# tests spacing of symbolic syntax
#
for FILE in "${test_files[@]}"
do
    echo "Input Line: " ;
    echo "[e $FILE] && echo \"$FILE exists\" ; exit" ;
    sleep .5 ;
    echo "[e $FILE] && echo \"$FILE exists\" ; exit" | bin/rshell
    echo "" ;
done
for FILE in "${test_files[@]}"
do
    echo "Input Line: " ;
    echo "[-e $FILE] && echo \"$FILE exists\" ; exit" ;
    sleep .5 ;
    echo "[-e $FILE] && echo \"$FILE exists\" ; exit" | bin/rshell
    echo "" ;
done
for FILE in "${test_files[@]}"
do
    echo "Input Line: " ;
    echo "[-f $FILE ] && echo \"$FILE exists and is a regular file\" ; exit" ;
    sleep .5 ;
    echo "[-f $FILE ] && echo \"$FILE exists and is a regular file\" ; exit" | bin/rshell
    echo "" ;
done
for FILE in "${test_files[@]}"
do
    echo "Input Line: " ;
    echo "[ -d $FILE] && echo \"$FILE exists and is a directory\" ; exit" ;
    sleep .5;
    echo "[ -d $FILE] && echo \"$FILE exists and is a directory\" ; exit" | bin/rshell
    echo "" ;
done

rm has\ spaces\ in\ its\ name
