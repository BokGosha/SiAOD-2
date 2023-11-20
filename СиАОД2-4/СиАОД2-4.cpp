#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <sstream>

using namespace std;

string linearSearch(string& text, string pattern) {
    int c = 0;

    for (int i = 0; i < text.length(); i++) {
        int j;

        for (j = 0; j < pattern.length(); j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }

        if (j == pattern.length()) {
            c++;
            text.erase(i, j);
        }
        else {
            i += j;
        }
    }

    if (c == 0) {
        return "-";
    }
    else {
        return text;
    }
}

string findLongestPalindrome(string s) {
    string newString = "^#";

    for (char c : s) {
        newString += c;
        newString += "#";
    }
    newString += "$";

    int n = newString.size();
    vector<int> lps(n, 0);
    int center = 0, right = 0;
    int maxCenter = 0, maxLength = 0;

    for (int i = 1; i < n - 1; i++) {
        int mirror = 2 * center - i;

        if (i < right) {
            lps[i] = min(right - i, lps[mirror]);
        }

        while (newString[i + 1 + lps[i]] == newString[i - 1 - lps[i]]) {
            lps[i]++;
        }

        if (i + lps[i] > right) {
            center = i;
            right = i + lps[i];
        }

        if (lps[i] > maxLength) {
            maxLength = lps[i];
            maxCenter = i;
        }
    }

    int start = (maxCenter - maxLength) / 2;

    return s.substr(start, maxLength);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string s, m;
    int choice;

    while (true) {
        cout << "0. Удалить в строке слова, равные заданному;" << endl;
        cout << "1. Найти максимальной длины полиндром в строке;" << endl;
        cout << "2. Выход." << endl;

        cin >> choice;

        switch (choice) {
        case 0:
            cin.ignore();
            cout << "Введите строку: ";
            getline(cin, s);

            cout << "Введите образец: ";
            cin >> m;

            if (linearSearch(s, m) == "-") {
                cout << "Нет слов, равных данному" << endl;
            }
            else {
                cout << "Новая строка: " << linearSearch(s, m) << endl;
            }
            break;
        case 1:
            cout << "Введите строку: ";
            cin >> s;

            cout << "Палиндром максимальной длины: " << findLongestPalindrome(s) << endl;
            break;
        case 2:
            exit(1);
        default:
            cout << "Такой команды нет" << endl;
        }
    }

    return 0;
}