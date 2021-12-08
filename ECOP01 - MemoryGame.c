#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include<stdbool.h>
int main (int argc,char * argv[]){
    char tab[6][6],mask[6][6],vet[36];
    int i,j,count,lin,col,player1 = 0,player2 = 0,lin2,col2;
    bool move1,move2;
    srand(time(NULL));

    for (i=0;i<18;i++){ //vetor
        vet[i] = 65 + i;
        //printf("%c",vet[i]);
    }
    count = 18;
    for (i=0;i<18;i++){ //vetor
        vet[count] = 65 + i;
        count++;
       // printf("%c",vet[i]);
    }
    //printf("\n");
    printf("*** WELCOME TO THE MEMORY GAME *** \n \n");
    printf("   0  1  2  3  4  5 \n"); //mask print
    for (i=0;i<6;i++){
        printf(" %d",i);
        for (j=0;j<6;j++){
            mask[i][j] = ' ';
            tab[i][j] = mask[i][j];
            printf("[%c]",mask[i][j]);
        }
    printf("\n");
    }

    count = 0; //matrix ini
    while (count < 36){
        i = rand() % 6;
        j = rand() % 6;

        if (tab[i][j] == ' '){
            tab[i][j] = vet[count];
            count++;
        }
    }
    //player2 = 18; // test ending message

    i,j = 0,0;// gaming and players go here
    while ((player1 < 36) && (player2 < 36)){
        while (move1 == false){
            printf(" Player 1 select position 1 (lin,col): "); //use  move = true/ false to check if move is correct inside a repeat loop.
            scanf("%d,%d",&lin,&col);
            if ((lin > 5)|| (col>5)||(mask[lin][col]!=' ')){
                printf("Invalid move, try again. \n");
            }
            else{
                move1 = true;
            }
        }
        mask[lin][col] = tab[lin][col];

        printf("   0  1  2  3  4  5 \n"); //mask print end
        for (i=0;i<6;i++){
            printf(" %d",i);
            for (j=0;j<6;j++){
                printf("[%c]",mask[i][j]);
            }
        printf("\n");
        }
        while (move2 == false){
            printf(" Player 1 select position 2 (lin,col): ");
            scanf("%d,%d",&lin2,&col2);
            if ((lin2 > 5)|| (col2>5)||(mask[lin2][col2]!=' ')){
                printf("Invalid move, try again. \n");
            }
            else{
                move2 = true;
            }
        }
        mask[lin2][col2] = tab[lin2][col2];

        printf("   0  1  2  3  4  5 \n"); //mask print end
        for (i=0;i<6;i++){
            printf(" %d",i);
            for (j=0;j<6;j++){
                printf("[%c]",mask[i][j]);
            }
        printf("\n");
        }

        if (mask[lin2][col2] == mask[lin][col]){ //score 2
            player1 = player1 + 2;
        }
            else{
                mask[lin2][col2] = ' ';
                mask[lin][col] = ' ';
        }

        printf("   0  1  2  3  4  5 \n"); //mask print end
        for (i=0;i<6;i++){
            printf(" %d",i);
            for (j=0;j<6;j++){
                printf("[%c]",mask[i][j]);
            }
        printf("\n");
        }
        printf("\n *** Score: Player 1 = %d / Player 2 = %d *** \n \n", player1,player2);

        move1 = false; //restoring bool for new player
        move2 = false;
        while (move1 == false){
            printf(" Player 2 select position 1 (lin,col): "); //use  move = true/ false to check if move is correct inside a repeat loop.
            scanf("%d,%d",&lin,&col);
            if ((lin > 5)|| (col>5)||(mask[lin][col]!=' ')){
                printf("Invalid move, try again. \n");
            }
            else{
                move1 = true;
            }
        }
        mask[lin][col] = tab[lin][col];

        printf("   0  1  2  3  4  5 \n"); //mask print end
        for (i=0;i<6;i++){
            printf(" %d",i);
            for (j=0;j<6;j++){
                printf("[%c]",mask[i][j]);
            }
        printf("\n");
        }
        while (move2 == false){
            printf(" Player 2 select position 2 (lin,col): ");
            scanf("%d,%d",&lin2,&col2);
            if ((lin2 > 5)|| (col2>5)||(mask[lin2][col2]!=' ')){
                printf("Invalid move, try again. \n");
            }
            else{
                move2 = true;
            }
        }
        mask[lin2][col2] = tab[lin2][col2];

        printf("   0  1  2  3  4  5 \n"); //mask print end
        for (i=0;i<6;i++){
            printf(" %d",i);
            for (j=0;j<6;j++){
                printf("[%c]",mask[i][j]);
            }
        printf("\n");
        }

        if (mask[lin2][col2] == mask[lin][col]){ //score 2
            player2 = player2 + 2;
        }
            else{
                mask[lin2][col2] = ' ';
                mask[lin][col] = ' ';
        }

        printf("   0  1  2  3  4  5 \n"); //mask print end
        for (i=0;i<6;i++){
            printf(" %d",i);
            for (j=0;j<6;j++){
                printf("[%c]",mask[i][j]);
            }
        printf("\n");
        }
        printf("\n *** Score: Player 1 = %d / Player 2 = %d *** \n \n", player1,player2);
        move1 = false; //restoring bool for new player
        move2 = false;
    }
    printf("   0  1  2  3  4  5 \n"); //tab test print
        for (i=0;i<6;i++){
            printf(" %d",i);
            for (j=0;j<6;j++){
                printf("[%c]",tab[i][j]);
            }
        printf("\n");
        }
    if (player1 == 36){
        printf("\n \n !!!!!! PLAYER 1 WINS !!!!!! \n \n");
    }
    if (player2 == 36){
        printf("\n \n !!!!!! PLAYER 2 WINS !!!!!!\n \n ");
    }
    return 0;
}
