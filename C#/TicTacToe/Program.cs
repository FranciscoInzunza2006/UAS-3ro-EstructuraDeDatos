
 // Globals and constants
const int GRID_LENGTH = 3;

const char EMPTY = '#';
const char X = 'X';
const char O = 'O';

const string SEPARATOR = "---------------------------";

int turn = 0;
char[,] board = new char[GRID_LENGTH,GRID_LENGTH];

// Functions
void initializeGrid()
{
	for (int x = 0; x < GRID_LENGTH; x++)
	{
		for (int y = 0; y < GRID_LENGTH; y++)
		{
			board[x, y] = EMPTY;
		}
	}
}

void printGameTitle() {
	Console.WriteLine(SEPARATOR);
	Console.WriteLine("\tGatito");
	Console.WriteLine(SEPARATOR);
	Console.WriteLine($"Turno: {turn+1}");
	Console.WriteLine(SEPARATOR);
}

void printArray()
{
	for (int x = 0; x < GRID_LENGTH; x++)
	{
		for (int y = 0; y < GRID_LENGTH; y++)
		{
			char c = board[y, x];
			Console.Write(c.ToString());
		}
		Console.WriteLine();
	}

}

void playerTurn()
{
	int getValidPosition()
	{
		int pos;
		do
		{
			pos = -1;
			try
			{
				pos = Convert.ToInt32(Console.ReadLine());
			}
			catch (Exception)
			{

			}

			if (pos < 0 || pos > GRID_LENGTH - 1)
			{
				Console.WriteLine("Valor invalido!");
			}
		} while (pos < 0 || pos > GRID_LENGTH - 1);
		return pos;
	}
	int x;
	Console.Write("Columna: ");
	x = getValidPosition();

	int y;
	Console.Write("Fila: ");
	y = getValidPosition();

	board[x, y] = X;
}

void cpuTurn()
{
	for (int x = 0; x < GRID_LENGTH; x++)
	{
		for (int y = 0; y < GRID_LENGTH; y++)
		{
			if (board[x, y] == EMPTY)
			{
				board[x, y] = O;
				return;
			}			 
		}
	}
}

bool checkForWinner(char c)
{
	if (board[0,0] == c &&  board[1,0] == c && board[2,0] == c) return true;
	if (board[0, 1] == c && board[1, 1] == c && board[2, 1] == c) return true;
	if (board[0, 2] == c && board[1, 2] == c && board[2, 2] == c) return true;

	if (board[0, 0] == c && board[0, 1] == c && board[0, 2] == c) return true;
	if (board[1, 0] == c && board[1, 1] == c && board[1, 2] == c) return true;
	if (board[2, 0] == c && board[2, 1] == c && board[2, 2] == c) return true;

	if (board[0, 0] == c && board[1, 1] == c && board[2, 2] == c) return true;
	if (board[0, 2] == c && board[1, 1] == c && board[2, 0] == c) return true;
	
	return false;
}

void updateBoard()
{
	Console.Clear();
	printGameTitle();
	printArray();
}

// Main
initializeGrid();
updateBoard();
do
{
	playerTurn();
	updateBoard();
	if (checkForWinner(X))
	{
		Console.WriteLine(SEPARATOR);
		Console.WriteLine("Ganaste!");
		return;
	}
	
	cpuTurn();
	updateBoard();
	if (checkForWinner(O))
	{
		Console.WriteLine(SEPARATOR);
		Console.WriteLine("Gano la CPU.");
		return;
	}
	turn++;
} while (turn <= (GRID_LENGTH * GRID_LENGTH/2));

Console.WriteLine(SEPARATOR);
Console.WriteLine("Empate...");