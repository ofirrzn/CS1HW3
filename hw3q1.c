//
//  main.c
//  hw3q1.c
//
//  Created by Ofir Razon on 12/18/18.
//  Copyright © 2018 Ofir Razon. All rights reserved.
//
/*-------------------------------------------------------------------------
 Include files:
 --------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*=========================================================================
 Constants and definitions:
 ==========================================================================*/

/* put your #defines and typedefs here*/
#define N 25
#define S 4
#define s_max_input_succes 1
#define s_max_invalid 2
#define size_input_success 1
#define food_input_success 2
#define direc_input_success 1
#define snakepos 625
#define ROW 2
#define BOARD_ELEMENT '#'
#define PERCENT 0
#define FIRST_PLAYER PERCENT
#define PERCENT_HEAD '%'
#define PERCENT_BODY '*'
#define SHTRODEL 1
#define SHTRODEL_HEAD '@'
#define SHTRODEL_BODY '+'
#define ILLEGAL_MOVE 0
#define SNAKE_DIE 1
#define ER -1
#define input_movesnake 2
#define down 2
#define left 4
#define right 6
#define up 8
#define no_moves 4
#define turn_c 2
#define valid_move 0
#define invalid_move 1
#define board_full 1
#define board_notf 0
#define not_yet 0
#define game_ended 1

#define p_stepnoF_index 2
#define s_stepnoF_index 3

/*-------------------------------------------------------------------------
 *   Function declartion
 *--------------------------------------------------------------------------*/

void print_introduction_msg();
//print welcome message , and introduction message to the game

void print_board_size_msg();
//print message to enter board size

int prntstore_steps_without_food();
//print message to enter maximum number of steps can snake do without food
//store user input, error checks user input

void print_food_location_msg();
//print message to insert place for next food

void help_print_board(int size);
//printing static part of the board

void print_board(char board[N][N], int size);
//print the current board for the user

void print_player_message(int player);
//print message when we switch between users

void print_insert_direction();
//print message asking the user to insert his move

void print_finish_msg(int player,int finish_reason );
//get the player who lose and the reason of losing and print message state

void print_error_input();
//print message - there is error in the input

void print_invalid_input();
//print message - re-insert valid input

void print_full_board();
//print message - full board - no winner
int input_game_initialize();
//print messages, scan user input(/error check) for game intialization
void array_initialize();
//initializes array
int food_location();
//places food on matrix as specified by user input
void snakes_initialize();
//intialize the starting point of the snakes on the board
//intializes array that stores location of each snake

int snake_direction();
//takes user input to move snake

bool out_of_bounds(int i, int j, int size);

// aux function to check that coordinates are within bounds

bool movement_input_invalid();
//boolean function that checks whether the movement key pressed is valid
int move_down_p();
//moves snake  % down

int move_left_p();
//moves snake % left

int move_right_p();
//moves snake % right

int move_up_p();
//moves snake % up

int move_down_s();
//moves snake @ down

int move_left_s();
//moves snake @ left

int move_right_s();
//moves snake @ right

int move_up_s();
//moves snake @ up

int move_snake_p();
//moves percent snake in accordance with user input

int move_snake_s();
//moves strudel snake in accordance with user input

int game_over();
//function used to end game and declare games winner
void snake_move_loop();
//allows for exectuion of game: distributing turns

int main_function_central();
// stores and executes all functions needed for program
//used to end game whenever error in input

int ssnake_movement_direction();
//take in input direction and moves snake for @

int psnake_movement_direction();
//take in input direction and moves snake for %

void move_d_changeindex(int sleng_steps[S],int shead[ROW][snakepos],
                        int turncount);
//changes location of snake in array when movement is down
//array contains in order- row and column locations of individual bodyparts

void move_l_changeindex(int sleng_steps[S],int shead[ROW][snakepos],
                        int turncount);
//changes location of snake in array when movement is down

int  check_boardfull_yes_F();
//ends game if board is full
//includes F as empty space

int check_boardfull_no_F();
//checks if board is full-doesnt regard F as empty space

