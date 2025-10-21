#include <iostream>

using namespace std;

int main() {
    int j = 1;
    cout << "Result: " << endl;
    do {
        cout << "*" << ' ';
        ++j;
    } while (j <= 3);
    cout << '\n';

    return 0;
}