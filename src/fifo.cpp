#include "page_replacement.h"
#include <iostream>

using namespace std;

class FIFO : public PageReplacement {
private:
    int nextFrameToReplace;

public:
    FIFO(int numFrames) : PageReplacement(numFrames, "FIFO") {
        nextFrameToReplace = 0;
    }
    
    int replacePage(int pageNumber) override {
        // Find empty frame first
        int emptyFrame = findEmptyFrame();
        
        if (emptyFrame != -1) {
            // Empty frame available, use it
            frames[emptyFrame] = pageNumber;
            return emptyFrame;
        }
        
        // No empty frame, replace using FIFO (circular)
        int frameToReplace = nextFrameToReplace;
        frames[frameToReplace] = pageNumber;
        
        // Move to next frame for next replacement
        nextFrameToReplace = (nextFrameToReplace + 1) % numberOfFrames;
        
        return frameToReplace;
    }
};