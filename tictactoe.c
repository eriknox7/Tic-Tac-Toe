#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
typedef struct playerInfo {
    char name[25];
    char filledCells[5];
} player;
void initialiseFilledCells(player *ptr1, player *ptr2);
void welcome();
void assignPlayer(player *ptr1, player *ptr2);
int toss();
void assignSymbol(player *ptr1, player *ptr2);
void initialPicture();
int runGame(player *ptr1, player *ptr2);
void setWinnerMatrix(char winnermatrix[] [3]);
int handlePlayerTurn(int filledCells, player *currentPlayer, player *ptr1, player *ptr2, char winnermatrix[] [3], char symbol);
char takeInput(player *ptr, char winnermatrix[] [3]);
int isAlreadyFilled(char winnermatrix[] [3], char cell);
void setFilledCells(player *ptr, char cell);
void editWinnerMatrix(char winnermatrix[] [3], char cell, char symbol);
void displayPicture(player *ptr1, player *ptr2);
int isPresent(player *ptr1, player *ptr2, char key);
int winnerDetermined(int filledCells, char winnermatrix[] [3]);
int isWinner(char winnermatrix[] [3]);
int checkHorizontal(char winnermatrix[] [3]);
int checkVertical(char winnermatrix[] [3]);
int checkDiagonal(char winnermatrix[] [3]);
void printWinner(player *ptr1, player *ptr2, int winner);
void spaces();
void Yellow();
void Green();
void Red();
void Blue();
void purple();
void ResetColor();
int main () {
    int winner;
    player p1, p2;
    initialiseFilledCells(&p1, &p2);
    welcome();
    assignPlayer(&p1, &p2);
    assignSymbol(&p1, &p2);
    initialPicture();
    winner = runGame(&p1, &p2);
    printWinner(&p1, &p2, winner);
    return 0;
}
void initialiseFilledCells(player *ptr1, player *ptr2) {
    for(int i=0; i<5; i++) {
        ptr1->filledCells[i] = ptr2->filledCells[i] = '0';
    }
}
void welcome() {
    Red();
    printf("WELCOME TO TIC-TAC-TOE GAME!");
    spaces();
}
void assignPlayer(player *ptr1, player *ptr2) {
    char name1[25], name2[25];
    Blue();
    printf("ENTER THE NAME OF THE PLAYER 1: ");
    Green();
    gets(name1);
    Blue();
    printf("ENTER THE NAME OF THE PLAYER 2: ");
    Green();
    gets(name2);
    ResetColor();
    if(toss()) {
        strcpy(ptr1->name, name1);
        strcpy(ptr2->name, name2);
    } else {
        strcpy(ptr1->name, name2);
        strcpy(ptr2->name, name1);
    }
    spaces();
}
int toss() {
    srand(time(NULL));
    return rand()%2;
}
void assignSymbol(player *ptr1, player *ptr2) {
    Yellow();
    printf("%s OWNS THE SYMBOL ", ptr1->name);
    Red();
    printf("\"O\"\n");
    Yellow();
    printf("%s OWNS THE SYMBOL ", ptr2->name);
    Red();
    printf("\"X\"\n");
}
void initialPicture() {
    char c;
    FILE *fptr = fopen("map.txt", "r");
    while((c = fgetc(fptr))!=EOF) {
        if(!(c >= '0' && c <= '9')) {
            Yellow();
            printf("%c", c);
            ResetColor();
        } else {
            printf("%c", c);
        }
    }
    fclose(fptr);
}
int runGame(player *ptr1, player *ptr2) {
    int filledCells = 0;
    char winnermatrix[3] [3];
    setWinnerMatrix(winnermatrix);
    while(filledCells<9) {
        filledCells = handlePlayerTurn(filledCells, ptr1, ptr1, ptr2, winnermatrix, 'O');
        if(winnerDetermined(filledCells, winnermatrix)) {
            return 1;
        }
        if(filledCells < 9) {
            filledCells = handlePlayerTurn(filledCells, ptr2, ptr1, ptr2, winnermatrix, 'X');
            if(winnerDetermined(filledCells, winnermatrix)) {
                return 2;
            }
        }
    }
    return 0;
}
void setWinnerMatrix(char winnermatrix[] [3]) {
    int i, j;
    char element = '1';
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            winnermatrix[i] [j] = element++;
        }
    }
}
int handlePlayerTurn(int filledCells, player *currentPlayer, player *ptr1, player *ptr2, char winnermatrix[] [3], char symbol) {
    char cell;
    cell = takeInput(currentPlayer,winnermatrix);
    setFilledCells(currentPlayer, cell);
    editWinnerMatrix(winnermatrix, cell, symbol);
    system("cls");
    displayPicture(ptr1, ptr2);
    return ++filledCells;
}
char takeInput(player *ptr, char winnermatrix[] [3]) {
    int cell;
    Blue();
    printf("%s, ENTER THE CELL NO: ", ptr->name);
    while(1) {
        cell = 0;
        fflush(stdin);
        Green();
        scanf("%d", &cell);
        if((cell < 1 || cell > 9)) {
            Red();
            printf("INVALID INPUT, ENTER AGAIN: ");
        } else if(isAlreadyFilled(winnermatrix, cell+'0')) {
            Red();
            printf("CELL ALREADY FILLED, ENTER AGAIN: ");
        } else {
            Beep(1500, 250);
            return cell+'0';
        } 
    }
}
int isAlreadyFilled(char winnermatrix[] [3], char cell) {
    int i, j;
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            if(winnermatrix[i] [j] == cell) {
                return 0;
            }
        }
    }
    return 1;
}
void setFilledCells(player *ptr, char cell)  {
    int i=0;
    while(ptr->filledCells[i] != '0') {
        i++;
    }
    ptr->filledCells[i] = cell;
}
void editWinnerMatrix(char winnermatrix[] [3], char cell, char symbol) {
    int i, j, flag = 0;
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            if(winnermatrix[i] [j] == cell) {
                winnermatrix[i] [j] = symbol;
                flag = 1;
                break;
            }
        }
        if(flag) {
            break;
        }
    }
}
void displayPicture(player *ptr1, player *ptr2) {
    char key;
    FILE *fptr = fopen("map.txt", "r");
    while((key = fgetc(fptr))!=EOF) {
        if(key >= '1' && key <= '9') {
            if(isPresent(ptr1, ptr2, key) == 1) {
                Red();
                printf("O");
            } else if(isPresent(ptr1, ptr2, key) == 2) {
                Green();
                printf("X");
            } else {
                ResetColor();
                printf("%c", key);
            }
        } else {
            Yellow();
            printf("%c", key);
        }
    }
    fclose(fptr);
}
int isPresent(player *ptr1, player *ptr2, char key) {
    int i=0;
    while(ptr1->filledCells[i] != '0' && i<5) {
        if(ptr1->filledCells[i] == key) {
            return 1;
        }
        i++;
    }
    i=0;
    while(ptr2->filledCells[i] != '0' && i<5) {
        if(ptr2->filledCells[i] == key) {
            return 2;
        }
        i++;
    }
    return 0;
}
int winnerDetermined(int filledCells, char winnermatrix[] [3]) {
    if(filledCells >= 5) {
        if(isWinner(winnermatrix)) {
            return 1;
        }
    }
    return 0;
}
int isWinner(char winnermatrix[] [3]) {
    if(checkHorizontal(winnermatrix) || checkVertical(winnermatrix) || checkDiagonal(winnermatrix)) {
        return 1;
    }
    return 0;
}
int checkHorizontal(char winnermatrix[] [3]) {
    for(int i=0; i<3; i++) {
        if(winnermatrix[i] [0] == winnermatrix[i] [1]) {
            if(winnermatrix[i] [1] == winnermatrix[i] [2]) {
                return 1;
            }
        }
    }
    return 0;
}
int checkVertical(char winnermatrix[] [3]) {
    char tempmatrix[3] [3];
    int i, j;
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            tempmatrix[i] [j] = winnermatrix[j] [i];
        }
    }
    for(int i=0; i<3; i++) {
        if(tempmatrix[i] [0] == tempmatrix[i] [1]) {
            if(tempmatrix[i] [1] == tempmatrix[i] [2]) {
                return 1;
            }
        }
    }
    return 0;
}
int checkDiagonal(char winnermatrix[] [3]) {
    if(winnermatrix[0] [0] == winnermatrix[1] [1]) {
        if(winnermatrix[1] [1] == winnermatrix[2] [2]) {
            return 1;
        }
    }
    if(winnermatrix[0] [2] == winnermatrix[1] [1]) {
        if(winnermatrix[1] [1] == winnermatrix[2] [0]) {
            return 1;
        }
    }
    return 0;
}
void printWinner(player *ptr1, player *ptr2, int winner) {
    purple();
    if(winner == 1) {
        printf("%s IS THE WINNER.\n", ptr1->name);
    } else if(winner == 2) {
        printf("%s IS THE WINNER.\n", ptr2->name);
    } else {
        printf("IT'S A DRAW, BETTER LUCK NEXT TIME.\n");
    }
    Beep(1500, 1500);
    ResetColor();
}
void spaces() {
    printf("\n\n\n");   
}
void Yellow() {
    printf("\033[0;33m");
}
void Green() {
    printf("\033[0;32m");
}
void Red() {
    printf("\033[1;31m");
}
void Blue() {
    printf("\033[0;34m");
}
void purple() {
    printf("\033[0;35m");
}
void ResetColor() {
    printf("\033[0m");
}