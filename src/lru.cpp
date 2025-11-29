#include "page_replacement.h"
#include <iostream>
#include <climits>

using namespace std;

class LRU : public PageReplacement {
private:
    vector<int> lastUsedTime;  // Track when each frame was last used

public:
    LRU(int numFrames) : PageReplacement(numFrames, "LRU") {
        lastUsedTime.resize(numFrames, -1);
    }
    
    int replacePage(int pageNumber, int currentIndex) override {
        int emptyFrame = findEmptyFrame();
        
        if (emptyFrame != -1) {
            frames[emptyFrame] = pageNumber;
            lastUsedTime[emptyFrame] = currentIndex;
            return emptyFrame;
        }
        
        // No empty frame - find least recently used page
        int lruIndex = 0;
        int oldestTime = lastUsedTime[0];
        
        for (int i = 1; i < numberOfFrames; i++) {
            if (lastUsedTime[i] < oldestTime) {
                oldestTime = lastUsedTime[i];
                lruIndex = i;
            }
        }
        
        // Replace the LRU page
        frames[lruIndex] = pageNumber;
        lastUsedTime[lruIndex] = currentIndex;
        
        return lruIndex;
    }

    void onPageHit(int pageNumber, int currentIndex) override {
    // Update the last used time for this page
    for (int i = 0; i < numberOfFrames; i++) {
        if (frames[i] == pageNumber) {
            lastUsedTime[i] = currentIndex;
            break;
        }
    }
}
};