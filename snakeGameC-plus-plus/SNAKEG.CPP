#include <fstream.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

int X = 40;
int Y = 12;
#define XB X/2
#define YB Y/2
#define SIZE 3
#define ESC 27
#define xisdigit( y ) ( y >= 48 && y <= 57 )
//Max X
//Max Y
//Beginning x for snake
//Beginning y for snake
//Beginning size for snake (no. of smileys)
//ascii value of ESC key
// isdigit

int speed = 100;

enum { RIGHT , LEFT , UP , DOWN };
//for knowing the direction of snake
//not for checking user's input!

// array_beg , CLASS DEFINITION STARTS HERE///////////////////////////////////////////////

//A class to create a linked list which works like an array
//only for linear array
//can vary its length any time
class array
{
	private:
		int n;
		int ret;//if memory allocation is unsuccessfull ret takes the value which assigned to the reference returned by ( )
		int state;
		struct list
		{
			int a;
			list *prev;
			list *next;
		};
		list *start;
		list *last;
	public:
		array( );
		~array( );
		int getstate( )
		{
			return state;
		}
		int& operator()( int no );
};

array :: ~array( )
{
	list *l , *ll ;
	l = start;
	for( int i = 0 ; i <= n ; ++ i )
	{
		ll = ( *l ).next ;
		delete l ;
		l = ll ;
	}
}

array :: array( )
{
	n = -1;
	state = 0;
	start = NULL;
	last = NULL;
}

int& array :: operator()( int no )
{
	if( no < 0 )
	{
		++ state;
		return ret;
	}
	if( no > n )
	{
		list *l;
		int chk = 0;
		if( n == -1 )
		{
			l = new list;
			if( l == NULL )
			{
				++ state;
				return ret;
			}
			chk = 1;
			n = 0;
			start = l;
			last = l;
		}
		for( int i = n + 1 ; i <= no ; ++ i )
		{
			l = new list;
			if( l == NULL )
			{
				list *ll ;
				l = start;

				int j;
				int ran;
				if( !chk )
				ran = i;
				else
				ran = i + 1;
				for( j = 0 ; j <= n ; ++ j )
				{
					l = ( *l ).next;
				}

				for( j = 0 ; j < ran ; ++ j )
				{
					ll = ( *l ).next ;
					delete l ;
					l = ll ;
				}
				++ state;
				return ret;
			}
			( *l ).prev = last;
			( *l ).next = NULL ;
			( *last ).next = l;
			last = l;
		}
		n = i - 1 ;
		return ( *l ).a ;
	}
	else
	{
		list *l;
		l = start;
		for( int i = 0 ; i < no ; ++ i )
		{
			l = ( *l ).next ;
		}
		return ( ( *l ).a ) ;
	}
}

// array_end , CLASS DEFINITION ENDS HERE///////////////////////////////////////////////

// p_beg
void box( int x , int y , int ch );//To print the box in which snake moves
int isleft( char c1 , char c2 );
int isup( char c1 , char c2 );
int isright( char c1 , char c2 );
int isdown( char c1 , char c2 );
int chk_up_wall( int y );     //
int chk_right_wall( int x );  // check wall collisions
int chk_left_wall( int x );   //
int chk_down_wall( int y );   //
void gameover( int s , int is );
void homepage( );
int onlynum( char * );
// p_end

// main_beg

