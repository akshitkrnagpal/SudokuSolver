#include<iostream>
#include<windows.h>
#include<conio.h>

using namespace std;

int BOARD[9][9],solved=0;
void Start();
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// Prints the sudoku puzzle BEAUTIFULLY..!!
void Print(int A[9][9])
{
	system("cls");
	cout<<"\n\t_________________________________________";
	for(int i=0;i<9;i++)
	{
		cout<<"\n\t|            |             |             |";
		cout<<"\n\t| ";
		for(int j=0;j<9;j++)
		{
			if(A[i][j]==0)
				cout<<"  ";
			else
			{
				if(BOARD[i][j]!=0)
					SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE) , FOREGROUND_RED | FOREGROUND_GREEN );
				cout<<A[i][j];
				if(BOARD[i][j]!=0)
					SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE) , FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
				cout<<" ";
			}
			if(j%3==2)
				cout<<" |  ";
			else
				cout<<"  ";
		}
		if(i%3==2)
			cout<<"\n\t|____________|_____________|_____________|";
	}
}

//Checks if n can be place at A[i][j]
bool check(int A[9][9],int i,int j, int n)
{
	//Check Lines
	for(int x=0;x<9;x++)
	{
		if(A[i][x]==n || A[x][j]==n)
			return false;
	}
	//check Box
	for(int x= (i/3)*3 ; x < ((i/3)+1)*3 ; x++)
	{
		for(int y= (j/3)*3 ; y < ((j/3)+1)*3 ; y++)
		{
			if(A[x][y]==n)
				return false;
		}
	}
	// All Clear Dude..!!
	return true;
}

//Solves A[i][j]
void SolveCell(int A[9][9],int i,int j,int moving=1)
{
	// If i and j goes out of scope then there exists no solution for that sudoku
	if(i>8 || j>8 || i<0 || j<0)
	{
		Print(A);
		int offset =52;
		gotoxy(offset,3);
		cout<<" SUDOKU CANNOT BE SOLVED ";
		gotoxy(offset,5);
		cout<<" The sudoku puzzle you  ";
		gotoxy(offset,6);
		cout<<" provided is wrong or has";
		gotoxy(offset,7);
		cout<<" no solution.";
		Start();
		return;
	}
	
	// Skip cell where number is fixed
	if(BOARD[i][j]!=0)
	{
		if(moving==-1)
		{
			int id=i*9 + j -1;
			i=id/9;
			j=id%9;
			SolveCell(A,i,j,-1);
		}
		return;
	}
	
	// Places a valid number in A[i][j] 	
	bool placed=false;
	for(int x=A[i][j]+1 ; x<=9 && placed==false ;x++)
	{
		
		if(check(A,i,j,x)==true)
		{
			A[i][j]=x;
			placed=true;
		}
	}
	
	// If none can be placed, change the number of previous cell and 
	// then again try to place in current cell 
	if(placed==false)
	{
		A[i][j]=0;
		int id=i*9 + j -1;
		i=id/9;
		j=id%9;
		SolveCell(A,i,j,-1);
		i=(id+1)/9;
		j=(id+1)%9;
		SolveCell(A,i,j);
	}
	//Print(A);
	return;
	
	
}

// Solves each cell one by one
void SolveSudoku(int A[9][9])
{
	for(int x=0; x<9 ;x++)
	{
		for(int y=0; y<9; y++)
		{
			SolveCell(A,x,y);
		}	
	}
}

//Prints Logo
void PrintLogo()
{
	cout<<"\n\t      /======        __    _                    ";
	cout<<"\n\t     //         | |  | \\  / \\  |_/  | |         ";
	cout<<"\n\t    //          \\_/  |_/  \\_/  | \\  \\_/         ";
	cout<<"\n\t   /======/                                     ";
	cout<<"\n\t        //    _             __   _              ";
	cout<<"\n\t       //    / \\  |  \\  /  |_   |_)             ";
	cout<<"\n\t ======/     \\_/  |_  \\/   |__  | \\             ";
	cout<<"\n\n\n\t                                           - Akshit Kr Nagpal\n\n";  
}

