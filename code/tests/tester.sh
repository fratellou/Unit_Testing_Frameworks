#!/bin/bash

./testing

# Run the calculator on each test file and compare with expected results
../calculator test_file_1 >> calc_file_1.txt
echo -n "\nTest file 1:\nCalculator result: "
../calculator test_file_1
echo "2" >> real_result_file_1.txt
echo "Real result: 2"
if diff -s calc_file_1.txt real_result_file_1.txt > /dev/null; 
    then echo "TEST: PASSED";
else
    echo "TEST:ERROR";
fi
rm real_result_file_1.txt calc_file_1.txt

../calculator test_file_2 >> calc_file_2.txt
echo -n "\nTest file 2:\nCalculator result: "
../calculator test_file_2
echo "9" >> real_result_file_2.txt
echo "Real result: 9"
if diff -s calc_file_2.txt real_result_file_2.txt > /dev/null; 
    then echo "TEST: PASSED";
else
    echo "TEST:ERROR";
fi
rm real_result_file_2.txt calc_file_2.txt

../calculator test_file_3 >> calc_file_3.txt
echo -n "\nTest file 3:\nCalculator result: "
../calculator test_file_3
../calculator test_file_3 > calc_file_3.txt 2>&1
echo "Error: An attempt to divide by 0." >> real_result_file_3.txt
echo "Real result: Error: An attempt to divide by 0."
if diff -s calc_file_3.txt real_result_file_3.txt > /dev/null; 
    then echo "TEST: PASSED";
else
    echo "TEST:ERROR";
fi
rm real_result_file_3.txt calc_file_3.txt

echo "\nCalculator tests completed."