void main( )
{
	homepage( );
	clrscr( );
	ifstream spd( "speed.mih" );
	if( spd )
	{
		spd >> speed;
		spd.close( );
	}
	ifstream d( "dim.mih" );
	if( d )
	{
		d >> X;
		d.get( );
		d >> Y;
		d.close( );
	}
	else
	{
		X = 80;
		Y = 24;
	}
	randomize( );
	int wall = 177;//character for making wall
	int sface = 2;
	int sbody = 1;
	int food = 4;
	box( X , Y , wall );
	int size = SIZE;
	int i;//for iteration of for loops
	array posnx , posny;
	for( i = 0 ; i < size ; ++ i )
	{
		posnx( i ) = ( XB - i );
		posny( i ) = YB;
		if( posny.getstate( ) || posnx.getstate( ) )
		{
			posnx.array::~array( );
			posny.array::~array( );
			main( );
		}
	}
	int dir = RIGHT;
	//direction in which snake is going
	char n1 , n2;
	int lposx , lposy;
	int fx , fy;
	int chk;
	int eaten = 1;

	for( ;; )
	{

		if( eaten )
		{
			do
			{
				chk = 0;
				fx = random( X - 3 ) + 2;
				fy = random( Y - 3 ) + 2;
				for( i = 0 ; i < size ; ++ i )
				{
					if( ( posnx( i ) == fx ) && ( posny( i ) == fy ) )
					chk = 1;
				}
			}while( chk == 1 );
			gotoxy( fx , fy );
			putchar( ( char )food );
		}
		eaten = 0;
		for( i = 0 ; i < size ; ++ i )
		{
			gotoxy( posnx( i ) , posny( i ) );

			if( i )
			putchar( ( char )sbody );
			else
			putchar( ( char )sface );
		}

		lposx = posnx( size - 1 );
		lposy = posny( size - 1 );

		for( i = size - 1 ; i > 0 ; -- i )
		{
			posnx( i ) = posnx( i - 1 );
			posny( i ) = posny( i - 1 );
		}
		if( kbhit( ) )
		{
			do
			{
				n1 = getch( );
				if( n1 == ESC )
				{
					posnx.array::~array( );
					posny.array::~array( );
					clrscr( );
					main( );
				}
				if( n1 == '\0' )
				n2 = getch( );
			}while( n1 == 'p' );

			if( isup( n1 , n2 ) && dir != DOWN )
			dir = UP;
			else
			if( isright( n1 , n2 ) && dir != LEFT )
			dir = RIGHT;
			else
			if( isleft( n1 , n2 ) && dir != RIGHT )
			dir = LEFT;
			else
			if( isdown( n1 , n2 ) && dir != UP )
			dir = DOWN;
		}
		if( dir == UP )
		-- posny( 0 );
		else
		if( dir == DOWN )
		++ posny( 0 );
		else
		if( dir == RIGHT )
		++ posnx( 0 );
		else
		if( dir == LEFT )
		-- posnx( 0 );

		if( chk_up_wall( posny( 0 ) ) )
		{
			posny( 0 ) = Y - 1;
		}
		else
		if( chk_down_wall( posny( 0 ) ) )
		{
			posny( 0 ) = 2;
		}
		else
		if( chk_right_wall( posnx( 0 ) ) )
		{
			posnx( 0 ) = 2;
		}
		else
		if( chk_left_wall( posnx( 0 ) ) )
		{
			posnx( 0 ) = X - 1;
		}
		for( i = 1 ; i < size ; ++ i )
		{
			if( ( posnx( i ) == posnx( 0 ) ) && ( posny( i ) == posny( 0 ) ) )
			{
				int dl = 150;
				int chk = 0;
				int check = 1;
				gotoxy( lposx , lposy );
				putchar( ' ' );
				for( int sd = 0 ; sd <= 5000 ; sd += dl )
				{
					if( sd <= 3500 )
						sound( random( 500 ) + 500 );
					for( int pr = size - 1 ; pr >= 0 ; -- pr )
					{
						gotoxy( posnx( pr ) , posny( pr ) );

						if( check == 1 )
						{
							if( pr )
								putchar( ( char )sbody );
							else
								putchar( ( char )sface );
						}
						else
						{
							putchar( ' ' );
						}
					}
					delay( dl );
					if( sd <= 3500 )
						nosound( );
					++ chk;
					if( chk > 1 )
					{
						chk = 0;
						if( check )
							check = 0;
						else
							check = 1;
					}
				}
			       //	delay( 1000 );
				clrscr( );
				posnx.array::~array( );
				posny.array::~array( );
				gameover( size , SIZE );
			}
		}

		if( ( posnx( 0 ) == fx ) && ( posny( 0 ) == fy ) )
		{
			++ size;
			posnx( size - 1 ) = lposx;
			posny( size - 1 ) = lposy;
			if( posnx.getstate( ) || posny.getstate( ) )
			{
				posnx.array::~array( );
				posny.array::~array( );
				main( );
			}
			eaten = 1;
		}

		delay( speed );
		gotoxy( lposx , lposy );
		putchar( ' ' );
	}
}

// main_end

