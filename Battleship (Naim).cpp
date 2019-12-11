#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const int row = 5;
const int col = 5;
string battleboard[row][col];
string enemyBoard[row][col];
string playerBoard[row][col];

void InitBoard(string board[][col]);
void DisplayBoard(string board[][col]);
void BoardTitle();
void BoardSetup();
void InitEnemyShip(int amount, int size);
void InitPlayerShip(int amount, int size);
void PlayerAttack();
void EnemyAttack();
void PlayerHit();
void EnemyHit();

int main() 
{
	bool loopExit = false;
	int score1 = 0, score2 = 0;
	do
	{
		system("CLS");
		string choice;
		bool isExit = false;
		int amount = 0;
		int size = 0;
		int x, y, total, hit1 = 0, hit2 = 0;
		srand(time(NULL));
		
		BoardTitle();
		
		InitBoard(battleboard);
		InitBoard(enemyBoard);
		InitBoard(playerBoard);
		
		cout << "How many enemy ships do you want to go against? \n";
		cin >> amount;
		cout << endl;
		do
		{
			cout << "How big are the ships? (1 - 3) \n";
			cin >> size;
			if (size >= 1 && size <= 3)
			{
				isExit = true;
			}
			else
			{
				cout << "Invalid choice.\n";
			}
		}while(!isExit);
		
		total = amount * size;
		InitEnemyShip(amount,size);
		InitPlayerShip(amount,size);
		isExit = false;
		do
		{
			
			system("CLS");
			BoardTitle();
			cout << endl;
			cout << "   GAME BOARD" << endl;
			cout << endl;
			
			DisplayBoard(battleboard);
			
			cout << endl;
			cout << "   PLAYER BOARD" << endl;
			cout << endl;
			
			DisplayBoard(playerBoard);
			
			do
			{
				cout << "Choose where to attack your enemy\n";
				cin >> x; cin >> y;
				
				if(x > col)
				{
					cout << "Invalid choice\n";
				}
				else if(y > row)
				{
					cout << "Invalid choice\n";
				}
				else if(x <= 0 || y <= 0)
				{
					cout << "Invalid choice\n";
				}
				else
				{
					isExit = true;
				}
			}while(!isExit);
			
			isExit = false;
			
			x -= 1; y -= 1;
			
			if (enemyBoard[x][y] == " E")
			{
				cout << "You hit the enemy at x : " << x + 1 << " y : " << y + 1 << endl;
				battleboard[x][y] = " *";
				hit1 += 1;
			}
			if (enemyBoard[x][y] == " .")
			{
				cout << "Your target missed. There was no enemy there\n";
				battleboard[x][y] = " o";
			}
			
			if(hit1 == total)
			{
				cout << "You win!!\n";
				score1 += 1;
				isExit = true;
			}
			system("pause");
			
			if(isExit == false)
			{
				x= rand() % (col - 1);
				y= rand() % (row - 1);
				
				if (playerBoard[x][y] == " P")
				{
					cout << "You were hit at x : " << x + 1 << " y : " << y + 1 << endl;
					playerBoard[x][y] = " *";
					hit2 += 1;
				}
				else
				{
					cout << "Your enemy missed his mark" << endl;
				}
				
				if(hit2 == total)
				{
					cout << "You lose\n";
					isExit = true;
					score2 += 1;
				}
				system("pause");
			}
			
			
		}while(!isExit);
		
		isExit = false;
		
		do
		{
			system("CLS");
			BoardTitle();
			cout << "PLAYER 1 SCORE : " << score1 << " || PLAYER 2 SCORE : " << score2 << endl;
			cout << "Do you want to play again? ( y / n)\n";
			cin >> choice;
			if (choice == "y")
			{
				isExit = true;
			}
			else if (choice == "n")
			{
				loopExit = true;	
				isExit = true;
			}
			else
			{
				cout << "Invalid choice\n";
			}
		}while(!isExit);
	}while(!loopExit);
	
	system("pause");
	return 0;
}

void InitBoard(string board[][col])
{
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			board[j][i] = " .";
		}
	}
}

void DisplayBoard(string board[][col])
{
	cout << " ";
	for(int i = 0; i < col; i++)
	{
		cout << " " << i+1 << "|";
	}
	cout << endl;
	for (int i = 0; i < col; i++)
	{
		cout << i+1;
		for (int j = 0; j < row; j++)
		{
			cout << board[j][i] << "|";
		}
		cout << endl;
	}
}

void BoardTitle()
{
	cout << endl;
	cout << "=  BATTLESHIP  =" << endl;
	cout << endl;
}

