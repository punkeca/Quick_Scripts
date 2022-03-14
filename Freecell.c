/*
DESENVOLVEDOR: Patricia Brenny Ribeiro
DISCIPLINA: ECOP02 - Estrutura de Dados
CURSO: Engenharia de Computação - IESTI
UNIVERSIDADE FEDERAL DE ITAJUBÁ - Itajubá, MG.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // Useful for sleep functions.
typedef struct no{
    unsigned int num;
    char naipe;
    struct no *prox;
}stCarta;

stCarta *primMesa[8];
stCarta *primNaipe[4];
stCarta *temp[4];
stCarta *primMonte = NULL;
void SetColor(int ForgC){ //this functions came straight from Google.

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
void geraBaralho(){
    stCarta *novo;
    unsigned char i;
    int j,num,mat[4][13]; //this matrix will be used to shuffle the cards in the deck.
    novo = NULL;
    for(i=0;i<4;i++){ //initializes matrix
        for(j=0;j<13;j++){
            mat[i][j] = 0;
        }//end for j
    }//end for i
    num=0;
    while(num<52){ //this loop shuffles the cards by randomly accessing the matrix's coordinates without repeating any.
        i = rand()%4;
        j = rand()%13;
        if(mat[i][j]==0){
            novo = (stCarta*) malloc(sizeof(stCarta));
            if(primMonte != NULL){
                novo->prox = primMonte;
            }//end if
            novo->num = j+1; //converting to suits in ASCII.
            novo->naipe = i+3;
            primMonte = novo; //updates the first card in the deck.
            novo = NULL;
            num++;
            mat[i][j] = 1;
        }//end if
    }//end while
}//end gera baralho

void distribuiMesa(){
    stCarta *atual,*aux;
    atual = primMonte;
    int i,j,max=7;
    for(i=0;i<8;i++){
        if(i>3){
            max = 6;
        }//end if
        primMesa[i] = atual;
        for(j=0;j<(max-1);j++){
            atual = atual->prox;
        }//end for
        aux = atual;
        atual = aux->prox;
        aux->prox = NULL;
    }//end for i
}//end distribui

void imprime(){
    stCarta *atual;
    int i,j,max=7;
    SetColor(1);
    printf("*************************** BEM VINDO AO FREECELL **************************** \n \n");
    SetColor(15);
    //ini imprime temp
    printf("[TEMP]: ");
    for(i=0;i<4;i++){
        if(temp[i] != NULL){
            printf("%d-",i);
            if(temp[i]->naipe == 3 || temp[i]->naipe == 4){SetColor(4);} //set colors red
            printf("[%-2d%c]  ",temp[i]->num,temp[i]->naipe);
            SetColor(15);
        }else{
            printf("%d-[   ]  ",i);
        }//end else
    }//end for i
    printf("\n \n");
    //fim imprime temp

    //inicio imprime naipe
    for(i=0;i<4;i++){
        atual = primNaipe[i];
        printf("[NAIPE %d]: ",i);
        while(atual!=NULL){
            if(atual->naipe == 3 || atual->naipe == 4){SetColor(4);} //set colors red
            printf("[%-2d%c]",atual->num,atual->naipe);
            SetColor(15);
            atual = atual->prox;
        }//end for j
        printf("\n");
    }//end for i
    printf("\n");
    //fim imprime naipe

    //inicio imprime mesa
    for(i=0;i<8;i++){
        atual = primMesa[i];
        printf("[MESA %d]: ",i);
        while(atual!=NULL){
            if(atual->naipe == 3 || atual->naipe == 4){SetColor(4);} //set colors red
            printf("[%-2d%c]",atual->num,atual->naipe);
            SetColor(15);
            atual = atual->prox;
        }//end for j
        printf("\n");
    }//end for i
    printf("\n");
    //fim imprime mesa
    SetColor(1);
    printf("***********************************%c%c%c%c*************************************** \n",3,4,5,6);
    SetColor(15);
}//end imprime

void moveMesaTemp(){
     stCarta *atual,*ult;
     unsigned char pos=99,i;
     while((pos<0)||(pos>=8)){
        if(pos!=99){
            printf("Tente novamente. \n");
        }//end for
        printf("Indique a mesa a ser retirada a carta: ");
        scanf(" %d",&pos);
     }//end while

     if(primMesa[pos]==NULL){
            printf("Mesa vazia.\n");
            return;
     }else if(primMesa[pos]->prox==NULL){
         ult = primMesa[pos];
         for(i=0;i<4;i++){
            if(temp[i]==NULL){
            temp[i] = ult;
            primMesa[pos] = NULL;
            break;
            }//end if
        }//end for i
        if(i==4){
            printf("\n Temporario sem espaco!!! \n \n");
            sleep(2);
        }//end if
        return;
     }
     //end if mesa vazia
     atual = primMesa[pos];
     while((atual->prox->prox!=NULL)&&(atual->prox!=NULL)){
        atual = atual->prox; //anda até o ult.
     }//end while
     ult = atual->prox;
     ult->prox = NULL;
     for(i=0;i<4;i++){
        if(temp[i]==NULL){
            temp[i] = ult;
            atual->prox = NULL;
            break;
        }//end if
     }//end for i
    if(i==4){
        printf("\n Temporario sem espaco!!! \n \n");
        sleep(2);
    }//end if
}//end move mesa temp

void moveTempMesa(){
    stCarta *ult,*atual;
    int postemp=99,posmesa=99;
 //checa se é permitido
    while((postemp<0)||(postemp>=4)){
        if(postemp!=99){
            printf("Tente novamente. \n");
            sleep(2);
        }//end for
        printf("Indique o temp a ser retirada a carta: ");
        scanf(" %d",&postemp);
     }//end while

    if(temp[postemp]==NULL){
            printf("Temp vazio!\n");
            sleep(2);
            return;
     }//end if mesa vazia

    while((posmesa<0)||(posmesa>=8)){
        if(posmesa!=99){
            printf("Tente novamente. \n");
            sleep(2);
        }//end for
        printf("Indique a mesa a ser colocada a carta: ");
        scanf(" %d",&posmesa);
     }//end while

     if(primMesa[posmesa]==NULL){
            primMesa[posmesa] = temp[postemp];
            temp[postemp] = NULL;
            return;
     }//end if mesa vazia
    //fim checagem

    ult = primMesa[posmesa];
    while(ult->prox!=NULL){
        ult = ult->prox; //descobre ultimo elemento da mesa
    }//end while

    //init regras do jogo.
    if(ult->num - temp[postemp]->num == 1){
        if(((ult->naipe == 3)||(ult->naipe == 4))&&((temp[postemp]->naipe == 6)||(temp[postemp]->naipe == 5))){
            ult->prox = temp[postemp];
            temp[postemp] = NULL;
       }else if(((ult->naipe == 5)||(ult->naipe == 6))&&((temp[postemp]->naipe == 3)||(temp[postemp]->naipe == 4))){
            ult->prox = temp[postemp];
            temp[postemp] = NULL;
            }//end else
    }else{
        printf(" \n Jogada nao permitida!!!\n");
        sleep(2);
    }//end else
}//end move temp mesa

void moveMesaNaipe(){
    stCarta *atual,*ult,*aux;
     int pos=99,i;
     while((pos<0)||(pos>=8)){
        if(pos!=99){
            printf("Tente novamente. \n");
            sleep(2);
        }//end for
        printf("Indique a mesa a ser retirada a carta: ");
        scanf(" %d",&pos);
     }//end while

     if(primMesa[pos]==NULL){
        printf("Mesa vazia.\n");
        sleep(2);
        return;
     }else if(primMesa[pos]->prox==NULL){ //checa se mesa tem 1 item só
        ult = primMesa[pos];
        for(i=0;i<4;i++){
            if(primNaipe[i]!=NULL){
                aux = primNaipe[i]; // aux inicia pilha de naipe
                while(aux->prox!=NULL){
                    aux = aux->prox; //anda até o ult naipe.
                    }//end while
                }//end if
            if((primNaipe[i]==NULL)&&(ult->num == 1)){
                primNaipe[i] = ult; //atribui o num ao naipe correto
                primMesa[pos] = NULL; // retira o ult da mesa
                break;
            }else if((aux!=NULL)&&((ult->num - aux->num)==1)&&(ult->naipe == aux->naipe)){
                aux->prox = ult; //ult naipe aponta para removido da  mesa
                primMesa[pos] = NULL;
             break;
            }//end else
        }//end for i
        if(i==4){
            printf(" \n  Carta Invalida. \n");
            sleep(2);
        }//end if
        return;
     }//end if mesa vazia ou pos vazia

     atual = primMesa[pos];
     while(atual->prox->prox!=NULL){
        atual = atual->prox; //atual anda até o ult.
     }//end while
     ult = atual->prox; // atribui o ultimo
     for(i=0;i<4;i++){

        if(primNaipe[i]!=NULL){
            aux = primNaipe[i]; // aux inicia pilha de naipe
            while(aux->prox!=NULL){
                aux = aux->prox; //anda até o ult naipe.
                }//end while
            }//end if

        if((primNaipe[i]==NULL)&&(ult->num == 1)){
            primNaipe[i] = ult; //atribui o num ao naipe correto
            atual->prox = NULL; // retira o ult da mesa
            break;
        }else if((aux!=NULL)&&((ult->num - aux->num)==1)&&(ult->naipe == aux->naipe)){
            aux->prox = ult; //ult naipe aponta para removido da  mesa
            atual->prox = NULL;
             break;
        }//end else
     }//end for i
    if(i==4){
        printf("\n Carta Invalida. \n");
        sleep(2);
    }//end if
}//end move mesa naipe

void moveTempNaipe(){
    stCarta *ult,*aux;
    int postemp=99, i;
 //checa se é permitido
    while((postemp<0)||(postemp>=4)){
        if(postemp!=99){
            printf("Tente novamente. \n");
            sleep(2);
        }//end for
        printf("Indique o temp a ser retirada a carta: ");
        scanf(" %d",&postemp);
     }//end while

    if(temp[postemp]==NULL){
            printf("Temp vazio!\n");
            sleep(2);
            return; //sai da função
     }//end if mesa vazia

    for(i=0;i<4;i++){

        if(primNaipe[i]!=NULL){
            aux = primNaipe[i]; // aux inicia pilha de naipe
            while(aux->prox!=NULL){
                aux = aux->prox; //anda até o ultimo do naipe.
                }//end while
            }//end if

        if((primNaipe[i]==NULL)&&(temp[postemp]->num == 1)){
            primNaipe[i] = temp[postemp]; //atribui temp ao naipe correto
            temp[postemp]=NULL; //retira carta do temp
            break;
        }else if((aux!=NULL)&&((temp[postemp]->num - aux->num)==1)&&(temp[postemp]->naipe == aux->naipe)){
            aux->prox = temp[postemp]; //ult naipe aponta para removido da temp
            temp[postemp] = NULL;
             break;
        }//end else
     }//end for i
    if(i==4){
        printf("\n Carta Invalida. \n");
        sleep(2);
    }//end if
}//end move temp-naipe

void moveNaipeMesa(){
    stCarta *ult,*atual,*penultimo;
    int posnaipe=99,posmesa=99;
 //checa se é permitido
    while((posnaipe<0)||(posnaipe>=4)){
        if(posnaipe!=99){
            printf("Tente novamente. \n");
            sleep(2);
        }//end for
        printf("Indique a pilha de naipe a ser retirada a carta: ");
        scanf(" %d",&posnaipe);
     }//end while

    if(primNaipe[posnaipe]==NULL){
            printf("Pilha vazia!\n");
            sleep(2);
            return;
     }//end if pilha naipe vazia

    while((posmesa<0)||(posmesa>=8)){
        if(posmesa!=99){
            printf("Tente novamente. \n");
            sleep(2);
        }//end for
        printf("Indique a mesa a ser colocada a carta: ");
        scanf(" %d",&posmesa);
     }//end while

    atual = primNaipe[posnaipe];
    penultimo = primNaipe[posnaipe];
    while(atual->prox!=NULL){
        penultimo = atual;
        atual = atual->prox; //atualiza atual como ultimo
    }//end while

     if(primMesa[posmesa]==NULL){
        primMesa[posmesa] = atual;
        if(penultimo->prox==NULL){
            primNaipe[posnaipe] = NULL;
        }else{
            penultimo->prox = NULL;
        }
        return;
     }//end if mesa vazia
    //fim checagem

    ult = primMesa[posmesa];
    while(ult->prox!=NULL){
        ult = ult->prox; //descobre ultimo elemento da mesa
    }//end while

    //init regras do jogo.
    if(ult->num - atual->num == 1){
        if(((ult->naipe == 3)||(ult->naipe == 4))&&((atual->naipe == 6)||(atual->naipe == 5))){
            ult->prox = atual;
            if(penultimo->prox==NULL){
                primNaipe[posnaipe] = NULL;
            }else{
                penultimo->prox = NULL;
            }
       }else if(((ult->naipe == 5)||(ult->naipe == 6))&&((atual->naipe == 3)||(atual->naipe == 4))){
            ult->prox = atual;
             if(penultimo->prox==NULL){
                primNaipe[posnaipe] = NULL;
            }else{
                penultimo->prox = NULL;
                }
            }//end else
    }else{
        printf(" \n Jogada nao permitida!!!\n");
        sleep(2);
    }//end else
}//end move naipe mesa

void moveNaipeTemp(){
    stCarta *atual,*ult;
    int posnaipe=99,i;
 //checa se é permitido
    while((posnaipe<0)||(posnaipe>=4)){
        if(posnaipe!=99){
            printf("Tente novamente. \n");
            sleep(2);
        }//end for
        printf("Indique a pilha de naipe a ser retirada a carta: ");
        scanf(" %d",&posnaipe);
     }//end while

    if(primNaipe[posnaipe]==NULL){
            printf("Pilha vazia!\n");
            sleep(2);
            return;
     }//end if pilha naipe vazia

     if(primNaipe[posnaipe]->prox==NULL){
         ult = primNaipe[posnaipe];
         for(i=0;i<4;i++){
            if(temp[i]==NULL){
            temp[i] = ult;
            primNaipe[posnaipe] = NULL;
            break;
            }//end if
        }//end for i
        if(i==4){
            printf("\n Temporario sem espaco!!! \n \n");
            sleep(2);
        }//end if
        return;
     }

     atual = primNaipe[posnaipe];
     while((atual->prox->prox!=NULL)&&(atual->prox!=NULL)){
        atual = atual->prox; //anda até o penultimo.
     }//end while
     ult = atual->prox;
     ult->prox = NULL;
     for(i=0;i<4;i++){
        if(temp[i]==NULL){
            temp[i] = ult;
            atual->prox = NULL;
            break;
        }//end if
     }//end for i
    if(i==4){
        printf("\nTemporario sem espaco!!! \n \n");
        sleep(2);
    }//end if

}//end move naipe temp

void moveMesaMesaCarta(){
    stCarta *ult,*aux,*penultimo;
    int pos1=75,pos2=99,i,op;


     while((pos1<0)||(pos1>=8)){
        if(pos1!=75){
            printf("Tente novamente. \n");
        }//end for
        printf("Indique a mesa de origem: ");
        scanf(" %d",&pos1);
     }//end while

     while((pos2<0)||(pos2>=8)){
        if(pos2!=99){
            printf("Tente novamente. \n");
        }//end for
        printf("Indique a mesa de destino: ");
        scanf(" %d",&pos2);
     }//end while

    if(primMesa[pos1]==NULL){
        printf("Mesa de origem vazia.\n");
        sleep(3);
        return;
    }//end if


    aux = primMesa[pos1];
    penultimo = primMesa[pos1];
    while(aux ->prox!=NULL){
        penultimo = aux ;
        aux  = aux ->prox; //encontra o  ultimo  da mesa  de origem
    }//end while


    if(primMesa[pos2]==NULL){
        primMesa[pos2] = aux ;
        if(penultimo->prox==NULL){
            primMesa[pos1] = NULL;
        }else{
            penultimo->prox = NULL;
        }
        return;
     }//end if mesa 2 vazia
    //fim checagem

    ult = primMesa[pos2];
    while(ult->prox!=NULL){
        ult = ult->prox; //descobre ultimo elemento da mesa de destino
    }//end while


    //init regras do jogo.
    if(ult->num - aux->num == 1){
        if(((ult->naipe == 3)||(ult->naipe == 4))&&((aux->naipe == 6)||(aux->naipe == 5))){
            ult->prox = aux ;
            if(penultimo->prox==NULL){
                primMesa[pos1] = NULL;
            }else{
                penultimo->prox = NULL;
            }
       }else if(((ult->naipe == 5)||(ult->naipe == 6))&&((aux ->naipe == 3)||(aux->naipe == 4))){
            ult->prox = aux ;
             if(penultimo->prox==NULL){
                primMesa[pos1] = NULL;
            }else{
                penultimo->prox = NULL;
                }
            }//end else
    }else{
        printf(" \nJogada nao permitida!!!\n");
        sleep(2);
    }//end else
    return;
}//end move mesa mesa

void moveMesaMesaPilha(){
     stCarta *cartadest,*aux,*inicio, *atual,*penultimo;
    int pos1=75,pos2=99,i,op;


    while((pos1<0)||(pos1>=8)){
        if(pos1!=75){
            printf("Tente novamente. \n");
        }//end for
        printf("Indique a mesa de origem: ");
        scanf(" %d",&pos1);
     }//end while

     while((pos2<0)||(pos2>=8)){
        if(pos2!=99){
            printf("Tente novamente. \n");
        }//end for
        printf("Indique a mesa de destino: ");
        scanf(" %d",&pos2);
     }//end while

    if(primMesa[pos1]==NULL){
        printf("Mesa de origem vazia.\n");
        sleep(3);
        return;
    }


    //encontra sequencia ou ultimo elem
    inicio = primMesa[pos1];
    aux = primMesa[pos1];
    atual = primMesa[pos1];
    while(atual!=NULL){
        if(((aux->naipe == 3)||(aux->naipe == 4))&&((atual->naipe == 6)||(atual->naipe == 5))&&(aux->num - atual->num == 1)){
                aux = atual;
                atual = atual->prox;
        }else if(((aux->naipe == 5)||(aux->naipe == 6))&&((atual ->naipe == 3)||(atual->naipe == 4))&&(aux->num - atual->num == 1)){
                aux = atual;
                atual = atual->prox;
        }else{
            aux = atual;
            inicio = aux;
            atual = atual->prox;
        }//end else
    }//end while
    //fim encontra sequencia ou ultimo elem

    //encontra penultimo
    penultimo = primMesa[pos1];
    while((penultimo->prox!=inicio)&&(penultimo!=inicio)){
        penultimo = penultimo->prox;
    }//end while

    if(primMesa[pos2]==NULL){
        primMesa[pos2] = inicio;
        if(primMesa[pos1]==inicio){
            primMesa[pos1] = NULL;
        }else{
            penultimo->prox = NULL;
        }
        return;
     }//end if mesa 2 vazia

    cartadest = primMesa[pos2];
    while(cartadest->prox!=NULL){
        cartadest = cartadest->prox; //descobre ultimo elemento da mesa de destino
    }//end while


     //init regras do jogo.
    if(((cartadest->naipe == 3)||(cartadest->naipe == 4))&&((inicio->naipe == 6)||(inicio->naipe == 5))&&(cartadest->num - inicio->num == 1)){
            cartadest->prox = inicio;
            if(primMesa[pos1]==inicio){
                primMesa[pos1] = NULL;
            }else{
                penultimo->prox = NULL;
            }
    }else if(((cartadest->naipe == 5)||(cartadest->naipe == 6))&&((inicio ->naipe == 3)||(inicio->naipe == 4))&&(cartadest->num - inicio->num == 1)){
            cartadest->prox = inicio;
            if(primMesa[pos1]==inicio){
                primMesa[pos1] = NULL;
            }else{
                penultimo->prox = NULL;
            }
    }else{
        printf(" \n Jogada nao permitida!!!\n");
        sleep(2);
        return;
    }//end else
    return;
}//end move mesa-mesa pilha

int gameOver(){
    stCarta *ult[4];
    int i,venceu=0;

    if((primNaipe[0]==NULL)||(primNaipe[1]==NULL)||(primNaipe[2]==NULL)||(primNaipe[3]==NULL)){
        return 0;
    }//end if

    for(i=0;i<4;i++){
        ult[i] = primNaipe[i];
        while(ult[i]->prox!=NULL){
            ult[i] = ult[i]->prox;
        }//encontra o ultimo da pilha de naipe
    }//end for

    if((ult[0]->num == 13)&&(ult[1]->num == 13)&&(ult[2]->num == 13)&&(ult[3]->num == 13)){ //condição de vencedor
        venceu = 1;
    }else{
        venceu = 0;
    }//end else)
    return venceu;
}//end game over

void destroi(){
    stCarta *atual, *remove = NULL;
    int i;

    for(i=0;i<4;i++){
        atual = primNaipe[i];
        if(atual!=NULL){
            while(atual->prox!=NULL){
                remove = atual;
                atual = atual->prox;
                free(remove);
            }//end while
            free(atual);
        }//end if
    }//end for

    for(i=0;i<4;i++){
        remove = temp[i];
        if(atual!=NULL){
            free(remove);
        }//end if
    }//end for

    for(i=0;i<8;i++){
        atual = primMesa[i];
        if(atual!=NULL){
            while(atual->prox!=NULL){
                remove = atual;
                atual = atual->prox;
                free(remove);
            }//end while
            free(atual);
        }//end if
    }//end for

    return;
}//end destroi

int main(int argc,char **argv){
    stCarta *aux;
    int i;
    int op = 9;
    srand(time(NULL));
    geraBaralho();
    distribuiMesa();
    imprime();
    while(op!=0){
        printf("  MENU:\n");
        SetColor(15);
        printf(" %c (1)Mover Mesa->Temp.\n %c (2)Mover Temp->Mesa.\n %c (3)Mover Mesa->Naipe.\n %c (4)Mover Temp->Naipe.\n",16,16,16,16);
        printf(" %c (5)Mover Naipe->Temp.\n %c (6)Mover Naipe->Mesa.\n %c (7)Mover Sequencia Mesa->Mesa. \n %c (8)Mover Carta Mesa->Mesa. \n %c (0)Sair. \n",16,16,16,16,16);
        printf(" Escolha:");
        scanf(" %d",&op);
        getchar();
        switch(op){
        case 1:
            moveMesaTemp();
            break;
        case 2:
            moveTempMesa();
            break;
        case 3:
            moveMesaNaipe();
            break;
        case 4:
            moveTempNaipe();
            break;
        case 5:
            moveNaipeTemp();
            break;
        case 6:
            moveNaipeMesa();
            break;
        case 7:
            moveMesaMesaPilha();
            break;
        case 8:
            moveMesaMesaCarta();
            break;
        case 0:
            break;
        default:
            printf(" Opcao Invalida, tente novamente. \n");
            sleep(2);
            break;
        }//end switch op
        system("cls");
        imprime();
    }//end while
    if (gameOver() == 1){
        SetColor(2);
        printf("-------------------------------- VOCE VENCEU --------------------------------- \n \n");
        SetColor(15);
        printf("--------------------------------- GAME OVER ---------------------------------- \n");
    }else{
        SetColor(4);
        printf("-------------------------------- VOCE PERDEU --------------------------------- \n \n");
        SetColor(15);
        printf("--------------------------------- GAME OVER ---------------------------------- \n");
    }//end else
    destroi();
    return 0;
}//end main
