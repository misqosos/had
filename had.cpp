#include <iostream>
#include <cstring>
#include <string>
#include "windows.h"
#include <cstdlib>  
#include <ctime>  
#include <map>
#include <vector>

using namespace std;


void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

int main()
{
    ShowConsoleCursor(false);
    srand(time(0));

    char block = '#';
    char space = ' ';
    int height = 20, width = 30;
    int borderLayers = 1;

    int snakeX = 1;
    int snakeY = 1;
    string snake = "O";
    int moveX = 0, moveY = 0;
    vector<int> prevX{ snakeX };
    vector<int> prevY{ snakeY };

    int foodX = 4;
    int foodY = 4;
    char food = '%';

    char tail = '*';
    int tailLength = 0;

    while (true)
    {
        if (GetKeyState(VK_DOWN) & 0x8000) {
            moveY = 1;
            moveX = 0;
        }
        if (GetKeyState(VK_UP) & 0x8000) {
            moveY = -1;
            moveX = 0;
        }
        if (GetKeyState(VK_RIGHT) & 0x8000) {
            moveX = 1;
            moveY = 0;
        }
        if (GetKeyState(VK_LEFT) & 0x8000) {
            moveX = -1;
            moveY = 0;
        }
        snakeY += moveY;
        snakeX += moveX;

        if (snakeY > height - 2 * borderLayers) {
            snakeY = 1;
        }
        if (snakeY < 1) {
            snakeY = height - 2 * borderLayers;
        }
        if (snakeX > width - 2 * borderLayers) {
            snakeX = 1;
        }
        if (snakeX < 1) {
            snakeX = width - 2  * borderLayers;
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i > 0 && i < height - borderLayers) {
                    if (j > 0 && j < width - borderLayers) {

                        bool goingLeft = j > snakeX;
                        bool goingUp = i > snakeY;
                        
                        if (j == snakeX && i == snakeY) {
                            cout << snake;
                            prevX.push_back(snakeX);
                            prevY.push_back(snakeY);
                            continue;
                        }
                        
                        bool tailAdded = false;
                        if (tailLength > 0) {
                            for (int k = 0; k < tailLength; k++) {
                                int step = goingLeft || goingUp ? 2 : 1;
                                if (prevY[prevY.size() - k - step] == i &&
                                    prevX[prevX.size() - k - step] == j) {
                                    cout << tail;
                                    tailAdded = true;
                                }
                                
                            }
                            if (tailAdded) { continue; }
                        }
                        
                        if (j == foodX && i == foodY) {
                            cout << food;
                            continue;
                        }
                        
                        if (foodX == snakeX && foodY == snakeY) {
                            foodX = (rand() % (width - 2 * borderLayers)) + 1;
                            foodY = (rand() % (height - 2 * borderLayers)) + 1;
                            tailLength++;
                        }
                        
                        cout << space;
                        continue;
                    }
                }
                cout << block;
            }
            cout << endl;
        }
        system("CLS");
    }

    return 0;
}