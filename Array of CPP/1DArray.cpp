#include <iostream>

using namespace std;

int main() {
    // Array (index 0..4)
    string animals[5] = { "Cats", "Dogs", 
        "Rabbits", "Gerbils", "Hamsters" };

    for (int i = 0; i < 5; ++i) {
        // animals[i] buat panggil array
        cout << "Index " << i << ": " << animals[i] << "\n"; 
    }

    return 0;
}