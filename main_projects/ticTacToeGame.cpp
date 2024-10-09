#include <iostream>
#include <ctime>

void drawBoard(char *spaces);
void playerMove(char *spaces, char player);
void computerMove(char *spaces, char computer);
bool checkWinner(char* spaces, char player);
bool checkTie(char *spaces);

int main(){

    char spaces[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char player = 'X';
    char computer = 'O';
    bool running = true;

    drawBoard(spaces);

    while (running) {
        // Player's turn
        playerMove(spaces, player);
        drawBoard(spaces);
        if (checkWinner(spaces, player)) {
            std::cout << "You Win!\n";
            running = false;
            break;
        }
        if (checkTie(spaces)) {
            std::cout << "It's a Tie!\n";
            running = false;
            break;
        }

        // Computer's turn
        computerMove(spaces, computer);
        drawBoard(spaces);
        if (checkWinner(spaces, computer)) {
            std::cout << "You Lose!\n";
            running = false;
            break;
        }
        if (checkTie(spaces)) {
            std::cout << "It's a Tie!\n";
            running = false;
            break;
        }
    }

    return 0;
}

void drawBoard(char *spaces) {
    std::cout << '\n';
    std::cout << "     |     |     " << '\n';
    std::cout << "  " << spaces[0] << "  |  " << spaces[1] << "  |  " << spaces[2] << " " << '\n';
    std::cout << "_____|_____|_____" << '\n';
    std::cout << "     |     |     " << '\n';
    std::cout << "  " << spaces[3] << "  |  " << spaces[4] << "  |  " << spaces[5] << " " << '\n';
    std::cout << "_____|_____|_____" << '\n';
    std::cout << "     |     |     " << '\n';
    std::cout << "  " << spaces[6] << "  |  " << spaces[7] << "  |  " << spaces[8] << " " << '\n';
    std::cout << "     |     |     " << '\n';
    std::cout << '\n';
}

void playerMove(char *spaces, char player) {
    int number;
    
    do {
        std::cout << "Enter a spot to place a marker (1-9): ";
        std::cin >> number;
        number--;
        if (number >= 0 && number < 9 && spaces[number] == ' ') {
            spaces[number] = player;
            break;
        } else {
            std::cout << "Invalid move. Try again.\n";
        }
    } while (true);
}

void computerMove(char *spaces, char computer) {
    int number;
    srand(time(0));

    while (true) {
        number = rand() % 9;
        if (spaces[number] == ' ') {
            spaces[number] = computer;
            break;
        }
    }
}

bool checkWinner(char *spaces, char player) {
    // Check rows, columns, and diagonals for a winner
    if ((spaces[0] == player && spaces[1] == player && spaces[2] == player) ||  // Row 1
        (spaces[3] == player && spaces[4] == player && spaces[5] == player) ||  // Row 2
        (spaces[6] == player && spaces[7] == player && spaces[8] == player) ||  // Row 3
        (spaces[0] == player && spaces[3] == player && spaces[6] == player) ||  // Column 1
        (spaces[1] == player && spaces[4] == player && spaces[7] == player) ||  // Column 2
        (spaces[2] == player && spaces[5] == player && spaces[8] == player) ||  // Column 3
        (spaces[0] == player && spaces[4] == player && spaces[8] == player) ||  // Diagonal 1
        (spaces[2] == player && spaces[4] == player && spaces[6] == player)) {  // Diagonal 2
        return true;
    }
    return false;
}

bool checkTie(char *spaces) {
    // If there are no empty spaces left, it's a tie
    for (int i = 0; i < 9; i++) {
        if (spaces[i] == ' ') {
            return false;
        }
    }
    return true;
}
