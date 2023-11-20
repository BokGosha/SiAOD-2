#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

vector<int> sortNumbers(vector<int> numbers) {
    unsigned char bitArray[8] = { 0 };
    vector<int> sortedNumbers;

    for (int num : numbers) {
        bitArray[num / 8] |= (1 << (num % 8));
    }

    for (int i = 0; i < 64; i++) {
        if (bitArray[i / 8] & (1 << (i % 8))) {
            sortedNumbers.push_back(i);
        }
    }

    return sortedNumbers;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<int> numbers;
    int num;
    int count;

    cin >> count;

    for (int i = 0; i < count; i++) {
        cout << "Введите число (от 0 до 63): ";

        cin >> num;
        numbers.push_back(num);
    }

    vector<int> sortedNumbers = sortNumbers(numbers);

    cout << "Отсортированный вектор чисел:";

    for (int num : sortedNumbers) {
        cout << " " << num;
    }
    cout << endl;

    return 0;
}