#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

const int ROWS =10;
const int COLUMNS = 10;

void clearGrid(int grid[ROWS][COLUMNS])
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int column = 0; column < COLUMNS; column++)
		{
			grid[row][column] = 0;
		}
	}
}

void showGrid(int grid[ROWS][COLUMNS])
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int column = 0; column < COLUMNS; column++)
		{
			cout << grid[row][column] << " ";
		}
		cout << endl;
	}
}

void setShips(int totalShips, int grid[ROWS][COLUMNS])
{
	int shipsPlaced = 0;
	while(shipsPlaced < totalShips)
	{
		int x_coord = rand() % ROWS;
		int y_coord = rand() % COLUMNS;
		
		if(grid[x_coord][y_coord] != 1)
		{
			shipsPlaced++;
			grid[x_coord][y_coord] = 1;
		}
	}
}

bool attack(int x_coord, int y_coord, int grid[ROWS][COLUMNS])
{
	if(grid[x_coord][y_coord] == 1)
	{
		cout << endl << "Damn it, you sunk my ship!" << endl << "---------------" << endl;
		grid[x_coord][y_coord] = 2; //2 means sunk
		return true;
	}
	
	cout << "Your attack missed, HAHAHA!" << endl << "---------------" << endl;
	return false;
}

int shipsRemaining(int totalShips, int grid[ROWS][COLUMNS])
{
	int shipsLeft = totalShips;
	
	for (int row = 0; row < ROWS; row++)
	{
		for (int column = 0; column < COLUMNS; column++)
		{
			if(grid[row][column] == 2)
			{
				shipsLeft--;	
			}
		}
	}
	
	return shipsLeft;	
}

int main()
{
	srand(time(NULL));
	cout << "Welcome to BattleShip++" << endl;
	cout << "Please select the game difficulty: " << endl;
	cout << "(1) Easy  "<< "(2) Normal  "<< "(3) Hard" << endl << endl;   
	
	char gameDifficulty; //used char instead of int b/c using boolean condition with type conversion caused errors if invalid input was received in cin stream
	cin >> gameDifficulty;
	
	while(!(gameDifficulty == '1' || gameDifficulty == '2' || gameDifficulty == '3'))
	{
		cout << "Please select the game difficulty: " << endl;
		cin >> gameDifficulty;
	}
	
	int totalShips;

	switch (gameDifficulty)
	{
		case '1':
			totalShips = 20;
			break;
		case '2':
			totalShips = 10;
			break;
		case '3':
			totalShips = 5;
			break;
		default:
			cout << "Please contact the game developer to fix the game." << endl << endl;
			return 0;
	}
	
	cout << endl << "HINT: The map has a maximum size of " << ROWS << "x" << COLUMNS << endl << endl;
	
	int grid[ROWS][COLUMNS];
	clearGrid(grid);
	setShips(totalShips, grid);

	while(shipsRemaining(totalShips, grid) != 0)
	{
		int x_coord, y_coord;
		cout << "Please input attack coordinates: x-coord [enter] and y-coord [enter] " << endl; 
		cin >> x_coord >> y_coord;
		if(x_coord > ROWS || x_coord < 0 || y_coord > COLUMNS || y_coord < 0)
		{
			cout << endl << "INVALID COORDINATES. YOU LOSE YOUR NEXT TURN." << endl;
		}
		attack(x_coord, y_coord, grid);
		cout << "Number of ships remaining is: " << shipsRemaining(totalShips, grid) << endl << endl;
		
	}
	
	cout << endl << "--------------------------------------------------------" 
		 << endl << "CONGRATUALATIONS!!! YOU HAVE DESTROYED ALL ENEMY SHIPS AND ARE AWARDED THE RANK OF ADMIRAL OF THE HIGH SEAS" << endl;	
	
	return 0;
}
