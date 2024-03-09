#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int pentominos[12][8][8] =
{
 {
  { -1,1, 0,1, 1,1, 0,2 }
 },

 {
  { 1,0, 1,1, 2,1, 2,2 },
  { -1,1, 0,1, -2,2, -1,2 },
  { 0,1, 1,1, 1,2, 2,2 },
  { 1,0, -1,1, 0,1, -1,2 }
 },

 {
  { -1,1, 0,1, 0,2, 1,2 },
  { -1,1, 0,1, 1,1, -1,2 },
  { 1,0, 1,1, 2,1, 1,2 },
  { -2,1, -1,1, 0,1, -1,2 },
  { 0,1, 1,1, -1,2, 0,2 },
  { 0,1, 1,1, 2,1, 1,2 },
  { 1,0, -1,1, 0,1, 0,2 },
  { -1,1, 0,1, 1,1, 1,2 }
 },

 {
  { 0,1, 0,2, 1,2, 2,2 },
  { 1,0, 2,0, 0,1, 0,2 },
  { 1,0, 2,0, 2,1, 2,2 },
  { 0,1, -2,2, -1,2, 0,2 }
 },

 {
  { 1,0, -2,1, -1,1, 0,1 },
  { 0,1, 0,2, 1,2, 1,3 },
  { 1,0, 2,0, -1,1, 0,1 },
  { 0,1, 1,1, 1,2, 1,3 },
  { 1,0, 1,1, 2,1, 3,1 },
  { -1,1, 0,1, -1,2, -1,3 },
  { 1,0, 2,0, 2,1, 3,1 },
  { 0,1, -1,2, 0,2, -1,3 }
 },

 {
  { 0,1, 1,1, 2,1, 0,2 },
  { 1,0, 2,0, 1,1, 1,2 },
  { -2,1, -1,1, 0,1, 0,2 },
  { 0,1, -1,2, 0,2, 1,2 }
 },

 {
  { 0,1, 1,1, 0,2, 0,3 },
  { 1,0, 2,0, 3,0, 2,1 },
  { 0,1, -1,2, 0,2, 0,3 },
  { -1,1, 0,1, 1,1, 2,1 },
  { -1,1, 0,1, 0,2, 0,3 },
  { -2,1, -1,1, 0,1, 1,1 },
  { 0,1, 0,2, 1,2, 0,3 },
  { 1,0, 2,0, 3,0, 1,1 }
 },
 
 {
  { 1,0, 1,1, 1,2, 1,3 },
  { -3,1, -2,1, -1,1, 0,1 },
  { 0,1, 0,2, 0,3, 1,3 },
  { 1,0, 2,0, 3,0, 0,1 },
  { 1,0, 0,1, 0,2, 0,3 },
  { 1,0, 2,0, 3,0, 3,1 },
  { 0,1, 0,2, -1,3, 0,3 },
  { 0,1, 1,1, 2,1, 3,1 }
 },

 {
  { 1,0, 0,1, 0,2, 1,2 },
  { 1,0, 2,0, 0,1, 2,1 },
  { 1,0, 1,1, 0,2, 1,2 },
  { 2,0, 0,1, 1,1, 2,1 }
 },

 {
  { -1,1, 0,1, -1,2, 0,2 },
  { 1,0, 0,1, 1,1, 2,1 },
  { 1,0, 0,1, 1,1, 0,2 },
  { 1,0, 2,0, 1,1, 2,1 },
  { 0,1, 1,1, 0,2, 1,2 },
  { 1,0, 2,0, 0,1, 1,1 },
  { 1,0, 0,1, 1,1, 1,2 },
  { 1,0, -1,1, 0,1, 1,1 }
 },

 {
  { 1,0, 1,1, 1,2, 2,2 },
  { -2,1, -1,1, 0,1, -2,2 },
  { 1,0, 0,1, -1,2, 0,2 },
  { 0,1, 1,1, 2,1, 2,2 }
 },

 {
  { 0,1, 0,2, 0,3, 0,4 },
  { 1,0, 2,0, 3,0, 4,0 }
 }
};

int board[22][22];
int tempboard[22][22];
int w;
int h;

const int numVariants[12] = {
 1, 4, 8, 4, 8, 4, 8, 8, 4, 8, 4, 2
};

