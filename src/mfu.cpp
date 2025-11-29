#include "page_replacement.h"
#include <iostream>

using namespace std;

class MFU : public PageReplacement {
private:
    vector<int> frequency;  // Track frequency count for each frame

public:
    MFU(int numFrames) : PageReplacement(numFrames, "MFU") {
        frequency.resize(numFrames, 0);
    }
    
    int replacePage(int pageNumber, int currentIndex) override {
        int emptyFrame = findEmptyFrame();
        
        if (emptyFrame != -1) {
            frames[emptyFrame] = pageNumber;
            frequency[emptyFrame] = 1;
            return emptyFrame;
        }
        
        // No empty frame - find MOST frequently used page
        int mfuIndex = 0;
        int maxFreq = frequency[0];
        
        for (int i = 1; i < numberOfFrames; i++) {
            if (frequency[i] > maxFreq) {
                maxFreq = frequency[i];
                mfuIndex = i;
            }
        }
        
        // Replace the MFU page
        frames[mfuIndex] = pageNumber;
        frequency[mfuIndex] = 1;
        
        return mfuIndex;
    }
    
    void onPageHit(int pageNumber, int currentIndex) override {
        // Increase frequency for this page
        for (int i = 0; i < numberOfFrames; i++) {
            if (frames[i] == pageNumber) {
                frequency[i]++;
                break;
            }
        }
    }
};