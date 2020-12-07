/*
Name:Chen Wenlin
E-mail Adress:1852378928@qq.com
Date:2020.12.5
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 4
#define MARK 32
#include <conio.h>

int score = 0;
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
void RotateBoard();//Clockwise
void PrintRule();
int FindPairDown();
int Win();
int HasEmpty();
int HasPair();
int GameEnded();
void move();
void Save();
int Load();
void Hints();
int HasSame();
char GetInput_h();
int main() {
	InitBoard();
	DrawBoard();
	PrintRule();
	while(1) {
		char Input = GetInput();
		if (Input=='q')
			return 0;
		if (Input=='h') {
			Input = GetInput_h();
		}
		MoveChess(Input);
		while(HasEmpty()==0&&HasPair()==1) {
			printf("\nThe board is full!\nBut there is a pair,change a direction!\n");
			char Input = GetInput();
			MoveChess(Input);
		}
		AddChess();
		DrawBoard();
		PrintRule();
		if (GameEnded()) {
			if (!ShowResult()) { //0 for quit
				return 0;
			}
		}
	}
}

void InitBoard() {//judge if open a new game 
	srand(time(NULL));
	char input;
	printf("'N'for a new game\n'L'to load the latest memory\n");
	printf("Please enter a command:");
	while (input=getch()) {

		if (input=='N'||input=='L')
			break;
	}
	int LoadError = 1;
	if (input=='L')
		LoadError = Load();
	if (input=='N'||!LoadError) {
		CleanBoard();
		AddChess();
		AddChess();
	}
}
void CleanBoard() {
	for (int i=0; i<SIZE; i++) {
		for (int j=0; j<SIZE; j++) {
			board[i][j]=0;
		}
	}
}
void AddChess() {//add one chess
	int i,j;
	do {
		i = rand()%4;
		j = rand()%4;
	} while(board[i][j]!=0);

	if (rand()%400<=300) {
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
	printf("'h'for HINTS\n");
	printf("'q'for Save and Quit\n");
	printf("Score:%d\n",score);
}

void DrawBoard() {
	system("cls");
	int len1=19;
	printf("  **** GAME 2048 ****\n\n");
	for (int i=0; i<SIZE; i++) {
		for (int j=0; j<SIZE; j++) {
			if (board[i][j]!=0) {
				if(board[i][j]<10)
					printf("[ %d  ]",board[i][j]);
				else if(board[i][j]<100)
					printf("[ %d ]",board[i][j]);
				else if(board[i][j]<1000)
					printf("[%d ]",board[i][j]);
				else if(board[i][j]<10000)
					printf("[%d]",board[i][j]);
			} else
				printf("[%4s]"," ");
		}
		printf("\n\n");
	}
}

char GetInput() {
	char input;
	printf("Please enter a command:");
	while (input=getch()) {
		if (input=='a'||input=='s'||input=='w'||input=='d'||input=='q'||input=='h')
			break;
	}
	if (input=='q') {
		Save();
	}
	if (input=='h') {
		Hints();
	}
	return input;
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
				score += board[i][j]*2;
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
void RotateBoard() { //Clockwise
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
			if (board[i][j]==0)
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
		for (int j=0; j<SIZE-1; j++) {
			if (board[i][j]==board[i][j+1]&&board[i][j]!=0) {
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
		printf("WIN\nScore:%d\n",score);
		printf("Well Down!\nYour have got a 2048 and won the game.\n");
	} else if (!HasEmpty()&&!FindPairDown()) {
		printf("GAME OVER\nScore:%d\n",score);
		printf("Oh!There is no empty in the board!\nYou have lose the game.\n");
	}
	printf("Do you want to play again?\n");
	printf("'q'for QUIT   'a'for PLAY AGAIN\n");
	int input2;
	while (input2=getch()) {
		if (input2=='a'||input2=='q')
			break;
	}
	if (input2=='a') {
		InitBoard();
		DrawBoard();
		PrintRule();
		return 1;
	} else if (input2=='q') {
		printf("\nOK!BYE!\n");
		return 0;
	}
}
int HasPair() {
	int a = FindPairDown();
	RotateBoard();
	int b = FindPairDown();
	RotateBoard();
	RotateBoard();
	RotateBoard();
	if (a==1||b==1)
		return 1;
	else
		return 0;
}
int GameEnded() {//1 for ended; 0 for not
	if (Win())
		return 1;
	else if (HasEmpty()==0&&HasPair()==0)
		return 1;
	else
		return 0;
}
void Save() {//file
	FILE *file = fopen("save.bin","wb");
	if(file == NULL) {
		printf("save error!\n");
	}
	fwrite(board, sizeof board[0][0], SIZE*SIZE, file);
	fprintf(file , "%d" , score);
	fclose(file);
	printf("\n\nSuccessfully Save\n");
}
int Load() {
	FILE *file2 = fopen("save.bin","rb");
	fread(board, sizeof board[0][0], SIZE*SIZE, file2);
	fscanf(file2 , "%d" , &score);
	fclose(file2);
	return 1;
}
void Hints() {
	int board2[SIZE][SIZE];
	for(int i=0; i<SIZE; i++) {
		for (int j=0; j<SIZE; j++) {
			board2[i][j]=board[i][j];
		}
	}
	if (!HasSame()) {
		RotateBoard();
		if (HasSame()) {
			printf("'a'or'd'\n");
		} else
			printf("There is no number can be combined.\n");
		RotateBoard();
		RotateBoard();
		RotateBoard();
	} else {
		printf("'w'or's'\n");
	}
	for(int i=0; i<SIZE; i++) {
		for (int j=0; j<SIZE; j++) {
			board[i][j]=board2[i][j];
		}
	}


}
int HasSame() {
	int comp,comp1;
	int is_zero=1;
	int hassame=0;
	for (int j=0; j<SIZE; j++) {

		for (int i=0; i<SIZE-1; i++) {
			if (board[i][j]!=0) {
				comp=board[i][j];
				for (int k=i+1; k<SIZE; k++) {
					if (board[k][j]==0) {
						is_zero=0;
					} else if(board[k][j]==comp&&is_zero==1) {
						hassame=1;
						goto label;
					} else
						break;
				}
			}
		}
	}
label:
	if (hassame)
		return 1;
	else
		return 0;
}
char GetInput_h() {//after giving a hint,cannot get a hint again
	char input;
	printf("Please enter a command:");
	while (input=getch()) {
		if (input=='a'||input=='s'||input=='w'||input=='d'||input=='q')
			break;
	}
	if (input=='q') {
		Save();
	}
	return input;
}
