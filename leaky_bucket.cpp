/*Step - 1 :
Initialize buffer size and leak rate.
Step - 2 :
At clock tick, Initialize n as the leak rate.
Step - 3 :
If the n is greater than the size of the packet at front of the queue, send the packet into the network.
Step - 4 :
Decrement n by the size of the packet.
Step - 5 :
Repeat Step 3 and Step 4 until n is less than the size of the packet at the front of the queue or the bucket is empty. No other packet can be transmitted till the next clock tick.
Step - 6 :
Go to Step 2.*/


#include <iostream>
#include <queue>
#include <chrono>
#include <thread>

using namespace std;

class Packet {
    int id, size;

public:
    Packet(int id, int size) {
        this->id = id;
        this->size = size;
    }

    int getSize() {
        return this->size;
    }

    int getId() {
        return this->id;
    }
};

class LeakyBucket {
    int leakRate, bufferSizeLimit, currBufferSize;
    queue<Packet> buffer;

public:
    LeakyBucket(int leakRate, int size) {
        this->leakRate = leakRate;
        this->bufferSizeLimit = size;
        this->currBufferSize = 0;
    }

    void addPacket(Packet newPacket) {
        if (currBufferSize + newPacket.getSize() > bufferSizeLimit) {
            cout << "Bucket is full. Packet rejected." << endl;
            return;
        }

        buffer.push(newPacket);
        currBufferSize += newPacket.getSize();
        cout << "Packet with id = " << newPacket.getId() << " added to bucket." << endl;
    }

    void transmit() {
        if (buffer.size() == 0) {
            cout << "No packets in the bucket." << endl;
            return;
        }

        int n = leakRate;
        while (buffer.empty() == 0) {
            Packet topPacket = buffer.front();
            int topPacketSize = topPacket.getSize();

            if (topPacketSize > n)
                break;

            n = n - topPacketSize;
            currBufferSize -= topPacketSize;
            buffer.pop();
            cout << "Packet with id = " << topPacket.getId() << " transmitted." << endl;
        }
    }
};

int main() {
    int leakRate, bufferSize;
    cout << "Enter the leak rate: ";
    cin >> leakRate;
    cout << "Enter the buffer size: ";
    cin >> bufferSize;

    LeakyBucket* bucket = new LeakyBucket(leakRate, bufferSize);

    int packetCount;
    cout << "Enter the number of packets to add: ";
    cin >> packetCount;

    for (int i = 0; i < packetCount; i++) {
        int packetId, packetSize;
        cout << "Enter packet ID: ";
        cin >> packetId;
        cout << "Enter packet size: ";
        cin >> packetSize;
        bucket->addPacket(Packet(packetId, packetSize));
    }

    while (true) {
        bucket->transmit();
        cout << "Waiting for next tick." << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    delete bucket;
    return 0;
}
