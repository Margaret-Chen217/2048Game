#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 4
#define MARK 2048
#define WIDTH 110
#include <conio.h>
int board[SIZE][SIZE]= {0};

void InitBoard();
void DrawBoard();
void AddChess();
char GetInput();
void MoveChess(char Input);
int ShowResult();
void CleanBoard();
void MoveChessLeft();
void MoveChessRight();
void MoveChessUp();
void MoveChessDown();
void SlideArray();
void RotateBoard();
void PrintRule();
int FindPairDown();
int Win();
int HasEmpty();
int JudgeResult();
void move();
//void save();
int main() {
	InitBoard();
	DrawBoard();
	PrintRule();
	while(1) {
		char Input = GetInput();
		MoveChess(Input);
		AddChess();
		DrawBoard();
		PrintRule();
		int GameEnded = JudgeResult();//1 for ended,0 for not
		if (GameEnded) {
			if (!ShowResult()){//0 for quit
			return 0;
		}
	}
}
}

void InitBoard() {
	CleanBoard();
	srand(time(NULL));
	AddChess();
	AddChess();
}
void CleanBoard() {
	for (int i=0; i<SIZE; i++) {
		for (int j=0; j<SIZE; j++) {
			board[i][j]=0;
		}
	}
}
void AddChess() {
	int a = rand();
	int b = rand();
	int i,j;
	i = a%4;
	j = b%4;
	while(board[i][j]!=0) {
		a*=123;
		b*=122;
		i = a%4;
		j = b%4;
	}
	if (a%400<=300) {
		board[i][j]=2;
	} else
		board[i][j]=4;

	//printf("AddChess\n");
}
void PrintRule() {
	printf("'w'for UP\n");
	printf("'s'for DOWN\n");
	printf("'a'for LEFT\n");
	printf("'d'for RIGHT\n");
}
void DrawBoard() {
	system("cls");
	int len1=19;
	//for (int i=1; i<=(WIDTH-len1+1)/2; i++) {
	//	printf(" ");
	//}
	printf("**** GAME 2048 ****\n");
	for (int i=0; i<SIZE; i++) {
		for (int j=0; j<SIZE; j++) {
			if (board[i][j]!=0)
				printf("[%4d]",board[i][j]);
			else
				printf("[%4s]"," ");
		}
		printf("\n\n");
	}
}
char GetInput() {
	printf("Please enter a command:");
	char input;
	while (input=getch()) {
		if (input=='a'||input=='s'||input=='w'||input=='d'||input=='\n')
			break;
		if (input!='\n')
			while (getch() != '\n');
		return input;
	}

}
void MoveChess(char Input) {
	switch (Input) {
		case 'a':
			MoveChessLeft();
			break;
		case 's':
			MoveChessDown();
			break;
		case 'w':
			MoveChessUp();
			break;
		case 'd':
			MoveChessRight();
			break;
	}
}
void MoveChessDown() {
	SlideArray();
}
void MoveChessRight() {
	RotateBoard();
	MoveChessDown();
	RotateBoard();
	RotateBoard();
	RotateBoard();
}
void MoveChessUp() {
	RotateBoard();
	RotateBoard();
	MoveChessDown();
	RotateBoard();
	RotateBoard();
}
void MoveChessLeft() {
	RotateBoard();
	RotateBoard();
	RotateBoard();
	MoveChessDown();
	RotateBoard();
	
}

void SlideArray() {
	for (int j=0; j<SIZE; j++) {
		move();
		for (int i=SIZE-1; i>0; i--) {
			if (board[i-1][j]==board[i][j]) {
				board[i][j]*=2;
				board[i-1][j]=0;
				i--;
			}
		}
		move();
	}

}
void move() {
	for (int j=0; j<SIZE; j++) {
		for (int i=SIZE-1; i>0; i--) {
			if (board[i][j]==0) {
				board[i][j]=board[i-1][j];
				board[i-1][j]=0;
			}
		}
	}

}
void RotateBoard() { //clockwise
	int arr[SIZE][SIZE];
	for (int i=0; i<SIZE; i++) {
		for (int j=0; j<SIZE; j++) {
			arr[j][3-i]=board[i][j];

		}
	}
	for (int i=0; i<SIZE; i++) {
		for (int j=0; j<SIZE; j++) {
			board[i][j]=arr[i][j];
		}
	}
}
int HasEmpty() {
	int isEmpty=0;
	for (int i=0; i<SIZE; i++) {
		for (int j=0; j<SIZE; j++) {
			if (board[i][j]==0);
			isEmpty=1;
		}
	}
	if (isEmpty)
		return 1;
	else
		return 0;
}
int FindPairDown() {
	for (int i=0; i<SIZE; i++) {
		for (int j=0; j<SIZE; j++) {
			if (board[i][j]==board[i][j+1]) {
				return 1;
			}
		}
	}
	return 0;
}

int Win() {
	for (int i=0; i<SIZE; i++) {
		for (int j=0; j<SIZE; j++) {
			if (board[i][j]==MARK) {
				return 1;
			}
		}
	}
	return 0;
}
int ShowResult() { 
	if (Win()) {
		printf("WIN\n");
		printf("Well Down!\nYour have got a 2048 and won the game.\n");
	} else if (!HasEmpty&&!FindPairDown) {
		printf("GAME OVER\n");
		printf("Oh!There is no empty in the board!\nYou have lose the game.\n");
	}
	printf("Do you want to play again?\n");
	printf("'q'for QUIT   'a'for PLAY AGAIN\n");
	int c = getch();
	if (c=='a'){
		CleanBoard();
		DrawBoard(); 
		return 1;
	} 
	else if (c=='q'){
		return 0;
	}
}
int JudgeResult() {
	if (Win())
		return 1;
	else if (!HasEmpty()&&!FindPairDown())
		return 1;
	else
		return 0;
}
