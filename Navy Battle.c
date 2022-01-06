/*
AUTHOR: Patricia Brenny Ribeiro
Computer Engineering undergraduate - UNIFEI
NAVY BATTLE GAME - SINGLE PLAYER
January 6th, 2022
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define LIN 15
#define COL 30
#define RED SetColor(4);
#define GREEN SetColor(2);
#define YELLOW SetColor(6);
#define WHITE SetColor(15);
#define GREY SetColor(8);
#define BLUE SetColor(1);

typedef enum{true, false}bool;
    char mask[LIN][COL];
    char board[LIN][COL];
    int lin,col;
    int pts=0,bombs=120;
    bool gameover = false;

void fillBoard(){
    int i,j;
    for(i=0;i<LIN;i++){
        for(j=0;j<COL;j++){
            mask[i][j] = '?';
            board[i][j] = '~';
        }//end for
    }//end for
    return;
}//end fill

void printBoard(){
    int i,j;
    WHITE
    printf("   0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2  \n");
    printf("                       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 \n");
    printf("   ------------------------------------------------------------\n");
    for(i=0;i<LIN;i++){
        printf("%2d|", i);
        for(j=0;j<COL;j++){

            switch(mask[i][j]){//chose color
            case '?':
                YELLOW
                break;
            case '~':
                BLUE
                break;
            default:
                GREY
                break;
            }//end switch

            printf("%c ",mask[i][j]);
        }//end for
        WHITE
        printf("|\n");
    }//end for
    printf("   ------------------------------------------------------------\n");
    WHITE
    return;
}//end print

void placeBoats(){
    int lin,col,i,j,k;
    char submarine1[6] = "~~_f_~";
    char submarine2[6] = "x(___)";
    char boat1[8] = "~___R___";
    char boat2[8] = "x\\_____/";
    srand(time(NULL));


    //placing submarines
    for(i=0;i<3;i++){
        lin = rand()%(15 - 2);
        col = rand()%(30 - 7) ;
        if((board[lin][col] == '~')&&(board[lin][col+6] == '~')&&(board[lin+1][col] == '~')&&(board[lin+1][col+6] == '~')){ //making sure its not off bounds
            for(k=0;k<6;k++){
                board[lin][col] = submarine1[k];
                board[lin+1][col] = submarine2[k];
                col++;
            }//end for
        }else{
            i--;
        }//end else
    }//end for

    //placing smaller boats
    for(i=0;i<3;i++){
        lin = rand()%15 - 2;
        col = rand()%25 - 8;
        if((board[lin][col] == '~')&&(board[lin][col+8] == '~')&&(board[lin+1][col] == '~')&&(board[lin+1][col+8] == '~')){
            for(k=0;k<8;k++){
                board[lin][col] = boat1[k];
                board[lin+1][col] = boat2[k];
                col++;
            }//end for
        }else{
            i--; //if off bombs overwrite information
        }//end else
    }//end for

}//end if

void jogada(){
    int lin = 99,col = 99;
    while((lin > 15 || lin < 0)||(col > 30) || (col < 0)||(mask[lin][col]!= '?')){ //doesnt allow fowl play
        printf("\nType the coordinates of the attack (lin col): ");
        scanf("%d %d",&lin,&col);
        if((lin > 15 || lin < 0)||(col > 30) || (col < 0)||(mask[lin][col]!= '?')){
            RED
            printf("\n Invalid move. \n");
            WHITE
        }//end if
    }//end while
    mask[lin][col] = board[lin][col];
    RED
    printf("\n ---------------- Press button to send bomb -------------------");
    getch();
    bombs--;
    switch(board[lin][col]){
    case '~':
        BLUE
        printf("\n ~~~~~~~~~~~~~~~~~~~~~     Splash!    ~~~~~~~~~~~~~~~~~~~~~\n");
        WHITE
        sleep(2);
        break;
    default: //anything else
        pts++;
        RED
        printf("\n ********************      BOOM!!!      *********************\n");
        WHITE
        sleep(2);
        break;
    }//end switch
    return;
}//end jogada

void SetColor(int ForgC){

     WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                 //Mask out all but the background attribute, and add in the forgournd     color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }

int main (int argc, char **argv){
    fillBoard();
    placeBoats();
    while(gameover == false){
        system("cls");
        printBoard();
        printf("Player #1: %d points and %d bombs left \n", pts,bombs);
        jogada();
        if((bombs == 0)&&(pts < 90)){ //if you ran out of bombs
            gameover = true;
            RED
            printf("\nYou lost! Bombs are over and enemies were not defeated. \n");
        }else if(pts == 90){ //if you conquered all points
            gameover = true;
            GREEN
            printf("\nYou win! All enemy ships were destroyed succesfully. \n");
        }//end else
    }//end while

    return 0;
}//end main
