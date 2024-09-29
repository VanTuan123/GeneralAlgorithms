/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
typedef unsigned char uint8;
typedef unsigned short uint16;
uint8 getLeftMask(uint8 numOfBit) {
    uint8 result = 0xFF;
    result = result >> (8-numOfBit);
    result = result << (8-numOfBit);
    return result;
}

uint8 getRightMask(uint8 numOfBit) {
    uint8 result = 0xFF;
    result = result << (8-numOfBit);
    result = result >> (8-numOfBit);
    return result;
}

void setValueToArray(uint8* BufPtr, uint8* ValuePtr, uint16 startBit, uint16 bitLength) {
    uint8 tempBuf[50];
    uint8 startByte = startBit / 8;
    uint8 startOffsetBit = startBit % 8;
    uint8 endOffsetBit = (bitLength + startOffsetBit) % 8;
    uint8 byteLength;
    uint8 loopIdx;
    uint8 tempMask = 0;
    uint8 tempValue;
    for (loopIdx= 0; loopIdx < 50; loopIdx++) {
        tempBuf[loopIdx] = 0;
    }
    byteLength = (startOffsetBit + bitLength) / 8;
    if (((startOffsetBit + bitLength) % 8) != 0) {
        byteLength++;
    }
    loopIdx = 0;
    while (loopIdx < byteLength) {
        if (loopIdx == 0) {
            tempBuf[loopIdx] = ValuePtr[loopIdx] >> startOffsetBit;
        } else if ( loopIdx != (byteLength - 1)) {
            tempBuf[loopIdx] = (ValuePtr[loopIdx - 1] << (8-startOffsetBit)) | (ValuePtr[loopIdx]>>startOffsetBit); 
        } else {
            tempValue = bitLength % 8;
            if (tempValue == 0) {
                tempValue = 8;
            }
            if ((startOffsetBit + tempValue) > 8) {
                tempBuf[loopIdx] = ValuePtr[loopIdx-1] << (8 - startOffsetBit);
            } else {
                if (loopIdx > 0) {
                    tempBuf[loopIdx] = (ValuePtr[loopIdx - 1] << (8-startOffsetBit)) | (ValuePtr[loopIdx] >> startOffsetBit); 
                } else {
                    tempBuf[loopIdx] = (ValuePtr[loopIdx] >> startOffsetBit); 
                }
                
            }
        }
        loopIdx++;
    }
    loopIdx = 0;
    while (loopIdx < byteLength) {
        tempMask = 0xFF;
        if (loopIdx == 0) {
            tempMask &= getRightMask(8 - startOffsetBit);
        } 
        if (loopIdx == (byteLength - 1)) {
            tempMask &= getLeftMask(endOffsetBit);
        } 
        
        BufPtr[loopIdx + startByte] &= ~tempMask;
        
        BufPtr[loopIdx + startByte] |= tempBuf[loopIdx];
        loopIdx++;
    }
}
int main()
{
    uint8 data[] = {0b10100110, 0b10110011,0b00100011};
    uint8 value[] =   {0b11010110, 0b11000101};
    
    setValueToArray(data, value, 3, 16);
    for (uint8 i = 0; i < 3; i++) {
        printf("%u\n", data[i]);
    }
    return 0;
}
