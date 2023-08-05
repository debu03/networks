#include <iostream>
#include <string>
using namespace std;

string addBin(string x, string y) {
    string res = "";
    int tmp = 0;
    int len_x = x.size() - 1;
    int len_y = y.size() - 1;

    while (len_x >= 0 || len_y >= 0 || tmp == 1) {
        if (len_x >= 0) {
            tmp += (x[len_x] - '0');
        }
        if (len_y >= 0) {
            tmp += (y[len_y] - '0');
        }
        res = char(tmp % 2 + '0') + res;
        tmp /= 2;
        len_x--;
        len_y--;
    }
    return res;
}

string onesComp(string a) {
    int size = a.length();
    for (int i = 0; i < size; i++) {
        if (a[i] == '1') {
            a[i] = '0';
        } else if (a[i] == '0') {
            a[i] = '1';
        }
    }
    return a;
}

string senderSide(string s, int b) {
    int n = s.length();
    if (n % b != 0) {
        int mlen = b - (n % b);
        for (int i = 0; i < mlen; i++) {
            s = '0' + s;
        }
    }

    string rslt = "";
    for (int i = 0; i < b; i++) {
        rslt += s[i];
    }

    for (int i = b; i < n; i += b) {
        string nxt_blk = "";
        for (int j = i; j < i + b; j++) {
            nxt_blk += s[j];
        }
        rslt = addBin(rslt, nxt_blk);

        if (nxt_blk.length() < rslt.length()) {
            rslt = addBin(rslt.substr(1, rslt.length()), "1");
        }
    }
    return onesComp(rslt);
}

string receiverSide(string s, int b, string chkSum) {
    string rslt = onesComp(senderSide(s, b));
    rslt = addBin(rslt, chkSum);
    return onesComp(rslt);
}

int main() {
    string s;
    cout << "Enter the data to be transmitted: ";
    cin >> s;

    cout << "Enter the number of sections: ";
    int n;
    cin >> n;
    int bs = s.length() / n;

    string chkSum = senderSide(s, bs);
    cout << "The checksum obtained is: " << chkSum << endl;

    string r;
    cout << "Enter the received string: ";
    cin >> r;

    string chk = receiverSide(r, bs, chkSum);
    int flag = 1;

    for (int i = 0; i < chk.length(); i++) {
        if (chk[i] == '1') {
            flag = 0;
            cout << "Error found!!!" << endl;
            break;
        }
    }

    if (flag) {
        cout << "No error found!" << endl;
    }
    return 0;
}