int food_found(int sleng_steps[S],char board[N][N],int shead[ROW][snakepos],
               int rowh, int columnh, int turncount);
//makes snake longer when snake head reaches F(food)
//adds the location of new  body part in the corresponding snake array


int main()
{
    int direction=0, sleng_steps[S]={3, 3, 0, 0}, turncount=0;
    
    //sleng_steps- first two indexes store snake length % and @
    //in that order next two indexes store steps take in same order
    
    char board[N][N];
    int shead_p[ROW][snakepos], shead_s[ROW][snakepos];
    //array stores location of snake's body on board
    
    int size=0,  max_steps=0;
    if((size = input_game_initialize())==ER){
        print_error_input();
        return 0;}
    
    array_initialize(board,size);
    
    
    
    if((max_steps= prntstore_steps_without_food())==ER){
        print_error_input();
        return 0;
    }
    //determines max steps each snake can take without food
    snakes_initialize(board,size,shead_s, shead_p);
    
    if(food_location(board, size)==ER){
        print_error_input();
        return 0;
    }
    
    print_board(board, size);
    
    snake_move_loop( size,  direction,sleng_steps,board,
                    shead_s, shead_p,
                    turncount,  max_steps);
    
    
    return 0;
}





void print_introduction_msg()
{
    printf("Welcome to multi-snake  game, The game have 2 player"
           " Percent and Shtrodel.\n"
           "The game starts with PERCENT player.\n");
    printf("You have to choose 4 moves :Up,Down,Right and Left "
           "The Percent player is the snake that starts in (0,0)\n\n");
}

void print_board_size_msg(){
    printf("Insert board size between 4 and 25:\n");
}

int prntstore_steps_without_food(){
    printf("Insert the maximum number of steps"
           " the snake can do without food:\n");
    int s_max=0;
    if(scanf("%d", &s_max)!=s_max_input_succes){
        print_error_input();
        
    }
    //checks for valid stepswithout food size
    while(s_max<s_max_invalid){
        print_invalid_input();
        scanf("%d", &s_max);
        
    }
    return s_max;
    
}

void print_food_location_msg(){
    printf("in order to continue the game please Insert"
           " a row then column numbers to place the next food: \n");
}

void help_print_board(int size)
{
    int i=0;
    printf("%c",BOARD_ELEMENT);
    for(i=0;i<size;i++)
    {
        printf("%c",BOARD_ELEMENT);
    }
    printf("%c\n",BOARD_ELEMENT);
}

void print_board(char board[N][N], int size)
{
    int i=0,j=0;
    help_print_board(size);
    for(i=0;i<size;i++)
    {
        printf("%c",BOARD_ELEMENT);
        for(j=0;j<size;j++)
        {
            printf("%c",board[i][j]);
        }
        printf("%c\n",BOARD_ELEMENT);
    }
    help_print_board(size);
    printf("\n\n");
}

void print_player_message(int player )
{
    printf("******* Turn of %c ***********\n"
           ,player==PERCENT?PERCENT_HEAD:SHTRODEL_HEAD);
}

void print_insert_direction(){
    printf("Enter the direction to move your snake:"
           " (2-down,4-left,6-right,8-up):\n");
}

void print_finish_msg(int player ,int finish_reason)
{
    printf("\nThe game finish and the winner is:\n");
    printf("*** %s player ****.\n",player==PERCENT?"SHTRODEL":"PERCENT");
    printf("The reason is %s of the ",finish_reason==ILLEGAL_MOVE?
           "Illegal move" : "Snake die");
    printf("%s player.\n\n",player==PERCENT?"PERCENT":"SHTRODEL");
}

void print_invalid_input(){
    printf("Please re-Inset valid input:\n");
}

void print_full_board(){
    printf("Full Board. The game over with no Winner.\n");
}
void print_error_input(){
    printf("Error with the input.\n");
}





int input_game_initialize(){
    int size=0;
    print_introduction_msg();
    //check if input is valid
    print_board_size_msg();
    if(scanf("%d", &size)!=size_input_success){
        return ER;
        
    }
    //checks for valid boardsize
    while((size<S||size>N ) ){
        
        print_invalid_input();
        scanf("%d", &size);
    }
    
    
    return size;
}






