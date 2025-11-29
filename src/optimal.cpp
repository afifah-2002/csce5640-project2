#include "page_replacement.h"
#include <iostream>
#include <climits>

using namespace std;

class Optimal : public PageReplacement {
public:
    Optimal(int numFrames) : PageReplacement(numFrames, "Optimal") {
    }
    
    // Find when this page will be used next (return -1 if never used again)
    int findNextUse(int pageNumber, int startIndex) {
        for (size_t i = startIndex; i < referenceString.size(); i++) {
            if (referenceString[i] == pageNumber) {
                return i;
            }
        }
        return -1;  // Never used again
    }
    
    int replacePage(int pageNumber, int currentIndex) override {
        int emptyFrame = findEmptyFrame();
        
        if (emptyFrame != -1) {
            frames[emptyFrame] = pageNumber;
            return emptyFrame;
        }
        
        // No empty frame - find page to replace using optimal strategy
        int farthestUse = -1;
        int frameToReplace = 0;
        
        for (int i = 0; i < numberOfFrames; i++) {
            int nextUse = findNextUse(frames[i], currentIndex + 1);
            
            if (nextUse == -1) {
                // This page is never used again - replace it!
                frameToReplace = i;
                break;
            }
            
            if (nextUse > farthestUse) {
                farthestUse = nextUse;
                frameToReplace = i;
            }
        }
        
        frames[frameToReplace] = pageNumber;
        return frameToReplace;
    }
};