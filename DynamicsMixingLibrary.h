#ifndef DYNAMICS_MIXING_LIBRARY
#define DYNAMICS_MIXING_LIBRARY
#include <Arduino.h>

bool setSigns(bool &a, bool &b, uint8_t &type);

bool simpleMix(uint8_t &inA, 
               uint8_t &inB, 
               uint8_t &type, 
               uint8_t zeroPoint1 = 150,  //defaults to 1.5ms
               uint8_t zeroPoint2 = 150); //defaults to 1.5ms
      
bool maxMix(uint8_t &inA, 
            uint8_t &inB, 
            uint8_t &type, 
            uint8_t zeroPoint1 = 150,  //defaults to 1.5ms
            uint8_t zeroPoint2 = 150); //defaults to 1.5ms

bool fullThrottleMix(uint8_t &thrIn, 
                     uint8_t &inB, 
                     uint8_t &type, 
                     uint8_t zeroPointThr = 150,  //defaults to 1.5ms
                     uint8_t zeroPoint2 = 150); //defaults to 1.5ms

bool dualScrewMix(uint8_t &thrLIn, 
                  uint8_t &thrRIn, 
                  uint8_t &rudIn, 
                  uint8_t &type, 
                  uint8_t zeroPointThrL = 150,  //defaults to 1.5ms
                  uint8_t zeroPointThrR = 150,  //defaults to 1.5ms
                  uint8_t zeroPointRud = 150); //defaults to 1.5ms

#endif // DYNAMICS_MIXING_LIBRARY