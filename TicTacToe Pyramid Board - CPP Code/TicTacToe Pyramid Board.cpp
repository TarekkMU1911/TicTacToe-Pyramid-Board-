#include <iostream>
#include <cstdlib> // for rand() function
#include <ctime>   // for srand() function

using namespace std;

string PyramidBoard[3][5];

class Player {
public:
    string symp;
    string Name;

    void SetSymp(string symp) {
        if (symp == "X" || symp == "O" || symp == "x" || symp == "o") {
            this->symp = symp;
        }
        else {
            cin >> symp;
            SetSymp(symp);
        }
    }

    Player(string Name, string symp) {
        SetSymp(symp);
        this->Name = Name;
    }
};

bool ValidCell(int row, int col) {
    return (row >= 0 && row <= 2 && col >= 0 && col <= 4 && PyramidBoard[row][col] == "[ ]");
}

class RandomPlayer : public Player {
public:
    RandomPlayer(string symp) : Player("Computer Player", symp) {}
    void get_move(int& x, int& y) {
        do {
            x = (int)(rand() % 3);
            y = (int)(rand() % 5);
        } while (!ValidCell(x, y));

        PyramidBoard[x][y] = "[" + symp + "]";
    }
};

void InitBoard() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if ((i == 0 && j == 0) || (i == 0 && j == 1) ||
                (i == 1 && j == 0) || (i == 0 && j == 3) || (i == 0 && j == 4) || (i == 1 && j == 4)) {
                PyramidBoard[i][j] = '-';
            }
            else
                PyramidBoard[i][j] = "[ ]";
        }
    }
}

bool IsWinner(string player) {
    if ((PyramidBoard[1][1] == PyramidBoard[1][2] && PyramidBoard[1][2] == PyramidBoard[1][3] && PyramidBoard[1][3] == "[" + player + "]") ||
        (PyramidBoard[2][0] == PyramidBoard[2][1] && PyramidBoard[2][1] == PyramidBoard[2][2] && PyramidBoard[2][2] == "[" + player + "]") ||
        (PyramidBoard[2][2] == PyramidBoard[2][3] && PyramidBoard[2][3] == PyramidBoard[2][4] && PyramidBoard[2][4] == "[" + player + "]") ||
        (PyramidBoard[2][1] == PyramidBoard[2][2] && PyramidBoard[2][2] == PyramidBoard[2][3] && PyramidBoard[2][3] == "[" + player + "]")) {
        return true;
    }

    if (PyramidBoard[0][2] == PyramidBoard[1][2] && PyramidBoard[1][2] == "[" + player + "]" && PyramidBoard[2][2] == "[" + player + "]") {
        return true;
    }

    if ((PyramidBoard[0][2] == "[" + player + "]" && PyramidBoard[1][3] == "[" + player + "]" && PyramidBoard[2][4] == "[" + player + "]") ||
        (PyramidBoard[0][2] == "[" + player + "]" && PyramidBoard[1][1] == "[" + player + "]" && PyramidBoard[2][0] == "[" + player + "]")) {
        return true;
    }

    return false;
}

bool IsDraw() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (PyramidBoard[i][j] == "[ ]") {
                return false;
            }
        }
    }
    return true;
}

void PrintBoard() {
    cout << "    ";
    for (int i = 0; i < 3; ++i) {
        if (i == 1)
            cout << "  ";
        for (int j = 0; j < 5; ++j) {
            cout << PyramidBoard[i][j];
        }

        cout << endl;
    }
    cout << "----------------\n";
}

void Info() {
    cout << "Hello in our game , you have to know the board first :\n ";
    cout << "The board contains cells [ x , y ] , every cell has row number (x) and column number (y)\n";
    cout << "so this is the board and each cell's information :\n";
    cout << "                   -- [ 1 , 3 ] -- \n";
    cout << "          - [ 2 , 2 ] [ 2 , 3 ] [ 2 , 4 ] - \n";
    cout << "  [ 3 , 1 ] [ 3 , 2 ] [ 3 , 3 ] [ 3 , 4 ] [ 3 , 5 ] \n";
    cout << "-----------------------------------------------------\n";
    cout << "You have to enter the row's number first , then the column's number . \n";
    cout << "                    Have a good game bro :)                         \n";
}

