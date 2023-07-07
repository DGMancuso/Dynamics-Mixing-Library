#include "DynamicsMixingLibrary.h"

#define POS_DML true
#define NEG_DML false

bool setSigns(bool &a, bool &b, uint8_t &type)
{
    switch (type){
        case 0: 
            a = POS_DML; b = POS_DML; break;
        case 1:
            a = POS_DML; b = NEG_DML; break;
        case 3:
            a = NEG_DML; b = POS_DML; break;
        case 4:
            a = NEG_DML; b = NEG_DML; break;
        default:
            return false;
    }
    return true;
}


bool simpleMix(uint8_t &inA, 
               uint8_t &inB, 
               uint8_t &type, 
               uint8_t zeroPoint1, 
               uint8_t zeroPoint2)
{
    int16_t orig1 = inA - zeroPoint1;
    int16_t orig2 = inB - zeroPoint2;
    bool sign1, sign2;
    setSigns(sign1, sign2, type);
    inA = zeroPoint1 + (((sign1 ? orig1 : -orig1) + (sign2 ? orig2 : -orig2))/2);
    inB = zeroPoint1 + (((!sign1 ? orig1 : -orig1) + (!sign2 ? orig2 : -orig2))/2);
    return true;
}

bool fullThrottleMix(uint8_t &thrIn, 
                     uint8_t &inB, 
                     uint8_t &type, 
                     uint8_t zeroPointThr, 
                     uint8_t zeroPoint2)
{
    return false;
}
