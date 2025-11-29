# csce5640-project2

# **README - Page Replacement Algorithms Simulator**

## **Project Information**
- **Course:** CSCE 5640 - Operating System Design
- **Project:** Project 2 - Page Replacement Algorithms
- **Team Members:**
  - Afifah Khan (ID: 11800954)
  - Bhavana Bayyapu (ID: 11680072)
  - Deepika Thakur (ID: 11751906)
  - Nanditha Aitha (ID: 11759521)

---

## **Project Overview**
This project implements and compares five page replacement algorithms:
- FIFO (First-In-First-Out)
- Optimal
- LRU (Least Recently Used)
- LFU (Least Frequently Used)
- MFU (Most Frequently Used)

---

## **File Structure**
```
csce5640-project2/
├── src/
│   ├── main.cpp                  # Main program
│   ├── page_replacement.h        # Base class header
│   ├── page_replacement.cpp      # Base class implementation
│   ├── fifo.cpp                  # FIFO algorithm
│   ├── optimal.cpp               # Optimal algorithm
│   ├── lru.cpp                   # LRU algorithm
│   ├── lfu.cpp                   # LFU algorithm
│   └── mfu.cpp                   # MFU algorithm
├── test_cases/
│   ├── generate_tests.py         # Python script to generate test cases
│   ├── sample_test.txt           # Sample test file
│   ├── test_small_frames.txt     # Small test file
│   └── test_*frames_*.txt        # Generated test files (35 files)
├── results/
│   ├── all_results.csv           # All experimental results
│   └── summary_statistics.csv    # Summary statistics
├── Makefile                      # Build configuration
├── run_all_tests.sh              # Script to run all tests
└── README.md                     # This file
```

---

## **Prerequisites**
- **Operating System:** Linux (tested on UNT CSE Ubuntu 24 machines)
- **Compiler:** g++ with C++11 support
- **Python:** Python 3 (for test generation)
- **Make:** GNU Make

---

## **Installation and Setup**

### **Step 1: Navigate to Project Directory**
```bash
cd ~/csce5640/csce5640-project2
```

### **Step 2: Generate Test Cases (if needed)**
The repository already includes generated test cases. If you want to regenerate them:
```bash
cd test_cases
python3 generate_tests.py
cd ..
```

---

## **How to Run**

# Step 1: Clean and compile
make clean
make

# Step 2: Make script executable (only needed once)
chmod +x run_all_tests.sh

# Step 3: Run all tests
./run_all_tests.sh

# Step 4: Verify results
wc -l results/all_results.csv  # Should show 181 lines

**Example output:**
```
========================================
Page Replacement Simulation
Test File: test_cases/sample_test.txt
Frames: 10
Reference String Length: 12
========================================

Algorithm: FIFO
Page Faults: 5
Hit Rate: 58.33%

Algorithm: Optimal
Page Faults: 5
Hit Rate: 58.33%
...
```
---

## **Understanding Test Files**

### **Test File Format**
Each test file has this structure:
```
frames: 10
reference_string: 1 2 3 4 1 2 5 1 2 3 4 5
```

- **Line 1:** Number of frames (memory slots)
- **Line 2:** Space-separated page reference sequence

### **Available Test Categories**
- **3 frames:** 5 test files (test_3frames_1.txt to test_3frames_5.txt)
- **5 frames:** 5 test files
- **10 frames:** 5 test files
- **15 frames:** 5 test files
- **20 frames:** 5 test files
- **25 frames:** 5 test files
- **30 frames:** 5 test files

**Total:** 35 generated tests + 2 manual tests = 37 test files

---

## **Output Files**

### **results/all_results.csv**
Contains all experimental results in CSV format:
```
Algorithm,Frames,PageFaults,HitRate,TestFile
FIFO,10,76,24.00,test_cases/test_10frames_1.txt
Optimal,10,58,42.00,test_cases/test_10frames_1.txt
...
```

### **results/summary_statistics.csv**
Contains averages and standard deviations (generated in Google Colab analysis):
```
Algorithm,Frames,PageFaults_Mean,PageFaults_Std,HitRate_Mean,HitRate_Std
FIFO,3,79.83,34.75,9.17,7.99
...
```

---

## **Data Analysis (Optional)**

We performed data analysis using Google Colab. To replicate:

1. Upload `results/all_results.csv` to Google Drive
2. Open Google Colab
3. Mount your drive and load the CSV
4. Use Python/Pandas to calculate statistics
5. Generate graphs using Matplotlib

The analysis code and graphs are included in our project report.

---

## **Expected Results**

Based on our experiments:
- **Optimal algorithm** performs best (fewest page faults)
- **FIFO, LRU, LFU, MFU** perform similarly
- Page faults **decrease** as frame count **increases**
- At 3 frames: ~80-90 page faults (high)
- At 30 frames: ~44-52 page faults (low)

---

## **Troubleshooting**

### **Compilation Errors**
If you get compilation errors:
```bash
# Check g++ version (should be 7.0+)
g++ --version

# Ensure C++11 support
g++ -std=c++11 -Wall -Wextra -c src/main.cpp
```

### **Permission Denied for Scripts**
```bash
chmod +x run_all_tests.sh
chmod +x test_cases/generate_tests.py
```

### **Empty Results File**
If `all_results.csv` is empty:
- Make sure you're not recreating the file in main.cpp
- The script `run_all_tests.sh` handles file creation

---

## **Quick Test Commands**

```bash
# Clean and compile
make clean && make

# Test with small frames (high page faults)
./page_replacement test_cases/test_3frames_1.txt

# Test with large frames (low page faults)
./page_replacement test_cases/test_30frames_1.txt

# Run complete experiment
./run_all_tests.sh

# Check results
wc -l results/all_results.csv  # Should show 181 lines
head -20 results/all_results.csv  # View first 20 results
```