void array_initialize(char board[N][N], int size){
    int i=0, j=0;
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            board[i][j]=' ';
        }
    }
    
}
bool out_of_bounds(int i, int j, int size){
    if((i<0||i>(size-1))||(j<0||j>(size-1))){
        return 1;
    }
    return 0;
}

int food_location(char board[N][N], int size){
    int i=0, j=0;
    print_food_location_msg();
    if(scanf("%d %d", &i, &j)!= food_input_success){
        return ER;
    }
    //ensures food location is within bounds of the board
    
    while(out_of_bounds(i,j,size)|| board[i][j]!=' '){
        
        print_invalid_input();
        scanf("%d %d", &i, &j);
    }
    board[i][j]='F';
    
    return 0;
}

void snakes_initialize(char board[N][N], int size,int shead_s[ROW][snakepos], int shead_p[ROW][snakepos]){
    int j=0;
    board[0][0]=PERCENT_HEAD;
    board[size-1][0]=SHTRODEL_HEAD;
    for(j=1;j<3;j++){
        board[0][j]=PERCENT_BODY;
        
        
        board[size-1][j]=SHTRODEL_BODY;
        
        
    }
    for(j=0;j<3;j++){
        shead_p[0][j]=0;
        shead_p[1][j]=j;
        // first row in array holds indexs for row number
        //second row in array holds indexs for column number
        shead_s[0][j]=size-1;
        shead_s[1][j]=j;
    }
    
}
bool movement_input_invalid(int direction){
    for(int i=1;i<=no_moves;i++){
        if(direction == input_movesnake*i){
            return valid_move;
        }
    }
    return invalid_move;
}
//11 lines
int snake_direction( int turncount){
    int direction=0;
    if(turncount%turn_c==PERCENT){
        print_player_message(PERCENT);
    }else{
        print_player_message(SHTRODEL);
    }
    print_insert_direction();
    if(scanf("%d", &direction)!=direc_input_success){
        return ER;
        
    }
    while(movement_input_invalid(direction)){
        print_invalid_input();
        scanf("%d", &direction);
    }
    return direction;
}


int move_down_p(int size, int sleng_steps[S],
                char board[N][N], int shead_p[ROW][snakepos], int turncount){
    int rowh=shead_p[0][0], columnh=shead_p[1][0], L=sleng_steps[0];
    int endgame=0, snakeate=0;
    if(board[rowh+1][columnh]==' '|| board[rowh+1][columnh]=='F'){
        //ensures snake is allowed to move
        if(board[rowh+1][columnh]=='F'){
            snakeate=1;
            shead_p[0][L]=shead_p[0][L-1];
            shead_p[1][L]=shead_p[1][L-1];
        }
        board[rowh+1][columnh]=board[rowh][columnh];
        
        for(int j=0;j<L; j++){
            if(j==L-1){
                
                if(snakeate==1){
                    board[shead_p[0][j]][shead_p[1][j]]=PERCENT_BODY;
                    sleng_steps[0]=sleng_steps[0]+1;
                    sleng_steps[p_stepnoF_index]=0;
                    if(check_boardfull_no_F(size, board)==board_notf){
                        food_location(board, size);
                    }
                    break;
                }
                else{
                    board[shead_p[0][j]][shead_p[1][j]]=' ';
                    //makes sure tail is erased
                    break;}
            }
            board[ shead_p[0][j] ][ shead_p[1][j] ]=board[ shead_p[0][j+1] ][ shead_p[1][j+1] ];
            // switches every body part with previous body part
            
        }
        move_d_changeindex( sleng_steps, shead_p,
                            turncount);
        
        
    }
    else if (rowh+1>size) {
        endgame=game_over(turncount, ILLEGAL_MOVE);
        //this coveres case where snake hits snake but what about #case
    }
    else{
        endgame=game_over(turncount, ILLEGAL_MOVE);
    }
    
    return endgame;
    
    
}

