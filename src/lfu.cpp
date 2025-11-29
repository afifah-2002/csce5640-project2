#include "page_replacement.h"
#include <iostream>
#include <climits>

using namespace std;

class LFU : public PageReplacement {
private:
    vector<int> frequency;  // Track frequency count for each frame

public:
    LFU(int numFrames) : PageReplacement(numFrames, "LFU") {
        frequency.resize(numFrames, 0);
    }
    
    int replacePage(int pageNumber, int currentIndex) override {
        int emptyFrame = findEmptyFrame();
        
        if (emptyFrame != -1) {
            frames[emptyFrame] = pageNumber;
            frequency[emptyFrame] = 1;
            return emptyFrame;
        }
        
        // No empty frame - find least frequently used page
        int lfuIndex = 0;
        int minFreq = frequency[0];
        
        for (int i = 1; i < numberOfFrames; i++) {
            if (frequency[i] < minFreq) {
                minFreq = frequency[i];
                lfuIndex = i;
            }
        }
        
        // Replace the LFU page
        frames[lfuIndex] = pageNumber;
        frequency[lfuIndex] = 1;
        
        return lfuIndex;
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