#include <iostream>
#include <ctime>
#include <cstdlib>  // For rand and srand
#include <conio.h>  // For _kbhit() and _getch(), Windows-specific for input handling

using namespace std;

enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, 
           RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };

class cBall {
    private:
        int x, y;
        int originalX, originalY;
        eDir direction;
    public:
        cBall(int posX, int posY) {
            originalX = posX;
            originalY = posY;
            x = posX; y = posY;
            direction = STOP;
        }

        void Reset() {
            x = originalX; 
            y = originalY;
            direction = STOP;
        }

        void changeDirection(eDir d) {
            direction = d;
        }

        void randomDirection() {
            direction = (eDir)((rand() % 6) + 1);
        }

        inline int getX() { return x; }
        inline int getY() { return y; }
        inline eDir getDirection() { return direction; }

        void move() {
            switch (direction) {
                case STOP:
                    break;
                case LEFT:
                    x--;
                    break;
                case RIGHT:
                    x++;
                    break;
                case UPLEFT:
                    x--; y--;
                    break;
                case DOWNLEFT:
                    x--; y++;
                    break;
                case UPRIGHT:
                    x++; y--;
                    break;
                case DOWNRIGHT:
                    x++; y++;
                    break;
                default:
                    break;
            }
        }

        friend ostream& operator<<(ostream& o, cBall c) {
            o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]" << '\n';
            return o;
        }
};

class cPaddle {
    private:
        int x, y;
        int originalX, originalY;
    public:
        cPaddle() {
            x = y = 0;
        }

        cPaddle(int posX, int posY) : cPaddle() {
            originalX = posX;
            originalY = posY;
            x = posX;
            y = posY;
        }

        inline void Reset() { 
            x = originalX; 
            y = originalY; 
        }

        inline int getX() { return x; }
        inline int getY() { return y; }
        inline void moveUp() { y--; }
        inline void moveDown() { y++; }

        friend ostream& operator<<(ostream& o, cPaddle p) {
            o << "Paddle [" << p.x << "," << p.y << "]";
            return o;
        }
};

class cGameManager {
    private:
        int width, height;
        int score1, score2;
        char up1, down1, up2, down2;
        bool quit;
        cBall* ball;
        cPaddle* player1;
        cPaddle* player2;
    public:
        cGameManager(int w, int h) {
            srand(time(NULL));
            quit = false;
            up1 = 'w'; up2 = 'i';
            down1 = 's'; down2 = 'k';
            score1 = score2 = 0;
            width = w; height = h;
            ball = new cBall(w / 2, h / 2);
            player1 = new cPaddle(1, h / 2 - 3);
            player2 = new cPaddle(w - 2, h / 2 - 3);
            ball->randomDirection();  // Make the ball start moving
        }

        ~cGameManager() {
            delete ball;
            delete player1;
            delete player2;
        }

        void ScoreUp(cPaddle* player) {
            if (player == player1)
                score1++;
            else if (player == player2)
                score2++;

            ball->Reset();
            player1->Reset();
            player2->Reset();
            ball->randomDirection();
        }

        void Draw() {
            system("cls");  // Clears the console screen (Windows-specific)

            // Draw the top wall
            for (int i = 0; i < width + 2; i++)
                cout << "#";
            cout << endl;

            // Draw the game area
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (j == 0)  // Left wall
                        cout << "#";
                    
                    // Display ball
                    if (ball->getX() == j && ball->getY() == i)
                        cout << "O";
                    // Display player1
                    else if (player1->getX() == j && player1->getY() == i)
                        cout << "|";
                    // Display player2
                    else if (player2->getX() == j && player2->getY() == i)
                        cout << "|";
                    else
                        cout << " ";  // Empty space

                    if (j == width - 1)  // Right wall
                        cout << "#";
                }
                cout << endl;
            }

            // Draw the bottom wall
            for (int i = 0; i < width + 2; i++)
                cout << "#";
            cout << endl;

            // Display the scores
            cout << "Player 1: " << score1 << "  Player 2: " << score2 << endl;
        }

        void Input() {
            if (_kbhit()) {  // Check if a key was pressed
                char current = _getch();
                if (current == up1)  // Player 1 up
                    if (player1->getY() > 0)
                        player1->moveUp();
                if (current == down1)  // Player 1 down
                    if (player1->getY() < height - 1)
                        player1->moveDown();
                if (current == up2)  // Player 2 up
                    if (player2->getY() > 0)
                        player2->moveUp();
                if (current == down2)  // Player 2 down
                    if (player2->getY() < height - 1)
                        player2->moveDown();
                if (current == 'q')  // Quit the game
                    quit = true;
            }
        }

        void Logic() {
            ball->move();

            // Ball collision with the left wall (Player 2 scores)
            if (ball->getX() == 0)
                ScoreUp(player2);

            // Ball collision with the right wall (Player 1 scores)
            if (ball->getX() == width - 1)
                ScoreUp(player1);

            // Ball collision with the paddles
            if (ball->getX() == player1->getX() + 1 && ball->getY() == player1->getY())
                ball->changeDirection((eDir)((rand() % 3) + 4));  // Bounce off player 1
            if (ball->getX() == player2->getX() - 1 && ball->getY() == player2->getY())
                ball->changeDirection((eDir)((rand() % 3) + 1));  // Bounce off player 2

            // Ball collision with the top and bottom walls
            if (ball->getY() == 0)
                ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
            if (ball->getY() == height - 1)
                ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
        }

        void Run() {
            while (!quit) {
                Draw();
                Input();
                Logic();
            }
        }
};

int main() {
    cGameManager game(40, 20);
    game.Run();
    return 0;
}
