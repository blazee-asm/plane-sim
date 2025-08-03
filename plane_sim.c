// windows stuff like SetConsoleCursorPosition
#include <windows.h>
// input-output like printf
#include <stdio.h>
// system() and stuff
#include <stdlib.h>
// yes, booleans (true/false) aren't in C by default
#include <stdbool.h>

void setPos(int x, int y) {
    // sets cursor position
    COORD coord;
    coord.X = (x - 1) * 2;
    coord.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printxy(int x, int y, bool block) {
    // skip all this if out-of-bounds
    if (x > 0 && y > 0 && x < 40 && y < 25) {
        setPos(x, y);
        if (block) { printf("##"); } else { printf("  "); }
    }
}

void printHorizontalLine(int xStart, int xEnd, int y, bool block) {
    for (int x = xStart; x <= xEnd; x++) {
        printxy(x, y, block);
    }
}

void printVerticalLine(int x, int yStart, int yEnd, bool block) {
    for (int y = yStart; y <= yEnd; y++) {
        printxy(x, y, block);
    }
}

int main() {
    bool gameOver = false;
    int playerX = 1;
    int playerY = 3;
    int objects[] = {40, 5, 50, 2, 60, 8};
    while (1) {
        // is esc pressed? if so, end
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            gameOver = true;
            break;
        } else if ((GetAsyncKeyState(VK_UP) & 0x8000) && playerY > 3) {
            playerY--;
        } else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && playerY < 22) {
            playerY++;
        }
        // clear screen
        system("cls");
        // draw plane
        printVerticalLine(4, playerY - 2, playerY + 2, true);
        printHorizontalLine(1, 5, playerY, true);
        // draw objects
        for (int i = 0; i < 6; i += 2) {
            printxy(objects[i] - playerX, objects[i + 1], true);
            // check collision
            if ((objects[i] - playerX == 4 && objects[i + 1] >= playerY - 2 && objects[i + 1] <= playerY + 2) || (objects[i] - playerX > 0 && objects[i] - playerX <= 5 && objects[i + 1] == playerY)) {
                gameOver = true;
                break;
            }
        }
        if (gameOver) { break; }
        playerX++;
        Sleep(50);
    }
    // clear screen again
    system("cls");
    // oh no u lost :c
    setPos(1, 1);
    printf("Game over.");
    Sleep(1000);
    return 0;
}