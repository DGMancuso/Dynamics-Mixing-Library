#ifndef DYNAMICS_MIXING_LIBRARY
#define DYNAMICS_MIXING_LIBRARY
#include <Arduino.h>

bool setSigns(int8_t &a, int8_t &b, uint8_t &type);

// averages the channels together
// 100 output only if both inputs are 100 (stick to corner)
// 50 output if one channel maxxed (stick full forward) 
bool averageMix(int8_t &in1, 
                int8_t &in2, 
                uint8_t &type); 
      
// doubles average mix gain
// 100 output on BOTH channels if one input maxxed (stick full forward) 
// 100 output on one channel if if both inputs are 50 (stick 50% to corner)
// Outside this 'diamond', signal saturates at 100 - lose 50% resolution
bool maxMix(int8_t &in1, 
            int8_t &in2, 
            uint8_t &type); 

// mix for maxMix in one stick direction and average mix in other direction 
bool fullThrottleMix(int8_t &thrIn, 
                     int8_t &in2, 
                     uint8_t &type); 

//arbitrarily tuned mix for control of twin screws with rudder
bool dualScrewMix(int8_t &thrLIn, 
                  int8_t &thrRIn, 
                  int8_t &rudIn, 
                  uint8_t &type, 
                  bool flipDelta = false); 

#endif // DYNAMICS_MIXING_LIBRARY