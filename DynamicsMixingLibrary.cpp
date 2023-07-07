#include "DynamicsMixingLibrary.h"

#define POS_DML true
#define NEG_DML false

bool simpleMix(uint8_t &inA, 
               uint8_t &inB, 
               uint8_t type, 
               uint8_t zeroPoint1, 
               uint8_t zeroPoint2)
{
    int16_t orig1 = inA - zeroPoint1;
    int16_t orig2 = inB - zeroPoint2;
    bool sign1, sign2;
    switch (type){
        case 0: 
            sign1 = POS_DML;
            sign2 = POS_DML;
            break;
        case 1:
            sign1 = POS_DML;
            sign2 = NEG_DML;
            break;
        case 3:
            sign1 = NEG_DML;
            sign2 = POS_DML;
            break;
        case 4:
            sign1 = NEG_DML;
            sign2 = NEG_DML;
            break;
        default:
            return false;
    }
    inA = zeroPoint1 + (((sign1 ? orig1 : -orig1) + (sign2 ? orig2 : -orig2))/2);
    inB = zeroPoint1 + (((!sign1 ? orig1 : -orig1) + (!sign2 ? orig2 : -orig2))/2);
    return true;
}

bool fullThrottleMix(uint8_t &thrIn, 
                     uint8_t &inB, 
                     uint8_t type, 
                     uint8_t zeroPointThr, 
                     uint8_t zeroPoint2)
{
    return false;
}
