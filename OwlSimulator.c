/*
DESENVOLVEDOR: Patricia Brenny Ribeiro
DISCIPLINA: ECOP01 - Algoritmos
CURSO: Engenharia de Computação - IESTI
UNIVERSIDADE FEDERAL DE ITAJUBÁ - Itajubá, MG.
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
int ramo=1;
int baga=0;
int farinha=0;
int jogadas=1;
char caverna[25][90];
void inicializa(){
    int i,j,lin,col;
    for(i=0;i<25;i++){
        for(j=0;j<90;j++){
            caverna[i][j]=' ';
        }
    }
    for(i=0;i<10;i++){ //ramos
        col = rand()%90;
        if(caverna[0][col]==' '){
            caverna[0][col]=':';
        }else{i--;}
    }
    for(i=0;i<4;i++){ //rochas 2
        col = rand()%90;
        if((caverna[24][col]==' ')&&(caverna[24][col+1]==' ')){
            for(j=24;j>=20;j--){
            caverna[j][col]='.';
            caverna[j][col+1]='.';
            }
        }else{i--;}
    }
    for(i=0;i<3;i++){ //rochas 3
        col = rand()%90;
        if((caverna[24][col]==' ')&&(caverna[24][col+1]==' ')&&(caverna[24][col+2]==' ')){
            for(j=24;j>=19;j--){
            caverna[j][col]='.';
            caverna[j][col+1]='.';
            caverna[j][col+2]='.';
            }
        }else{i--;}
    } //fim rochas
    for(i=0;i<10;i++){ //estalagmites
        col = rand()%90;
        if(caverna[24][col]==' '){
            caverna[24][col]='^';
        }else{i--;}
    }//fim estalagmites
    for(i=0;i<13;i++){ //corujas
        col = rand()%90;
        lin = (rand()%12)+6;
        if(caverna[lin][col]==' '){
            caverna[lin][col]='V';
        }else{i--;}
    }// fim corujas
    for(i=0;i<31;i++){ //morcegos
        col = rand()%90;
        lin = (rand()%12)+6;
        if(caverna[lin][col]==' '){
            caverna[lin][col]='W';
        }else{i--;}
    }//fim morcegos
}
void imprime(){
    int i,j;
    printf("\n");
    printf(" -------------------------------   A CAVERNA DE CORUJAS  ------------------------------------- \n");
    printf("\n");
    printf("              11111111112222222222333333333344444444445555555555666666666677777777778888888888 \n");
    printf("    012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789 \n");
    for(i=0;i<25;i++){
            printf("[%2d]",i);
        for(j=0;j<90;j++){
            printf("%c",caverna[i][j]);
        }
        printf("\n");
    }
}
void alimentar(){
    int lin,col,i;
    if(baga>0){
        printf(" Escolha uma coruja para alimentar[lin][col]: ");
        scanf(" %d %d",&lin,&col);
        if((lin >= 0)&&(col >= 0)&&(lin < 25)&&(col < 90)){
            switch(caverna[lin][col]){
            case 'v':
                caverna[lin][col]='V';
                jogadas++;
                baga--;
                printf("\n Coruja alimentada! \n");
                sleep(3);
                break;
            case 'V':
                jogadas++;
                printf("\n Coruja alimentada! \n");
                if((caverna[lin+1][col]=='V')&&(caverna[lin+2][col]=='#')){
                    printf("\n Olhe, um bebe coruja! \n");
                    caverna[lin+2][col]='v';
                }
                baga--;
                sleep(3);
                break;
            default:
                printf("\n Nao ha nada para alimentar aqui... \n");
                sleep(3);
                break;
            }
        }else{
            printf("\n Nao pode alimentar aqui! \n");
            sleep(3);
            }
    }else{
        printf("\n Nao ha bagas suficientes! \n");
        sleep(3);
        }
}//fimalimentar
void colher(){
    int lin,col,i;
    printf(" Escolha um ramo ou baga para a colheita[lin][col]: ");
    scanf(" %d %d",&lin,&col);
    if((lin > 0)&&(col >= 0)&&(lin < 25)&&(col < 90)){
        switch(caverna[lin][col]){
        case '%':
            for(i=lin;i<25;i++){
                    if(caverna[i][col]=='%'){
                        baga++;
                        caverna[i][col]=' ';
                    }else if(caverna[i][col]==':'){
                        ramo++;
                        caverna[i][col]=' ';
                    }
            }
            jogadas++;
            printf("\n Colheita feita! \n");
            sleep(3);
            break;
        case ':':
            for(i=lin;i<25;i++){
                    if(caverna[i][col]=='%'){
                        baga++;
                        caverna[i][col]=' ';
                    }else if(caverna[i][col]==':'){
                        ramo++;
                        caverna[i][col]=' ';
                    }
            }
            jogadas++;
            printf("\n Colheita feita! \n");
            sleep(3);
            break;
        default:
            printf("\n Nao ha nada para colher aqui... \n");
            sleep(3);
            break;
        }
    }else{
        printf("\n Nao pode colher aqui! \n");
        sleep(3);}
}//fim colher
void fertilizar(){
    int lin,col;
    if (farinha > 0){
        printf(" Digite a posicao do ramo[lin][col] : ");
        scanf(" %d %d",&lin,&col);
        if((lin >0)&&(col >= 0)&&(lin < 25)&&(col < 90)){
            if(caverna[lin][col] == ':'){
                caverna[lin][col] ='%';
                printf("\n Fertilizacao bem sucedida!!! \n");
                farinha--;
                sleep(3);
                jogadas++;
            }else{
                printf("\n Nao ha ramos aqui, nada foi fertilizado. \n");
                sleep(3);
            }
        }else{
            printf("\n Nao pode fertilizar aqui! \n");
            sleep(3);
        }
    }else{
        printf("\n Farinha de ossos insuficiente. \n");
        sleep(3);
    }
}//fim fertilizar
void mover(){
    int lin,col,i,lin2,col2;
    printf(" Escolha uma coruja para mover[lin][col]: ");
    scanf(" %d %d",&lin,&col);
    printf(" Escolha um destino para mover[lin2][col2]: ");
    scanf(" %d %d",&lin2,&col2);
    if((lin >= 0)&&(col >= 0)&&(lin < 25)&&(col < 90)){
        switch(caverna[lin][col]){
        case 'v':
            if((lin2 >= 0)&&(col2 >= 0)&&(lin2 < 25)&&(col2 < 90)){
                if(((lin2 - lin == 1)||(lin2 - lin == -1)||(lin2 == lin))&&((col2 - col == 1)||(col2 - col == -1)||(col==col2))){
                    if((caverna[lin2][col2]==' ')){
                        caverna[lin][col]= ' ';
                        caverna[lin2][col2]= 'v';
                        printf("\n Coruja movida! \n");
                        jogadas++;
                    }else{
                        printf("\n Posicao ja ocupada! \n");
                        }//check morcego ou espaço
                }else{
                    printf("\n Corujas nao voam mais que 1 casa nesse jogo. \n");
                }//check vizinho
            }else{
                printf("\n Nao pode mover algo aqui! \n");
            }//check matriz
            sleep(3);
            break;
        case 'V':
            if((lin2 >= 0)&&(col2 >= 0)&&(lin2 < 25)&&(col2 < 90)){
                if(((lin2 - lin == 1)||(lin2 - lin == -1)||(lin2 == lin))&&((col2 - col == 1)||(col2 - col == -1)||(col==col2))){
                    if((caverna[lin2][col2]==' ')){
                        caverna[lin][col]= ' ';
                        caverna[lin2][col2]= 'V';
                        printf("\n Coruja movida!!!\n");
                        jogadas++;
                    }else if(caverna[lin2][col2]=='W'){
                        caverna[lin][col]= ' ';
                        caverna[lin2][col2]= 'V';
                        printf("\n Coruja derrotou o morcego e tomou seu lugar! \n");
                        farinha++;
                        jogadas++;
                    }//check morcego ou espaço
                }else{
                    printf("\n Corujas nao voam mais que 1 casa nesse jogo. \n");
                }//check vizinho
            }else{
                printf("\n Nao pode mover algo aqui! \n");
            }//check matriz
            sleep(3);
            break;
        default:
            printf("\n Nao ha nada para mover aqui... \n");
            sleep(3);
            break;
        }
    }else{
        printf("\n Nao pode mover nada daqui! \n");
        sleep(3);
        }
}//fim mover
void ninho(){
    int lin,col;
    if (ramo >= 4){
        printf(" Contruir ninho em [lin][col]: ");
        scanf(" %d %d",&lin,&col);
        if((lin >= 0)&&(col >= 0)&&(lin < 24)&&(col < 90)&&(caverna[lin+1][col]=='.')){
            caverna[lin][col]='#';
            ramo = ramo-4;
            jogadas++;
            printf("\n Novo ninho construido! \n");
            sleep(3);
        }else{
            printf("\n Nao pode construir ninhos aqui! \n");
            sleep(3);
        }//posicao
    }else{
        printf("\n Ramos insuficientes... \n");
        sleep(3);
    }//saldo ramo
}//fim ninho
void dia(){
    int i,j,lin,col;
     for(i=0;i<25;i++){ // apaga morcegos
        for(j=0;j<90;j++){
            if(caverna[i][j]=='W'){
                caverna[i][j]=' ';
            }
        }
    }
    for(i=0;i<31;i++){ // bota morcegos
        col = rand()%90;
        lin = (rand()%12)+6;
        if((caverna[lin][col]==' ')||(caverna[lin][col]=='v')||(caverna[lin][col]=='V')||(caverna[lin][col]=='#')){
            caverna[lin][col]='W';
        }else{i--;}
    }
    for(j=0;j<80;j++){
        if((caverna[0][j]==':'&&(rand()%100<15))){
            i=0;
            do{
                i++;
            }while((caverna[i][j] ==':')||(caverna[i][j] =='%'));
            caverna[i][j]= ':';
        }
    }//cresce ramo
    for(j=0;j<80;j++){
        if((caverna[24][j]=='^')&&(rand()%100<15)){
            i=24;
            do{
                i--;
            }while(caverna[i][j] =='^');
            caverna[i][j]= '^';
        }
    }//cresce estalagmite


    system("cls");
    printf(" 7 JOGADAS ATINGIDAS, AMANHECEU UM NOVO DIA...\n");
    sleep(3);
}//fimdia
int main(int argc, char * arv[]){
    char op=' ';
    srand(time(NULL));
    //system("start cavernamusic.mp3");
    inicializa();
    while(op != 's'){
        imprime(); // imprimir matriz
        printf(" RECURSOS: ");
        printf(" baga=%d ramo=%d  farinha de ossos=%d\n", baga, ramo, farinha);
        printf(" MENU: (a)alimentar / (c)olher/ (d)ia / (f)ertilizar / (m)over / (n)inho / (s)air \n");
        printf(" [Jogada %d] digite sua jogada: ", jogadas);
        op = getch();
        printf("%c\n", op);
        switch(op){
            case 'a' :
                alimentar();
                break;
            case 'c' :
                colher();
                break;
            case 'd' :
                dia();
                break;
            case 'f' :
                fertilizar();
                break;
            case 'm' :
                mover();
                break;
            case 'n' :
                ninho();
                break;
            case 's' :
                break;
            default:
                printf("\n AVISO: OPCAO INVALIDA, TENTE NOVAMENTE!!! \n");
                sleep(1);
        }
        if(jogadas > 7){
            imprime();
            dia();
            jogadas = 1;
        }
        system("cls");
    }
    return 0;
}
