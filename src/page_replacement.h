#ifndef PAGE_REPLACEMENT_H
#define PAGE_REPLACEMENT_H

#include <vector>
#include <string>
#include <fstream>

using namespace std;

class PageReplacement {
protected:
    int numberOfFrames;
    vector<int> frames;
    vector<int> referenceString;
    int pageFaults;
    string algorithmName;

public:
    // Constructor
    PageReplacement(int numFrames, string algName);

    // Virtual function for handling page hits (optional for algorithms to override)
    virtual void onPageHit(int pageNumber, int currentIndex) {
    // Default: do nothing
    }
    
    // Virtual destructor
    virtual ~PageReplacement();
    
    // Pure virtual function - each algorithm implements this
    virtual int replacePage(int pageNumber, int currentIndex) = 0;
    
    // Common functions
    void setReferenceString(vector<int> refString);
    void simulate();
    void displayResults();
    void saveResults(string filename, string testFile);
    int getPageFaults();
    
    // Helper functions
    bool isPageInFrames(int pageNumber);
    int findEmptyFrame();
};

#endif