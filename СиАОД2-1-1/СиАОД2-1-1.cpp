#include <iostream>
#include <Windows.h>
#include <bitset>

using namespace std;

int Bit_5(unsigned char x) {
    unsigned char maska_x = 1;

    x = x & (~(maska_x << 4));

    return x;
}

int Bit_7(unsigned char x) {
    unsigned char maska_x = 1;

    x = x | (maska_x << 6);

    return x;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unsigned char z = 255;      // 11111111
    cout << Bit_5(z) << endl;   // 11101111 = 239

    unsigned char y = 191;      // 10111111
    cout << Bit_7(y) << endl;   // 11111111 = 255

    unsigned int x = 25;
    const int n = sizeof(int) * 8;
    unsigned maska = (1 << n - 1);

    cout << "Начальный вид маски: " << bitset<n>(maska) << endl;
    cout << "Результат: ";

    for (int i = 1; i <= n; i++) {
        cout << ((x & maska) >> (n - i));
        maska = maska >> 1;
    }
    cout << endl;

    return 0;
}