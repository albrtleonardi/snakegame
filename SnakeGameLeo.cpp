#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20

//Kalau bisa fix bug [yang daniel ngomong]
//Kalau ada username sama, update di file

struct playerData{
	char username[101];
	int userScore;
};

playerData dat[101];

int numScore;
int i,j;
int height = HEIGHT;
int width = WIDTH;
int gameOver;
int out;
int x, y, fruitX, fruitY, score;
int tailX[100];
int tailY[100];
int nTail;

enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
enum eDirection dir;

void setup(){
	gameOver = 0;
	out = 0;
	
	x = width/2;
	y = height/2;
	
	fruitX = rand() % width;
	fruitY = rand() % height;
	
	score = 0;
	nTail = 0;
	
	dir = STOP;
}

void drawMap(){
	printf("\033[0;0H");
	
	for(i = 0; i<width + 2; i++) 
		printf("#"); 
	printf("\n");
	
	for(i = 0; i<height; i++){
		for(j = 0; j<width; j++){
			if(j == 0) 
				printf("#");
			
			if(i == y && j == x) 
				printf("0");
			else if(i == fruitY && j == fruitX) 
				printf("O");
			else{
				int printTail = 0;
				for(int k = 0; k<nTail; k++){
					if(tailX[k] == j && tailY[k] == i){
						printf("o");
						printTail = 1;
					}
				}
				if(!printTail) 
					printf(" ");
			}
			
			if(j == width - 1) 
				printf("#");
		}
		printf("\n");
	}
	
	for(i = 0; i<width + 2; i++) 
		printf("#"); 
	printf("\n");
	
	printf("Score: %d", score);
}

void controller(){
	if(_kbhit()){
		switch(_getch()){
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'x':
				out = 1;
				break;
		}
	}
}

