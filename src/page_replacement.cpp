#include "page_replacement.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Constructor
PageReplacement::PageReplacement(int numFrames, string algName) {
    numberOfFrames = numFrames;
    algorithmName = algName;
    pageFaults = 0;
    
    // Initialize frames with -1 (meaning empty)
    frames.resize(numberOfFrames, -1);
}

// Destructor
PageReplacement::~PageReplacement() {
    // Nothing special needed here
}

// Set the reference string
void PageReplacement::setReferenceString(vector<int> refString) {
    referenceString = refString;
}

// Check if page is already in frames
bool PageReplacement::isPageInFrames(int pageNumber) {
    for (int i = 0; i < numberOfFrames; i++) {
        if (frames[i] == pageNumber) {
            return true;
        }
    }
    return false;
}

// Find an empty frame (returns -1 if none found)
int PageReplacement::findEmptyFrame() {
    for (int i = 0; i < numberOfFrames; i++) {
        if (frames[i] == -1) {
            return i;
        }
    }
    return -1;
}

// Get page faults count
int PageReplacement::getPageFaults() {
    return pageFaults;
}

// Display results to console
void PageReplacement::displayResults() {
    cout << "\nAlgorithm: " << algorithmName << endl;
    cout << "Page Faults: " << pageFaults << endl;
    
    double hitRate = ((double)(referenceString.size() - pageFaults) / referenceString.size()) * 100;
    cout << "Hit Rate: " << fixed << setprecision(2) << hitRate << "%" << endl;
}

// Simulate the page replacement algorithm
void PageReplacement::simulate() {
    // Reset page faults and frames
    pageFaults = 0;
    frames.clear();
    frames.resize(numberOfFrames, -1);
    
    // Process each page in reference string
    for (size_t i = 0; i < referenceString.size(); i++) {
        int currentPage = referenceString[i];
        
        // Check if page is already in frames (page hit)
        if (isPageInFrames(currentPage)) {
            // Page hit - no fault
            continue;
        }
        
        // Page fault occurred
        pageFaults++;
        
        // Call the specific algorithm's replace function
        replacePage(currentPage);
    }
}