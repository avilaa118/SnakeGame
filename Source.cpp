/*
    Project Name: Snake Game
    Date: April 12th, 2021
    Developers: Anderson Avila, Jing Gan, Ogulcan Gorgulu
*/
#include <iostream>
#include <conio.h>  //_kbhit() and _getch
#include <ctime>    // rand location
#include <windows.h> // for sleep function and colors
using namespace std;

// global varaibles
bool gameOver;
const int width = 30;
const int height = 20;
int x, y, fruitX, fruitY, score, fruit = 0;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// function to change color
void changeColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void Setup()
{

    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;

    // random fruit location based on width and height limits
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;


}
void gameDraw()
{
    
    system("cls");  // clear the screen
    cout << "\n\t~ Snake Game ~\n";
    for (int i = 0; i < width + 2; i++) {
        cout << char(254);
    }
    cout << "\n";

    // i height, j width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0) // print first element of vertical border
            {
                cout << char(219);
            }
            if (i == y && j == x)   // print the head of snake on the middle
            {
                cout << char(223); // head character
            }
            else if (i == fruitY && j == fruitX)    // print the food on random location
            {   
                
                cout << char(5);    // fruit character
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++) { // going through every element of our tail
                    if (tailX[k] == j && tailY[k] == i) // j is current x coordinate that we are printing
                    {
                        cout << char(223); // body character, same as head
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1) {
                cout << char(219);
            }
        }
        cout << "\n";
    }
    for (int i = 0; i < width + 2; i++)
    {
        cout << char(254);
    }
    cout << "\n\n";
    cout << " Score: " << score << "\n\n *Press 'X' to end the game.*";

}
void gameInput()
{
    if (_kbhit())   // if a character on the keyboard is pressed
    {
        switch (_getch())   // return ASCII value that was pressed
        {
        case 'a':
        case 'A':
            dir = LEFT;
            break;
        case 'd':
        case 'D':
            dir = RIGHT;
            break;
        case 'w':
        case 'W':
            dir = UP;
            break;
        case 's':
        case 'S':
            dir = DOWN;
            break;
        case 'x':
        case 'X':
            gameOver = true;
            break;

        }
    }
}
void gameLogic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    // set first element char(223) to follow the head
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    // if we want to end the game when we hit the wall, uncomment the code bellow.
    /* if (x > width || x < 0 || y > height || y < 0)
        gameOver = true;*/

    // to continue the game even if we gp through the wall, comment the code bellow if we don't want this feature
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    // if we hit ourselves the game ends, comment the code below if we don't want this feature.
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;   // if we eat the fruit tail increases by 1
        fruit++;   // keeps track of the fruits eaten
    }
}

int main()
{
    // setting console to light blue, change color by changing passing value
    changeColor(11);

    Setup();
    while (!gameOver)
    {
        gameDraw();
        gameInput();
        gameLogic();
        // You can modify this, lower number to make it faster, higher number to make it slower.
        Sleep(30);  // andy; personally the game is really fast so I had to slow it down to 30 for my cpu.
    }
    // changing the text color to a light yellow (makes it easier to read after snake dies.
    changeColor(14);
    cout << "\n\n Ahh! You did great!!\n\n";
    cout << " You scored " << score << " points and ate the fruit " << fruit << " times!\n";
    // changing the text back to white to make the game more immersive by makiong thw user focus on the game and texts.
    changeColor(15) cout << "\n\n";;
    system("Pause");
    return 0;
}

/*
 Developer Notes:

    MODIFICATIONS:
    1) We got rid of endl. 
        - Reason for this is that I personally noticed a smoother experience (although not by a lot).

    2) We changed the characters of the borders, snake and fruit/food.
        - We did this by referencing an ASCII table and used their char values.

    3) We implemented a function called changeColor that can be called anywhere in the source code.
        - We chose a color that is lighter and nice looking on the eye to help the player feel better.

    4) We modified the gameInput.
        - A simple modification to allow the user to keep playing even if their CAPS are on or off
        - This goes a long way.

    5) We added other simple features that improve the quality for the user.
        - A title.
        - We reminded the user to press 'x' to stop the game.
        - A message after the game ends to let the user know they did great and what their score was as well as how many fruits they ate.

    IDEAS:
    1) ---> We can make the screen not flicker as much. (Top priority!!!) <---
        - After a bit of reaseach I noticed that the issue lies on system("cls");
        - To fix this we must implement other functions from header file <windows.h> which requires further individual research.

    2) We can change the color of of the fruit/snake head/the snake itself after a certain score has been reached.
        - This requires a bit more research.

    3) We can make the game change colors after a certain score has reached. (easy fix)
        - Simply go to the gameDraw function and implement changeColor function after a certain condition has met. (if)

    4) We can add other special rules and extra features.
        - Like money
        - A text that appear to the side of the border saying "Awesome!", "Good!", etc and then it disappears
        - Make the user change the color of the game.
        - Make the game faster after a certain score has been reached. (makes the game harder for the user)

    5) We can implement new things we have been learing such as POINTERS, STRUCTS, CLASSES, etc, to make the game better.

    OVERALL:
        * We enjoyed making this simple project despite our time zone differences and semester work. Thank you for the encouragement.
*/