//11 lines
void move_d_changeindex(int sleng_steps[S],int shead[ROW][snakepos],
                        int turncount){
    int L=0,  rowh=shead[0][0], columnh=shead[1][0];
    if(turncount%2==PERCENT){
     L=sleng_steps[0] ;
    }else{
        L=sleng_steps[1];
}
    for(int j=0; j<L; j++){
        if(L-1-j==0){
            shead[0][0]=rowh+1;
            shead[1][0]=columnh;
            break;
        }
        shead[0][L-1-j]=shead[0][L-2-j];
        shead[1][L-1-j]=shead[1][L-2-j];
        
        
    }


}
//11 lines
void move_u_changeindex(int sleng_steps[S],int shead[ROW][snakepos],
                        int turncount){
    int L=0,  rowh=shead[0][0], columnh=shead[1][0];
    if(turncount%2==PERCENT){
        L=sleng_steps[0] ;
    }else{
        L=sleng_steps[1];
    }
    for(int j=0; j<L; j++){
        if(L-1-j==0){
            shead[0][0]=rowh-1;
            shead[1][0] = columnh;
            break;
        }
        shead[0][L-1-j] = shead[0][L-2-j];
        //assigns to each body part its new coordinates
        shead[1][L-1-j] = shead[1][L-2-j];
        
    }

    
}
//11 lines
void move_r_changeindex(int sleng_steps[S],int shead[ROW][snakepos],
                        int turncount){
    int L=0,  rowh=shead[0][0], columnh=shead[1][0];
    if(turncount%2==PERCENT){
        L=sleng_steps[0] ;
    }else{
        L=sleng_steps[1];
    }
    for(int j=0; j<L; j++){
        if(L-1-j==0){
            shead[0][0]=rowh;
            shead[1][0]=columnh+1;
            break;
        }
        shead[0][L-1-j]=shead[0][L-2-j];
        //assigns to each body part its new coordinates
        shead[1][L-1-j]=shead[1][L-2-j];
        
    }
    
}
//11 lines
void move_l_changeindex(int sleng_steps[S],int shead[ROW][snakepos],
                        int turncount){
        int L=0,  rowh=shead[0][0], columnh=shead[1][0];
    if(turncount%2==PERCENT){
        L=sleng_steps[0] ;
    }else{
        L=sleng_steps[1];
    }
    for(int j=0; j<L; j++){
        if(L-1-j==0){
            shead[0][0]=rowh;
            shead[1][0]=columnh-1;
            break;
        }
        shead[0][L-1-j]=shead[0][L-2-j];
        //assigns to each body part its new coordinates
        shead[1][L-1-j]=shead[1][L-2-j];
        
        
    }
    
}

//9 lines
int food_found(int sleng_steps[S],char board[N][N],int shead[ROW][snakepos],
               int rowh, int columnh, int turncount){
    int snakeate=0,L=0;
    
    if(turncount % 2==PERCENT){
        L=sleng_steps[0] ;
    }else{
        L=sleng_steps[1];
    }
    
    if(board[rowh][columnh]=='F'){
        snakeate=1;
        shead[0][L]=shead[0][L-1];
        shead[1][L]=shead[1][L-1];
    }
    
    
    
    return snakeate;
}




int move_left_p(int size, int sleng_steps[S],char board[N][N],
                int shead_p[ROW][snakepos], int turncount){
    int rowh=shead_p[0][0], columnh=shead_p[1][0], L=sleng_steps[0];
    int endgame=0, snakeate=0;
    if(board[rowh][columnh-1]==' '|| board[rowh][columnh-1]=='F'){
        //ensures snake is allowed to move
        
        if(board[rowh][columnh-1]=='F'){
            snakeate=1;
            shead_p[0][L]=shead_p[0][L-1];
            shead_p[1][L]=shead_p[1][L-1];
        }
        board[rowh][columnh-1]=board[rowh][columnh];
        
        for(int j=0;j<L; j++){
            if(j==L-1){
                if( snakeate==1){
                    board[shead_p[0][j]][shead_p[1][j]]=PERCENT_BODY;
                    sleng_steps[0]=sleng_steps[0]+1;
                     sleng_steps[p_stepnoF_index]=0;
                    if(check_boardfull_no_F(size, board)==board_notf){
                        food_location(board, size);
                    }
                    break;
                }
                
                else{ board[shead_p[0][j]][shead_p[1][j]]=' ';
                    //makes sure tail is erased
                    break;
                }
            }
            board[ shead_p[0][j] ][ shead_p[1][j] ]=board[ shead_p[0][j+1] ][ shead_p[1][j+1] ];
            // switches every body part with previous body part
            
        }
        move_l_changeindex( sleng_steps, shead_p,
                            turncount);
        
        
        
    }
    else if (columnh-1<0) {
        endgame=game_over(turncount, ILLEGAL_MOVE);
    }
    else{
        endgame=game_over(turncount, ILLEGAL_MOVE);
    }
    
    return endgame;
    
    
    
}

