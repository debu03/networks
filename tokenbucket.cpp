/*Initialize the Token Bucket with the token rate (tokenRate) and the maximum number of tokens it can hold (maxTokens). Set the current number of tokens (currTokens) to 0.

Add tokens to the bucket:

If currTokens is less than maxTokens, add a token to the bucket.
Increment currTokens by 1.
Process a packet:

Get the packet size as input.
If the packet size is less than or equal to currTokens, process the packet:
Decrement currTokens by the packet size.
If the packet size exceeds currTokens, drop the packet.
Repeat steps 2 and 3 indefinitely to simulate the continuous process of adding tokens and processing packets in the Token Bucket.*/


#include <iostream>
#include <queue>
#include <chrono>
#include <thread>
using namespace std;

class TokenBucket {
    int tokenRate, maxTokens, currTokens;
    queue<int> buffer;

public:
    TokenBucket(int tokenRate, int maxTokens) {
        this->tokenRate = tokenRate;
        this->maxTokens = maxTokens;
        this->currTokens = 0;
    }

    void addToken() {
        if (currTokens < maxTokens) {
            buffer.push(1);
            currTokens++;
            cout << "Token added to the bucket. Current token count: " << currTokens << endl;
        } else {
            cout << "Bucket is full. Token rejected." << endl;
        }
    }

    void processPacket(int packetSize) {
        if (packetSize <= currTokens) {
            currTokens -= packetSize;
            cout << "Packet of size " << packetSize << " processed. Remaining tokens: " << currTokens << endl;
        } else {
            cout << "Not enough tokens to process the packet of size " << packetSize << ". Packet dropped." << endl;
        }
    }
};

int main() {
    int tokenRate, maxTokens;
    cout << "Enter the token rate: ";
    cin >> tokenRate;
    cout << "Enter the maximum number of tokens in the bucket: ";
    cin >> maxTokens;

    TokenBucket bucket(tokenRate, maxTokens);

    while (true) {
        bucket.addToken();
        int packetSize;
        cout << "Enter the packet size (or 0 to exit): ";
        cin >> packetSize;

        if (packetSize == 0) {
            break;
        }

        bucket.processPacket(packetSize);
        cout << "Waiting for next packet..." << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    return 0;
}
