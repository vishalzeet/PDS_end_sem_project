#include<stdio.h>
#include<conio.h>
#include<windows.h>

#define h 20
#define w 70

HANDLE hConsole;
COORD coord ;

int bX,bY;
int p1Y,p2Y;
int bspeedX=1,bspeedY=-1;
int score1=0;
int score2=0;
int gameover;

int sound(){
    Beep(600,400);
    return 0;}

void prepare(){
    hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    bX=w/2;
    bY=h/2;
    p1Y=h/2-2;
    p2Y=h/2-2;
    gameover=0;
    coord.X=0;
    coord.Y=0;
}

void custom(){

    SetConsoleCursorPosition(hConsole,coord);
    for(int x=0;x<w;x++){
    printf("\033[0;32m");
    printf("#");
    }
    printf("\n");
    for(int j=0;j<h;j++){
    for(int i=0;i<w;i++){
     if(i==0 || i==w-1){
     printf("\033[0;32m");
     printf("*");}
     else if(i==bX && j==bY){
     printf("\033[0;34m");
     printf("O");}
     else if(i==1 && (j>=p1Y && j<p1Y+4)){
     printf("\x1b[31m"); 
     printf("|");
     
     }
     else if(i==w-2 && (j>=p2Y && j<p2Y+4)){
     printf("\x1b[31m");
     printf("|");}
     else
     printf(" ");
    }
    printf("\n");
    }
    for(int k=0;k<w;k++){
    printf("\033[0;32m");
    printf("#");}
    printf("\n");

    printf("  score1:%d                        score2: %d\n\n",score1,score2);}

void value(){
    if(_kbhit()){
    char opt =_getch();
    if(opt=='a' && p1Y>0)
    p1Y--;
    if(opt=='z' && p1Y+4<h)
    p1Y++;
    if(opt=='k' && p2Y>0)
    p2Y--;
    if(opt=='m' && p2Y+4<h)
    p2Y++;
    if (opt=='g')
    gameover=1;}
}

void logic()
{  
    bX += bspeedX;
    bY += bspeedY;
    if (bX == 2 && (bY >= p1Y && bY < p1Y + 4))
        bspeedX = -bspeedX;
    if (bX == w-3 && (bY >= p2Y  && bY < p2Y + 4))
        bspeedX = -bspeedX;
    if (bY == 0 || bY==h-1)
       bspeedY = -(bspeedY);
    if (bX == 0)
    {
        score2++;
        sound();
        bspeedX=1;
        prepare();
    }
    if (bX == w- 1)
    {
        score1++;
        sound();
        bspeedX=-1;
        prepare();}

    if(score1==5 || score2==5){
      custom();
      gameover=1;
      printf("\033[0;34m");
      printf("\t\t\tgame over!!!\n\n");  
    if(score1==5){
      score1 = score2 = 0 ;
      printf("\t\t\tPlayer1 wins\n");}
    else if(score2==5)
      score1 = score2 = 0;
      printf("\t\t\tPlayer2 wins\n");
      printf(" \n\t\tPress 'c' to go in Main Menu\n\n"); }
}

void gameplay(){

     prepare();
     while(!gameover){
     custom();
     value();
     logic();
     Sleep(20);
     }
    
}

void start()
{    printf("\033[0;32m");
     printf("  \t**********************************************\t\n");

    printf("\033[0;34m");
    printf("\t\t CHOOSE AN OPTION TO PROCEED:\n\n");
    printf("\t\t Enter '1' to view game rules\n");
    printf("\t\t Enter '2' to start game\n");
    printf("\t\t Enter '3' to Exit \n");
    printf("\n");
    printf("\033[0;32m");
     printf("  \t**********************************************\t\n");

    int r;
      scanf("%d",&r);
    switch(r){

    case 1:
        printf("\033[0;34m");
        printf("\t\t\t> It is a two-player game.\n");
        printf("\t\t\t> Each player gets alternate choices to play.\n");
        printf("\t\t\t> The ball starts moving automatically once the game is started.\n");
        printf("\t\t\t> To move the right paddle up press 'A' and to move it down press 'Z'.\n");
        printf("\t\t\t> To move the left paddle up press 'K' and to move it down press 'M'.\n");
        printf("\t\t\t> The player gets a point once if the opponent fails to hit the ball with paddle.\n");
        printf("\t\t\t> Whomever first reaches to 5 points, he/she will be declared as the winner.\n");
        printf("\t\t\t> Press 'g' to stop the game in between.\n");
        printf("\t\t\t> Press 'c' to go back\n");
        char run=getch();
        while(run!='c'){
            printf("\n");
            printf("\x1b[31m");
            printf("\t\t\t\tPress 'c' to go Main Menu\n\n");
            run=getch();
        }
        
         if(run == 'c'){
           printf("\n");
           start();
        }
        break ;

    case 2:
        gameplay();
        char con=getch();
        if(con=='c')
        start();
        break;

    case 3:
        gameover=1;
        printf("\nYou Exit\n\n");
        break;
    }
}

void main(){

start();
}