void DisplayInstructions()
{
	int offset =52;
	gotoxy(offset,3);
	cout<<" INSTRUCTIONS ";
	gotoxy(offset,5);
	cout<<" Press \'0\' to leave cell";
	gotoxy(offset,6);
	cout<<" blank or the cell\'s ";
	gotoxy(offset,7);
	cout<<" corresponding number.";
	gotoxy(offset,9);
	cout<<" Press \'backspace\' to ";
	gotoxy(offset,10);
	cout<<" go back and edit.";

}
//Input Sudoku
void InputSudoku(int A[9][9])
{
	system("cls");
	Print(A);
	DisplayInstructions();
	int offsetx=10,offsety=3,x;
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			cout<<" \b";
			gotoxy(offsetx+(j*4)+(2*(j/3)),offsety+(i*2)+(i/3));
			cout<<"_\b";
			x=(getch()- 48);
			if(x==-40 && (i+j!=0))
			{
				if(j==0)
				{
					i--;
					j=8;
				}
				else
					j--;
				BOARD[i][j]=0;		
			}
				
			if(x>=0 && x<=9)
			{
				BOARD[i][j]=x;
				if(x!=0)
				{
					SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE) , FOREGROUND_RED | FOREGROUND_GREEN );
					cout<<BOARD[i][j];
					SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE) , FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
				}
				else
				{
					cout<<" ";
				}
			}
			else
			{
				if(j==0)
				{
					i--;
					j=8;
				}
				else
					j--;
			}
			//Print(BOARD);
			//DisplayInstructions();		
		}
	}
	for(int i=0;i<81;i++)
	{
		if( check(A,i/9,i%9,BOARD[i/9][i%9]) ==true || BOARD[i/9][i%9]==0 )
		{
			A[i/9][i%9]=BOARD[i/9][i%9];
		}
		else
		{
			Print(BOARD);
			int offset =52;
			gotoxy(offset,3);
			cout<<" WRONG PUZZLE ";
			gotoxy(offset,5);
			cout<<" Don\'t mess with me. ";
			gotoxy(offset,6);
			cout<<" I know that its a wrong";
			gotoxy(offset,7);
			cout<<" puzzle.";
			gotoxy(offset,9);
			cout<<" Don\'t irritate me.  ";
			return;
		}
	}
	
	SolveSudoku(A);
	Print(A);
	
	int offset =52;
	gotoxy(offset,3);
	cout<<" SOLVED SUDOKU ";
	gotoxy(offset,5);
	cout<<" The solution of sudoku ";
	gotoxy(offset,6);
	cout<<" puzzle you provided";
	gotoxy(offset,7);
	cout<<" has been displayed. ";
}

void Start()
{
	int A[9][9];/*={ 
				  6,0,0,  0,0,0,  0,0,2,
				  0,9,2,  0,0,0,  3,5,0,
				  0,0,8,  2,0,9,  6,0,0,
				  
				  0,0,5,  7,0,4,  2,0,0,
				  0,3,0,  0,0,0,  0,8,0,
				  0,0,7,  6,0,2,  5,0,0,
				  
				  0,0,3,  1,0,6,  9,0,0,
				  0,2,1,  0,0,0,  8,7,0,
				  4,0,0,  0,0,0,  0,0,3
				};*/
				
	
	do
	{
		for(int i=0;i<81;i++)
		{	
			A[i/9][i%9]=0;
			BOARD[i/9][i%9]=A[i/9][i%9];
		}
		system("cls");
		cout<<"\n\n";
		PrintLogo();
		cout<<"\n\n\n\t  Press any key to continue ...";
		getch();
		InputSudoku(A);
	} while(getch());
}

// Main Function
int main()
{
	Start();
}
