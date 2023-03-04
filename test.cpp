#include<iostream>
#include<fstream>

using namespace std;

int main() {
    ofstream file("hello.txt", ios::app);

    char text[100] = "ебал вашу маму";

    file << text;

    file.close();

    return 0;
}
