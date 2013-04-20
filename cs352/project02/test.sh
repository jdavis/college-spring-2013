#
# Project 2 Tests
# Josh Davis
#

if [[ "$1" == "--verbose" || "$1" == "-v" ]]; then
    VERBOSE=1
fi

# Test One
echo Running Test One...
./rw_test 3 0 1 0 1 > tempOutput.txt
diff tempOutput.txt - <<- EOF
output:
Reader thread 0 enters CS.
Reader thread 0 is exiting CS.
Writer thread 1 enters CS.
Writer thread 1 is exiting CS.
Reader thread 2 enters CS.
Reader thread 2 is exiting CS.
EOF

# Test Two
echo Running Test Two...
./rw_test 3 0 0 1 1 > tempOutput.txt
diff tempOutput.txt - <<- EOF
Reader thread 0 enters CS.
Reader thread 1 enters CS.
Reader thread 0 is exiting CS.
Reader thread 1 is exiting CS.
Writer thread 2 enters CS.
Writer thread 2 is exiting CS.
EOF

# Test Three
echo Running Test Three...
./rw_test 3 1 0 0 1 > tempOutput.txt
diff tempOutput.txt - <<- EOF
Writer thread 0 enters CS.
Writer thread 0 is exiting CS.
Reader thread 1 enters CS.
Reader thread 2 enters CS.
Reader thread 1 is exiting CS.
Reader thread 2 is exiting CS.
EOF

# Test Four
echo Running Test Four...
./rw_test 5 0 0 1 1 0 1 > tempOutput.txt
diff tempOutput.txt - <<- EOF
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

# Test Five
echo Running Test Five...
./rw_test 5 0 0 1 0 1 1 > tempOutput.txt
diff tempOutput.txt - <<- EOF
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

rm -f tempOutput.txt
