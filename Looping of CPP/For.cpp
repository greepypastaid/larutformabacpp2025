#include <iostream>

using namespace std;

int main() {
    for (int i = 1; i <= 5; i++) { // Looping satu
        for(int j = 1; j <= i; j++) { // Looping 2
            cout << "Hidup Jokowi! ";
        } // looping 2
        cout << endl;
    } // Stop looping 1
    return 0;
}