int move_right_p(int size, int sleng_steps[S],char board[N][N],
                 int shead_p[ROW][snakepos], int turncount){
    
    int rowh=shead_p[0][0], columnh=shead_p[1][0], L=sleng_steps[0];
    int endgame=0, snakeate=0;
    if((board[rowh][columnh+1]==' ')|| (board[rowh][columnh+1]=='F')){
        //ensures snake is allowed to move
        //make sure that you create a special case for F
        
        if(board[rowh][columnh+1]=='F'){
            snakeate=1;
            shead_p[0][L]=shead_p[0][L-1];
            shead_p[1][L]=shead_p[1][L-1];
            // CREATES A NEW ADDRESS IN THE ARRAY FOR NEW BODY PART ADDED
        }
        
        board[rowh][columnh+1]=board[rowh][columnh];
        
        for(int j=0;j<L; j++){
            if(j==L-1){
                if( snakeate==1){
                    board[shead_p[0][j]][shead_p[1][j]]=PERCENT_BODY;
                    sleng_steps[0]=sleng_steps[0]+1;
                    sleng_steps[p_stepnoF_index]=0;
                    if(check_boardfull_no_F(size, board)==board_notf){
                        food_location(board, size);
                    }
                    
                    break;
                }
                else {
                    board[shead_p[0][j]][shead_p[1][j]]=' ';
                    //makes sure tail is erased
                    break;
                }
            }
            board[ shead_p[0][j] ][ shead_p[1][j] ]=board[ shead_p[0][j+1] ][ shead_p[1][j+1] ];
            // switches every body part with previous body part
            
        }
        
        move_r_changeindex( sleng_steps, shead_p,
                           turncount);
    }
    else if (columnh+1>size) {
        endgame=game_over(turncount, ILLEGAL_MOVE);
        //this coveres case where snake hits snake but what about #case
    }
    else{
        endgame=game_over(turncount, ILLEGAL_MOVE);
    }
    
    return endgame;
    
}


int move_up_p(int size, int sleng_steps[S],char board[N][N],
              int shead_p[ROW][snakepos], int turncount){
    
    int rowh=shead_p[0][0], columnh=shead_p[1][0], L=sleng_steps[0];
    int endgame=0, snakeate=0;
    if(board[rowh-1][columnh]==' '|| board[rowh-1][columnh]=='F'){
        //ensures snake is allowed to move
        //make sure that you create a special case for F
        if(board[rowh-1][columnh]=='F'){
            snakeate=1;
            shead_p[0][L]=shead_p[0][L-1];
            shead_p[1][L]=shead_p[1][L-1];
        }
        board[rowh-1][columnh]=board[rowh][columnh];
        
        for(int j=0;j<L; j++){
            if(j==L-1){
                
                if( snakeate==1){
                    board[shead_p[0][j]][shead_p[1][j]]=PERCENT_BODY;
                    sleng_steps[0]=sleng_steps[0]+1;
                    sleng_steps[p_stepnoF_index]=0;
                    if(check_boardfull_no_F(size, board)==board_notf){
                        food_location(board, size);
                    }
                    break;
                }
                else { board[shead_p[0][j]][shead_p[1][j]]=' ';
                    //makes sure tail is erased
                    break;}
            }
            board[ shead_p[0][j] ][ shead_p[1][j] ]=board[ shead_p[0][j+1] ][ shead_p[1][j+1] ];
            // switches every body part with previous body part
            
        }
        move_u_changeindex( sleng_steps, shead_p,
                           turncount);
    }
    else if (rowh-1<0) {
        endgame=game_over(turncount, ILLEGAL_MOVE);
        //this coveres case where snake hits snake but what about #case
    }
    else{
        endgame=game_over(turncount, ILLEGAL_MOVE);
    }
    
    return endgame;
    
    
}
//13 lines
int move_snake_p(int size, int direction,int sleng_steps[S],char board[N][N],
                 int shead_p[ROW][snakepos],int turncount, int max_steps){
    int endgame=not_yet;
    sleng_steps[p_stepnoF_index]++;
    
    if(sleng_steps[p_stepnoF_index]==max_steps){
        endgame=game_over(turncount, SNAKE_DIE);
        return endgame;
    }
    
    endgame = psnake_movement_direction(size, direction, sleng_steps, board,
                                         shead_p, turncount);
    
    if(check_boardfull_yes_F(size, board)==board_full){
        
        print_board(board, size);
        print_full_board();
        return board_full;
        
    }
    if(endgame==not_yet){
        
        print_board(board, size);
        
    }
    return endgame;
    
}






