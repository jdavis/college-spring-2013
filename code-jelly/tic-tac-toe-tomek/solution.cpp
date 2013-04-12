#include <cstdio>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char *argv[]) {
    int nCases, i;
    ifstream file;
    string line;

    file.open(argv[1]);

    // Read the number of cases defined
    getline(file, line);
    nCases = atoi(line.c_str());

    for(i = 0; i < nCases; i++) {
        cout << "Case #" << i + 1 << ": ";
    }

    // Cleanup
    file.close();

    return 0;
}
