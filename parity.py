def calculate_parity(frame, parity):
    count = frame.count('1')
    if parity == 'even':
        return count % 2 == 0
    elif parity == 'odd':
        return count % 2 != 0

def detect_errors(data_size, num_frames, parity):
    frames = []
    errors = []

    for i in range(num_frames):
        frame = input("Enter frame {}: ".format(i + 1))
        if len(frame) != 8:
            print("Invalid frame size. ( Enter 8 bits number only per frame).")
            return
        frames.append(frame)

    for i in range(num_frames):
        if not calculate_parity(frames[i], parity):
            errors.append(i + 1)

    if len(errors) == 0:
        print("No errors detected for {} parity.".format(parity))
    else:
        print("Errors detected for {} parity in frames: {}".format(parity, ", ".join(map(str, errors))))

# Main program
print("Debanjana Chanda-21bce0019")
data_size = int(input("Enter total size of data: "))
num_frames = int(input("Enter number of frames: "))
parity = input("Enter parity (even/odd): ")
detect_errors(data_size, num_frames, parity)