int move_down_s(int size, int sleng_steps[S],
                char board[N][N],int shead_s[ROW][snakepos],
                int turncount){
    int rowh=shead_s[0][0], columnh=shead_s[1][0], L=sleng_steps[1];
    int endgame=not_yet, snakeate=not_yet;
    if(board[rowh+1][columnh]==' '|| board[rowh+1][columnh]=='F'){
        //ensures snake is allowed to move
snakeate=food_found(sleng_steps,board,shead_s, rowh+1, columnh,
                            turncount);
        board[rowh+1][columnh]=board[rowh][columnh];
        
        for(int j=0;j<L; j++){
            if(j==L-1){
                if(snakeate==1){
                    board[shead_s[0][j]][shead_s[1][j]]=SHTRODEL_BODY;
                    sleng_steps[1]=sleng_steps[1]+1;
                    sleng_steps[s_stepnoF_index]=0;
                    if(check_boardfull_no_F(size, board)==board_notf){
                        food_location(board, size);
                    }
                    break;
                }
                //lengthens the snake incase snake eats
            
                else{    board[shead_s[0][j]][shead_s[1][j]]=' ';
                    //makes sure tail is erased
                    break;}
            }
            board[ shead_s[0][j] ][ shead_s[1][j] ]=board[ shead_s[0][j+1] ][ shead_s[1][j+1] ];
            // switches every body part with previous body part
            
        }
        move_d_changeindex( sleng_steps, shead_s,
                           turncount);
        

        
    }
    else if (rowh+1>size) {
        endgame=game_over(turncount, ILLEGAL_MOVE);
        //this coveres case where snake hits snake but what about #case
    }
    else{
        endgame=game_over(turncount, ILLEGAL_MOVE);
    }
    
    return endgame;
    
    
}

int move_left_s(int size, int sleng_steps[S],
                char board[N][N],int shead_s[ROW][snakepos],
                int turncount){
    int rowh=shead_s[0][0], columnh=shead_s[1][0], L=sleng_steps[1];
    int endgame=0, snakeate=0;
    if(board[rowh][columnh-1]==' '|| board[rowh][columnh-1]=='F'){
        //ensures snake is allowed to move
        
     //   if(board[rowh][columnh-1]=='F'){
       //     snakeate=1;
      //      shead_s[0][L]=shead_s[0][L-1];
       //     shead_s[1][L]=shead_s[1][L-1];
       // }
 snakeate=food_found(sleng_steps,board,shead_s, rowh, columnh-1 ,
                     turncount);
        
        board[rowh][columnh-1]=board[rowh][columnh];
        
        for(int j=0;j<L; j++){
            if(j==L-1){
                if( snakeate==1){
                    board[shead_s[0][j]][shead_s[1][j]]=SHTRODEL_BODY;
                    sleng_steps[1]=sleng_steps[1]+1;
                    sleng_steps[s_stepnoF_index]=0;
                    if(check_boardfull_no_F(size, board)==board_notf){
                        food_location(board, size);
                    }
                    break;
                }
                else{
                    board[shead_s[0][j]][shead_s[1][j]]=' ';
                    //makes sure tail is erased
                    break;
                }
            }
            board[ shead_s[0][j] ][ shead_s[1][j] ]=board[ shead_s[0][j+1] ][ shead_s[1][j+1] ];
            // switches every body part with previous body part
            
        }
      
        move_l_changeindex( sleng_steps, shead_s,
                           turncount);
        
        
        
    }
    else if (columnh-1<0) {
        endgame=game_over(turncount,ILLEGAL_MOVE);
        //this coveres case where snake hits snake but what about #case
    }
    else{
        endgame=game_over(turncount,ILLEGAL_MOVE);
    }
    
    return endgame;
    
    
    
}

