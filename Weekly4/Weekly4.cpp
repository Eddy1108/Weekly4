// Weekly4.cpp

#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <ctime>
#include <time.h>
#include <thread>
#include <algorithm>

int choice{ 0 };

//task 1 variables
char letter = ' ';

//task 2 variables
char board[10][20] = {
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
};

struct objects {
    char icon;
    int forPosX;
    int forPosY;
};

char pInput = ' ';
int currentY{ 1 };
int currentX{ 1 };
int lastY{ 0 };
int lastX{ 0 };
int direction{ 0 };     //0, didnt move //1, Moved Up // 2, Moved Right // 3, Moved Down //4, Moved Left //enum?

//task 3 variables
struct people {
    std::string name{};
    long int number;
};

int amount{ 0 };
int temp{ 0 };

//task 4 variables
char hold = ' ';
int diceNr{ 0 };
bool diceFinished = false;

char lowerToUpper(char l) {
    return l - 32;
}

void task1() 
{
    std::vector<char> sentence{};

    system("cls");

    std::cout << "Please type a lowercase letter to convert: ";
    letter = _getch();
    std::cout << letter;

    std::cout << "\nConverted: " << lowerToUpper(letter) << std::endl;

    system("pause");
}

void printBoard()
{
    for (int i = 0; i <= 9; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            std::cout << board[i][j];
        }
        std::cout << "\n";
    }
}

void calculateDir() 
{
    if (currentX - lastY < 0) {
        direction = 4;
    }
    else if (currentX - lastY > 0) {
        direction = 2;
    }
    if (currentY - lastX < 0) {
        direction = 1;
    }
    else if (currentY - lastX > 0) {
        direction = 3;
    }
}

void task2() 
{
    objects forward{ '/', 7, 7};
    objects backwards{ '\\', 3, 3 };
    objects exit{ 'G', 9, 9 };
    currentX = 1;
    currentY = 1;

    while (true) {
        system("cls");
        
        board[lastY][lastX] = ' ';
        board[currentY][currentX] = '*';
        board[forward.forPosX][forward.forPosY] = forward.icon;
        board[backwards.forPosX][backwards.forPosY] = backwards.icon;
        board[exit.forPosX][exit.forPosY] = exit.icon;
        
        printBoard();
        //std::cout << "BOARD PRINTED\n" << "Current: " << currentY << " " << currentX;
        //std::cout << "\nLast: " << lastY << " " << lastX;
        pInput = _getch();

        switch (pInput) {
        case 'w':
        case 'W':
            lastY = currentY;
            lastX = currentX;
            currentY--;
            break;
        case 'a':
        case 'A':
            lastX = currentX;
            lastY = currentY;
            currentX--;
            break;
        case 's':
        case 'S':
            lastY = currentY;
            lastX = currentX;
            currentY++;
            break;
        case 'd':
        case 'D':
            lastX = currentX;
            lastY = currentY;
            currentX++;
            break;
        }

        if (board[currentY][currentX] != ' ') {
            if (board[currentY][currentX] == '/') {
                currentY++;
            }
            else if (board[currentY][currentX] == '\\') {
                currentY--;
            }
            else if (board[currentY][currentX] == 'G') {
                break;
            }
        }

        //Exit the board on one side, appear on the other.
        if (currentX < 0) {
            currentX = 9;
        }
        if (currentX > 9) {
            currentX = 0;
        }
        if (currentY <= 0) {
            currentY = 9;
        }
        if (currentY >= 10) {
            currentY = 1;
        }
    }
    std::cout << "\nGAME OVER\n";
    system("pause");

}

void task3() {
    
    while (true) 
    {
    system("cls");
    std::cout << "How many people? (Max 10) :";
    std::cin >> amount;
    std::cin.ignore();

        if (amount > 0 && amount < 11) 
        {
            break;
        }
    }
   
    people n1[10];
    for (int i = 1; i < amount+1; i++)
    {
        system("cls");
        std::cout << "Saving info for person " << i << "...";
        std::cout << "\nName: ";
        std::cin.ignore();
        std::getline(std::cin, n1[i - 1].name);
        std::cout << "Number: ";
        std::cin >> n1[i-1].number;
        
    }

    while (true) {
        system("cls");
        while (true){
            std::cout << "Would you like to view the saved info? (Between 1 - " << amount << ", 0 to exit) :";
            std::cin >> temp;
            if (temp <= amount && temp >= 0) {
                break;
            }
        };
        if (temp == 0) {
            break;
        }

        std::cout << "Info for person " << temp << ": ";
        std::cout << "\nName: " << n1[temp - 1].name;
        std::cout << "\nNumber: " << n1[temp - 1].number << std::endl;

        system("pause");
    }
}

