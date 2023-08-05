#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    int no_frame, window_size;
    srand(time(NULL));

    cout << "Enter the number of Frames: ";
    cin >> no_frame;

    cout << "Enter the Window Size: ";
    cin >> window_size;

    int i = 1;
    int flg = 1;

    while (i <= no_frame)
    {
        int x = 0;

        for (int j = i; j < i + window_size && j <= no_frame; j++)
        {
            cout << "Sent Frame " << j << endl;
        }

        for (int j = i; j < i + window_size && j <= no_frame; j++)
        {
            char userChoice;
            cout << "Did Frame " << j << " get lost during transmission? (y/n): ";
            cin >> userChoice;

            if (userChoice == 'y' || userChoice == 'Y')
            {
                cout << "Frame " << j << " Lost" << endl;
                cout << "Retransmitting Window" << endl;
                flg = !flg;
                break;
            }
            else
            {
                cout << "Acknowledgment for Frame " << j << endl;
                x++;
            }
        }

        cout << endl;
        i += x; // Sliding the window
    }

    return 0;
}