int move_right_s(int size, int sleng_steps[S],
                 char board[N][N],int shead_s[ROW][snakepos],
                 int turncount){
    
    int rowh=shead_s[0][0], columnh=shead_s[1][0], L=sleng_steps[1];
    int endgame=0, snakeate=0;
    
    if((board[rowh][columnh+1]==' ')|| (board[rowh][columnh+1]=='F')){
        //ensures snake is allowed to move
        //make sure that you create a special case for F
        snakeate=food_found(sleng_steps,board,shead_s, rowh, columnh+1 ,
                            turncount);
        
        board[rowh][columnh+1]=board[rowh][columnh];
        
        for(int j=0;j<L; j++){
            if(j==L-1){
                if( snakeate==1){
                    board[shead_s[0][j]][shead_s[1][j]]=SHTRODEL_BODY;
                    sleng_steps[1]=sleng_steps[1]+1;
                    sleng_steps[s_stepnoF_index]=0;
                    if(check_boardfull_no_F(size, board)==board_notf){
                        food_location(board, size);
                    }
                    break;
                }
                else {board[shead_s[0][j]][shead_s[1][j]]=' ';
                    //makes sure tail is erased
                    break;
                }
            }
board[ shead_s[0][j] ][ shead_s[1][j] ]=board[ shead_s[0][j+1] ][ shead_s[1][j+1] ];
            // switches every body part with previous body part
            
        }
        move_r_changeindex( sleng_steps, shead_s,
                           turncount);
        
        
    }
    else if (columnh+1>size) {
        endgame=game_over(turncount, ILLEGAL_MOVE);
        //this coveres case where snake hits snake but what about #case
    }
    else{
        endgame=game_over(turncount, ILLEGAL_MOVE);
    }
    
    return endgame;
    
}


int move_up_s(int size, int sleng_steps[S],
              char board[N][N],int shead_s[ROW][snakepos],
              int turncount){
    
    int rowh=shead_s[0][0], columnh=shead_s[1][0], L=sleng_steps[1];
    int endgame=0, snakeate=0;
    if(board[rowh-1][columnh]==' '|| board[rowh-1][columnh]=='F'){
        //ensures snake is allowed to move
        //make sure that you create a special case for F
snakeate=food_found(sleng_steps,board,shead_s, rowh-1, columnh,
                            turncount);
        board[rowh-1][columnh]=board[rowh][columnh];
        
        for(int j=0;j<L; j++){
            if(j==L-1){
                if( snakeate==1){
                    board[shead_s[0][j]][shead_s[1][j]]=SHTRODEL_BODY;
                    sleng_steps[1]=sleng_steps[1]+1;
                    sleng_steps[s_stepnoF_index]=0;
                    if(check_boardfull_no_F(size, board)==board_notf){
                        food_location(board, size);
                    }
                    break;
                }
                else{board[shead_s[0][j]][shead_s[1][j]]=' ';
                    //makes sure tail is erased
                    break;}
            }
            board[ shead_s[0][j] ][ shead_s[1][j] ]=board[ shead_s[0][j+1] ][ shead_s[1][j+1] ];
            // switches every body part with previous body part
            
        }
        
        move_u_changeindex( sleng_steps, shead_s,
                           turncount);
        
        
    }
    else if (rowh-1<0) {
        endgame= game_over(turncount, ILLEGAL_MOVE);
        //this coveres case where snake hits snake but what about #case
    }
    else{
        endgame= game_over(turncount, ILLEGAL_MOVE);
    }
    return endgame;
    
    
    
    
}

