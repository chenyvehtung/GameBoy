#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <unistd.h> //for usleep
#include <pthread.h> 
#include <termios.h>     //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO
using namespace std;

#define GAMESIZE 20
#define MAXLEN 200
#define APPLE 2
#define SNAKEHEAD 3
#define SNAKEBODY 4
#define SNAKETAIL 5
#define WALL 6
#define SPACE 7
#define SHOWAPPLE " $"
#define SHOWHEAD " @"
#define SHOWBODY " O"
#define SHOWTAIL " >"
#define SHOWWALL " #"
#define SHOWSPACE "  "
#define UP 65  //A
#define DOWN 66 //B
#define LEFT 68 //D
#define RIGHT 67 //C

struct node{
	int x;
	int y;
}snakePos[MAXLEN]; 

//if you don't give the row size, you will get problem! Try it.
int game[GAMESIZE][GAMESIZE] = {SPACE};
int headIndex = 3;
int tailIndex = 0;
char direction = RIGHT;
pthread_t snakeThread = 0;
pthread_mutex_t snakeLock;
int gameLevel = 1;
int TURNTIME = 500000; //500ms
int snakeLen = 4;

void createApple() {
	srand(time(0));
	int x, y;
	do {
		x = rand()%GAMESIZE + 1;
		y = rand()%GAMESIZE + 1;
	} while(game[x][y] != SPACE);
	game[x][y] = APPLE;
}

void gameInit() {
	for (int i = 0; i < GAMESIZE; i++) {
		for (int j = 0; j < GAMESIZE; j++) {
			if (i == 0 || i == GAMESIZE-1 || j == 0 || j == GAMESIZE-1) 
				game[i][j] = WALL;
			else
				game[i][j] = SPACE;
		}
	}

	for (int k = 0; k < 4; k++) {
		snakePos[k].x = 1;
		snakePos[k].y = k+1;
		game[1][k+1] = SNAKEBODY;
	}

	game[snakePos[tailIndex].x][snakePos[tailIndex].y] = SNAKETAIL;
	game[snakePos[headIndex].x][snakePos[headIndex].y] = SNAKEHEAD;

	createApple();
}

void gameShow() {
	system("clear");
	for (int i = 0; i < GAMESIZE; i++) {
		for (int j = 0; j < GAMESIZE; j++) {
			switch(game[i][j]) {
				case APPLE: printf(SHOWAPPLE); break;
				case SPACE: printf(SHOWSPACE); break;
				case WALL: printf(SHOWWALL); break;	
				case SNAKEHEAD: printf(SHOWHEAD); break;
				case SNAKEBODY: printf(SHOWBODY); break;
				case SNAKETAIL: printf(SHOWTAIL); break;
				default: printf(" %c", game[i][j]); break;
			}
		}
		if (i == 4)
			printf("  Level: %d", gameLevel);
		if (i == 5)
			printf("  Interval: %dms", TURNTIME/1000);
		if (i == 6)
			printf("  Snake Length: %d", snakeLen);
		printf("\n");
	}
}

node nextStep(char direct) {
	struct node tempNode;
	tempNode.x = snakePos[headIndex].x;
	tempNode.y = snakePos[headIndex].y;
	//x here represent Row, and y represents Column
	switch(direct) {
		case UP: tempNode.x--; break;
		case DOWN: tempNode.x++; break;
		case LEFT: tempNode.y--; break;
		case RIGHT: tempNode.y++; break;
		default: break;
	}
	return tempNode;
}

char reverseDire(char direct) {
	switch(direct) {
		case UP: return DOWN;
		case DOWN: return UP;
		case LEFT: return RIGHT;
		case RIGHT: return LEFT;
		default: return direct;
	}
}

//get char without Enter and ignore echo
//http://stackoverflow.com/questions/1798511/how-to-avoid-press-enter-with-any-getchar
char imdiChar() {
	static struct termios oldt, newt;

    /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
    tcgetattr( STDIN_FILENO, &oldt);
    /*now the settings will be copied*/
    newt = oldt;

    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL
    and ignore echo back*/
    newt.c_lflag &= ~(ICANON | ECHO);   
    //newt.c_lflag &= ~(ICANON);       

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    char tempChar = getchar();

    /*restore the old settings*/
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    return tempChar;
}

void* getDirection(void* arg) {
	while(1) {
		pthread_mutex_lock(&snakeLock);
		direction = imdiChar();
		if (direction == 'Q' || direction == 'q') {
			break;
		}
		pthread_mutex_unlock(&snakeLock);
	}
	pthread_exit(NULL);
}

void createThread() {
	int tempStatus;
	tempStatus = pthread_create(&snakeThread, NULL, getDirection, NULL);
	if (!tempStatus) {
		printf("Error: failed to create a thread");
	}
}

void waitThread() {
	if (snakeThread != 0) {
		pthread_join(snakeThread, NULL);
	}
}

int main() {
	gameInit();
	gameShow();
	struct node tempNode;
	createThread();
	while (1) {
		if (direction == 'Q' || direction == 'q') {
			break;
		}
		tempNode = nextStep(direction);
		int posX = tempNode.x;
		int posY = tempNode.y;
		int afterHead = (headIndex == 0) ? (MAXLEN - 1) : (headIndex-1);
		if (game[posX][posY] == APPLE || game[posX][posY] == SPACE || 
			game[posX][posY] == SNAKETAIL) {		
			//if it is an apple, enlarge the snake,create a new apple
			if (game[posX][posY] == APPLE) {
				snakeLen++;
				if (snakeLen % 4 == 0) {
					gameLevel++;
					if (TURNTIME > 100000) {
						TURNTIME -= 50000;
					}
				}
				createApple();
			}
			//if not, shove the snake's tail with one step
			else {
				game[snakePos[tailIndex].x][snakePos[tailIndex].y] = SPACE;
				tailIndex = (tailIndex+1)%MAXLEN;
				game[snakePos[tailIndex].x][snakePos[tailIndex].y] = SNAKETAIL;
			}

			//change the old snake head to snake body
			game[snakePos[headIndex].x][snakePos[headIndex].y] = SNAKEBODY;
			//make new snake head
			headIndex = (headIndex+1)%MAXLEN;
			snakePos[headIndex].x = posX;
			snakePos[headIndex].y = posY;
			game[posX][posY] = SNAKEHEAD;
 		}
 		//the reversal direction 
 		else if (posX == snakePos[afterHead].x && posY == snakePos[afterHead].y) {
 			direction = reverseDire(direction);
 			continue;
 		}
 		//wall or the snake itself, die
 		else {
 			char gameOver[10]="GAME*OVER";
 			for (int cnt = 0; cnt < 9; cnt++) {
 				game[GAMESIZE/2][cnt+5] = gameOver[cnt];
 			}
 			gameShow();
 			puts("Please input Q or q to quit.");
 			break;
 		}
 		
 		gameShow();
 		usleep(TURNTIME);
	}
	waitThread();
	return 0;
}
