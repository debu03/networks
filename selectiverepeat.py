import time
import random

# Constants
LINK_BANDWIDTH = 10 * 10**6  # 10 Mbps (bits per second)
PROPAGATION_DELAY = 100 / 1000  # 100 milliseconds to seconds
SEGMENT_SIZE = 10000  # 10,000 bits per segment
WINDOW_SIZE = 4

def simulate_transmission():
    sender_window = list(range(1, 11))  # 10 segments to transmit
    receiver_window = []

    def simulate_transmit(segment):
        print(f"Transmitting segment {segment}...")
        time.sleep(SEGMENT_SIZE / LINK_BANDWIDTH)  # Simulate transmission time

    def simulate_propagation_delay():
        time.sleep(PROPAGATION_DELAY)

    while sender_window:
        # Transmit the segments in the sender window
        for segment in sender_window:
            if segment in [3, 7]:
                print(f"Segment {segment} lost!")
            else:
                simulate_transmit(segment)

        # Move the acknowledged segments from sender to receiver window
        for segment in sender_window[:WINDOW_SIZE]:
            simulate_propagation_delay()
            receiver_window.append(segment)
            print(f"Received ACK for segment {segment}")
        
        sender_window = sender_window[WINDOW_SIZE:]

    print("All segments transmitted successfully!")

if __name__ == "__main__":
    simulate_transmission()