void game(){
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	
	tailX[0] = x;
	tailY[0] = y;
	
	for(int i = 1; i<nTail; i++){
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	
	switch(dir){
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
	
	if(x >= width) x = 0; else if(x < 0) x = width - 1;
	if(y >= height) y = 0; else if(y < 0) y = height - 1;
	
	for(int i = 0; i<nTail; i++){
		if(tailX[i] == x && tailY[i] == y) gameOver = 1;
	}
	
	if(x == fruitX && y == fruitY){
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

void setRed(){
	printf("\033[0;31m"); 
}

void setBlack(){
	printf("\033[0m"); 
}

void art(){
	printf("   _____             _         _____                      _                \n");
	printf("  / ____|           | |       / ____|                    | |               \n");
	printf(" | (___  _ __   __ _| | _____| |  __  __ _ _ __ ___   ___| |     ___  ___  \n");
	printf("  \\___ \\| '_ \\ / _` | |/ / _ \\ | |_ |/ _` | '_ ` _ \\ / _ \\ |    / _ \\/ _ \\ \n");
	printf("  ____) | | | | (_| |   <  __/ |__| | (_| | | | | | |  __/ |___|  __/ (_) |\n");
	printf(" |_____/|_| |_|\\__,_|_|\\_\\___|\\_____|\\__,_|_| |_| |_|\\___|______\\___|\\___/ \n");
}

void howToPlay(){
	system("cls");
	setRed();
	printf("HOW TO PLAY\n\n");
	setBlack();
	printf("W --> Up\n");
	printf("S --> Down\n");
	printf("A --> Left\n");
	printf("D --> Right\n");
	printf("O --> Food\n");
	printf("0 --> Head\n");
	printf("o --> Body\n");
	printf("x --> Exit\n");
	printf("If you hit the body with the head, then the game will over.\n");
	printf("Thats all, enjoy the game! ^^\n");
	system("pause");
}

void bubbleSort(struct playerData player[], int score) {
    for (int i = 0; i < score; i++) {
        for (int j = 0; j < score - i - 1; j++) {
            if (player[j].userScore < player[j + 1].userScore) { 
                struct playerData temp = player[j];
                player[j] = player[j + 1];
                player[j + 1] = temp;
            }
        }
    }
}

void scoreBoard(){
	system("cls");
	FILE *fptr;
	
	fptr = fopen("scoreboard.txt", "r");
	
	numScore = 0;

	while(fscanf(fptr, "%s %d", dat[numScore].username, &dat[numScore].userScore) == 2){
		numScore++;
	}
	
	fclose(fptr);
	
	bubbleSort(dat, numScore);
		
	setRed();
	printf("SCOREBOARD\n");
	setBlack();
	printf("================================\n");
	printf("| %-20s | %s |\n", "Username", "Score");
	printf("================================\n");
	for(int i = 0; i < numScore; i++){
        printf("| %-20s | %-5d |\n", dat[i].username, dat[i].userScore);
    }
	printf("================================\n");
	
	printf("\n");
	
	system("pause");
}

void dashboard(){
	int ipt = 0;
	int selectedIdx = 0;
	
	while(true){
		system("cls");
		art();
		if(selectedIdx == 0){
			setRed();
			printf("Play Game\n");
			setBlack();
			printf("How to Play\n");
			printf("Scoreboards\n");
			printf("Exit");
		}else if(selectedIdx == 1){
			printf("Play Game\n");
			setRed();
			printf("How to Play\n");
			setBlack();
			printf("Scoreboards\n");
			printf("Exit");
		}else if(selectedIdx == 2){
			printf("Play Game\n");
			printf("How to Play\n");
			setRed();
			printf("Scoreboards\n");
			setBlack();
			printf("Exit");
		}else if(selectedIdx == 3){
			printf("Play Game\n");
			printf("How to Play\n");
			printf("Scoreboards\n");
			setRed();
			printf("Exit");
			setBlack();
		}
		
		ipt = getch();
		
		if(ipt == 'w' || ipt == 'W'){
			selectedIdx = (selectedIdx - 1 + 4) % 4;
		}else if(ipt == 's' || ipt == 'S'){
			selectedIdx = (selectedIdx + 1) % 4;
		}else if(ipt == '\r'){
			switch(selectedIdx){
				case 0:
					system("cls");
					setup();
    				while(!gameOver && !out){
    					drawMap();
    					controller();
    					game();
    					Sleep(20);
    					
    					if(gameOver){
    						printf("\n");
    						printf("Game Over\n");
    						system("pause");
    						
    						dat[numScore].userScore = score;
    						
    						printf("Input your username [No Spacing]: ");
							scanf("%s", dat[numScore].username);
    						
    						int userExists = 0;
							for(int i = 0; i<numScore; i++){
								if(strcmp(dat[i].username, dat[numScore].username) == 0){
									userExists = 1;
									dat[i].userScore = dat[numScore].userScore;
									break;
								}
							}
	
							FILE *fptr;
							fptr = fopen("scoreboard.txt", "a");
							
							if(!userExists){
								fprintf(fptr, "%s %d\n", dat[numScore].username, dat[numScore].userScore);	
							}
	
							fclose(fptr);
	
							printf("Score saved!\n");
							system("pause");
							system("cls");
						}else if(out){
							printf("\n");
							printf("Exiting the game...\n");
							system("pause");
							system("cls");
						}
					}
					break;
				case 1:
					howToPlay();
					break;
				case 2:
					scoreBoard();
					break;
				case 3:
					break;
			}
			
			if(selectedIdx == 3){
				break;
			} 
		}
	}
}

int main(){
	SMALL_RECT r;
    COORD      c;
    r.Top = 0;
    r.Left = 0;
    r.Bottom = HEIGHT + 10;
    r.Right = WIDTH + 10;
    c.X = WIDTH + 10;
    c.Y = HEIGHT + 10;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), c);
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &r);
    
    srand(time(NULL));
    
    dashboard();
	
	return 0;
}