// box_beg
void box( int x , int y , int ch )
{
	int i , j;
	for(i = 1 ; i <= y ; ++i )
	{
		gotoxy( 1 , i );
		for( j = 1 ; j <= x ; ++j )
		{
			if( ( i == 1 ) || ( i == y ) || ( j == 1 ) || ( j == x ) )
			{
				printf( "%c" , ch );
			}
			else
			putchar( ' ' );
		}
	}
}
// box_end
// arrow_beg
int isup( char c1 , char c2 )
{
	if( c1 == '\0' && c2 == 'H' )
	return 1;
	else
	return 0;
}
int isdown( char c1 , char c2 )
{
	if( c1 == '\0' && c2 == 'P' )
	return 1;
	else
	return 0;
}
int isright( char c1 , char c2 )
{
	if( c1 == '\0' && c2 == 'M' )
	return 1;
	else
	return 0;
}
int isleft( char c1 , char c2 )
{
	if( c1 == '\0' && c2 == 'K' )
	return 1;
	else
	return 0;
}
// arrow_end
// chkwall_beg
int chk_up_wall( int y )
{
	if( y == 1 )
	return 1;
	else
	return 0;
}
int chk_down_wall( int y )
{
	if( y == Y )
	return 1;
	else
	return 0;
}
int chk_right_wall( int x )
{
	if( x == X  )
	return 1;
	else
	return 0;
}
int chk_left_wall( int x )
{
	if( x == 1 )
	return 1;
	else
	return 0;
}
// chkwall_end
// go_beg
void gameover( int s , int is )
{
	clrscr( );
	int score = s - is;
	int ok = 0;
	int hs;
	char name[80];
	printf( "GAME OVER\nPOINTS = %d" , score );
	ifstream scr( "score.mih" );
	if( !scr )
	{
		ok = 1;
	}
	else
	{
		scr >> hs;
		if( score > hs )
		ok = 1;
		scr.close( );
	}
	if( ok )
	{
		printf( "\nCongrats!\nYou have made a high score." );
		printf( "\nPlease enter your name:\t" );
		gets( name );

		ofstream sc( "score.mih" );
		sc << score;
		sc.put( '\n' );
		int l;
		for( l = 0 ; *( name + l ) != '\0' ; ++ l );
		sc.write( name , l );
		sc.close( );
	}
	else
	{
		delay( 3000 );
	}
	main( );
}
// go_end
//hpage_beg
void homepage( )
{
	do
	{
		clrscr( );
		printf( "Choose from the following options:\n" );
		printf( "1.New Game\n2.High scores\n3.Adjust Speed\n4.Adjust dimension\n5.Exit" );
		char ch;
		ch = getch( );
		if( ch == '1' )
		return;
		else
		if( ch == '2' )
		{
			int score;
			char name[ 80 ];
			ifstream sc( "score.mih" );
			if( sc )
			{
				sc >> score;
				sc.get( );
				sc.getline( name , 80 );
				clrscr( );
				printf( "Name:\t" );
				puts( name );
				printf( "Score:\t%d" , score );
				getch( );
				sc.close( );
			}
			continue;
		}
		else
		if( ch == '3' )
		{
			printf( "\nChoose from the following:\n" );
			printf( "1.Very Slow\n2.Slow\n3.Medium\n4.Fast\n5.Very Fast\n" );
			ofstream spd( "speed.mih" );
			char c;
			c = getch( );
			if( c == '1' )
				spd << 150;
			else
			if( c == '2' )
				spd << 125;
			else
			if( c == '3' )
				spd << 100;
			else
			if( c == '4' )
				spd << 75;
			else
			if( c == '5' )
				spd << 50;
			spd.close( );
			continue;
		}
		else
		if( ch == '4' )
		{
			printf( "\nDo you want to change dimensions?(y/n)" );
			char ask;
			int out = 0;
			for( ;; )
			{
				ask = getch( );
				if( ask == 'Y' || ask == 'y' )
					break;
				else
				if( ask == 'N' || ask == 'n' )
				{
					out = 1;
					break;
				}
			}
			if( !out )
			{
				clrscr( );
				int chk = 0;
				ofstream d( "dim.mih" );
				char temp[80];
				int x , y;
				printf( "Enter new x dimension( 30 - 80 ):\n" );
				do
				{
					gets( temp );
					chk = onlynum( temp );
					if( !chk )
					{
						x = atoi( temp );
						if( x >= 30 && x <= 80 )
							break;
						else
						{
							chk = 1;
							printf( "Enter a number in the range 30 - 80\n" );
							continue;
						}
					}
					printf( "Enter a valid input:\n" );
				}while( chk );
				printf( "Enter new y dimension( 10 - 24 ):\n" );
				do
				{
					gets( temp );
					chk = onlynum( temp );
					if( !chk )
					{
						y = atoi( temp );
						if( y >= 10 && y <= 24 )
							break;
						else
						{
							chk = 1;
							printf( "Enter a number in the range 30 - 80\n" );
							continue;
						}
					}
					printf( "Enter a valid input:\n" );
				}while( chk );
				d << x;
				d.put( '\n' );
				d << y;
				d.close( );
			}
		}
		else
		if( ch == '5' )
			exit( 0 );
	}while( 1 );
}
//hpage_end
// on_beg
int onlynum( char *str )
{
	int i ;
	for( i = 0 ; *( str + i ) != '\0' ; ++ i )
	{
		if( !xisdigit( *( str + i ) ) )
		return 1;
	}
	return 0;
}
// on_end
