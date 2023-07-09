#include "DynamicsMixingLibrary.h"

// note - all these assume 0 is zero, -100 is +1 and 100 is -1. Please remap inputs accordingly.

// sets directions of each channel from midpoint based on arbitrary type
// this allows servo reversing in the mixing function
// choose correct type based on needed functionallity
bool setSigns(int8_t &a, int8_t &b, uint8_t type)
{
    switch (type){
        case 0: 
            a = 1; b = 1; break;
        case 1:
            a = 1; b = -1; break;
        case 3:
            a = -1; b = 1; break;
        case 4:
            a = -1; b = -1; break;
        default:
            a = 0; b = 0; // zero motion should be returned if incorrect type set
            return false;
    }
    return true;
}


bool averageMix(int8_t &in1, 
                int8_t &in2, 
                uint8_t type)
{
    int8_t orig1 = in1;
    int8_t sign1, sign2; setSigns(sign1, sign2, type);      // set directions of outputs using these variables: -1 & 1 are only values
    in1 = ((sign1 * orig1 + sign2 * in2)/2);
    in2 = ((-sign1 * orig1 + -sign2 * in2)/2);
    return true;
}

bool maxMix(int8_t &in1, 
            int8_t &in2, 
            uint8_t type)
{
    int8_t orig1 = in1;
    int8_t sign1, sign2;
    setSigns(sign1, sign2, type);                           // set directions of outputs using these variables: -1 & 1 are only values
    in1 = min(sign1 * orig1 + sign2 * in2, 100);
    in2 = min(-sign1 * orig1 + -sign2 * in2, 100);
    return true;
}

bool fullThrottleMix(int8_t &thrIn, 
                     int8_t &in2, 
                     uint8_t type)
{
    int8_t origThr = thrIn;
    int8_t orig2 = in2;
    int8_t sign1, sign2; setSigns(sign1, sign2, type);      // set directions of outputs using these variables: -1 & 1 are only values
    thrIn = min(sign1 * origThr + sign2 * in2/2, 100);
    in2 = min(-sign1 * origThr + -sign2 * in2/2, 100);
    return false;
}

bool dualScrewMix(int8_t &thrLIn, // Assumed this is the single input for throttle
                  int8_t &thrRIn, // Only an output
                  int8_t &rudIn, 
                  uint8_t type,
                  bool flipDelta)
{
    float gamma = 1.2;                                                          // exponent for throttle difference calculation
    int8_t signThr, signRud; setSigns(signThr, signRud, type);                  // set directions of outputs using these variables: -1 & 1 are only values
    int8_t origRud = rudIn; int8_t origThrL = thrLIn;                           // saves origional values for calculations after overwrite
    int8_t deltaThrot = max(pow(max(origRud - .5 * origThrL, 0), gamma) - 1, 0);// calculation of individual throttle change
    deltaThrot *= flipDelta ? -1 : 1;                                           // flips throttle delta if flagged
    thrRIn = origThrL * signThr - deltaThrot;                                   // write new throttle percentage
    thrLIn = origThrL * signThr + deltaThrot;
    rudIn = min(origRud * (2 - origThrL), 1) * signRud;                         // write new rudder percentage
    return true;
}