int inUse[12] = {
 0,0,0,0,0,0,0,0,0,0,0,0
};

int freeSpaces = 9999;
int solutionsFound = 0;
int searchUntil = 1;

void configureBoard(int width, int height){
 if( width < 1 || height < 1 || width > 20 || height > 20 ){
  fprintf(stderr, "Invalid board configuration\n");
  exit(1);
 }
 int x,y;
 for( y=0; y<22; y++){
  for( x=0; x<22; x++ ){
   board[x][y]=-1;
   if(x && y && x<=width && y<=height ){
    board[x][y]=0;
   }
  }
 }
 w = width;
 h = height;
 freeSpaces = width*height;
}

int printSolutionColoursEnabled = 0;


void printSolution_pointedLines(){
 int x,y,this,last=0,surrounds;
 printf("\n ");
 for( y=1; y<=h; y++){
  for( x=1; x<=w; x++ ){
   this = board[x][y];
   if( this>0 ){
    if( printSolutionColoursEnabled && last != this ){
     printf("\x1b[38;5;%dm", 29+(this<<4) );
     last = this;
    }
    surrounds = (board[x-1][y] == this)  |  (board[x][y-1] == this)<<1  | (board[x+1][y] == this)<<2  |  (board[x][y+1] == this)<<3;
    printf("%s", (char*[]){ "0 ", "╾ ", "╿ ", "┛ ", "╼━", "━━", "┗━", "┻━", "╽ ", "┓ ", "┃ ", "┫ ", "┏━", "┳━", "┣━", "╋━"}[surrounds] );
   } else {
    printf("  ");
   }
  }
  printf("\n ");
 }
}

void printSolution_roundedEdges(){
 int x,y,this,last=0,surrounds;
 printf("\n ");
 for( y=1; y<=(h<<1)+1; y++){
  for( x=1; x<=(w<<2)+3; x++ ){
   this = board[x>>2][y>>1];
   if( this>0 ){
    if( printSolutionColoursEnabled && last != this ){
     printf("\x1b[38;5;%dm", 29+(this<<4) );
     last = this;
    }
    surrounds = (board[(x-1)>>2][y>>1] == this)  |  (board[x>>2][(y-1)>>1] == this)<<1  | (board[(x+1)>>2][y>>1] == this)<<2  |  (board[x>>2][(y+1)>>1] == this)<<3
                | (board[(x-1)>>2][(y-1)>>1]==this)<<4 | (board[(x+1)>>2][(y-1)>>1]==this)<<5 | (board[(x-1)>>2][(y+1)>>1]==this)<<6 | (board[(x+1)>>2][(y+1)>>1]==this)<<7;
    printf("%s", (char*[]){
     "A0","A1","A2","A3","A4","A5","A6","A7","A8","A9","Aa","Ab","Ac","Ad","Ae","Af",
     "B0","B1","B2","╯" ,"B4","B5","B6","B7","B8","B9","Ba","Bb","Bc","Bd","Be","Bf",
     "C0","C1","C2","C3","C4","C5","╰" ,"C7","C8","C9","Ca","Cb","Cc","Cd","Ce","Cf",
     "D0","D1","D2","D3","D4","D5","D6","─" ,"D8","D9","Da","Db","Dc","Dd","De","Df",
     "E0","E1","E2","E3","E4","E5","E6","E7","E8","╮" ,"Ea","Eb","Ec","Ed","Ee","Ef",
     "F0","F1","F2","F3","F4","F5","F6","F7","F8","F9","Fa","│" ,"Fc","Fd","Fe","Ff",
     "G0","G1","G2","G3","G4","G5","G6","G7","G8","G9","Ga","Gb","Gc","Gd","Ge","Gf",
     "H0","H1","H2","H3","H4","H5","H6","─" ,"H8","H9","Ha","│" ,"Hc","Hd","He","╭" ,
     "I0","I1","I2","I3","I4","I5","I6","I7","I8","I9","Ia","Ib","╭" ,"Id","Ie","If",
     "J0","J1","J2","J3","J4","J5","J6","J7","J8","J9","Ja","Jb","Jc","Jd","Je","Jf",
     "K0","K1","K2","K3","K4","K5","K6","K7","K8","K9","Ka","Kb","Kc","Kd","│" ,"Kf",
     "L0","L1","L2","L3","L4","L5","L6","─" ,"L8","L9","La","Lb","Lc","Ld","│" ,"╮" ,
     "M0","M1","M2","M3","M4","M5","M6","M7","M8","M9","Ma","Mb","Mc","─" ,"Me","Mf",
     "N0","N1","N2","N3","N4","N5","N6","N7","N8","N9","Na","│" ,"Nc","─" ,"Ne","╰" ,
     "O0","O1","O2","O3","O4","O5","O6","O7","O8","O9","Oa","Ob","Oc","─" ,"│" ,"╯" ,
     "P0","P1","P2","P3","P4","P5","P6","P7","P8","P9","Pa","Pb","Pc","Pd","Pe"," " 
    }[surrounds] );
   } else {
    printf(" ");
   }
  }
  printf("\n ");
 }
}

