#include <cstdio>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

enum TileState {
    X,
    O,
    T,
    DOT,
};

enum GameState {
    XWINS,
    OWINS,
    DRAW,
};

//
// Declaration
//

class TicTacToe {
    public:
        void setArray(int i, string s);
        GameState checkState();
        string toString();

    private:
        GameState checkHorizontal(int h);
        GameState checkVertical(int v);
        TileState board[4][4];
        string original;
};

//
// Definition
//

void TicTacToe::setArray(int i, string s) {
    int j, c;
    TileState state;

    for(j = 0; j < 4; j++) {
        c = s[j];
        switch(c) {
            case '.':
                state = DOT;
                break;
            case 'O':
                state = O;
                break;
            case 'X':
                state = X;
                break;
            case 'T':
                state = T;
                break;
        }
    }

    original += s;
}

GameState TicTacToe::checkState() {
    int i;
    GameState state;

    for(i = 0; i < 4; i++) {
        state = checkHorizontal(i);
        if (state != DRAW) return state;

        state = checkVertical(i);
        if (state != DRAW) return state;
    }
}

string TicTacToe::toString() {
    return original;
}

GameState TicTacToe::checkHorizontal(int h) {
    int i;
    GameState result = DRAW;

    for(i = 0; i < 4; i++) {
        board[]
    }
}

GameState TicTacToe::checkVertical(int h) {

}

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
