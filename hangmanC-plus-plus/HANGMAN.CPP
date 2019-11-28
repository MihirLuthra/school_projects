#include <iostream.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <stdio.h>
#include <dos.h>

#define SIZE 16
#define toupper( x ) ( x > 96 && x < 123 ? x -= 32 : x )
#define isalpha( x ) ( x > 64 && x < 91 ? 1 : 0 )

//Prototypes
void Hangman( ) ;
void ask( ) ; // Asks the user whether he wants to play.
void refresh( char * , char * ) ; // Refreshes all data to start a new game
void sample_game( ) ; // Shows the user a sample game.
void draw( int ) ; // To draw the man.
//----------------

int main( )
{
	clrscr( ) ;
	ask( ) ;
	Hangman( ) ;
	getch( ) ;
	return 0 ;
}

void Hangman( )
{
	randomize( ) ;
	char sports[ SIZE ][ 20 ] = {
					"CRICKET" ,
					"SOCCER" ,
					"VOLLEYBALL" ,
					"SKATING" ,
					"BADMINTON" ,
					"TABLETENNIS" ,
					"LAWNTENNIS" ,
					"BASKETBALL" ,
					"BASEBALL" ,
					"HOCKEY" ,
					"ICESKATING" ,
					"ICEHOCKEY" ,
					"SWIMMING" ,
					"SHOOTING" ,
					"ARCHERY" ,
					"RACING"
				    } ;
	char hangman[80] ;  // To store the random sport name.
	int rand = random( SIZE ) ;
	int chance = 0 ;//To count the wrong attempts made
	int i , l = strlen( sports[ rand ] ) ;
	for( i = 0 ; i < l ; ++ i )
	{
		*( hangman + i ) = '-' ;//initially hangman contains dashes
	}
	*( hangman + l ) = '\0' ;// So that when we do operations with this
	//string it checks till here only
	char c ;   // To input letter
	char store[80] ; //Stores the characters which have already been entered
	int gd = DETECT , gm , gerror ;
	initgraph( &gd , &gm , "C:\\TC\\BGI" ) ;
	gerror = graphresult( ) ;
	if( gerror != grOk )
	{
		cout << grapherrormsg( gerror ) ;
		getch( ) ;
		exit( 0 ) ;
	}

	cleardevice( ) ;

	gotoxy( 1 , 1 ) ;

	puts( "Do you want to see a sample game ? Enter y or n. " ) ;

	fflush( stdin ) ;

	char y ;
	y = getchar( ) ;

	if( y == 'y' )
	sample_game( ) ;



	cleardevice( ) ;

	int j = 0 ;  //For incrementing store

	setcolor( 3 ) ;
	line( 1 , 100 , getmaxx( ) , 100 ) ;//So that the text portion can be
	//floodfilled

	gotoxy( 1 , 1 ) ;

	setcolor( 15 ) ;

	setfillstyle( 0 , 0 ) ;

	for( ; ; )
	{
		fflush( stdin ) ;
		moveto( 1 , 1 ) ;
		outtext( hangman ) ;
		outtextxy( 1 , 10 , "Guess a letter:" ) ;
		gotoxy( 1 , 4 ) ;
		c = getchar( ) ;
		toupper( c ) ;
		if( !isalpha( c ) ) // So that user can only enter alphabets.
		{
			floodfill( 1 , 1 , 3 ) ;
			continue ;
		}

		if( strchr( store , c ) )
		{
			outtextxy( 1 , 40 , "Already filled." ) ;
			getch( ) ;
		}
		else
		if( strchr( sports[ rand ] , c ) )//If the letter is there it
		{                                //gets filled
			for( i = 0 ; i < l ; ++ i )
			{
				//if( sports[ rand ][ i ] == c )
				if( *( *( sports + rand ) + i ) == c )
				*( hangman + i ) = c ;
			}
			*( store + j ) = c ;
			++ j ;
		}
		else
		{
			++ chance ;// increments wrong attempt
			draw( chance ) ;


			if( chance == 6 ) //Checks whether no. of wrong attempts
			{                 //is equal to 6 or not
				floodfill( 1 , 1 , 3 ) ;
				moveto( 1 , 1 ) ;
				outtext( hangman ) ;
				outtextxy( 1 , 20 , "The sport was:" ) ;
				outtextxy( 1 , 40 , sports[ rand ] ) ;
				getch( ) ;
				cleardevice( ) ;
				settextstyle( 0 , 0 , 2 ) ;
				outtext( "GAME OVER!" ) ;
				getch( ) ;
				cleardevice( ) ;
				closegraph( ) ;
				ask( ) ;
				refresh( hangman , store ) ;
				getch( ) ;
				Hangman( ) ;
			}
		}
		draw( chance ) ;
		if( !strcmp( hangman , sports[ rand ] ) )  // Checks whether
		{                                         //the strings have
			floodfill( 1 , 1 , 3 ) ;         //become same or
			moveto( 1 , 1 ) ;                //not
			outtext( hangman ) ;
			getch( ) ;
			setcolor( 13 ) ;
			settextstyle( 0 , 0 , 2 ) ;
			cleardevice( ) ;
			outtext( "YOU WON!" ) ;
			getch( ) ;
			cleardevice( ) ;
			closegraph( ) ;
			ask( ) ;
			refresh( hangman , store ) ;
			getch( ) ;
			Hangman( ) ;
		}

		floodfill( 1 , 1 , 3 ) ;

	}
}