void (*printSolution)(void) = printSolution_roundedEdges;

#define ISPOSSIBLE_FILLED_VALUE -2
int isPossibleFloodFiller(int x, int y){
 tempboard[x][y] = ISPOSSIBLE_FILLED_VALUE;
 int count = 1;
 if(!tempboard[x-1][y]) count += isPossibleFloodFiller( x-1, y );
 if(!tempboard[x][y-1]) count += isPossibleFloodFiller( x, y-1 );
 if(!tempboard[x+1][y]) count += isPossibleFloodFiller( x+1, y );
 if(!tempboard[x][y+1]) count += isPossibleFloodFiller( x, y+1 );
 return count;
}
int isPossible(int start_y){
 int x,y, result = 1;
 memcpy( tempboard, board, sizeof(board) );
 for(y=start_y; y<=h; y++){
  for(x=1; x<=w; x++){
   if( !tempboard[x][y] && (isPossibleFloodFiller(x,y)%5) ){
    return 0;
   }
  }
 }
 return 1;
}

void solve(int x, int y){
 while( board[x][y] ){
  x+=1; if(x>w){ x=1; y+=1; }
 }
 int piece, variant, n, *pieceIndices;
 for( piece=0; piece<12; piece++ ){
  if( !inUse[piece] ){
   n = numVariants[piece];
   for( variant=0; variant<n; variant++ ){
    pieceIndices = pentominos[piece][variant];
    if( !( board[x+pieceIndices[0]][y+pieceIndices[1]]
           ||
           board[x+pieceIndices[2]][y+pieceIndices[3]]
           ||
           board[x+pieceIndices[4]][y+pieceIndices[5]]
           ||
           board[x+pieceIndices[6]][y+pieceIndices[7]] ) )
    {
     int v = piece+1;

     board[x][y] = v;
     board[x+pieceIndices[0]][y+pieceIndices[1]] = v;
     board[x+pieceIndices[2]][y+pieceIndices[3]] = v;
     board[x+pieceIndices[4]][y+pieceIndices[5]] = v;
     board[x+pieceIndices[6]][y+pieceIndices[7]] = v;

     if( !isPossible(y) ) goto wasntPossible;
     #ifdef DEBUG
     else {
      printf("\n\x1b[38;5;%dm",255 );
      for(int i=0; i<12; i++){
       printf(" %d", numVariants[i]);
      }
      putchar('\n');
      for(int i=0; i<12; i++){
       printf(" %d", inUse[i]);
      }
      printf("\nfreeSpaces == %d\n",freeSpaces);
      printSolution();
      #ifndef DONTWAIT
      usleep(16.6*1000*7);
      #endif
     }
     #endif
     inUse[piece] = 1;/* 1 */ freeSpaces -= 5;
     if( !freeSpaces ){
      #ifdef DEBUG
      system("beep");
      #endif
      solutionsFound++;
      printSolution();
      if( solutionsFound == searchUntil ){
       printf("\n\n");
       exit(0);
      }
      #ifdef QUIT
      exit(0);
      #endif
     } else {
      solve(x,y);
     }
     inUse[piece] = 0; freeSpaces += 5;
     wasntPossible:
     board[x][y] = 0;
     board[x+pieceIndices[0]][y+pieceIndices[1]] = 0;
     board[x+pieceIndices[2]][y+pieceIndices[3]] = 0;
     board[x+pieceIndices[4]][y+pieceIndices[5]] = 0;
     board[x+pieceIndices[6]][y+pieceIndices[7]] = 0;
     
    }
   }
  }
 }
}

