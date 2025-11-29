#!/bin/bash

# Delete old results file
rm -f results/all_results.csv

# Create new file with header
echo "Algorithm,Frames,PageFaults,HitRate,TestFile" > results/all_results.csv

# Run all test files
for testfile in test_cases/test_*.txt; do
    echo "Running $testfile..."
    ./page_replacement "$testfile"
done

echo ""
echo "All tests completed! Results saved to results/all_results.csv"
echo "Total lines: $(wc -l < results/all_results.csv)"