void InitEnemyShip(int amount, int size)
{
	for (int i = 0; i < amount; i++)
	{
		int x = 0, y = 0;
		int check = 0;
		bool isExit = false;
		if (size > 1)
		{
			do
			{
				check = 0;
				int orientation = rand() % 2;
				
				if (orientation == 0)
				{
					x = rand() % (row - size);
					y = rand() % col;
				}
				else if (orientation == 1)
				{
					y = rand() % (col - size);
					x = rand() % row;
				}
				
				
				for (int j = 0; j < size; j++)
				{
					if(orientation == 0)
					{
						if(enemyBoard[x+j][y] == " E")
						{
							check += 1;
						}
					}
					else if(orientation == 1)
					{
						if(enemyBoard[x][y+j] == " E")
						{
							check +=1;
						}
					}
				}
				
				if(check == 0)
				{
					for (int j = 0; j < size; j++)
					{
						if(orientation == 0)
						{
							enemyBoard[x + j][y] = " E";
							isExit = true;
						}
						else if(orientation == 1)
						{
							enemyBoard[x][y+j] = " E";
							isExit = true;
						}
					}
				}
			}while(!isExit);
		}
		else
		{
			do
			{
				check = 0;
				isExit = false;
				x = rand() % row;
				y = rand() % col;
				
				if(enemyBoard[x][y] == " E")
				{
					check += 1;
				}
				
				if(check == 0)
				{
					enemyBoard[x][y] = " E";
					isExit = true;
				}
			}while(!isExit);
		}
	}
}

void InitPlayerShip(int amount, int size)
{
	bool isExit = false;
	
	for (int i = 0; i < amount; i++)
	{
		system("CLS");
		BoardTitle();
		DisplayBoard(playerBoard);
		int x = 0, y = 0;
		int check = 0;
		
		isExit = false;
		if (size > 1)
		{
			do
			{
				check = 0;
				int orientation = 0;
				cout << "Choose where to place your ships and its orientation. (0 = Horizontal Rightward, 1 = Vertical Downward)\n";
				
				do
				{
					cout << "Available ships left : " << amount - i << endl;
					cin >> x; cin >> y;
					cin >> orientation;
					
					x -= 1;
					y -= 1;
					
					if (orientation == 0)
					{
						if(x >= ((row + 1) - size))
						{
							cout << "Invalid choice\n";
						}
						else
						{
							isExit = true;
						}
					}
					else if (orientation == 1)
					{
						if(y >= ((col + 1) - size))
						{
							cout << "Invalid choice\n";
						}
						else
						{
							isExit = true;
						}
					}
				}while(!isExit);
				
				isExit = false;
				
				for (int j = 0; j < size; j++)
				{
					if(orientation == 0)
					{
						if(playerBoard[x+j][y] == " P")
						{
							check += 1;
						}
					}
					else if(orientation == 1)
					{
						if(playerBoard[x][y+j] == " P")
						{
							check +=1;
						}
					}
				}
				
				if(check == 0)
				{
					for (int j = 0; j < size; j++)
					{
						if(orientation == 0)
						{
							playerBoard[x + j][y] = " P";
							isExit = true;
						}
						else if(orientation == 1)
						{
							playerBoard[x][y+j] = " P";
							isExit = true;
						}
					}
				}
			}while(!isExit);
		}
		else
		{
			do
			{
				check = 0;
				isExit = false;
				
				do
				{
					cout << "Choose where to place your ships. \n";
					cout << "Available ships left : " << amount - i << endl;;
					cin >> x; cin >> y;
					
					x -= 1;
					y -= 1;
					
					if (x >= col)
					{
						cout << "Invalid choice\n";
					}
					else if (y >= row)
					{
						cout << "Invalid choice\n";
					}
					else
					{
						isExit = true;
					}
				}while(!isExit);
				
				isExit = false;
				
				if(playerBoard[x][y] == " P")
				{
					check += 1;
				}
				
				if(check == 0)
				{
					playerBoard[x][y] = " P";
					isExit = true;
				}
			}while(!isExit);
		}
	}
}

void PlayerAttack()
{
	int x = 0, y = 0;
	bool isExit = false;
	int hit1 = 0;
	
	do
	{
		cout << "Choose where to attack your enemy\n";
		cin >> x; cin >> y;
		
		if(x > col)
		{
			cout << "Invalid choice\n";
		}
		else if(y > row)
		{
			cout << "Invalid choice\n";
		}
		else if(x <= 0 || y <= 0)
		{
			cout << "Invalid choice\n";
		}
		else
		{
			isExit = true;
		}
	}while(!isExit);
	
	isExit = false;
	
	x -= 1; y -= 1;
	
	if (enemyBoard[x][y] == " E")
	{
		cout << "You hit the enemy at x : " << x + 1 << " y : " << y + 1 << endl;
		battleboard[x][y] = " *";
		hit1 = 1;
	}
	if (enemyBoard[x][y] == " .")
	{
		cout << "Your target missed. There was no enemy there\n";
		battleboard[x][y] = " o";
	}
	system("pause");
}

void EnemyAttack()
{
	int x= rand() % (col - 1);
	int y= rand() % (row - 1); 
	int hit2 = 0;
	
	if (playerBoard[x][y] == " P")
	{
		cout << "You were hit at x : " << x << " y : " << y << endl;
		playerBoard[x][y] = " *";
		hit2 = 1;
	}
	else
	{
		cout << "Your enemy missed his mark" << endl;
	}
	system("pause");
}