int findSixes(std::vector<int> array) {
    int sixes{ 0 };
    for (int i = 0; i < array.size(); i++)
    {
        if (array.at(i) == 6) {
            sixes++;
        }
    }
    return sixes;
}

int findPairs(std::vector<int> array) {
    int pairs{ 0 };
    sort(array.begin(), array.end());             //Sort the hand so finding pairs is easy.
    for (int i = 0; i < array.size(); i++)         //Find pairs!
    {
        if (i >= 1 && array.at(i) == array.at(i - 1)) {
            pairs++;
            i++;
        }
    }
    return pairs;
}

void rollDice(std::vector<int> &array) 
{
    for (int i = 0; i < array.size(); i++)
    {
    array.at(i) = std::rand() % 6 + 1;
    std::cout << array.at(i) << " ";
    }
}

void task4() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    diceFinished = false;
    std::vector<int> inPlay(5);
    std::vector<int> inHand{};
    while (true) 
    {
        hold = 'r';
        do        //Roll random numbers until the player presses H
        {
            system("cls");
            if (hold == 'r' || hold == 'R') {
                rollDice(inPlay);
                hold = ' ';
            }

            std::cout << "\n--Press 'H' to choose what to keep-- \n--Press 'R' to reroll Dice--";
            hold = _getch();

        } while (hold != 'h');
        
        while (true)       //Hold menu
        {
            hold = ' ';
            system("cls");

            for (int i = 1; i < inPlay.size() + 1; i++)     //Print the dice in play
            {
                std::cout << "Dice [" << i << "]: " << inPlay.at(i - 1) << "\n";
            }

            std::cout << "\nDice in hand : ";
            for (int i = 0; i < inHand.size(); i++)         //Print the dice in hand
            {
                std::cout << inHand.at(i) << ", ";
            }

            std::cout << "\n\n--Press 'R' to reroll-- \n--Press 'H' again to Finish-- \n--Type the dice [number] you wish to keep--\n";
            hold = _getch();

            if (hold == 'r' || hold == 'R') {           //Exit the hold menu, and return to rolling.
                break;
            }

            if (hold == 'h' || hold == 'H') {           //Press H again and the game ends
                diceFinished = true;
                break;
            }

            if (((int)hold - '0') > inPlay.size()) {    //Make sure you cant choose invalid dice numbers
                hold = '0';
            }

            switch (hold) {                         //Move numbers from inPlay to inHand, and remove it from inPlay
            case '1':
                inHand.push_back(inPlay.at(0));
                inPlay.erase(inPlay.begin());
                break;
            case '2':
                inHand.push_back(inPlay.at(1));
                inPlay.erase(inPlay.begin() + 1);
                break;
            case '3':
                inHand.push_back(inPlay.at(2));
                inPlay.erase(inPlay.begin() + 2);
                break;
            case'4':
                inHand.push_back(inPlay.at(3));
                inPlay.erase(inPlay.begin() + 3);
                break;
            case '5':
                inHand.push_back(inPlay.at(4));
                inPlay.erase(inPlay.begin() + 4);
                break;
            }
        }

        if (diceFinished == true) 
        {
            system("cls");
            std::cout << "The game is over! \nDice you kept: ";
            for (int i = 0; i < inHand.size(); i++)
            {
                std::cout << inHand.at(i) << " ";
            }

            std::cout << "\nYou have " << findPairs(inHand) << " pair(s) in your hand.";

            std::cout << "\nDice with 6 in your hand: " << findSixes(inHand) << "\n";
            system("pause");
            break;
        }
    }
}

int main()
{
    while (true) {
        //Print Menu
        system("cls");
        std::cout << "There are 4 tasks in this program, \nPlease choose a task: \n[1]: Lowercase to Uppercase \n[2]: 10x10 board w/player \n[3]: Save Names & Numbers \n[4]: Roll Dice \n\n[0]Exit \n";
        std::cin >> choice;

        switch (choice) {
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        case 3:
            task3();
            break;
        case 4:
            task4();
            break;
        case 0:
            exit(0);
            break;
        }
    }
}