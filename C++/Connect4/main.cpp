
#include <iostream>
#include <cstdlib>
#include <conio.h>

#define GRID_ROWS 6
#define GRID_COLUMNS 7

#define EMPTY ' '
#define RED_CHECKER '@'
#define YELLOW_CHECKER '%'

#define RED_COLOR "\033[38;2;255;0;0m"
#define YELLOW_COLOR "\033[38;2;255;255;0m"
#define RESET_COLOR "\033[0m"

char board[GRID_ROWS][GRID_COLUMNS];

void initGame();
void printGame();
void printSeparator();
void printBoard();

void playerTurn();
void cpuTurn();

int getIntInRange(const std::string message, const int min, const int max);
bool putChecker(const int column, const char checker);
void checkWinner(const int row, const int column, const char checker);

int main()
{
    initGame();

    int turn = 0;
    while (true)
    {
        printGame();

        if (turn % 2 == 0)
            playerTurn();
        else
            cpuTurn();

        turn++;
    }

    return 0;
}

void initGame()
{
    for (int x = 0; x < GRID_ROWS; x++)
    {
        for (int y = 0; y < GRID_COLUMNS; y++)
        {
            board[x][y] = EMPTY;
        }
    }
}

void printGame()
{
    std::system("cls");

    printSeparator();
    std::cout << "\tConecta 4\n";
    printSeparator();

    printBoard();
    printSeparator();
}

void printSeparator()
{
    std::cout << "---------------------------------------------\n";
}

void printBoard()
{
    std::cout << "\t+-------------+\n\t";
    for (int x = 0; x < GRID_ROWS; x++)
    {
        std::cout << '|';
        for (int y = 0; y < GRID_COLUMNS; y++)
        {
            std::cout << (board[x][y] == RED_CHECKER ? RED_COLOR : YELLOW_COLOR) << board[x][y]  << RESET_COLOR << '|';
        }
        if (x != GRID_ROWS-1)
            std::cout << "\n\t|-+-+-+-+-+-+-|\n\t";
    }
    std::cout << "\n\t+-------------+\n";
}

void playerTurn()
{
    int column = getIntInRange("En que columna(1-7) quieres poner tu ficha(@)? ", 1, GRID_COLUMNS + 1);
    putChecker(column - 1, RED_CHECKER);
}

void cpuTurn()
{
    int column;
    do
    {
        column = rand() % GRID_COLUMNS;
    } while (!putChecker(column, YELLOW_CHECKER));
}

bool putChecker(const int column, const char checker)
{
    for (int row = GRID_ROWS - 1; row >= 0; row--)
    {
        if (board[row][column] == EMPTY)
        {
            board[row][column] = checker;
            checkWinner(row, column, checker);

            return true;
        }
    }

    return false;
}

int getIntInRange(const std::string message, const int min, const int max)
{
    while (true)
    {
        int x;
        std::cout << '\r' << message;
        std::cin >> x;

        if (x < min || x > max)
        {
            std::cout << "\rFuera de rango!";
            getch();
            std::cout << "\r                         \x1b[A"; // El diablo (mueve el cursor para arriba)
            continue;
        }

        return x;
    }
}

void checkWinner(const int row, const int column, const char checker)
{
    int connected_thingies = 0;
    int x = row;
    int y = column;

    // Horizontal
    while (x >= 0 && board[x][y] == checker)
    {
        connected_thingies++;
        x--;
    }
    x = row + 1;
    while (x < GRID_ROWS && board[x][y] == checker)
    {
        connected_thingies++;
        x++;
    }
    if (connected_thingies >= 4)
        goto GG;

    // Vertical
    connected_thingies = 0;
    x = row;
    while (y >= 0 && board[x][y] == checker)
    {
        connected_thingies++;
        y--;
    }
    y = column + 1;
    while (y < GRID_COLUMNS && board[x][y] == checker)
    {
        connected_thingies++;
        y++;
    }
    if (connected_thingies >= 4)
        goto GG;

    // Diagonal left
    connected_thingies = 0;
    y = column;
    while (x >= 0 && y >= 0 && board[x][y] == checker)
    {
        connected_thingies++;
        x--;
        y--;
    }
    x = row + 1;
    y = column + 1;
    while (x < GRID_ROWS && y < GRID_COLUMNS && board[x][y] == checker)
    {
        connected_thingies++;
        x++;
        y++;
    }
    if (connected_thingies >= 4)
        goto GG;

    // Diagonal right
    connected_thingies = 0;
    x = row;
    y = column;
    while (x <= GRID_ROWS && y >= 0 && board[x][y] == checker)
    {
        connected_thingies++;
        x++;
        y--;
    }
    x = row - 1;
    y = column + 1;
    while (x >= 0 && y < GRID_COLUMNS && board[x][y] == checker)
    {
        connected_thingies++;
        x--;
        y++;
    }
    if (connected_thingies >= 4)
        goto GG;

    return;
GG: // Dirty af hack
    printGame();
    if (checker == RED_CHECKER)
        std::cout << "GG ez" << std::endl;
    else 
        std::cout << "Le gano la CPU, Tremendo manco" << std::endl;
    getch();
    std::exit(EXIT_SUCCESS);
}