//13 lines
int move_snake_s(int size, int direction,int sleng_steps[S],char board[N][N],
                 int shead_s[ROW][snakepos], int turncount, int max_steps){
    int endgame=not_yet;
    sleng_steps[s_stepnoF_index]++;
    if(sleng_steps[s_stepnoF_index]==max_steps){
        endgame=game_over(turncount, SNAKE_DIE);
        return endgame;
    }

    endgame = ssnake_movement_direction(size, direction, sleng_steps, board,
                                        shead_s, turncount);
    
    if(check_boardfull_yes_F(size, board)==board_full){
        
        print_board(board, size);
        print_full_board();
        return board_full;
        
    }
    if(endgame==not_yet){
        
        print_board(board, size);
        
    }
    return endgame;
}



// 10 lines
int ssnake_movement_direction(int size, int direction,
                              int sleng_steps[S],char board[N][N],
                              int shead_s[ROW][snakepos], int turncount){
    int endgame=not_yet;
    if(direction==down){
        endgame= move_down_s(size, sleng_steps, board, shead_s, turncount);
    }
    
    if(direction==left){
        endgame=move_left_s(size, sleng_steps, board, shead_s, turncount);
    }
    if(direction==right){
        endgame=move_right_s(size, sleng_steps, board, shead_s, turncount);
    }
    
    if(direction==up){
        endgame= move_up_s(size, sleng_steps, board, shead_s, turncount);
    }
    
    
    
    return endgame;
}

// 10 lines
int psnake_movement_direction(int size, int direction,
                              int sleng_steps[S],char board[N][N],
                              int shead_p[ROW][snakepos], int turncount){
    int endgame=not_yet;
    if(direction==down){
        endgame= move_down_p(size, sleng_steps, board, shead_p, turncount);
    }
    
    if(direction==left){
        endgame= move_left_p(size, sleng_steps, board, shead_p, turncount);
    }
    if(direction==right){
        endgame=move_right_p(size, sleng_steps, board, shead_p, turncount);
    }
    
    if(direction==up){
        endgame= move_up_p(size, sleng_steps, board, shead_p, turncount);
    }
    
    return endgame;
}



//7 lines
int game_over( int turncount, int finish_reason){
    int FR=finish_reason;
    int player;
    if(turncount%turn_c==PERCENT){
        player=PERCENT;
    }
    else {
        player=SHTRODEL;
    }
    print_finish_msg( player, FR);
    
    
    return game_ended;
    
}


//9 lines
int check_boardfull_yes_F(int size, char board[N][N]){
    int boardfull=board_full;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(board[i][j]==' '||board[i][j]=='F'){
                boardfull=board_notf;
                break;
            }
            
            
        }
        
    }
    if(boardfull==board_full){
        return board_full;
    }
    
    return board_notf;
    
    
}



//9 lines
int check_boardfull_no_F(int size, char board[N][N]){
    int boardfull=board_full;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(board[i][j]==' '){
                boardfull=board_notf;
                break;
            }
            
            
        }
        
    }
    if(boardfull==board_full){
        return board_full;
    }
    
    return board_notf;
    
    
}

//7 lines
void snake_move_loop(int size, int direction,int sleng_steps[S],
                     char board[N][N], int shead_s[ROW][snakepos],
                     int shead_p[ROW][snakepos],int turncount,
                     int max_steps){
    int endgame= not_yet;
    while(endgame==not_yet){
        direction=snake_direction(turncount);
        
        if(turncount%turn_c==PERCENT) {
            
            endgame= move_snake_p(size, direction,sleng_steps, board, shead_p,
                                  turncount, max_steps);
        }
        else {
            
            endgame= move_snake_s(size, direction,sleng_steps, board, shead_s,
                                  turncount, max_steps);
        }
        turncount++;
    }
}