void ask( )
{
	clrscr( ) ;
	cout << "Do you want to play hangman?\n" ;
	cout << "Enter y or n.\n" ;
	fflush( stdin ) ;
	char y ;
	y = getchar( ) ;
	if( y == 'y' )
	return ;
	else
	{
		cout << "Press any key to exit." ;
		getch( ) ;
		fflush( stdin ) ;
		exit( 0 ) ;
	}
}

void refresh( char *hangman , char *store )
{
	int i ;
	for( i = 0 ; *( hangman + i ) ; ++ i )
	{
		*( hangman + i ) = '-' ;
	}
	for( i = 0 ; *( store + i ) ; ++ i )
	{
		*( store + i ) = '_' ;
	}
}

void sample_game( )
{
    cleardevice( ) ;
    cout << "You will be given a random sport name and you have to\n"
    << "guess the name of the sports.\n "
    << "You will be asked to enter a letter and if the letter is\n "
    << "there in the word the dash will be filled else a part of man\n "
    << "will be drawn. If the man is made completely the game gets over.\n"
    << "If you guess the the word correctly you win.\n"
    << "Sample game:\n"
    << "Press any key to view the next move of the sample game.\n"
    << "Press any key to start te game.\n"
    << "The hidden word here is HOCKEY." ;

    getch( ) ;
    cleardevice( ) ;
    moveto( 1 , 1 ) ;
    gotoxy( 1 , 1 ) ;
    setcolor( 3 ) ;
    setfillstyle( 1 , 0 ) ;
    line( 1 , 150 , getmaxx( ) , 150 ) ;// So that the portion of text can
    //be simply floodfilled.
    setcolor( 15 ) ;
    cout << "\n------\n" ;
    cout << "\nGuess a letter:\n" ;
    getch() ;
    cout << 'k' ;
    getch( ) ;
    floodfill( 1 , 1 , CYAN ) ;
    gotoxy( 1 , 1 ) ;
    cout << "\n---K--\n" ;
    cout << "\nGuess a letter:\n" ;
    getch( ) ;
    cout << 'h' ;
    getch( ) ;
    floodfill( 1 , 1 , CYAN ) ;
    gotoxy( 1 , 1 ) ;
    cout << "\nH--K--\n" ;
    cout << "\nGuess a letter:\n" ;
    getch( ) ;
    cout << 'L' ;
    getch( ) ;
    cout << "\nWrong!" ;
    getch( ) ;
    draw( 1 ) ;
    getch( ) ;
    floodfill( 1 , 1 , CYAN ) ;
    gotoxy( 1 , 1 ) ;
    cout << "\nH--K--\n" ;
    cout << "\nGuess a letter:\n" ;
    getch( ) ;
    cout << 'm' ;
    getch( ) ;
    cout << "\nWrong!" ;
    getch( ) ;
    draw( 2 ) ;
    getch( ) ;
    floodfill( 1 , 1 , CYAN ) ;
    gotoxy( 1 , 1 ) ;
    cout << "\nH--K--\n" ;
    cout << "\nGuess a letter:\n" ;
    getch( ) ;
    cout << 'o' ;
    getch( ) ;
    floodfill( 1 , 1 , CYAN ) ;
    gotoxy( 1 , 1 ) ;
    cout << "\nHO-K--\n" ;
    cout << "\nGuess a letter:\n" ;
    getch( ) ;
    cout << 'n' ;
    getch( ) ;
    cout << "\nWrong!" ;
    getch( ) ;
    draw( 3 ) ;
    getch( ) ;
    floodfill( 1 , 1 , CYAN ) ;
    gotoxy( 1 , 1 ) ;
    cout <<"\nHO-K--\n" ;
    cout << "\nGuess a letter:\n" ;
    getch( ) ;
    cout << 'p' ;
    getch( ) ;
    cout << "\nWrong!" ;
    getch( ) ;
    draw( 4 ) ;
    getch( ) ;
    floodfill( 1 , 1 , CYAN ) ;
    gotoxy( 1 , 1 ) ;
    cout <<"\nHO-K--\n" ;
    cout << "\nGuess a letter:\n" ;
    getch( ) ;
    cout << 'd' ;
    getch( ) ;
    cout << "\nWrong!" ;
    draw( 5 ) ;
    getch( ) ;
    floodfill( 1 , 1 , CYAN ) ;
    gotoxy( 1 , 1 ) ;
    cout << "\nHO-K--\n" ;
    cout << "\nGuess a letter:\n" ;
    getch( ) ;
    cout << 'y' ;
    getch( ) ;
    floodfill( 1 , 1 , CYAN ) ;
    gotoxy( 1 , 1 ) ;
    cout << "\nHO-K-Y\n" ;
    cout << "\nGuess a letter:\n" ;
    getch( ) ;
    cout << 'q' ;
    getch( ) ;
    cout << "\nWrong!" ;
    getch( ) ;
    draw( 6 ) ;
    getch( ) ;
    floodfill( 1 , 1 , CYAN ) ;
    gotoxy( 1 , 1 ) ;
    cout << "GAME OVER!" ;
    cleardevice( ) ;
}

void draw( int num )
{
	int midx = getmaxx( ) / 2 , midy = getmaxy( ) / 2 ;
	bar3d( midx , midy , midx + 30 , midy + 200 , 10 , 1 ) ;
	setlinestyle( 0 , 0 , 3 ) ;
	line( midx , midy , midx - 60 , midy ) ;
	line( midx - 60 , midy , midx - 60 , midy + 20 ) ;
	switch( num )
	{
		case 6 : line( midx - 60 , midy + 90 , midx - 40 , midy + 120 ) ;
		case 5 : line( midx - 60 , midy + 90 , midx - 80 , midy + 120 ) ;
		case 4 : line( midx - 60 , midy + 150 , midx - 40 , midy + 200 ) ;
		case 3 : line( midx - 60 , midy + 150 , midx - 80 , midy + 200 ) ;
		case 2 : line( midx - 60 , midy + 60 , midx - 60 , midy + 150 ) ;
		case 1 : circle( midx - 60 , midy + 40 , 20 ) ;
		case 0 : return ;
	}
}