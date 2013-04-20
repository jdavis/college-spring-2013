#!/usr/bin/env sh
#
# Project 2 Tests
# Josh Davis
#
# Overview:
#   A few quick and crude tests for project 2
#
# Running:
#   To run it, make sure it has the right permissions:
#     chmod u+x test.sh
#   Next just execute it:
#     ./test.sh
#
# Output:
#   If the output matches up with the tests, you should only see the following
#   output:
#       Running Test One...
#       Running Test Two...
#       Running Test Three...
#       Running Test Four...
#       Running Test Five...
#   
#   A failed test will output the diff of what it should be and what it
#   actually was
#   

checkResult() {
    RESULT=$(diff tempShould.txt tempActual.txt)

    if [[ "$RESULT" != "" ]]; then
        echo Test failed.
        echo Diff Output:
        echo
        echo "$RESULT"
        echo
    fi
}

# Test One
echo Running Test One...

cat >tempShould.txt <<- EOF
Reader thread 0 enters CS.
Reader thread 0 is exiting CS.
Writer thread 1 enters CS.
Writer thread 1 is exiting CS.
Reader thread 2 enters CS.
Reader thread 2 is exiting CS.
EOF
./rw_test 3 0 1 0 1 > tempActual.txt
checkResult

# Test Two
echo Running Test Two...

cat >tempShould.txt <<- EOF
Reader thread 0 enters CS.
Reader thread 1 enters CS.
Reader thread 0 is exiting CS.
Reader thread 1 is exiting CS.
Writer thread 2 enters CS.
Writer thread 2 is exiting CS.
EOF
./rw_test 3 0 0 1 1 > tempActual.txt
checkResult

# Test Three
echo Running Test Three...

cat >tempShould.txt <<- EOF
Writer thread 0 enters CS.
Writer thread 0 is exiting CS.
Reader thread 1 enters CS.
Reader thread 2 enters CS.
Reader thread 1 is exiting CS.
Reader thread 2 is exiting CS.
EOF
./rw_test 3 1 0 0 1 > tempActual.txt
checkResult

# Test Four
echo Running Test Four...

cat >tempShould.txt <<- EOF
Reader thread 0 enters CS.
Reader thread 1 enters CS.
Reader thread 0 is exiting CS.
Reader thread 1 is exiting CS.
Writer thread 2 enters CS.
Writer thread 2 is exiting CS.
Writer thread 3 enters CS.
Writer thread 3 is exiting CS.
Reader thread 4 enters CS.
Reader thread 4 is exiting CS.
EOF
./rw_test 5 0 0 1 1 0 1 > tempActual.txt
checkResult

# Test Five
echo Running Test Five...

cat >tempShould.txt <<- EOF
Reader thread 0 enters CS.
Reader thread 1 enters CS.
Reader thread 0 is exiting CS.
Reader thread 1 is exiting CS.
Writer thread 2 enters CS.
Writer thread 2 is exiting CS.
Writer thread 4 enters CS.
Writer thread 4 is exiting CS.
Reader thread 3 enters CS.
Reader thread 3 is exiting CS.
EOF
./rw_test 5 0 0 1 0 1 1 > tempActual.txt
checkResult

rm -f tempActual.txt
rm -f tempShould.txt
