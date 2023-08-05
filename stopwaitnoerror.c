#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define FRAME_COUNT 6
#define TIMEOUT 2

typedef struct {
    int frameNumber;
    bool isAckReceived;
} Frame;

void simulateTransmission(Frame frames[], int frameCount) {
    int i;
    bool isTransmissionSuccessful;

    for (i = 0; i < frameCount; i++) {
        isTransmissionSuccessful = false;
        
        while (!isTransmissionSuccessful) {
            printf("\nSending Frame %d", frames[i].frameNumber);
            printf("\nWaiting for ACK (Press 'y' to simulate ACK received)...");
            
            char userInput;
            scanf(" %c", &userInput);
            
            if (userInput == 'y' || userInput == 'Y') {
                // ACK received
                printf("\nACK received for Frame %d\n", frames[i].frameNumber);
                frames[i].isAckReceived = true;
                isTransmissionSuccessful = true;
            } else {
                // ACK not received, retransmit the frame
                printf("\nACK not received for Frame %d, retransmitting...\n", frames[i].frameNumber);
            }
        }
    }
}

int main() {
    srand(time(NULL));
    
    // Create frames
    Frame frames[FRAME_COUNT];
    int i;

    for (i = 0; i < FRAME_COUNT; i++) {
        frames[i].frameNumber = i + 1;
        frames[i].isAckReceived = false;
    }

    // Transmit frames
    simulateTransmission(frames, FRAME_COUNT);
    
    printf("\nAll frames transmitted successfully!\n");
    return 0;
}
