#include <stdio.h>
#include <string.h>
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef struct {
    uint8 queueSize;
    uint8* dataPtr;
} queueType;

void pushQueue(queueType* queue, uint8* element, uint8 elementSize) {
    memcpy(&queue->dataPtr[queue->queueSize], element, elementSize);
    queue->queueSize += elementSize;
}

void popQueue(queueType* queue, uint8* element, uint8 elementSize) {
    queue->queueSize -= elementSize;
    memcpy(element, &queue->dataPtr[queue->queueSize], elementSize);
}
int main()
{
    queueType ethsmQueue;
    uint8 ethsmQueueData[20];
    uint8 elementPush[3] = {200,179,158};
    uint8 elementPop;
    
    ethsmQueue.dataPtr = ethsmQueueData;
    ethsmQueue.queueSize = 0;
    
    pushQueue(&ethsmQueue, &elementPush[1], 2);
    for (uint8 i; i < 2; i++) {
        printf("%u\n", ethsmQueueData[i]);
    }
    popQueue(&ethsmQueue, &elementPop, 1);
    printf("%u\n", elementPop);
    popQueue(&ethsmQueue, &elementPop, 1);
    printf("%u\n", elementPop);
    return 0;
}