void configureBoardFromString( char *string ){
 if( *string == '\n' ) string++;
 int width=0;
 while( string[width] && string[width] != '\n' ){
  width++;
 }
 int i=0,height=0;
 while( string[i] ){
  height += (string[i] == '\n');
  i++;
 }
 configureBoard( width, height + (string[i-1]!='\n') );
 i=0;
 int x=1,y=1;
 while( string[i] ){
  if( string[i] == '#' ){
   board[x][y] = -1;
   freeSpaces--;
  }
  if(string[i]=='\n' || x>w){
   x=1; y+=1;
  } else {
   x++;
  }
  i++;
 }
}

int main(int argc, char **argv){
 int width = 0, height = 0;

 /* Usage message */
 if( argc == 1 ){ 
  usageMessage:
  printf("=== Pentomino puzzle solution finder ===\n\nUsage and command line options:\n");
  printf(" -w [width] \n");
  printf(" -h [height] \n");
  printf(" -board [board string] \n");
  printf(" -n [number of solutions to stop at, default 1] \n");
  printf(" -all (don't stop until search is exhausted)\n");
  printf(" -style [number] (choose the style you want to display the solutions in)\n   (0: rounded edges (bigger)  1: sharpened lines (smaller)) \n\n");
 
  printf("Try copy pasting these example commands:\n\n");
  printf("Example 1:\n%s  -w 20  -h 3\n\n",argv[0]);
  printf("Example 2:\n%s  -w 12  -h 5  -n 2\n\n",argv[0]);
  printf("Example 3:\n%s  -w 5 -h 5  -style 1\n\n",argv[0]);
  printf("Example 4:\n%s -board '\n#......#\n........\n........\n........\n........\n........\n........\n#......#'\n\n",argv[0]);
  return 1;
 }

 int i;

 /* Scenario: a command line option was missing its parameter */
 if(0){
  missingParameter:
  printf("%s : missing parameter\n\n",argv[i-1]);
  goto usageMessage;
 }

 /* Parse command line arguments */
 for( i=1; i<argc; i++ ){
  if( ! strcmp( "-w", argv[i] ) ){
   i++; if( i==argc ) goto missingParameter;
   width = atoi( argv[i] );
  }else if( ! strcmp( "-h", argv[i] ) ){ 
   i++; if( i==argc ) goto missingParameter;
   height = atoi( argv[i] );
  }else if( ! strcmp( "-board", argv[i] ) ){ 
   i++; if( i==argc ) goto missingParameter;
   width=0; height=0;
   configureBoardFromString(argv[i]);
  }else if( ! strcmp( "-n", argv[i] ) ){
   i++; if( i==argc ) goto missingParameter;
   searchUntil = atoi( argv[i] );
  }else if( ! strcmp( "-all", argv[i] ) ){ 
   searchUntil = 0;
  }else if( ! strcmp( "-style", argv[i] ) ){ 
   i++; if( i==argc ) goto missingParameter;
   int style = atoi( argv[i] ) & 1;
   printSolution = (void*[]){ printSolution_roundedEdges, printSolution_pointedLines }[style];
  }else {
   printf("Unknown option '%s'\n\n",argv[i]);
   goto usageMessage;
  }
 }

 /* Configure board using specified width height if they were given */
 if( width && height ) configureBoard(width,height);

 if( freeSpaces>12*5 || !isPossible(1) ){
  fprintf(stderr,"Impossible/unsolvable board configuration\n");
  return 1;
 }

 /* Print terminal colours if this is a terminal */
 printSolutionColoursEnabled = isatty(STDOUT_FILENO);

 /* Find solutions */
 solve(1,1);

 /* Reset colours if this is a terminal */
 if( printSolutionColoursEnabled ) printf("\x1b[38;5;%dm",255 );

 if( searchUntil )
  printf("\nCompleted\n");
 else
  printf("\nCompleted, %d solutions found\n",solutionsFound);
 return 0;
}