void PutInCell(Player& player) {
    int row, col;
    do {
        cout << player.Name << "'s turn. Enter row and column: ";
        cin >> row >> col;
    } while (!ValidCell(row - 1, col - 1));

    PyramidBoard[row - 1][col - 1] = "[" + player.symp + "]";
}

void PutInCell(RandomPlayer& player) {
    int x, y;
    player.get_move(x, y);
}

void GameMaster(Player& p1, Player& p2) {
    bool game_over = false;
    int moves = 0;

    while (!game_over) {
        PrintBoard();

        if (moves % 2 == 0) {
            PutInCell(p1);
            game_over = IsWinner(p1.symp) || IsDraw();

        }
        else {
            PutInCell(p2);
            game_over = IsWinner(p2.symp) || IsDraw();
        }

        moves++;
    }

    PrintBoard();
}

void GameMaster(Player& p1, RandomPlayer& p2) {
    bool game_over = false;
    int moves = 0;

    while (!game_over) {
        PrintBoard();

        if (moves % 2 == 0) {
            PutInCell(p1);
            game_over = IsWinner(p1.symp) || IsDraw();

        }
        else {
            PutInCell(p2);
            game_over = IsWinner(p2.symp) || IsDraw();
        }

        moves++;
    }

    PrintBoard();
}

void PrintWinner(Player& p1, Player& p2) {
    if (IsWinner(p1.symp) == true) {
        cout << "The winner is the player 1 [ " << p1.Name << " ] .";
    }
    else if (IsWinner(p2.symp) == true) {
        cout << "The winner is the player 2 [ " << p2.Name << " ] .";
    }
}

void PrintWinner(Player& p1, RandomPlayer& p2) {
    if (IsWinner(p1.symp) == true) {
        cout << "The winner is the player 1 [ " << p1.Name << " ] .";
    }
    else if (IsWinner(p2.symp) == true) {
        cout << "The winner is the player 2 [ " << p2.Name << " ] .";
    }
}

void With2Players() {
    Info();

    InitBoard();

    string name1, name2;
    string symp1, symp2;

    cout << "Player 1: Enter Your Name and character (X or O): ";
    cin >> name1 >> symp1;
    Player p1(name1, symp1);

    cout << "Player 2: Enter Your Name ";
    cin >> name2;
    if (symp1 == "X") {
        symp2 = "O";
    }
    else if (symp1 == "x") {
        symp2 = "o";
    }
    else if (symp1 == "O") {
        symp2 = "X";
    }
    else if (symp1 == "o") {
        symp2 = "x";
    }

    Player p2(name2, symp2);

    GameMaster(p1, p2);

    PrintWinner(p1, p2);
    if (IsDraw()) {
        cout << "The game is ended by draw .";
    }
}

void WithComp() {
    Info();

    InitBoard();

    string name1;
    string symp1, symp2;

    cout << "Player 1: Enter Your Name and character (X or O): ";
    cin >> name1 >> symp1;
    Player p1(name1, symp1);

    if (symp1 == "X") {
        symp2 = "O";
    }
    else if (symp1 == "x") {
        symp2 = "o";
    }
    else if (symp1 == "O") {
        symp2 = "X";
    }
    else if (symp1 == "o") {
        symp2 = "x";
    }

    RandomPlayer RP(symp2);

    GameMaster(p1, RP);

    PrintWinner(p1, RP);

    if (IsDraw()) {
        cout << "The game is ended by draw .";
    }
}
void ThePyramidGame() {

    srand(time(0));

    int Choice;
    cout << "Do you want to play with a friend or with the computer?\n1]With my friend           2]With Computer \n";
    cin >> Choice;
    switch (Choice) {
    case 1: {
        With2Players();
        break;
    }
    case 2: {
        WithComp();
        break;
    }
    default: {
        cout << "Wrong Choice";
        break;
    }
    }
}
//===================================================================================================================================================
int main() {
    ThePyramidGame();
    return 0;
}
