#include <conio.h>
#include <graphics.h>
#include <fstream.h>
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define midx ( getmaxx( ) / 2 )
#define midy ( getmaxy( ) / 2 )
#define ESC 27
#define UP 'H'
#define DOWN 'P'
#define ENTER 13
//ascii 13 & 27 are ascii characters of enter and esc
//'\n' doesn't work in graphics mode
//and 13 doesn't work in text mode
#define LEN 8
#define NO 20
#define WN 5

char pass[ 30 ] = "hello" ;
int doc_no = LEN ;
int dno = LEN ;
int n_no = 0 ;
int nno = 0 ;
int p_no = 0 ;
int pno = 0 ;
char s[ LEN ][ 50 ] =
	     {
		"Cardiologist" ,
		"Neurologist" ,
		"Dentist" ,
		"Physician" ,
		"Gynaecologist" ,
		"Paediatrician" ,
		"E.N.T specialist" ,
		"Gastroenterologist"
	     } ;

struct Date// Date bcz date structure is predefined
{
	int day ;
	char month[ 15 ] ;
	int year ;
} ;

void sort( int *a , int size )
{
	int i , j , temp , f ;
	for( i = 0 ; i < size - 1 ; ++ i )
	{
		f = 0 ;
		for( j = 0 ; j < size - 1 - i ; ++ j )
		{
			if( a[ j ] > a[ j + 1 ] )
			{
				temp = a[ j ] ;
				a[ j ] = a[ j + 1 ] ;
				a[ j + 1 ] = temp ;
				f = 1 ;
			}
		}
		if( f == 0 )
		break ;
	}
}

int onlynum( char *str )
{
	int i ;
	for( i = 0 ; str[ i ] != '\0' ; ++ i )
	{
		if( !isdigit( str[ i ] ) )
		return 1 ;
	}
	return 0 ;
}

char *convert( time_t tm )
{
	char str[ 30 ] ;
	strcpy( str , ctime( &tm ) ) ;
	char day[ 5 ] ;
	for( int i = 0 ; i < 3 ; ++ i )
	{
		day[ i ] = str[ i ] ;//first 3 chars of str are for day
	}
	day[ i ] = '\0' ;
	char mon[ 5 ] ;
	mon[ 0 ] = str[ 4 ] ;
	mon[ 1 ] = str[ 5 ] ;
	mon[ 2 ] = str[ 6 ] ;
	mon[ 3 ] = '\0' ;
	char dat[ 5 ] ;
	dat[ 0 ] = str[ 8 ] ;
	dat[ 1 ] = str[ 9 ] ;
	dat[ 2 ] = '\0' ;
	char year[ 5 ] ;
	year[ 0 ] = str[ 20 ] ;
	year[ 1 ] = str[ 21 ] ;
	year[ 2 ] = str[ 22 ] ;
	year[ 3 ] = str[ 23 ] ;
	year[ 4 ] = '\0' ;
	char ndate[ 30 ] ;
	strcpy( ndate , mon ) ;
	strcat( ndate , " " ) ;
	strcat( ndate , dat ) ;
	strcat( ndate , " , " ) ;
	strcat( ndate , year ) ;
	return ndate ;
}

Date getdate( )
{
	Date d ;
	int chk = 0 ;
	char temp[ 30 ] ;
	int result = 0 ;
	cout << "Enter day:\t" ;
	do
	{

	if( chk )
	{
		cout << "Enter a number between 1-31:\t" ;
	}
	result = 0 ;
	do
	{
	if( result )
	cout << "Enter a number between 1-31:\t" ;
	gets( temp ) ;
	result = onlynum( temp ) ;
	}while( result ) ;
	d.day = atoi( temp ) ;

	if( d.day >= 1 && d.day <= 31 )
	break ;
	else
	chk = 1 ;

	}while( chk ) ;

	chk = 0 ;
	int mon ;
	cout << "Enter month in numbers:\t" ;
	do
	{

	if( chk )
	{
		cout << "Enter a number between 1-12:\t" ;
	}
	result = 0 ;
	do
	{
	if( result )
	cout << "Enter a number between 1-12:\t" ;
	gets( temp ) ;
	result = onlynum( temp ) ;
	}while( result ) ;
	mon = atoi( temp ) ;
	chk = 0 ;

	switch( mon )
	{
		case 1 :
			strcpy( d.month , "January" ) ;
			break ;
		case 2 :
			strcpy( d.month , "February" ) ;
			break ;
		case 3 :
			strcpy( d.month , "March" ) ;
			break ;
		case 4 :
			strcpy( d.month , "April" ) ;
			break ;
		case 5 :
			strcpy( d.month , "May" ) ;
			break ;
		case 6 :
			strcpy( d.month , "June" ) ;
			break ;
		case 7 :
			strcpy( d.month , "July" ) ;
			break ;
		case 8 :
			strcpy( d.month , "August" ) ;
			break ;
		case 9 :
			strcpy( d.month , "September" ) ;
			break ;
		case 10 :
			strcpy( d.month , "October" ) ;
			break ;
		case 11 :
			strcpy( d.month , "November" ) ;
			break ;
		case 12 :
			strcpy( d.month , "December" ) ;
			break ;
		default :
			chk = 1 ;
	}
	}while( chk ) ;
	cout << "Enter year:\t" ;
	result = 0 ;
	do
	{
	if( result )
	cout << "Enter a number between 1-31:\t" ;
	gets( temp ) ;
	result = onlynum( temp ) ;
	}while( result ) ;
	d.year = atoi( temp ) ;
	return d ;
}

void fgetdays( int no[ ] )
{
	char temp[ 30 ] ;
	int chk ;
	int t ;
	cout << "1.Mon\n2.Tue\n3.Wed\n4.Thu\n5.Fri\n6.Sat\n7.Sun\n" ;
	for( int i = 0 ; i < 5 ; ++ i )
	{
		cout << "Enter day " << i + 1 << " :\n" ;
		chk = 0 ;
		do
		{
			if( chk )
			cout << "Enter a number from 1 - 7:\t" ;
			gets( temp ) ;
			chk = onlynum( temp ) ;
			t = atoi( temp ) ;
			if( ( !chk ) && ( t < 1 || t > 7 ) )
			chk = 1 ;
			if( !chk )
			{
				for( int j = 0 ; j < i ; ++ j  )
				{
					if( t == no[ j ] )
					{
						cout << "Already entered!\n" ;
						chk = 1 ;
						break ;
					}
				}
			}

		}while( chk ) ;

		no[ i ] = atoi( temp ) ;
	}
	sort( no , 5 ) ;
}

int chknum( char *str )
{
	int i ;
	for( i = 0 ; str[ i ] != '\0' ; ++ i )
	{
		if( !isalpha( str[ i ] ) && !isspace( str[ i ] ) && str[ i ] != '.' )
		return 1 ;
	}
	return 0 ;
}

int chkqual( char *str )
{
	int i ;
	for( i = 0 ; str[ i ] != '\0' ; ++ i )
	{
		if( !isalpha( str[ i ] ) && !isspace( str[ i ] ) && str[ i ] != '.' && str[ i ] != ',')
		return 1 ;
	}
	return 0 ;
}

int onlyalpha( char *str )
{
	int i ;
	for( i = 0 ; str[ i ] != '\0' ; ++ i )
	{
		if( !isalpha( str[ i ] ) && !isspace( str[ i ] ) )
		return 1 ;
	}
	return 0 ;
}

int chkcno( char *str )
{
	int i ;
	for( i = 0 ; str[ i ] != '\0' ; ++ i )
	{
		if( !isdigit( str[ i ] ) && str[ i ] != '+' && str[ i ] != ' ' )
		return 1 ;
	}
	return 0 ;
}

//PROTOTYPES
int page( int bkcolor1 , int bkcolor2 , int side , int no , char *s_text , int tcolor , int col_color , int xgap , char nm[ ][ 50 ] ) ;
int writecol( char * , int , int , int , int ) ; //1.string , 2.no. of the column
						//3. y coordinate of 1st column
						//4.gap b/w cols
						// 5. gap from max x
void employee( ) ;
void doctors_d( ) ;
void doctors( ) ;
void patients( ) ;
void WARD( ) ;
void openward( int ) ;
void WTYPE( int , int ) ;
char *inputpass( int , int , int ) ;// 1st 2 arguements are for x and y
					// 3rd arg is for the max pass length
					//returns the string typed by the user
					//also emits a sound if user is trying
					//to type more than the max length
					//4th arg -> if not 0 ->inputs only digits
void createfile(  ) ; // Creates new doctor record
void displayfile( ) ;// Displays existing doctor record
void modifyfile( ) ; // Modifies existing doctor record
void deletefile( ) ; // Deletes existing doctor record
void disp_all( ) ; // Displays existing doctor records
void createfile_p( ) ;
void displayfile_p( ) ;
void modifyfile_p( ) ;
void deletefile_p( int ID = 0 ) ;
void disp_all_p( ) ;
void disp_all_ip( ) ;
char *setpass( char * , int , int & ) ;// To change pass
					//1st arg old pass
					//2nd arg max length
					//3rd arg to check whether the pass
					//has been changed
int login( int ) ;
int fsizeof( char * ) ;//Returns size of file in bytes
void p_manage( int rec ) ;
void disp_all_p_date( int , int ) ;
void discharge( int ) ;
void genbill( ) ;
//----------

class doctor
{
	private :
		char name[ 40 ] ;
		int age ;
		char add[ 50 ] ;
		char cno[ 20 ] ;
		Date dob ;
		Date doj ;
		char email[ 60 ] ;
		char qual[ 90 ] ;
		int exp ;
		char spec[ 30 ] ;
		int doc_id ;
		char password[ 30 ] ;
		int days[ 5 ] ;
		int cn[ 5 ] ;//Patients assigned for a particular day-
//                                                                   |
//				--------------------------------------
//				|
		int apid[ 5 ][ NO ] ;
	public :
		doctor( )
		{
		}
		doctor( char *n , int a , char *address , char *c , Date d , Date dj , char *em , char *q , int e , char *s , int id , char *p )
		{
			strcpy( name , n ) ;
			strcpy( cno , c ) ;
			strcpy( add , address ) ;
			strcpy( qual , q ) ;
			strcpy( spec , s ) ;
			strcpy( email , em ) ;
			strcpy( password , p ) ;
			age = a ;
			dob = d ;
			doj = dj ;
			exp = e ;
			doc_id = id ;
		}
		int l ;
		time_t fdoa ;//first assigning index
		int getdoc_id( )
		{
			return doc_id ;
		}
		char *getname( )
		{
			return name ;
		}
		int getage( )
		{
			return age ;
		}
		char *getadd( )
		{
			return add ;
		}
		char *getcno( )
		{
			return cno ;
		}
		Date getdob( )
		{
			return dob ;
		}
		Date getdoj( )
		{
			return doj ;
		}
		char *getemail( )
		{
			return email ;
		}
		char *getqual( )
		{
			return qual ;
		}
		int getexp( )
		{
			return exp ;
		}
		char *getspec( )
		{
			return spec ;
		}
		char *getpassword( )
		{
			return password ;
		}
		int getdays( int v )
		{
			return days[ v ] ;
		}
		int getcn( int s )
		{
			return cn[ s ] ;
		}
		int getapid( int a , int b )
		{
			return apid[ a ][ b ] ;
		}

		doctor( doctor &d )
		{
			strcpy( name , d.name ) ;
			age = d.age ;
			strcpy( add , d.add ) ;
			strcpy( cno , d.cno ) ;
			dob.day = d.dob.day ;
			strcpy( dob.month , d.dob.month ) ;
			dob.year = d.dob.year ;
			doj.day = d.doj.day ;
			strcpy( doj.month , d.doj.month ) ;
			doj.year = d.doj.year ;
			strcpy( email , d.email ) ;
			strcpy( qual , d.qual ) ;
			exp = d.exp ;
			strcpy( spec , d.spec ) ;
			doc_id = d.doc_id ;
			strcpy( password , d.password ) ;
		}

		void getdata( ) ;
		void putdata( ) ;
		void modify( ) ;
		char *getnextd( int ) ;
		void d_id( int id )
		{
			doc_id = id ;
		}
		void d_pass( char *str )
		{
			strcpy( password , str ) ;
		}
		void assign_apid( int a , int b , int pid )
		{
			apid[ a ][ b ] = pid ;
		}
		void assign_cn( int j , int no )
		{
			cn[ j ] = no ;
		}
		void a_cn( int c  )
		{
			++ cn[ c ] ;
		}
		void s_cn( int c  )
		{
			-- cn[ c ] ;
		}
		void assign_days( int c , int a )
		{
			days[ c ] = a ;
		}
		void assign_name( char *nm )
		{
			strcpy( name , nm ) ;
		}
} ;

void doctor :: getdata( )
{
	int result = 0 ;
	char temp[ 30 ] ;
	cout << "Enter doctor's name:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid name:\t" ;
	gets( name ) ;
	result = chknum( name ) ;
	}while( result ) ;

	result = 0 ;

	cout << "Enter doctor's age:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid age:\t" ;
	gets( temp ) ;
	result = onlynum( temp ) ;
	if( strlen( temp ) > 3 && !result )
	{
		cout << "Age can't be that big!" ;
		result = 1 ;
	}
	}while( result ) ;
	age = atoi( temp ) ;
	cout << "Enter doctor's residential address:\n" ;
	gets( add ) ;
	result = 0 ;
	cout << "Enter doctor's contact no.:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid contact no.:\t" ;
	gets( cno ) ;
	result = chkcno( cno ) ;
	}while( result ) ;

	cout << "Enter doctor's date of birth:\n" ;

	dob = getdate( ) ;
	cout << "Enter doctor's date of joining:\n" ;
	doj = getdate( ) ;
	result = 0 ;
	cout << "Enter email:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid email id:\t" ;
	gets( email ) ;
	result = 1 ;
	}while( !strchr( email , '@') ) ;
	result = 0 ;
	cout << "Enter qualifications\nIf qualifications are more than 1 separate them by commas\n" ;
	do
	{
	if( result )
	cout << "Enter a valid qualification:\t" ;
	gets( qual ) ;
	result = chkqual( qual ) ;
	}while( result ) ;
	result = 0 ;
	cout << "Enter years of experience:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid number:\t" ;
	gets( temp ) ;
	result = onlynum( temp ) ;
	if( strlen( temp ) > 3 && !result )
	{
		cout << "Experience can't be that big!" ;
		result = 1 ;
	}
	}while( result ) ;
	exp = atoi( temp ) ;

	cout << "Select area of specialization:\n" ;
	cout << "1.Cardiologist\n2.Neurologist\n3.Dentist\n"
	     << "4.Physician\n5.gynaecologist\n6.Paediatrician\n"
	     << "7.E.N.T specialist\n8.Gastroenterologist\n" ;
	int ch ;
	int k = 0 ;
	do
	{
		if( k )
		{
			cout << "Enter a number between 1-8\t" ;
		}
		result = 0 ;
		do
		{
		if( result )
		cout << "Enter a number between 1-8\t" ;
		gets( temp ) ;
		result = onlynum( temp ) ;

		}while( result ) ;
		ch = atoi( temp ) ;
		if( ch >= 1 && ch <= 8 )
		{
			strcpy( spec , s[ ch - 1 ] ) ;
			break ;
		}
		k = 1 ;

	}while( 1 ) ;
	cout << "Select 5 days on which doctor is available:\n" ;
	fgetdays( days ) ;
}

void doctor :: putdata( )
{
	cout << "Doctor's id:\t" ;
	cout << doc_id ;
	cout << "\n\nDoctor's name:\t" ;
	puts( name ) ;
	cout << "\nDoctor's age:\t" ;
	cout << age ;
	cout << "\n\nDoctor's residential address:\t" ;
	puts( add ) ;
	cout << "\nDoctor's contact no.:\t" ;
	puts( cno ) ;
	cout << "\nDoctor's date of birth:" ;
	cout << '\t' << dob.month << ' ' ;
	cout << dob.day << ',';
	cout << ' ' << dob.year ;
	cout << "\nDoctor's date of joining:\t" ;
	cout << doj.month << ' ' ;
	cout << doj.day << ',';
	cout << ' ' << doj.year ;
	cout << "\n\nEmail:\t" ;
	puts( email ) ;
	cout << "\nQualification:\t" ;
	puts( qual ) ;
	cout << "\nYears of experience:\t" ;
	cout << exp ;
	cout << "\n\nArea of specialization:\t" ;
	puts( spec ) ;
	int lt ;
	lt = 5 ;
	cout << "Doctor is available on the following days:\n" ;
	char str[ 20 ] ;
	for( int i = 0 ; i < lt ; ++ i )
	{
		switch( days[ i ] )
		{
			case 1 : strcpy( str , "Mon" ) ;
				 break ;
			case 2 : strcpy( str , "Tue" ) ;
				 break ;
			case 3 : strcpy( str , "Wed" ) ;
				 break ;
			case 4 : strcpy( str , "Thu" ) ;
				 break ;
			case 5 : strcpy( str , "Fri" ) ;
				 break ;
			case 6 : strcpy( str , "Sat" ) ;
				 break ;
			case 7 : strcpy( str , "Sun" ) ;
				 break ;
		}
		puts( str ) ;
	}
}

void doctor :: modify( )
{
	cout << "\n1. Doctor's name:\t" ;
	puts( name ) ;
	cout << "2. Doctor's age:\t" ;
	cout << age ;
	cout << "\n3. Doctor's residential address:\t" ;
	puts( add ) ;
	cout << "4. Doctor's contact no.:\t" ;
	puts( cno ) ;
	cout << "5. Doctor's date of birth:\t" ;
	cout << dob.month << ' ' ;
	cout << dob.day << ',';
	cout << ' ' << dob.year ;
	cout << "\n6. Doctor's date of joining:\t" ;
	cout << doj.month << ' ' ;
	cout << doj.day << ',';
	cout << ' ' << doj.year ;
	cout << "\n7. Email:\t" ;
	puts( email ) ;
	cout << "8. Qualification:\t" ;
	puts( qual ) ;
	cout << "9. Years of experience:\t" ;
	cout << exp ;
	cout << "\n10. Doctor is available on the following days:\n" ;
	char str[ 20 ] ;
	for( int i = 0 ; i < 5 ; ++ i )
	{
		switch( days[ i ] )
		{
			case 1 : strcpy( str , "Mon" ) ;
				 break ;
			case 2 : strcpy( str , "Tue" ) ;
				 break ;
			case 3 : strcpy( str , "Wed" ) ;
				 break ;
			case 4 : strcpy( str , "Thu" ) ;
				 break ;
			case 5 : strcpy( str , "Fri" ) ;
				 break ;
			case 6 : strcpy( str , "Sat" ) ;
				 break ;
			case 7 : strcpy( str , "Sun" ) ;
				 break ;
		}
		cout << str << ',' ;
	}
	cout << '\b' << ' ' ;
	cout << "\n11. Area of specialization:\t" ;
	puts( spec ) ;
	int ii ;
	cout << "\nEnter a number from 1-11:\n" ;
	int result = 0 ;
	int j ;
	char temp[ 30 ] ;
	do
	{
	if( result )
	cout << "Enter a number between 1-11:\t" ;
	gets( temp ) ;
	result = onlynum( temp ) ;
	j = atoi( temp ) ;
	if( j >= 1 && j <= 11 )
	result = 0 ;
	else
	result = 1 ;

	}while( result ) ;
	ii = atoi( temp ) ;
	result = 0 ;

	if( ii == 1 )
	{
	cout << "Enter new data for name:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid name:\t" ;
	gets( name ) ;
	result = chknum( name ) ;
	}while( result ) ;
	}
	else
	if( ii == 2 )
	{
	cout << "Enter new data for age:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid age:\t" ;
	gets( temp ) ;
	result = onlynum( temp ) ;
	if( strlen( temp ) > 3 && !result )
	{
		cout << "Age can't be that big!" ;
		result = 1 ;
	}
	}while( result ) ;
	age = atoi( temp ) ;
	}
	else
	if( ii == 3 )
	{
	cout << "Enter new data for address:\n" ;
	gets( add ) ;
	}
	else
	if( ii == 4 )
	{
	cout << "Enter new data for contact no.:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid contact no.:\t" ;
	gets( cno ) ;
	result = chkcno( cno ) ;
	}while( result ) ;
	}
	else
	if( ii == 5 )
	{
	cout << "Enter new data for dob:\n" ;
	dob = getdate( ) ;
	}
	else
	if( ii == 6 )
	{
	cout << "Enter new data for date of joining:\n" ;
	doj = getdate( ) ;
	}
	else
	if( ii == 7 )
	{
	cout << "Enter new data for email:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid email id:\t" ;
	gets( email ) ;
	result = 1 ;
	}while( !strchr( email , '@') ) ;
	}
	else
	if( ii == 8 )
	{
	cout << "Enter new data for qualification:\n" ;
	do
	{
	if( result )
	cout << "Enter a valid qualification:\t" ;
	gets( qual ) ;
	result = chkqual( qual ) ;
	}while( result ) ;
	}
	else
	if( ii == 9 )
	{
	cout << "Enter new data for experience:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid number:\t" ;
	gets( temp ) ;
	result = onlynum( temp ) ;
	if( strlen( temp ) > 3 && !result )
	{
		cout << "Exp can't be that big!" ;
		result = 1 ;
	}
	}while( result ) ;
	exp = atoi( temp ) ;
	}
	else
	if( ii == 10 )
	{
	cout << "Enter new data for days on which doctor is available:\n" ;
	fgetdays( days ) ;
	}
	else
	if( ii == 11 )
	{
	cout << "Enter new data for area of specialization:\n" ;
	cout << "1.Cardiologist\n2.Neurologist\n3.Dentist\n"
	     << "4.Physician\n5.gynaecologist\n6.Paediatrician\n"
	     << "7.E.N.T specialist\n8.Gastroenterologist\n" ;
	int ch ;
	int k = 0 ;
	do
	{
		if( k )
		{
			cout << "Enter a number between 1-8\t" ;
		}
		result = 0 ;
		do
		{
		if( result )
		cout << "Enter a number between 1-8\t" ;
		gets( temp ) ;
		result = onlynum( temp ) ;

		}while( result ) ;
		ch = atoi( temp ) ;
		if( ch >= 1 && ch <= 8 )
		{
			strcpy( spec , s[ ch - 1 ] ) ;
			break ;
		}
		k = 1 ;

	}while( 1 ) ;
	}
}

char * doctor :: getnextd( int l )
{
	time_t t ;
	time( &t ) ;
	char str[ 30 ] ;
	int d ;
	strcpy( str , ctime( &t ) ) ;//stores today's time
	char day[ 5 ] ;
	for( int i = 0 ; i < 3 ; ++ i )
	{
		day[ i ] = str[ i ] ;//first 3 chars of str are for day
	}
	day[ i ] = '\0' ;
	if( !strcmp( day , "Mon" ) )
	d = 1 ;
	else
	if( !strcmp( day , "Tue" ) )
	d = 2 ;
	else
	if( !strcmp( day , "Wed" ) )
	d = 3 ;
	else
	if( !strcmp( day , "Thu" ) )
	d = 4 ;
	else
	if( !strcmp( day , "Fri" ) )
	d = 5 ;
	else
	if( !strcmp( day , "Sat" ) )
	d = 6 ;
	else
	if( !strcmp( day , "Sun" ) )
	d = 7 ;
	int nweek[ 7 ] ;//stores next 7 days
			//e.g., if tday is tuesday
			//nweek = { 3 , 4 , 5 , 6 , 7 , 1 , 2 } ;
			// codes for various days
	for( int k = 0 ; k < 7 ; ++ k )
	{
		if( d == 7 )
		d = 0 ;
		++ d ;
		nweek[ k ] = d ;
	}
	int chk = 1 ;
	k = 0 ;
	int f = 0 ;
	//when l = 0 implies that day space is left for other patients
	//in d.no[ 5 ]
	while( chk )
	{
		for( int j = 0 ; j < 5 ; ++ j )
		{
			if( days[ j ] == nweek[ k ] )//Q
			{
				if( l == 0 )
				{
					chk = 0 ;
					f = 1 ;
					break ;
				}
				else
				-- l ;
			}
		}
		++ k ;
		if( k == 8 )// if l >= 5 , when l attains 0 it will
		break ;     // all dys on which dr is available are checked
	}                   //by Q and now Q will not satisfy now
			    //and k will keep on increasing
	if( !f )
	return " " ;

	//k now is the diff b/w the next day on which dr is available
	//& tday
	for( int s = 0 ; s < k ; ++ s )
	t += ( 24L * 60L * 60L ) ; //t advances to the next day on which dr is available
	strcpy( str , ctime( &t ) ) ;

	char mon[ 5 ] ;
	mon[ 0 ] = str[ 4 ] ;
	mon[ 1 ] = str[ 5 ] ;
	mon[ 2 ] = str[ 6 ] ;
	mon[ 3 ] = '\0' ;
	char dat[ 5 ] ;
	dat[ 0 ] = str[ 8 ] ;
	dat[ 1 ] = str[ 9 ] ;
	dat[ 2 ] = '\0' ;
	char year[ 5 ] ;
	year[ 0 ] = str[ 20 ] ;
	year[ 1 ] = str[ 21 ] ;
	year[ 2 ] = str[ 22 ] ;
	year[ 3 ] = str[ 23 ] ;
	year[ 4 ] = '\0' ;
	char ndate[ 30 ] ;
	strcpy( ndate , mon ) ;
	strcat( ndate , " " ) ;
	strcat( ndate , dat ) ;
	strcat( ndate , " , " ) ;
	strcat( ndate , year ) ;
	return ndate ;
}

class ward
{
	private :
		int wtype ;//Cardio, surgical etc.
		int no[ 3 ] ;//no of patients in s , d or g ward
		int cost[ 3 ] ;// cost per day
		int pat_no[ 3 ][ 30 ] ;
	public :
		ward( )
		{
		}
		ward( int c , int a[ 3 ] , int b[ 3 ] )
		{
			wtype = c ;
			no[ 0 ] = a[ 0 ] ;
			no[ 1 ] = a[ 1 ] ;
			no[ 2 ] = a[ 2 ] ;
			cost[ 0 ] = b[ 0 ] ;
			cost[ 1 ] = b[ 1 ] ;
			cost[ 2 ] = b[ 2 ] ;
		}

		int getwtype( )
		{
			return wtype ;
		}
		int getcost( int a )
		{
			return cost[ a ] ;
		}
		int getno( int a )
		{
			return no[ a ] ;
		}
		int getpat_no( int a , int b )
		{
			return pat_no[ a ][ b ] ;
		}
		void assign_pat_no( int a , int b , int c )
		{
			pat_no[ a ][ b ] = c ;
		}
		void assign_no( int a , int c )
		{
			no[ a ] = c ;
		}
		void assign_cost( int a , int b )
		{
			cost[ a ] = b ;
		}
		void a_no( int a )
		{
			++ no[ a ] ;
		}
		void s_no( int a )
		{
			-- no[ a ] ;
		}
		void putdata( ) ;
		void modify( ) ;
} ;

void ward :: putdata( )
{
	gotoxy( 1 , 1 ) ;
	cout << "FOR ALL WARDS( cardio , ... )\n" ;
	cout << "\nNo. of single bed wards:\t10" ;
	cout << "\nNo. of double bed wards:\t10" ;
	cout << "\nNo. of general( 6 beds ) wards:\t5" ;
	cout << "\nCost of single bed ward per day:\t" << cost[ 0 ] ;
	cout << "\nCost of double bed ward per day:\t" << cost[ 1 ] ;
	cout << "\nCost of general ward per day:\t" << cost[ 2 ] ;
	getch( ) ;
}

class patient
{
	private :
		char name[ 60 ] ;
		int age ;
		char add[ 60 ] ;
		char cno[ 60 ] ;
		Date dob ;
		char email[ 60 ] ;
		int p_id ;
		char sym[ 60 ] ;
		char dis[ 60 ] ;
		int cdid ;
		int p_type ;
		int w ;
		int t ;
		time_t ad ;
		time_t dd ;
	public :
		patient( )
		{
		}
		int getp_id( )
		{
			return p_id ;
		}
		int done ;
		char *getname( )
		{
			return name ;
		}
		int getcdid( )
		{
			return cdid ;
		}
		int getp_type( )
		{
			return p_type ;
		}
		int getage( )
		{
			return age ;
		}
		char *getadd( )
		{
			return add ;
		}
		char *getcno( )
		{
			return cno ;
		}
		Date getdob( )
		{
			return dob ;
		}
		time_t getdd( )
		{
			return dd ;
		}
		time_t getad( )
		{
			return ad ;
		}
		char *getemail( )
		{
			return email ;
		}
		char *getsym( )
		{
			return sym ;
		}
		char *getdis( )
		{
			return dis ;
		}
		int getward( )
		{
			return w ;
		}
		int getwardtype( )
		{
			return t ;
		}
		patient( patient &p )
		{
			strcpy( name , p.name ) ;
			age = p.age ;
			strcpy( add , p.add ) ;
			strcpy( cno , p.cno ) ;
			dob.day = p.dob.day ;
			strcpy( dob.month , p.dob.month ) ;
			strcpy( dis , p.dis ) ;
			strcpy( sym , p.sym ) ;
			dob.year = p.dob.year ;
			strcpy( email , p.email ) ;
			p_id = p.p_id ;
		}
		int getdata( int PID ) ;
		void putdata( ) ;
		void modify( ) ;
		void pat_id( int id )
		{
			p_id = id ;
		}
		void p_dd( time_t dis_d )
		{
			dd = dis_d ;
		}
} ;

int patient :: getdata( int PID )
{

	int result = 0 ;
	char temp[ 30 ] ;
	char ee ;
	done = 0 ;
	cout << "Enter patient's name:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid name:\t" ;
	gets( name ) ;
	result = chknum( name ) ;
	}while( result ) ;

	result = 0 ;

	cout << "Enter patient's age:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid age:\t" ;
	gets( temp ) ;
	result = onlynum( temp ) ;
	if( strlen( temp ) > 3 && !result )
	{
		cout << "Age can't be that big\n" ;
		result = 1 ;
	}
	}while( result ) ;
	age = atoi( temp ) ;
	cout << "Enter patient's residential address:\n" ;
	gets( add ) ;
	result = 0 ;
	cout << "Enter patient's contact no.:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid contact no.:\t" ;
	gets( cno ) ;
	result = chkcno( cno ) ;
	}while( result ) ;
	cout << "Enter patient's date of birth:\n" ;
	dob = getdate( ) ;
	result = 0 ;
	cout << "Enter email:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid email id:\t" ;
	gets( email ) ;
	result = 1 ;
	}while( !strchr( email , '@') ) ;

	result = 0 ;
	cout << "Enter symptoms:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid symptom:\t" ;
	gets( sym ) ;
	result = chkqual( sym ) ;
	}while( result ) ;

	result = 0 ;
	cout << "Enter diseases:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid disease:\t" ;
	gets( dis ) ;
	result = chkqual( dis ) ;
	}while( result ) ;
	int chk = 0 ;
	cout << "Enter patient type\n" ;
	cout << "1.In-patient\n2.Out patient\n" ;
	do
	{
		if( chk )
		cout << "Enter 1 or 2\t" ;
		do
		{
		if( result )
		cout << "Enter 1 or 2:\t" ;
		gets( temp ) ;
		result = onlynum( temp ) ;
		}while( result ) ;
		p_type = atoi( temp ) ;
		chk = 1 ;

	}while( p_type != 1 && p_type != 2 ) ;


	if( p_type == 1 )
	{//1
		time_t t1 ;
		t1 = time( NULL ) ;
		ad = t1 ;
		ward w1 ;
		int ans2 ;
		int flag ;
		fstream wd( "WARD.mih" , ios :: in | ios :: out | ios :: binary ) ;
		while( 1 )
		{//2
			cleardevice( ) ;
			gotoxy( 1 , 1 ) ;
			cout << "Select ward type:\n" ;
			cout << "1.Cardio-Ward\n2.Gynae-Ward\n3.Medicine Ward\n4.Surgical Ward\n5.Paediatric ward\n" ;
			chk = 0 ;
			result = 0 ;
			do
			{//3
				if( chk )
				cout << "Enter a no. from 1 - 5:\t" ;
				do
				{//4
					if( result )
					cout << "Enter a no. from 1 - 5:\t" ;
					gets( temp ) ;
					result = onlynum( temp ) ;
				}while( result ) ;
				//4
				ans2 = atoi( temp ) ;
				chk = 1 ;

			}while( ans2 < 1 || ans2 > 5 ) ;
			//3
			w = ans2 - 1 ;
			wd.seekg( sizeof( w1 ) * ( w ) , ios :: beg ) ;
			wd.read( ( char * )&w1 , sizeof( w1 ) ) ;
			cout << "Select type:\n" ;
			cout << "1.Single bed- Rs" << w1.getcost( 0 ) << "\n2.Double Bed- Rs" << w1.getcost( 1 ) << "\n3.General- Rs" << w1.getcost( 2 ) << '\n' ;
			chk = 0 ;
			result = 0 ;
			do
			{//5
				if( chk )
				cout << "Enter a no. from 1 - 3:\t" ;
				do
				{ //6
					if( result )
					cout << "Enter a no. from 1 - 3:\t" ;
					gets( temp ) ;
					result = onlynum( temp ) ;
				}while( result ) ;
				//6
				ans2 = atoi( temp ) ;
				chk = 1 ;

			}while( ans2 < 1 || ans2 > 3 ) ;
			//5
			t = ans2 - 1 ;
			int chck = 1 ;
			if( t == 0 && w1.getno( t ) == 10 )
			chck = 0 ;
			else
			if( t == 1 && w1.getno( t ) == 20 )
			chck = 0 ;
			else
			if( t == 2 && w1.getno( t ) == 30 )
			chck = 0 ;
			if( chck )
			{ //7
				wd.seekp( sizeof( w1 ) * ( w ) , ios :: beg ) ;
				w1.assign_pat_no( t , w1.getno( t ) , PID ) ;
				w1.a_no( t ) ;
				wd.write( ( char * )&w1 , sizeof( w1 ) ) ;
				flag = 1 ;
				break ;
			} //7
			else
			{ //8
				cout << "The ward is full.\nDo you want to change your choice?( y/n )\n" ;
				char p ;
				int aa = 0 ;
				do
				{//9
					if( aa )
					cout << "\nEnter y or n:\t" ;
					p = getch( ) ;
					p = tolower( p ) ;
					if( p == 'y' || p == 'n' )
					break ;
					aa = 1 ;
				}while( 1 ) ;
				//9
				if( p == 'y' )
				{//10
					continue ;
				}//10
				else
				{//11
					flag = 0 ;
				}//11
			}//8
		}//2
		if( flag == 1 )
		{
			wd.close( ) ;
			return 1 ;
		}
		else
		if( flag == 0 )
		{
			wd.close( ) ;
			return 0 ;
		}

	}//1
	else
	{//1

		cout << "Enter specialization required:\n" ;
		cout << "1.Cardiologist\n2.Neurologist\n3.Dentist\n"
		     << "4.Physician\n5.gynaecologist\n6.Paediatrician\n"
		     << "7.E.N.T specialist\n8.Gastroenterologist\n" ;
		int ch ;
		int k = 0 ;
		char spec[ 30 ] ;
		do
		{//2
			if( k )
			{//3
				cout << "Enter a number between 1-8\t" ;
			}//3
			result = 0 ;
			do
			{//4
			if( result )
				cout << "Enter a number between 1-8\t" ;
			gets( temp ) ;
			result = onlynum( temp ) ;

			}while( result ) ;
			//4
			ch = atoi( temp ) ;
			if( ch >= 1 && ch <= 8 )
			{//5
				strcpy( spec , s[ ch - 1 ] ) ;
				break ;
			}//5
			k = 1 ;

		}while( 1 ) ;
		//2
		int s = 0 ;//Stores the no of doctors with the above spec

		doctor d1 ;
		ifstream fi( "DOCTORS.mih" , ios :: in | ios :: binary ) ;
		while( fi.read( ( char * )&d1 , sizeof( d1 ) ) )
		{//6
			if( !strcmp( spec , d1.getspec( ) ) )
			{//7
				++ s ;
			}//7
		}//6
		fi.close( );

		int *arr = NULL ;
		arr = new int[ s ] ;// stores the id of all the docs with spec
		int cnt = 0 ;//to increment the address of *arr
		int s1 = s ;//s1 = s - ( doctors who are not available this week)
		char a ;
		doctor d ;
		int n ;
		int l = 1 ;
		fi.open( "DOCTORS.mih" , ios :: in | ios :: binary ) ;
		fi.seekg( 0 , ios :: beg ) ;
		if( s )
		{//8
			int x , y ;
			setfillstyle( 1 , 0 ) ;
			cleardevice( ) ;
			x = 1 , y = 2 ;
			gotoxy( x , y ) ;
			cout << "ID" ;
			x = 10 ;
			gotoxy( x , y ) ;
			cout << "SPECIALIZATION" ;
			x = 30 ;
			gotoxy( x , y ) ;
			cout << "EXPERIENCE" ;
			x = 45 ;
			gotoxy( x , y ) ;
			cout << "EARLIEST APPOINTMENT DATE" ;
			y = 4 ;
			setcolor( 15 ) ;
			line( 0 , 30 , getmaxx( ) , 30 ) ;
			line( 0 , 320 , getmaxx( ) , 320 ) ;
			gotoxy( 1 , 1 ) ;
			cout << "Press ESC to go back & arrows for scrolling." ;
			y = 4 ;
			int c = 0 ;
			while( fi.read( ( char * )&d , sizeof( d ) ) )
			{//9
				++ c ;
				if( !strcmp( d.getspec( ) , spec ) )
				{//10
					x = 1 ;
					gotoxy( x , y ) ;
					cout << d.getdoc_id( ) ;
					x = 10 ;
					gotoxy( x , y ) ;
					cout << d.getspec( ) ;
					x = 30 ;
					gotoxy( x , y ) ;
					cout << d.getexp( ) ;
					x = 45 ;
					gotoxy( x , y ) ;
					int res = 1 ;
					char str[ 30 ] ;
					if( d.l == 5 )
					{//11
						res = 0 ;
					}//11
					if( res )
					{//12
						int aa = d.l ;
						for( int bb = 0 ; bb <= d.l ; ++ bb )
						{//13
							if( d.getcn( bb ) < NO )
							{//14
								aa = bb ;
								break ;
							}//14
						}//13
						cout << d.getnextd( aa ) ;
						d.l = aa ;
						arr[ cnt ] = d.getdoc_id( ) ;
						++ cnt ;
					}//12
					else
					{//15
						int aa = d.l ;
						for( int bb = 0 ; bb <= d.l ; ++ bb )
						{//16
							if( d.getcn( bb ) < NO )
							{//17
								aa = bb ;
								break ;
							}//17
						}//16
						if( aa == d.l )
						{//18
							cout << "Available next week" ;
							-- s1 ;
						}//18
						else
						{//19
							arr[ cnt ] = d.getdoc_id( ) ;
							++ cnt ;
						}//19
					}//15

					++ y ;
					if( y == 20 )//max y
					break ;
				}//10
			}//9
		}//8

	if( s1 )//If doctors with spec are available
	{//20
		gotoxy( 1 , 22 ) ;
		cout << "Choose doctor from the above options.\nEnter doctor id:\n" ;
		do
		{//21
			result = 0 ;
			do
			{//22
				if( result )
				cout << "Enter a valid id:\t" ;
				gets( temp ) ;
				result = onlynum( temp ) ;

			}while( result ) ;
			//22
			n = atoi( temp ) ;

			for( int j = 0 ; j < s1 ; ++ j )
			{//23
				if( n == arr[ j ] )
				{//24
					cdid = n ;
					int rec = 0 ;
					doctor d ;
					fstream f1( "DOCTORS.mih" , ios :: in | ios :: out | ios :: binary ) ;
					while( f1.read( ( char * )&d , sizeof( d ) ) )
					{//25
						++ rec ;
						if( cdid == d.getdoc_id( ) )
						{//26
							int cc = d.l ;
							for( int dd = 0 ; dd <= d.l ; ++ dd )
							{//27
								if( d.getcn( dd ) < NO )
								{//28
									cc = dd ;
									break ;
								}//28
							}//27
							int check ;
							for( int z = 0 ; z < 5 ; ++ z )
							{//29
								if( d.getcn( z ) == 0 )
								check = 1 ;
								else
								check = 0 ;
							}//29
							if( check == 1 )
							{//30
								time_t t1 ;
								t1 = time( NULL ) ;
								d.fdoa = t1 ;
							}//30

							cleardevice( ) ;
							gotoxy( 1 , 1 ) ;
							cout << "The earliest appointment date is:\t" << d.getnextd( cc ) ;
							cout << "\nDo you want to change it?( y/n )" ;
							do
							{//31
								ee = getch( ) ;
								ee = tolower( ee ) ;
								if( ee == 'y' || ee == 'n' )
								break ;
								cout << "\nEnter y or n:" ;

							}while( 1 ) ;
							//31
							if( ee == 'y' )
							{//32
								cout << "\nThe other dates on which doctor is available for the next 7 days:\n" ;
								char temp[ 30 ] ;
								int result = 0 ;
								int choice ;
								for( int gg = 0 ; gg < 5 ; ++ gg )
								{//33
									if( d.getcn( gg ) < NO )
									{//34
										cout << '\n' << gg + 1 << ".   " ;
									}//34
									else
										cout << '\n' << gg + 1 << ".   " << "( FULL )" ;
										puts( d.getnextd( gg ) ) ;
								}//33
								int jj , chk = 0 ;
								cout << "\nChoose from the above options:\t" ;
								do
								{//35

									do
									{//36
										if( chk )
										{//37
											cout << "FULL\n" ;
											cout << "Choose another option:\t" ;
										}//37
										else
										if( result )
											cout << "Enter a valid number:\t" ;
										gets( temp ) ;
										result = onlynum( temp ) ;
										jj = atoi( temp ) ;
										if( !result && ( ( jj - 1 ) >= 0 && ( jj - 1 ) <= 4 ) )
											break ;
										else
											result = 1 ;

									}while( result ) ;
									//36
									if( d.getcn( jj - 1 ) == NO )
									chk = 1 ;
									else
									chk = 0 ;

								}while( chk ) ;
								//35
								choice = atoi( temp ) ;
								-- choice ;
								d.assign_apid( choice , d.getcn( choice ) , PID ) ;
								d.a_cn( choice ) ;
								if( ( choice == d.l ) && ( d.getcn( choice ) == NO ) )
								{//38
									while( d.getcn( d.l ) == NO )
									++ d.l ;
								}//38
							}//32
							else
							{//39
								d.assign_apid( cc , d.getcn( cc ) , PID ) ;
								d.a_cn( cc ) ;
								while( d.getcn( d.l ) == NO )
								{//40
									++ d.l ;
								}//40
							}//39
							f1.seekp( sizeof( d ) * ( rec - 1 ) , ios :: beg ) ;
							f1.write( ( char * )&d , sizeof( d ) ) ;

						}//26
					}//25

					f1.close( ) ;
					l = 0 ;
					break ;
				}//24
			}//23
			if( l )
			cout << "Enter a valid id:\t" ;
			else
			break ;

		} while( 1 ) ;//21
	}//20
	else
	{//41
		cleardevice( ) ;
		gotoxy( 1 , 1 ) ;

		cout << "\nNo " << spec << " in the hospital\n" ;
		cout << "Record will be deleted.\n" ;
		fi.close( ) ;
		delete [ ] arr ;
		arr = NULL ;
		return 0 ;
	}//41
	delete [ ] arr ;
	arr = NULL ;
	fi.close( ) ;
	return 1 ;
	} //1
	return 1 ;
}

void patient :: putdata( )
{
	cout << "Patient's id:\t" ;
	cout << p_id ;
	cout << "\n\nPatient's name:\t" ;
	puts( name ) ;
	cout << "\nPatient's age:\t" ;
	cout << age ;
	cout << "\n\nPatient's residential address:\t" ;
	puts( add ) ;
	cout << "\nPatient's contact no.:\t" ;
	puts( cno ) ;
	cout << "\nPatient's date of birth:" ;
	cout << '\t' << dob.month << ' ' ;
	cout << dob.day << ',';
	cout << ' ' << dob.year ;
	cout << "\n\nEmail:\t" ;
	puts( email ) ;
	cout << "\nSymptoms:\t" ;
	puts( sym ) ;
	cout << "\nDisease:\t" ;
	puts( dis ) ;
	cout << "Patient type:\t" ;
	if( p_type == 1 )
	puts( "In-patient" ) ;
	else
	if( p_type == 2 )
	puts( "Out-patient" ) ;

	if( p_type == 1 )
	{
	if( done == 0 )
	{
	cout << "Patient ward:\n" ;

	char wards[ WN ][ 50 ] = {
					"Cardio-Ward" ,
					"Gynae-Ward" ,
					"Medicine Ward" ,
					"Surgical ward" ,
					"Paediatric-Ward" ,
				 } ;
	char types[ 3 ][ 50 ] = {
					"Single Bed" ,
					"Double bed" ,
					"General"
				} ;
	puts( wards[ w ] ) ;
	puts( types[ t ] ) ;
	}
	else
	{
		cout << "DISCHARGED" ;
	}
	}
	else
	{
	cout << "\nPatient consulting doctor id:\t" ;
	cout << cdid ;
	}
}

void patient :: modify( )
{
	cout << "1. Patient's name:\t" ;
	puts( name ) ;
	cout << "2. Patient's age:\t" ;
	cout << age ;
	cout << "\n3. Patient's residential address:\t" ;
	puts( add ) ;
	cout << "4. Patient's contact no.:\t" ;
	puts( cno ) ;
	cout << "5. Patient's date of birth:\t" ;
	cout << dob.month << ' ' ;
	cout << dob.day << ',';
	cout << ' ' << dob.year ;
	cout << "\n6. Email:\t" ;
	puts( email ) ;
	cout << "7. Symptoms:\t" ;
	puts( sym ) ;
	cout << "8. Disease:\t" ;
	puts( dis ) ;
	cout << "9. Patient type:\t" ;
	if( p_type == 1 )
	puts( "In-patient" ) ;
	else
	if( p_type == 2 )
	puts( "Out-patient" ) ;

	if( p_type == 2 )
	{
	cout << "10. Patient consulting doctor id:\t" ;
	cout << cdid ;
	}
	else
	if( p_type == 1 )
	{
	if( done == 1 )
	cout << "DISCHARGED\n" ;
	else
	{
	cout << "10. Patient ward:\n" ;
	char wards[ WN ][ 50 ] = {
					"Cardio-Ward" ,
					"Gynae-Ward" ,
					"Medicine Ward" ,
					"Surgical Ward" ,
					"Paediatric ward" ,
				 } ;
	char types[ 3 ][ 50 ] = {
					"Single Bed" ,
					"Double bed" ,
					"General"
				} ;
	puts( wards[ w ] ) ;
	puts( types[ t ] ) ;
	}
	}

	int ii ;
	if( done == 0 )
	cout << "\nEnter a number from 1-10:\n" ;
	else
	cout << "\nEnter a number from 1-9:\n" ;
	int result = 0 ;
	int j ;
	char temp[ 30 ] ;
	do
	{
	if( result && done == 0 )
	cout << "Enter a number between 1-10:\t" ;
	else
	if( result && done == 1 )
	cout << "Enter a number between 1-9:\t" ;
	gets( temp ) ;
	result = onlynum( temp ) ;
	j = atoi( temp ) ;
	if( done == 0 )
	{
	if( ( j >= 1 && j <= 10 ) )
	result = 0 ;
	else
	result = 1 ;
	}
	else
	{
	if( ( j >= 1 && j <= 9 ) )
	result = 0 ;
	else
	result = 1 ;
	}

	}while( result ) ;
	ii = atoi( temp ) ;
	result = 0 ;

	if( ii == 1 )
	{
	cout << "Enter new data for name:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid name:\t" ;
	gets( name ) ;
	result = chknum( name ) ;
	}while( result ) ;
	}
	else
	if( ii == 2 )
	{
	cout << "Enter new data for age:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid age:\t" ;
	gets( temp ) ;
	result = onlynum( temp ) ;
	if( strlen( temp ) > 3 && !result )
	{
		cout << "Age can't be that big!" ;
		result = 1 ;
	}
	}while( result ) ;
	age = atoi( temp ) ;
	}
	else
	if( ii == 3 )
	{
	cout << "Enter new data for address:\n" ;
	gets( add ) ;
	}
	else
	if( ii == 4 )
	{
	cout << "Enter new data for contact no.:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid contact no.:\t" ;
	gets( cno ) ;
	result = chkcno( cno ) ;
	}while( result ) ;
	}
	else
	if( ii == 5 )
	{
	cout << "Enter new data for dob:\n" ;
	dob = getdate( ) ;
	}
	else
	if( ii == 6 )
	{
	cout << "Enter new data for email:\t" ;
	do
	{
	if( result )
	cout << "Enter a valid email id:\t" ;
	gets( email ) ;
	result = 1 ;
	}while( !strchr( email , '@') ) ;
	}
	else
	if( ii == 7 )
	{
	cout << "Enter new data for symptoms:\n" ;
	do
	{
	if( result )
	cout << "Enter a valid symptom:\t" ;
	gets( sym ) ;
	result = chkqual( sym ) ;
	}while( result ) ;
	}
	else
	if( ii == 8 )
	{
	cout << "Enter new data for diseases:\n" ;
	do
	{
	if( result )
	cout << "Enter a valid disease:\t" ;
	gets( dis ) ;
	result = chkqual( dis ) ;
	}while( result ) ;
	}
	else
	if( ii == 9 )
	{
	int chk = 0 ;
	cout << "Enter new data for patient type:\t" ;
	cout << "1.In-patient\n2.Out patient\n" ;
	do
	{
		if( chk )
		cout << "Enter 1 or 2\t" ;
		do
		{
		if( result )
		cout << "Enter 1 or 2:\t" ;
		gets( temp ) ;
		result = onlynum( temp ) ;
		}while( result ) ;
		p_type = atoi( temp ) ;
		chk = 1 ;

	}while( p_type != 1 && p_type != 2 ) ;

	}
	if( ( ii == 9 || ii == 10 ) && p_type == 1 )
	{
		time_t t1 ;
		t1 = time( NULL ) ;
		ad = t1 ;
		ward w1 ;
		int ans2 ;
		int flag ;
		int chk = 0 ;
		int wrd = w ;
		int typ = t ;
		fstream wd( "WARD.mih" , ios :: in | ios :: out | ios :: binary ) ;
		while( 1 )
		{//2
			cleardevice( ) ;
			gotoxy( 1 , 1 ) ;
			cout << "Select ward type:\n" ;
			cout << "1.Cardio-Ward\n2.Gynae-Ward\n3.Medicine Ward\n4.Surgical Ward\n5.Paediatric ward\n" ;
			chk = 0 ;
			result = 0 ;
			do
			{//3
				if( chk )
				cout << "Enter a no. from 1 - 5:\t" ;
				do
				{//4
					if( result )
					cout << "Enter a no. from 1 - 5:\t" ;
					gets( temp ) ;
					result = onlynum( temp ) ;
				}while( result ) ;
				//4
				ans2 = atoi( temp ) ;
				chk = 1 ;

			}while( ans2 < 1 || ans2 > 5 ) ;
			//3
			wrd = ans2 - 1 ;
			wd.seekg( sizeof( w1 ) * ( wrd ) , ios :: beg ) ;
			wd.read( ( char * )&w1 , sizeof( w1 ) ) ;
			cout << "Select type:\n" ;
			cout << "1.Single bed- Rs" << w1.getcost( 0 ) << "\n2.Double Bed- Rs" << w1.getcost( 1 ) << "\n3.General- Rs" << w1.getcost( 2 ) << '\n' ;
			chk = 0 ;
			result = 0 ;
			do
			{//5
				if( chk )
				cout << "Enter a no. from 1 - 3:\t" ;
				do
				{ //6
					if( result )
					cout << "Enter a no. from 1 - 3:\t" ;
					gets( temp ) ;
					result = onlynum( temp ) ;
				}while( result ) ;
				//6
				ans2 = atoi( temp ) ;
				chk = 1 ;

			}while( ans2 < 1 || ans2 > 3 ) ;
			//5
			typ = ans2 - 1 ;
			int chck = 1 ;
			if( typ == 0 && w1.getno( typ ) == 10 )
			chck = 0 ;
			else
			if( typ == 1 && w1.getno( typ ) == 20 )
			chck = 0 ;
			else
			if( typ == 2 && w1.getno( typ ) == 30 )
			chck = 0 ;
			if( chck )
			{ //7

				ward w2 ;
				int wrd2 = w ;
				wd.seekg( sizeof( w2 ) * ( wrd2 ) , ios :: beg ) ;
				int g , gmax , u ;
				wd.read( ( char * )&w2 , sizeof( w2 ) ) ;
				int type = t ;
				gmax = w2.getno( type ) ;//No of patients
				for( g = 0 ; g < gmax ; ++ g )
				{
					if( w2.getpat_no( type , g ) == p_id )
					{
						for( u = g ; u < ( gmax - 1 ) ; ++ u )
						w2.assign_pat_no( type , u , w2.getpat_no( type , u + 1 ) ) ;
						w2.s_no( type ) ;//Deletion
						break ;
					}
				}
				wd.seekp( sizeof( w2 ) * ( wrd2 ) , ios :: beg ) ;
				wd.write( ( char * )&w2 , sizeof( w2 ) ) ;
				w = wrd ;
				t = typ ;
				wd.seekp( sizeof( w1 ) * ( wrd ) , ios :: beg ) ;
				w1.assign_pat_no( typ , w1.getno( typ ) , p_id ) ;
				w1.a_no( typ ) ;
				wd.write( ( char * )&w1 , sizeof( w1 ) ) ;
				flag = 1 ;
				wd.close( ) ;
				break ;
			} //7
			else
			{ //8
				cout << "The ward is full.\nDo you want to change your choice?( y/n )\n" ;
				char p ;
				int aa = 0 ;
				do
				{//9
					if( aa )
					cout << "\nEnter y or n:\t" ;
					p = getch( ) ;
					p = tolower( p ) ;
					if( p == 'y' || p == 'n' )
					break ;
					aa = 1 ;
				}while( 1 ) ;
				//9
				if( p == 'y' )
				{//10
					continue ;
				}//10
				else
				{//11
					flag = 0 ;
				}//11
			}//8
		}//2
		if( flag == 1 )
		{
			wd.close( ) ;
			return ;
		}
		else
		if( flag == 0 )
		{
			wd.close( ) ;
			deletefile_p( p_id ) ;
			return ;
		}
	}
	if( ( ii == 9 || ii == 10 ) && p_type == 2 )
	{
	cout << "Enter new data for specialization required:\n" ;
	cout << "1.Cardiologist\n2.Neurologist\n3.Dentist\n"
	     << "4.Physician\n5.Gynaecologist\n6.Paediatrician\n"
	     << "7.E.N.T specialist\n8.Gastroenterologist\n" ;
	int ch ;
	int k = 0 ;
	char spec[ 30 ] ;
	do
	{
		if( k )
		{
			cout << "Enter a number between 1-8\t" ;
		}
		result = 0 ;
		do
		{
		if( result )
		cout << "Enter a number between 1-8\t" ;
		gets( temp ) ;
		result = onlynum( temp ) ;

		}while( result ) ;
		ch = atoi( temp ) ;
		if( ch >= 1 && ch <= 8 )
		{
			strcpy( spec , s[ ch - 1 ] ) ;
			break ;
		}
		k = 1 ;

	}while( 1 ) ;

	int s = 0 ;//Stores the no of doctors with the above spec

	doctor d1 ;
	ifstream fi( "DOCTORS.mih" , ios :: in | ios :: binary ) ;
	while( fi.read( ( char * )&d1 , sizeof( d1 ) ) )
	{
		if( !strcmp( spec , d1.getspec( ) ) )
		{
			++ s ;
		}
	}
	fi.close( );

	int *arr = NULL ;
	arr = new int[ s ] ;// stores the od of all the docs with spec
	int cnt = 0 ;//to increment the address of *arr
	int s1 = s ;//s1 = s - ( doctors who are not available this week)
	char a ;
	doctor d ;
	char ee ;
	int n ;
	int l = 1 ;
	fi.open( "DOCTORS.mih" , ios :: in | ios :: binary ) ;
	fi.seekg( 0 , ios :: beg ) ;
	if( s )
	{
	int x , y ;
	setfillstyle( 1 , 0 ) ;
	cleardevice( ) ;
	x = 1 , y = 2 ;
	gotoxy( x , y ) ;
	cout << "ID" ;
	x = 10 ;
	gotoxy( x , y ) ;
	cout << "SPECIALIZATION" ;
	x = 30 ;
	gotoxy( x , y ) ;
	cout << "EXPERIENCE" ;
	x = 45 ;
	gotoxy( x , y ) ;
	cout << "NEXT APPOINTMENT DATE" ;
	y = 4 ;
	setcolor( 15 ) ;
	line( 0 , 30 , getmaxx( ) , 30 ) ;
	line( 0 , 320 , getmaxx( ) , 320 ) ;
	gotoxy( 1 , 1 ) ;
	cout << "Press ESC to go back & arrows for scrolling." ;
	y = 4 ;
	int c = 0 ;
	while( fi.read( ( char * )&d , sizeof( d ) ) )
	{
		++ c ;
		if( !strcmp( d.getspec( ) , spec ) )
		{
		x = 1 ;
		gotoxy( x , y ) ;
		cout << d.getdoc_id( ) ;
		x = 10 ;
		gotoxy( x , y ) ;
		cout << d.getspec( ) ;
		x = 30 ;
		gotoxy( x , y ) ;
		cout << d.getexp( ) ;
		x = 45 ;
		gotoxy( x , y ) ;
		int res = 1 ;
		char str[ 30 ] ;
		if( d.l == 5 )
		{
			res = 0 ;
		}
		if( res )
		{
			int aa = d.l ;
			for( int bb = 0 ; bb <= d.l ; ++ bb )
			{
				if( d.getcn( bb ) < NO )
				{
				aa = bb ;
				break ;
				}
			}
			cout << d.getnextd( aa ) ;
			arr[ cnt ] = d.getdoc_id( ) ;
			++ cnt ;
		}
		else
		{
			int aa = d.l ;
			for( int bb = 0 ; bb <= d.l ; ++ bb )
			{
				if( d.getcn( bb ) < NO )
				{
				aa = bb ;
				break ;
				}
			}
			if( aa == d.l )
			{
			cout << "Available next week" ;
			-- s1 ;
			}
			else
			{
			arr[ cnt ] = d.getdoc_id( ) ;
			++ cnt ;
			}
		}

		++ y ;
		if( y == 20 )//max y
		break ;
		}
	}
	}

	if( s1 )//If doctors with spec are available
	{
	doctor d2 ;
	int cnt2 = 0 ;
	int ID ;
	fstream dfi( "DOCTORS.mih" , ios :: in | ios :: out | ios :: binary ) ;
	while( dfi.read( ( char * )&d2 , sizeof( d2 ) ) )
	{
		++ cnt2 ;
		if( cdid == d2.getdoc_id( ) )
		{
			break ;
		}
	}
	int h , g , gmax , u ;

	for( h = 0 ; h < 5 ; ++ h )
	{
		gmax = d2.getcn( h ) ;//No of patients that day
		for( g = 0 ; g < gmax ; ++ g )
		{
			if( d2.getapid( h , g ) == p_id )
			{
				for( u = g ; u < ( gmax - 1 ) ; ++ u )
				d2.assign_apid( h , u , d2.getapid( h , u + 1 ) ) ;
				d2.s_cn( h ) ;//Deletion
				h = d2.l ;//to come out of loop
				break ;
			}
		}
	}
	dfi.seekp( sizeof( d2 ) * ( cnt2 - 1 ) , ios :: beg ) ;
	dfi.write( ( char * )&d2 , sizeof( d2 ) ) ;

	dfi.close( ) ;
	gotoxy( 1 , 22 ) ;
	cout << "Choose doctor from the above options.\nEnter doctor id:\n" ;
	do
	{
		result = 0 ;
		do
		{
		if( result )
		cout << "Enter a valid id:\t" ;
		gets( temp ) ;
		result = onlynum( temp ) ;

		}while( result ) ;
		n = atoi( temp ) ;

		for( int j = 0 ; j < s1 ; ++ j )
		{
			if( n == arr[ j ] )
			{
				cdid = n ;
				int rec = 0 ;
				fstream f1( "DOCTORS.mih" , ios :: in | ios :: out | ios :: binary ) ;
				while( f1.read( ( char * )&d , sizeof( d ) ) )
				{
				++ rec ;
				if( cdid == d.getdoc_id( ) )
				{
				int cc = d.l ;
				for( int dd = 0 ; dd <= d.l ; ++ dd )
				{
					if( d.getcn( dd ) < NO )
					{
					cc = dd ;
					break ;
					}
				}
				int check ;
				for( int z = 0 ; z < 5 ; ++ z )
				{
					if( d.getcn( z ) == 0 )
					check = 1 ;
					else
					check = 0 ;
				}
				if( check == 1 )
				{
				time_t t1 ;
				t1 = time( NULL ) ;
				d.fdoa = t1 ;
				}

				cleardevice( ) ;
				gotoxy( 1 , 1 ) ;
				cout << "The earliest appointment date is:\t" << d.getnextd( cc ) ;
				cout << "\nDo you want to change it?( y/n )" ;
				do
				{
					ee = getch( ) ;
					ee = tolower( ee ) ;
					if( ee == 'y' || ee == 'n' )
					break ;
					cout << "\nEnter y or n:" ;

				}while( 1 ) ;

				if( ee == 'y' )
				{
				cout << "\nThe other dates on which doctor is available:\n" ;
				char temp[ 30 ] ;
				int result = 0 ;
				int choice ;
				for( int gg = 0 ; gg < 5 ; ++ gg )
				{
					if( d.getcn( gg ) < NO )
					{
					cout << '\n' << gg + 1 << ". " ;
					}
					else
					cout << '\n' << gg + 1 << ". " << "( FULL )" ;
					puts( d.getnextd( gg ) ) ;
				}
				int jj , chk = 0 ;
				cout << "\nChoose from the above options:\t" ;
				do
				{

				do
				{
				if( chk )
				{
				cout << "FULL\n" ;
				cout << "Choose another option:\t" ;
				}
				else
				if( result )
				cout << "Enter a valid number:\t" ;
				gets( temp ) ;
				result = onlynum( temp ) ;
				jj = atoi( temp ) ;
				if( !result && ( ( jj - 1 ) >= 0 && ( jj - 1 ) <= 4 ) )
				break ;
				else
				result = 1 ;

				}while( result ) ;
				if( d.getcn( jj - 1 ) == NO )
				chk = 1 ;
				else
				chk = 0 ;

				}while( chk ) ;
				choice = atoi( temp ) ;
				-- choice ;
				d.assign_apid( choice , d.getcn( choice ) , p_id ) ;
				d.a_cn( choice ) ;
				if( ( choice == d.l ) && ( d.getcn( choice ) == NO ) )
				++ d.l ;
				}
				else
				{
				d.assign_apid( cc , d.getcn( cc ) , p_id ) ;
				d.a_cn( cc ) ;
				while( d.getcn( d.l ) == NO )
				{
					++ d.l ;
				}
				}
				f1.seekp( sizeof( d ) * ( rec - 1 ) , ios :: beg ) ;
				f1.write( ( char * )&d , sizeof( d ) ) ;

				}
				}
				f1.close( ) ;
				l = 0 ;
				break ;
			}
		}
		if( l )
		cout << "Enter a valid id:\t" ;
		else
		break ;

	} while( 1 ) ;
	}
	else
	{
		cleardevice( ) ;
		gotoxy( 1 , 1 ) ;
		char e ;
		cout << "\nNo " << spec << " in the hospital\n"
		     <<	"Do you want to delete the record?\n( y/n )\n" ;
		do
		{
			e = getch( ) ;
			e = tolower( e ) ;
			if( e == 'y' || e == 'n' )
			break ;
			cout << "\nEnter y or n:" ;

		}while( 1 ) ;
		if( e == 'y' )
		deletefile_p( p_id ) ;
		fi.close( ) ;
		delete [ ] arr ;
		arr = NULL ;
		return ;
	}
	delete [ ] arr ;
	arr = NULL ;
	fi.close( ) ;
	}
}

void main( )
{
	clrscr( ) ;
	int gd = DETECT , gm , error ;
	initgraph( &gd , &gm , "C:\\TC\\BGI" ) ;
	error = graphresult( ) ;
	if( error != grOk )
	{
		cout << grapherrormsg( error ) << "\nPress any key to exit." ;
		getch( ) ;
		exit( 0 ) ;
	}

	ofstream ed( "DOCTORS.mih" , ios :: out | ios :: noreplace | ios :: binary ) ;
	if( ed )
	{
	doctor doc ;
	int docn = 97 , addr = 65 ;
	char addr2[ 20 ] , docn2[ 20 ] ;
	int count = 0 ;
	Date dat1 = { 1 , "January" , 1986 } , dat2 = { 1 , "January" , 2010 } ;
	int cn ;
	char cn2[ 30 ] ;
	char em[ 30 ] ;
	cn = ( rand( ) % 100 ) + 1000 ;

	for( int i = 0 ; i < LEN ; ++ i )
	{
		docn2[ count ] = ( char )docn ;
		addr2[ count ] = ( char )addr ;
		cn += i ;
		itoa( cn , cn2 , 10 ) ;
		strcpy( em , addr2 ) ;
		strcat( em , "@gmail.com" ) ;
		docn2[ count + 1 ] = '\0' ;
		addr2[ count + 1 ] = '\0' ;
		doc = doctor( docn2 , 30 , addr2 , cn2 , dat1 , dat2 , em , "mbbs" , 6 , s[ i ] , i + 1 , "doctor" ) ;
		for( int ii = 0 ; ii < 5 ; ++ ii )
		doc.assign_days( ii , ( ii + 1 ) ) ;
		for( ii = 0 ; ii < 5 ; ++ ii )
		doc.assign_cn( ii , 0 ) ;
		doc.l = 0 ;
		doc.fdoa = 0 ;
		ed.write( ( char * )&doc , sizeof( doc ) ) ;
		if( ( char )docn == 'z' )
		{
			docn = 97 ;
			addr = 65 ;
			++ count ;
		}
		++ docn ;
		++ addr ;

	}
	ed.close( ) ;
	remove( "DN.mih" ) ;
	remove( "NO.mih" ) ;
	}

	ofstream wd( "WARD.mih" , ios :: out | ios :: noreplace | ios :: binary ) ;

	if( wd )
	{
	ward w ;
	int q , e , r , wt , wno[ 3 ] , wcost[ 3 ] ;
	for( int m = 0 ; m < WN ; ++ m )
	{
		wt = m ;
		wno[ 0 ] = 0 ;
		wno[ 1 ] = 0 ;
		wno[ 2 ] = 0 ;
		wcost[ 0 ] = 1000 ;
		wcost[ 1 ] = 500 ;
		wcost[ 2 ] = 100 ;
		w = ward( wt , wno , wcost ) ;
		w.assign_no( 0 ,  0 ) ;
		w.assign_no( 1 ,  0 ) ;
		w.assign_no( 2 ,  0 ) ;
		w.assign_cost( 0 ,  1000 ) ;
		w.assign_cost( 1 ,  500 ) ;
		w.assign_cost( 2 ,  100 ) ;
		for( q = 0 ; q < 3 ; ++ q )
		{
			for( e = 0 ; e < 30 ; ++ e )
			{
				w.assign_pat_no( q , e , 0 ) ;
			}
		}
		wd.write( ( char * )&w , sizeof( w ) ) ;
	}

	wd.close( ) ;

	}

	//Creates a file that stores last id of doctor if it doesn't exist
	ofstream dn( "dn.mih" , ios :: out | ios :: binary | ios :: noreplace ) ;
	if( dn )
	{
	dn << doc_no ;
	dn.close( ) ;
	}
	//Creates a file that stores no. of doctors if it doesn't exist
	ofstream d_no( "no.mih" , ios :: out | ios :: binary | ios :: noreplace ) ;
	if( d_no )
	{
	d_no << dno ;
	d_no.close( ) ;
	}
	// dn.mih & no.mih are nearly same but no.mih gets
	//decremented when a doctor record is deleted
	doctor d ;

	ifstream fi( "DOCTORS.mih" , ios :: in | ios :: binary ) ;

	int a , b , c = 0 , y = 0 ;
	int z , f ;
	char str[ 30 ] , array[ 5 ] ;
	long dtime ;
	int dat ;
	int week[ 7 ] ;
	time_t t ;
	t = time( NULL ) ;
	strcpy( str , ctime( &t ) ) ;
	array[ 0 ] = str[ 0 ] ;
	array[ 1 ] = str[ 1 ] ;
	array[ 2 ] = str[ 2 ] ;
	array[ 3 ] = '\0' ;

	if( !strcmp( array , "Mon" ) )
	dat = 1 ;
	else
	if( !strcmp( array , "Tue" ) )
	dat = 2 ;
	else
	if( !strcmp( array , "Wed" ) )
	dat = 3 ;
	else
	if( !strcmp( array , "Thu" ) )
	dat = 4 ;
	else
	if( !strcmp( array , "Fri" ) )
	dat = 5 ;
	else
	if( !strcmp( array , "Sat" ) )
	dat = 6 ;
	else
	if( !strcmp( array , "Sun" ) )
	dat = 7 ;
	while( fi.read( ( char * )&d , sizeof( d ) ) )
	{
	f = 0 ;
	y = 0 ;
	++ c ;
	for( z = 0 ; z < 5 ; ++ z )
	{
		if( d.getcn( z ) > 0 )
		{
			y = 1 ;
			break ;
		}
	}
	if( y == 1 )
	{
	dtime = ( difftime( t , d.fdoa ) / 86400 ) ;
       //	cout << dtime ;
      //	getch( ) ;
	}
	if( y == 1 && dtime )
	{
		if( dtime <= 7 )
		{
			for( int k = 0 ; k < dtime ; ++ k )
			{
				week[ k ] = dat ;

				for( int j = 0 ; j < 5 ; ++ j )
				{
					if( d.getdays( j ) == week[ k ] )//Q
					{
						++ f ;
						break ;
					}

				}
				if( dat == 1 )
				dat = 8 ;
				-- dat ;
			}
			if( !f )
			d.fdoa += 86400 ;
			for( int t1 = 0 ; t1 < f ; ++ t1 )
			{
			d.assign_cn( 0 , d.getcn( 1 ) ) ;
			d.assign_cn( 1 , d.getcn( 2 ) ) ;
			d.assign_cn( 2 , d.getcn( 3 ) ) ;
			d.assign_cn( 3 , d.getcn( 4 ) ) ;
			d.assign_cn( 4 , 0 ) ;
			d.fdoa += 86400 ;
			for( a = 0 ; a < 4 ; ++ a )
			{
			for( b = 0 ; b < d.getcn( a ) ; ++ b )
			{
			d.assign_apid( a , b , d.getapid( a + 1 , b ) ) ;
			}
			}
			if( d.l > 0 )
			-- d.l ;
			}

		}
		else
		{
			for( int t1 = 0 ; t1 < 5 ; ++ t1 )
			{
			d.assign_cn( 0 , d.getcn( 1 ) ) ;
			d.assign_cn( 1 , d.getcn( 2 ) ) ;
			d.assign_cn( 2 , d.getcn( 3 ) ) ;
			d.assign_cn( 3 , d.getcn( 4 ) ) ;
			d.assign_cn( 4 , 0 ) ;
			d.fdoa = 0 ;
			for( a = 0 ; a < 4 ; ++ a )
			{
			for( b = 0 ; b < d.getcn( a ) ; ++ b )
			{
			d.assign_apid( a , b , d.getapid( a + 1 , b ) ) ;
			}
			}
			if( d.l > 0 )
			-- d.l ;
			}
		}
	ofstream fo( "DOCTORS.mih" , ios :: ate | ios :: binary ) ;
	fo.seekp( sizeof( d ) * ( c - 1 ) , ios :: beg ) ;
	fo.write( ( char * )&d , sizeof( d ) ) ;
	fo.close( ) ;
	}

	}
	fi.close( ) ;

	int ch = 1 ;
	char nm[ 4 ][ 50 ] = {
				"Employee Management" ,
				"Doctors" ,
				"Patient Administration" ,
				"Wards"
			     } ;
	while( ch )
	{
	cleardevice( ) ;
	fflush( stdin ) ;
	fflush( stdout ) ;
	ch = page( 11 , 12 , 1 , 4 , "HOSPITAL MANAGEMENT" , 15 , 9 , 300 , nm ) ;

	//for storing password in a file
	ofstream ps( "pass.mih" , ios :: out | ios :: noreplace | ios :: binary ) ;
	if( ps ) // so that if the password is already set it doesn't get replaced
	{
	ps << pass ;
	ps.close( ) ;
	}
	else
	{
	ifstream ps( "pass.mih" , ios :: in | ios :: binary ) ;
	ps >> pass ;
	ps.close( ) ;
	}
	//
	switch( ch )
	{
		case 1 :
			employee( ) ;
			break ;
		case 2 :
			doctors( ) ;
			break ;
		case 3 :
			patients( ) ;
			break ;
		case 4 :
			WARD( ) ;
			break ;
	}

	}
	cleardevice( ) ;
	closegraph( ) ;
	restorecrtmode( ) ;
}

int page( int bkcolor1 , int bkcolor2 , int side , int no , char *s_text , int tcolor , int col_color , int xgap , char nm[ ][ 50 ] )
{
	if( side )
	{
	setcolor( 10 ) ;                  // Seperates the heading from the
	line( 50 , 0 , 50 , getmaxy( ) ) ; // main content & the color of
					   // the line is light green.
	setfillstyle( 1 , bkcolor2 ) ; // Solid fill & bkcolor2
	floodfill( 29 , 5 , 10 ) ; // Fills the left portion with bkcolor2
	}
	setfillstyle( 1 , bkcolor1 ) ; // Solid fill & bkcolor1
	floodfill( 61 , 1 , 10 ) ; // Fills the right portion with bkcolor1

	settextstyle( 3 , 1 , 4 ) ; // Displays the header s_text
					 //vertically in tcolor.
	setcolor( tcolor ) ;
	moveto( 1 , 1 ) ;
	if( side )
	outtext( s_text ) ;

	int v[ 10 ] ; // For vertices of the columns

	v[ 0 ] = getmaxx( ) ;
	v[ 1 ] = 20 ;

	v[ 2 ] = getmaxx( ) - xgap ;
	v[ 3 ] = 20 ;

	v[ 4 ] = getmaxx( ) - xgap - 20 ;
	v[ 5 ] = 45 ;

	v[ 6 ] = getmaxx( ) ;
	v[ 7 ] = 45 ;

	v[ 8 ] = v[ 0 ] ;
	v[ 9 ] = v[ 1 ] ;
	setfillstyle( 1 , col_color ) ;
	int q = 0 ;// to set floodfill pos for various columns
	int start = v[ 1 ] ; // for initial y posn
	int gap = 50 ; // gap b/w columns
	for( int i = 0 ; i < no ; ++ i ) // for printing columns
	{
		fillpoly( 5 , v ) ;
		q += gap ;
		for( int j = 1 ; j <= 9 ; j += 2 )
		v[ j ] += gap ;
	}
	int ii ;
	settextstyle( 1 , 0 , 2 ) ;
	for( ii = 0 ; ii < no ; ++ ii )
	writecol( nm[ ii ] , ii + 1 , start , gap , xgap ) ;

	settextstyle( 1 , 0 , 1 ) ;
	int ch = 1 , ch2[ 3 ] ; //ch tells the col no.
				//ch[ 0 ] receives the value
				//of ch before changing
				// ch[ 1 ] gets previous x coordinate
				// ch[ 2 ] gets previous y coordinate
	int v2[ 10 ] ; // for fillpoly , for drawing small boxes
	moveto( getmaxx( ) - xgap - 20 , start + 25 ) ;
	char n , c;
	int x , y ;
	while( n != ENTER )
	{
		  //Everytime the loop begins a small orange box is drawn
		  setfillstyle( 1 , 12 ) ;//orange
		  x = getx( ) ;
		  y = gety( ) ;

		  v2[ 0 ] = x ;
		  v2[ 1 ] = y ;

		  v2[ 2 ] = x - 50 ;
		  v2[ 3 ] = y ;

		  v2[ 4 ] = x - 30 ;
		  v2[ 5 ] = y - 25 ;

		  v2[ 6 ] = x + 20 ;
		  v2[ 7 ] = y - 25 ;

		  v2[ 8 ] = v2[ 0 ] ;
		  v2[ 9 ] = v2[ 1 ] ;

		  setcolor( bkcolor1 ) ;
		  fillpoly( 5 , v2 ) ;
		  n = getch( ) ;
		  setcolor( tcolor ) ;
		  if( n == ENTER )
		  continue ;
		  if( n == ESC )
		  {
			cleardevice( );
			return 0;
		  }
		  if( n == '\0' )
		 {
		  c = getch( );
		switch( c )
		{
			case UP :
				  x = getx( ) ;
				  y = gety( ) ;
				  if( ch == 1 )
				  {
					ch2[ 0 ] = ch ;
					x = ch2[ 1 ] = getx( ) ;
					y = ch2[ 2 ] = gety( ) ;
					moveto( x , y + ( no - 1 ) * gap  ) ;
					ch = no ;
				  }
				  else
				  {
					ch2[ 0 ] = ch ;
					x = ch2[ 1 ] = getx( ) ;
					y = ch2[ 2 ] = gety( ) ;
					moveto( x , y - gap ) ;
					-- ch ;
				  }

				  break ;

			case DOWN :
				  x = getx( ) ;
				  y = gety( ) ;
				  if( ch == no )
				  {
					ch2[ 0 ] = ch ;
					x = ch2[ 1 ] = getx( ) ;
					y = ch2[ 2 ] = gety( ) ;
					moveto( x , y - ( no - 1 ) * gap  ) ;
					ch = 1 ;
				  }
				  else
				  {
					ch2[ 0 ] = ch ;
					x = ch2[ 1 ] = getx( ) ;
					y = ch2[ 2 ] = gety( ) ;
					moveto( x , y + gap ) ;
					++ ch ;
				  }
				   break ;
		}
		}
		  setcolor( bkcolor1 ) ;
		  setfillstyle( 1 , bkcolor1 ) ;

		  v2[ 0 ] = x ;
		  v2[ 1 ] = y ;

		  v2[ 2 ] = x - 50 ;
		  v2[ 3 ] = y ;

		  v2[ 4 ] = x - 30 ;
		  v2[ 5 ] = y - 25 ;

		  v2[ 6 ] = x + 20 ;
		  v2[ 7 ] = y - 25 ;

		  v2[ 8 ] = v2[ 0 ] ;
		  v2[ 9 ] = v2[ 1 ] ;
		  fillpoly( 5 , v2 ) ;
		  setcolor( tcolor ) ;
		  line( x , y , x + 20 , y - 25 ) ;
	}
	cleardevice( ) ;
	return ch ;
}

int writecol( char *str , int no , int starty , int gap , int xgap )
{
	-- no ;
	if( starty + ( gap * no ) >= getmaxy( ) )
	return 0 ;
	settextstyle( 1 , 0 , 2 ) ;
	outtextxy( getmaxx( ) - xgap , starty + ( gap * no ) , str ) ;
	return 1 ;
}

void employee( )
{
	char str[ 30 ] ;//str is the pass typed by user
	static int check = 0 ;//It ensures that if the user has entered the
	//pass once then it will not ask for the pass again until user
	//returns to homepage
	static int a = 1 ;
	while( a )
	{
	if( !check )
	{
	setcolor( 15 ) ; // white
	setfillstyle( 1 , 8 ) ; //grey
	settextstyle( 0 , 0 , 1 ) ;
	outtextxy( midx - 50 , midy - 40, "Enter password:" ) ;
	rectangle( midx - 50 , midy  , midx + 60 , midy + 25 ) ;
	floodfill( midx - 49 , midy + 1 , 15 ) ;
	setcolor( 2 ) ;// green
	outtextxy( 1 , midy + 40 , "1.Only lowercase alphabets & numbers are allowed" ) ;
	outtextxy( 1 , midy + 60 , "2.Max 12 characters " ) ;
	setcolor( 2 ) ;//green
	outtextxy( 1 , midy + 100, "Press ESC to return to homepage" ) ;
	settextstyle( 0 , 0 , 1 ) ;
	setcolor( 2 ) ;
	char str3[ 40 ] = "Default password: hello" ;  // Displays the password on
	//the top
	outtextxy( 1 , 50 , str3 ) ;
	do
	{
		floodfill( midx - 44 , midy + 6 , 15 ) ;
		strcpy( str , inputpass( midx - 45 , midy + 5 , 12 ) ) ;
		if( !strcmp( str , "ESC" ) )
		{
			cleardevice( ) ;
			return ;
		}
		else
		if( !strcmp( str , pass ) )
		{
		a = 0 ;
		break ;
		}
		else
		{
			setcolor( 3 ) ;
			outtextxy( 100 , 100 , "Invalid Password!" ) ;
			//setcolor( 1 ) ;
			getch( ) ;
			cleardevice( ) ;
			break ;
		}
	} while( 1 ) ;

	}
	}

	int ch ;
	char nm[ 2 ][ 50 ] = {
				"Doctor Database" ,
				"Set Password" ,
			   } ;

	while( 1 )
	{
	ch = page( 11 , 12 , 1 , 2 , "EMPLOYEE MANAGEMENT" , 15 , 9 , 300 , nm ) ;

	if( !ch )
	{
		cleardevice( ) ;
		check = 0 ;
		a = 1 ;
		return ;
	}

	int c = 0 ;
	int r ;
	char passwd[ 30 ] ;
	char o ;
	switch( ch )
	{
		case 1 :
			check = 1 ;
			doctors_d( ) ;
			break ;
		case 2 :
			check = 0 ;
			a = 1 ;
			do
			{
			strcpy( passwd, setpass( pass , 12 , c ) ) ;
			if( !strcmp( passwd , "ESC" ) )
			{
				cleardevice( ) ;
				return ;
			}
			strcpy( pass , passwd ) ;
			cleardevice( ) ;
			}while( c == 0 ) ;
			ofstream ps( "pass.mih" , ios :: out | ios :: binary ) ;
			ps << pass ;
			ps.close( ) ;
			cleardevice( ) ;
			return ;
	}
	}
}

void doctors( )
{
	int rec = 0 , r ;
	do
	{
		r = login( 12 ) ;
		if( r == -1 )
		{
		cleardevice( ) ;
		return ;
		}
	}while( r == 0 ) ;
	ifstream fi( "DOCTORS.mih" , ios :: in | ios :: binary ) ;
	doctor d ;

	while( fi.read( ( char * )&d , sizeof( d ) ) )
	{
		++ rec ;
		if( r == d.getdoc_id( ) )
		{
			break ;
		}
	}
	fi.close( ) ;
	cleardevice( ) ;
	char nm[ 4 ][ 50 ] = {
				"Appointments" ,
				"Set password" ,
				"Sign Out"
			   } ;

	int a = 1 ;
	int c = 0 ;
	char p[ 30 ] ;
	int ch ;
	while( a )
	{
	cleardevice( ) ;
	ch = page( 11 , 12 , 1 , 3 , d.getname( ) , 15 , 9 , 300 , nm ) ;

	if( !ch )
	{
		cleardevice( ) ;
		return ;
	}

	switch( ch )
	{
		case 1 :
			p_manage( rec ) ;
			break ;
		case 2 :
			int yes = 0 ;
			do
			{
			strcpy( p , setpass( d.getpassword( ) , 12 , c ) ) ;
			if( !strcmp( p , "ESC" ) )
			{
			cleardevice( ) ;
			yes = 0 ;
			break ;
			}
			if( c == 1 )
			{
			d.d_pass( p ) ;
			yes = 1 ;
			break ;
			}
			cleardevice( ) ;
			}while( 1 ) ;
			if( yes == 1 )
			{
			ofstream fo ;
			fo.open( "DOCTORS.mih" , ios :: ate | ios :: binary ) ;
			fo.seekp( sizeof( d ) * ( rec - 1 ) , ios :: beg ) ;
			fo.write( ( char * )&d , sizeof( d ) ) ;
			fo.close( ) ;
			}
			break ;
		case 3 :
			return ;

	}

	}
}

void patients( )
{
	cleardevice( ) ;

	//Creates a file that stores last patient's id if it doesn't exist
	ofstream pid( "pid.mih" , ios :: out | ios :: noreplace | ios :: binary ) ;
	if( pid )
	{
	pid << p_no ;
	pid.close( ) ;
	}
	//Creates a file that stores no. of patients if it doesn't exist
	ofstream Pno( "pno.mih" , ios :: out | ios :: binary | ios :: noreplace ) ;
	if( Pno )
	{
	Pno << pno ;
	Pno.close( ) ;
	}
	// pid.mih & pno.mih are nearly same but pno.mih gets
	//decremented when a record is deleted
	char nm[ 9 ][ 50 ] = {
				"Display records of all Out-patients" ,
				"Display records of all In-patients" ,
				"Discharge a patient" ,
				"Add new Patient's record" ,
				"Display Patient's record" ,
				"Update Patient's information" ,
				"Delete Patient's record" ,
				"Generate patient bills" ,
				"Clear data of all patients"
			     } ;
	int ch ;
	while( 1 )
	{

	ch = page( 11 , 12 , 1 , 9 , "PATIENT ADMINISTRATION" , 15 , 9 , 400 , nm ) ;
	if( !ch )
	{
		cleardevice( ) ;
		return ;
	}

	char o , temp[ 30 ] ;
	int chk = 0 ;
	switch( ch )
	{
		case 1 :
			cleardevice( ) ;
			disp_all_p( ) ;

			break ;
		case 2 :
			cleardevice( ) ;
			disp_all_ip( ) ;

			break ;
		case 3 :
			cleardevice( ) ;
			int id ;
			gotoxy( 1 , 1 ) ;
			cout << "Enter id of the patient who is getting discharged from the hospital:\n" ;
			do
			{
			if( chk )
			cout << "Enter a valid no.:" ;
			gets( temp ) ;
			chk = onlynum( temp ) ;

			}while( chk ) ;
			id = atoi( temp ) ;

			discharge( id ) ;

			break ;
		case 4 :
			cleardevice( ) ;
			createfile_p( ) ;

			break ;
		case 5 :
			cleardevice( ) ;
			displayfile_p( ) ;

			break ;
		case 6 :
			cleardevice( ) ;
			modifyfile_p( ) ;

			break ;
		case 7 :
			cleardevice( ) ;
			deletefile_p( ) ;
			break ;
		case 8 :
			cleardevice( ) ;
			genbill( ) ;
			break ;
		case 9 :cleardevice( ) ;
			setcolor( 15 ) ;
			outtext( "Do you want to clear all the data?( y/n )" ) ;
			o = getch( ) ;
			tolower( o ) ;
			while( o != 'y' && o != 'n' )
			{
				cleardevice( ) ;
				outtext( "Enter y or n :" ) ;
				o = getch( ) ;
			}
			if( o == 'n' )
			break ;
			else
			{
			int p , r ;
			r = remove( "PATIENTS.mih" ) ;
			p = remove( "IPATIENTS.mih" ) ;
			remove( "pid.mih" ) ;
			remove( "pno.mih" ) ;

			if( !r )
			{
			ifstream fi( "DOCTORS.mih" , ios :: in | ios :: binary ) ;
			ofstream fo( "DOCTORS.mih" , ios :: ate | ios :: binary ) ;
			doctor d ;
			int cnt  = 0 , s ;
			while( fi.read( ( char * )&d , sizeof( d ) ) )
			{
				++ cnt ;
				for( s = 0 ; s < 5 ; ++ s )
				{
					d.assign_cn( s , 0 ) ;
				}
				d.l = 0 ;
				fo.seekp( sizeof( d ) * ( cnt - 1 ) , ios :: beg ) ;
				fo.write( ( char * )&d , sizeof( d ) ) ;
			}
			fo.close( ) ;
			fi.close( ) ;
			}
			if( !p )
			{
			ifstream fi( "WARD.mih" , ios :: in | ios :: binary ) ;
			ofstream fo( "WARD.mih" , ios :: ate | ios :: binary ) ;
			ward w ;
			int cnt  = 0 , s ;
			while( fi.read( ( char * )&w , sizeof( w ) ) )
			{
				++ cnt ;
				for( s = 0 ; s < 3 ; ++ s )
				{
					w.assign_no( s , 0 ) ;
				}

				fo.seekp( sizeof( w ) * ( cnt - 1 ) , ios :: beg ) ;
				fo.write( ( char * )&w , sizeof( w ) ) ;
			}
			fo.close( ) ;
			fi.close( ) ;
			}
			p_no = 0 ;
			pno = 0 ;
			/*
			ofstream fo ;
			fo.open( "DN.mih" , ios :: binary | ios :: out ) ;
			fo << p_no ;
			fo.close( ) ;
			fo.open( "NO.mih" , ios :: binary | ios :: out ) ;
			fo << pno ;
			fo.close( ) ;*/
			cleardevice( ) ;
			}
			break ;
	}
	}

}
void genbill( )
{
	gotoxy( 1 , 1 ) ;
	int id , chk = 0 , f = 0 , cnt = 0 ;
	char temp[ 30 ] ;
	char types[ 3 ][ 50 ] = {
					"Single Bed" ,
					"Double bed" ,
					"General"
				} ;
	patient p ;
	ifstream fi , fi2 ;
	fi.open( "PATIENTS.mih" , ios :: in | ios :: binary ) ;
	fi2.open( "IPATIENTS.mih" , ios :: in | ios :: binary ) ;
	cout << "Enter id of patient:\n" ;
	do
	{
	if( chk )
	cout << "Enter a valid number:\t" ;
	gets( temp ) ;
	chk = onlynum( temp ) ;

	}while( chk ) ;
	id = atoi( temp  ) ;
	while( fi.read( ( char * )&p , sizeof( p ) ) )
	{
		++ cnt ;
		if( p.getp_id( ) == id )
		{
			f = 1 ;
			break ;
		}
	}
	if( !f )
	{
		cnt = 0 ;
		while( fi2.read( ( char * )&p , sizeof( p ) ) )
		{
			++ cnt ;
			if( p.getp_id( ) == id )
			{
				f = 1 ;
				break ;
			}
		}
	}
	if( !f )
	{
		cout << "\nNo such record exists!" ;
		getch( ) ;
		fi.close( ) ;
		fi2.close( ) ;
		return ;
	}
	else
	{
		if( p.getp_type( ) == 1 )
		{
			if( p.done == 0 )
			{
				cout << "\nPatient needs to be discharged to generate the bill." ;
				getch( ) ;
				fi.close( ) ;
				fi2.close( ) ;
				return ;
			}
			else
			{
				int typ , dys , cost ;
				long bill = 0 ;
				time_t t1 , t2 ;
				t1 = p.getad( ) ;
				t2 = p.getdd( ) ;
				typ = p.getwardtype( ) ;
				if( typ == 0 )
				cost = 1000 ;
				else
				if( typ == 1 )
				cost = 500 ;
				else
				if( typ == 2 )
				cost = 100 ;
				dys = ( difftime( t2 , t1 ) / 86400 ) ;
				if( dys == 0 )
				dys = 1 ;
				cout << "Bill:\n" ;
				cout << "WARD - " ;
				puts( types[ typ ] ) ;
				cout << "Days - " << dys ;
				cout << "\nCost for staying in ward=" << ( dys * cost ) ;
				bill += ( dys * cost ) ;
				cout << "\nCost for servicing( Rs200 per day )=" << ( dys * 200 ) ;
				bill += ( dys * 200 ) ;
				cout << "\n\nTOTAL=" << bill ;
				getch( ) ;
			}
		}
		else
		{
			ifstream dd( "DOCTORS.mih" , ios :: in | ios :: binary ) ;
			int e ;
			doctor d ;
			while( dd.read( ( char * )&d , sizeof( d ) ) )
			{
				if( d.getdoc_id( ) == p.getcdid( ) )
				break ;
			}
			e = d.getexp( ) ;
			if( e == 0 )
			e = 1 ;
			if( e > 20 )
			e = 20 ;
			cout << "Bill:\n" ;
			cout << "Rs " << ( e * 100 ) ;
			dd.close( ) ;
			getch( ) ;
		}
	}
	fi.close( ) ;
	fi2.close( ) ;
}

void discharge( int id )
{
	fstream f( "IPATIENTS.mih" , ios :: in | ios :: out | ios :: binary ) ;
	fstream wd( "WARD.mih" , ios :: in | ios :: out | ios :: binary ) ;
	patient p ;
	int cnt = 0 , flag = 0 ;
	time_t tm ;
	tm = time( NULL ) ;
	while( f.read( ( char * )&p , sizeof( p ) ) )
	{
		++ cnt ;
		if( id == p.getp_id( ) )
		{
			flag = 1 ;
			p.done = 1 ;
			p.p_dd( tm ) ;
			f.seekp( sizeof( p ) * ( cnt - 1 ) , ios :: beg ) ;
			f.write( ( char * )&p , sizeof( p ) ) ;
			break ;
		}
	}
	if( flag == 1 )
	{
		ward w ;
		int wrd = p.getward( ) ;
		wd.seekg( sizeof( w ) * ( wrd ) , ios :: beg ) ;
		int g , gmax , u ;
		wd.read( ( char * )&w , sizeof( w ) ) ;
		int type = p.getwardtype( ) ;
		gmax = w.getno( type ) ;//No of patients
		for( g = 0 ; g < gmax ; ++ g )
		{
			if( w.getpat_no( type , g ) == p.getp_id( ) )
			{
				for( u = g ; u < ( gmax - 1 ) ; ++ u )
				w.assign_pat_no( type , u , w.getpat_no( type , u + 1 ) ) ;
				w.s_no( type ) ;//Deletion
				break ;
			}
		}
		wd.seekp( sizeof( w ) * ( p.getward( ) ) , ios :: beg ) ;
		wd.write( ( char * )&w , sizeof( w ) ) ;
		cout << "\nDischarged." ;
		getch( ) ;
	}
	else
	{
		cout << "\nRecord not present." ;
		getch( ) ;
	}
	f.close( ) ;
	wd.close( ) ;
}

void WARD( )
{
	char wards[ WN + 1 ][ 50 ] = {
					"Cardio-Ward" ,
					"Gynae-Ward" ,
					"Medicine Ward" ,
					"Surgical ward" ,
					"Paediatric-Ward" ,
					"Details"
				      } ;
	int ch ;
	while( 1 )
	{
	ch = page( 11 , 12 , 1 , WN + 1 , "WARDS" , 15 , 9 , 400 , wards ) ;

	if( !ch )
	{
		cleardevice( ) ;
		return ;
	}

	switch( ch )
	{
		case 1 :
			cleardevice( ) ;
			openward( 0 ) ;

			break ;
		case 2 :
			cleardevice( ) ;
			openward( 1 ) ;

			break ;
		case 3 :
			cleardevice( ) ;
			openward( 2 ) ;

			break ;
		case 4 :
			cleardevice( ) ;
			openward( 3 ) ;

			break ;
		case 5 :
			cleardevice( ) ;
			openward( 4 ) ;

			break ;
		case 6 :
			cleardevice( ) ;
			ward wrd ;
			ifstream wd( "WARD.mih" , ios :: in | ios :: binary ) ;
			wd.read( ( char * )&wrd , sizeof( wrd ) ) ;
			wrd.putdata( ) ;
			wd.close( ) ;
			break ;
	}
	}
}

void openward( int a )
{
	char types[ 3 ][ 50 ] = {
					"Single Bed" ,
					"Double bed" ,
					"General"
				} ;
	int ch ;
	while( 1 )
	{
	ch = page( 11 , 12 , 1 , 3 , "TYPES" , 15 , 9 , 400 , types ) ;

	if( !ch )
	{
		cleardevice( ) ;
		return ;
	}

	switch( ch )
	{
		case 1 :
			cleardevice( ) ;
			WTYPE( 0 , a ) ;

			break ;
		case 2 :
			cleardevice( ) ;
			WTYPE( 1 , a ) ;

			break ;
		case 3 :
			cleardevice( ) ;
			WTYPE( 2 , a ) ;

			break ;
	}
	}
}

void WTYPE( int a , int b )
{
	ifstream fi , fi2 ;
	fi.open( "IPATIENTS.mih" , ios :: in | ios :: binary ) ;
	fi2.open( "WARD.mih" , ios :: in | ios :: binary ) ;
	ward w ;
	fi2.seekg( sizeof( w ) * b , ios :: beg ) ;
	fi2.read( ( char * )&w , sizeof( w ) ) ;
	int x , y ;
	char n ;
	patient p ;
	x = 1 , y = 2 ;
	gotoxy( x , y ) ;
	cout << "PatientID" ;
	x = 15 ;
	gotoxy( x , y ) ;
	cout << "AdmitDate" ;
	x = 35 ;
	gotoxy( x , y ) ;
	cout << "Name" ;
	y = 4 ;
	gotoxy( 1 , 3 ) ;
	setcolor( 15 ) ;
	line( 0 , 32 , getmaxx( ) , 32 ) ;
	gotoxy( 1 , 1 ) ;
	int u , yes = 0 , v = w.getno( a ) ;
	cout << "Press ESC to go back & arrows for scrolling." ;
	while( fi.read( ( char * )&p , sizeof( p ) ) )
	{
		for( u = 0 ; u < v ; ++ u )
		{
			if( p.getp_id( ) == w.getpat_no( a , u ) )
			{
				yes = 1 ;
				break ;
			}
		}


		if( yes == 1 )
		{
		x = 1 ;
		gotoxy( x , y ) ;
		cout << p.getp_id( ) ;
		x = 15 ;
		gotoxy( x , y ) ;
		char dat[ 30 ] ;
		char str[ 30 ] ;
		time_t t ;
		t = p.getad( ) ;
		strcpy( dat , convert( t ) ) ;
		puts( dat ) ;
		x = 35 ;
		gotoxy( x , y ) ;
		puts( p.getname( ) ) ;
		++ y ;
		}
		yes = 0 ;
		if( y == 26 )//max y
		break ;
	}
	n = getch( ) ;
	while( n != ESC )
	n = getch( ) ;
	fi.close( ) ;
	fi2.close( ) ;
}

void doctors_d( )
{
	cleardevice( ) ;

	char nm[ 6 ][ 50 ] = {
				"Display records of all doctors" ,
				"Add new doctor's record" ,
				"Display doctor's record" ,
				"Update doctor's information" ,
				"Delete doctor's record" ,
				"Clear data of all doctors"
			     } ;
	int ch ;

	while( 1 )
	{
	//Creates a file that stores last id of doctor if it doesn't exist
	ofstream dn( "dn.mih" , ios :: out | ios :: binary | ios :: noreplace ) ;
	if( dn )
	{
	dn << doc_no ;
	dn.close( ) ;
	}
	//Creates a file that stores no. of doctors if it doesn't exist
	ofstream d_no( "no.mih" , ios :: out | ios :: binary | ios :: noreplace ) ;
	if( d_no )
	{
	d_no << dno ;
	d_no.close( ) ;
	}
	// dn.mih & no.mih are nearly same but no.mih gets
	//decremented when a doctor record is deleted
	ch = page( 11 , 12 , 1 , 6 , "DOCTOR'S DATABASE" , 15 , 9 , 400 , nm ) ;

	if( !ch )
	{
		cleardevice( ) ;
		return ;
	}
	char o ;
	switch( ch )
	{
		case 1 :
			cleardevice( ) ;
			disp_all( ) ;
			break ;
		case 2 :
			cleardevice( ) ;
			createfile( ) ;
			break ;
		case 3 :
			cleardevice( ) ;
			displayfile( ) ;
			break ;
		case 4 :
			cleardevice( ) ;
			modifyfile( ) ;
			break ;
		case 5 :
			cleardevice( ) ;
			deletefile( ) ;
			break ;
		case 6 :
			cleardevice( ) ;
			setcolor( 15 ) ;
			gotoxy( 1 , 1 ) ;
			cout << "Do you want to clear all the data?\nIf you clear data of all doctors , data of patients associated with\nthem will also get cleared.( y/n )" ;
			o = getch( ) ;
			tolower( o ) ;
			while( o != 'y' && o != 'n' )
			{
				cleardevice( ) ;
				outtext( "Enter y or n :" ) ;
				o = getch( ) ;
			}
			if( o == 'n' )
			break ;
			else
			{
			patient p ;
			ifstream fi( "PATIENTS.mih" , ios :: in | ios ::binary ) ;
			fi.close( ) ;
			remove( "PATIENTS.mih" ) ;
			/*remove( "pid.mih" ) ;
			remove( "pno.mih" ) ;
			p_no = 0 ;
			pno = 0 ;  */
			ifstream check( "IPATIENTS.mih" , ios :: in | ios :: binary ) ;
			if( !check )
			{
			remove( "pid.mih" ) ;
			remove( "pno.mih" ) ;
			p_no = 0 ;
			pno = 0 ;
			}
			check.close( ) ;
			remove( "DOCTORS.mih" ) ;
			remove( "dn.mih" ) ;
			remove( "no.mih" ) ;
			dno = 0 ;
			doc_no = 0 ;
			cleardevice( ) ;
			}
			break ;
	}
	}
}

char *inputpass( int x , int y , int max )//Bcz graphics.h offers no func
{                                         //to input a string
	char str[ 30 ] ;// Pass entered by user
	char stars[ 30 ] ;
	moveto( x , y ) ;
	char n ;//To scan character by character and store in str
	int b = 0 ;// when b = 1 implies n = backspace
	int i = 0 ;// Keeps a track of the posn of the letter
	setcolor( 1 ) ;
	while( n != ENTER )
	{
		if( n == ESC )
		return "ESC" ;
		b = 0 ; //Bcz if '\b' was pressed before b would have
			// got the value 1
		n = getch( ) ;

		if( islower( n ) || isdigit( n ) ) // Store only lowercase al & num
		{
		str[ i ] = n ;
		stars[ i ] = '*' ;
		}
		else
		if( n == '\b' )
		{
			if( i == 0 )
			continue ;
			else
			{
				-- i ;
				b = 1 ;
			}
		}
		else
		continue ;

		if( i == max )
		{
			while( n != ENTER && n != '\b' )
			{
				sound( 520 ) ;
				delay( 5 ) ;
				nosound( ) ;
				n = getch( ) ;
				if( n == ESC )
				return "ESC" ;
			}

			if( n == ENTER )break ;
			else
			if( n == '\b' )
			{
				--i ;
				b = 1 ;
			}
		}
		if( !b )
		{
		str[ i + 1 ] = '\0' ;
		stars[ i + 1 ] = '\0' ;
		}
		else
		{
		str[ i ] = '\0' ;
		stars[ i ] = '\0' ;
		}
		floodfill( x + 1 , y + 1 , 15 ) ;
		outtextxy( x , y , stars ) ;
		if( !b )
		++ i ;
	}
	return str ;
}

char *setpass( char *opass , int max , int &c )
{
	cleardevice( ) ;
	int j = 0 ; //Keeps a track of the block in which user is
	setcolor( 15 ) ; //white
	settextstyle( 0 , 0 , 1 ) ;   // small letters
	outtextxy( midx - 50 , midy - 100, "Enter current password:" ) ;
	rectangle( midx - 50 , midy - 80, midx + 60 , midy - 55 ) ;
	outtextxy( midx - 50 , midy - 45, "Enter new password:" ) ;
	rectangle( midx - 50 , midy - 25, midx + 60 , midy ) ;
	outtextxy( midx - 50 , midy + 10, "Confirm new password:" ) ;
	rectangle( midx - 50 , midy + 30 , midx + 60 , midy + 55 ) ;
	rectangle( midx - 50 , midy + 65 , midx + 30 , midy + 95 ) ;
	setfillstyle( 1 , 8 ) ;
	floodfill( midx - 49 , midy - 79 , 15 ) ;
	floodfill( midx - 49 , midy - 24 , 15 ) ;
	floodfill( midx - 49 , midy + 31 , 15 ) ;
	setfillstyle( 1 , 2 ) ;   //green
	floodfill( midx - 49 , midy + 66 , 15 ) ;
	setcolor( 0 ) ;   //black
	settextstyle( 1 , 0 , 3 ) ; // large
	outtextxy( midx - 45 , midy + 70 , "DONE" ) ;
	settextstyle( 0 , 0 , 1 ) ; //small
	setcolor( 2 ) ; // green
	setfillstyle( 1 , 8 ) ; //grey
	outtextxy( 1 , midy + 150 , "1.Only lowercase alphabets & numbers are allowed " ) ;
	outtextxy( 1 , midy + 170 , "2.Max 12 characters " ) ;
	setcolor( 10 ) ; //
	outtextxy( 1 , midy - 200, "Press ESC to go back" ) ;

	char str[ 4 ][ 30 ] ;
	strcpy( str[ 3 ] , "DONE" ) ;
	int x[ 4 ] , y[ 4 ] ;
	x[ 0 ] = midx - 45 , y[ 0 ] = midy - 75 ;  //
	x[ 1 ] = midx - 45 , y[ 1 ] = midy - 20 ;  //coordinates of text
	x[ 2 ] = midx - 45 , y[ 2 ] = midy + 35 ;  //
	x[ 3 ] = midx - 45 , y[ 3 ] = midy + 70 ;  //
	char n ;//To scan character by character and store in str
	int b = 0 ;// when b = 1 implies n = backspace
	int i[ 3 ] = { 0 , 0 , 0 } ;// Keeps a track of the posn of the letter
	setcolor( 1 ) ;//blue
	int ch1 = 0 , ch2 = 0 ; // for checking the correctness of old pass
				// & comparing new and confirmed
	int chk[ 3 ] = { 0 , 0 , 0 } ;
	// Checks whether user has started typing in a particular block
	int d = 0 ;//if enter, down key or tab is pressed d = 1
	while( 1 )
	{
		if( j < 3 )
		{
			setfillstyle( 1 , 14 ) ;
			floodfill( x[ j ] , y[ j ] , 15 ) ;
			if( chk[ j ] )
			outtextxy( x[ j ] , y [ j ] , str[ j ] ) ;
		}
		d = 0 ;
		char cc;
	while( 1 )
	{
		n = getch( ) ;
		if( n == ESC )
		{
			cleardevice( ) ;
			return "ESC" ;
		}
		if( n == '\0' )
		{
			cc = getch( );
			if( cc == DOWN )
				n = '\t';
		}
		if( j == 3 ) // done block
		{
			if( n == ENTER )
			{
				if( !strcmp( str[ 0 ] , opass ) )
				ch1 = 1 ;
				if( !strcmp( str[ 1 ] , str[ 2 ] ) )
				ch2 = 1 ;
				setcolor( 3 ) ;
				if( ch1 && ch2 )
				{
					c = 1 ;
					return str[ 1 ] ;
				}
				else
				{
					if( !ch1 )
					{
						outtextxy( 150 , midy - 170, "Current password is not correct" ) ;
					}
					else
					if( !ch2 )
					{
						outtextxy( 150 , midy - 170, "The two passwords don't match." ) ;
					}
				}
				getch( ) ;
				return opass ;
			}
		}

		if( n == '\0' && cc == UP )
		{
			if( j == 3 )
			{
			setfillstyle( 1 , 2 ) ;
			setcolor( 0 ) ;
			settextstyle( 1 , 0 , 3 ) ;
			floodfill( x[ j ] + 1 , y[ j ] + 1 , 15 ) ;
			outtextxy( x[ j ] , y[ j ] , str[ j ] ) ;
			settextstyle( 0 , 0 , 1 ) ;
			setcolor( 1 ) ;
			setfillstyle( 1 , 8 ) ;
			}

			if( j < 3 )
			{
				setfillstyle( 1 , 8 ) ;
				floodfill( x[ j ] , y[ j ] , 15 ) ;
				if( chk[ j ] )
				outtextxy( x[ j ] , y [ j ] , str[ j ] ) ;
			}
			if( j == 0 )
			{
				j = 2 ;// j = 2 bcz it will get incremented
				setfillstyle( 1 , 14 ) ;// yellow
				settextstyle( 1 , 0 , 3 ) ;//big font
				floodfill( midx - 49 , midy + 66 , 15 ) ;
				outtextxy( midx - 45 , midy + 70 , "DONE" ) ;
				settextstyle( 0 , 0 , 1 ) ; // small font
				setfillstyle( 1 , 8 ) ; // grey
				break ;
			}
			else
			{
				j -= 2 ; // j- 2 as it gets incremented at the end
				break ;
			}
		}
		else
		if( ( n == '\0' && cc == DOWN ) || n == ENTER || n == '\t' )
		{

			d = 1 ;
			if( j == 3 )
			{
				setfillstyle( 1 , 2 ) ;
				setcolor( 0 ) ;
				settextstyle( 1 , 0 , 3 ) ;
				floodfill( x[ j ] + 1 , y[ j ] + 1 , 15 ) ;
				outtextxy( x[ j ] , y[ j ] , str[ j ] ) ;
				settextstyle( 0 , 0 , 1 ) ;
				setcolor( 1 ) ;
				setfillstyle( 1 , 8 ) ;
				j = -1 ;
				break ;
			}
			else
			if( j == 2 )
			{
				setfillstyle( 1 , 14 ) ;//yellow
				settextstyle( 1 , 0 , 3 ) ;//large
				setcolor( 0 ) ; //black
				floodfill( midx - 49 , midy + 66 , 15 ) ;
				outtextxy( midx - 45 , midy + 70 , "DONE" ) ;
				settextstyle( 0 , 0 , 1 ) ;// small
				setcolor( 1 ) ;//blue
				setfillstyle( 1 , 8 ) ;//grey
				break ;
			}
			else
				break ;
		}
		b = 0 ; //Bcz if '\b' was pressed before b would have
			// got the value 1
		if( ( isdigit( n ) || islower( n ) ) && i[ j ] != max && j != 3 ) // Store only al & num
		str[ j ][ i[ j ] ] = n ;
		else
		if( n == '\b' )
		{
			if( i[ j ] == 0 )
			continue ;
			else
			{
				-- i[ j ] ;
				b = 1 ;
			}
		}
		else
		if( i[ j ] == max )
		{
			if( ( isdigit( n ) || islower( n ) ) )
			{
			sound( 520 ) ;
			delay( 5 ) ;
			nosound( ) ;
			}
			continue ;
		}
		else
		continue ;

		if( !b )
		str[ j ][ i[ j ] + 1 ] = '\0' ;
		else
		str[ j ][ i[ j ] ] = '\0' ;
		if( j == 3 )
		{
			setfillstyle( 1 , 2 ) ;
			setcolor( 0 ) ;
			settextstyle( 1 , 0 , 3 ) ;
			floodfill( x[ j ] + 1 , y[ j ] + 1 , 15 ) ;
			outtextxy( x[ j ] , y[ j ] , str[ j ] ) ;
			settextstyle( 0 , 0 , 1 ) ;
			setcolor( 1 ) ;
			setfillstyle( 1 , 8 ) ;
		}
		else
		{
			floodfill( x[ j ] + 1 , y[ j ] + 1 , 15 ) ;
			outtextxy( x[ j ] , y[ j ] , str[ j ] ) ;
			chk[ j ] = 1 ;
		}
		if( !b )
		++ i[ j ] ;
	}
	if( j < 3 && d )
	{
		setfillstyle( 1 , 8 ) ;
		floodfill( x[ j ] , y[ j ] , 15 ) ;
		if( chk[ j ] )
		outtextxy( x[ j ] , y [ j ] , str[ j ] ) ;
	}

	++ j ;

	}

}

int login( int max )// returns doc id on success and 0 if it fails
{
	cleardevice( ) ;
	ifstream fi( "DOCTORS.mih" , ios :: in | ios :: binary ) ;
	doctor d1 ;
	char stars[ 30 ] ;
	int j = 0 ; //Keeps a track of the block in which user is
	setcolor( 15 ) ; //white
	settextstyle( 0 , 0 , 1 ) ;   // small letters
	outtextxy( midx - 50 , midy - 45, "Enter id:" ) ;
	rectangle( midx - 50 , midy - 25, midx + 60 , midy ) ;
	outtextxy( midx - 50 , midy + 10, "Enter password:" ) ;
	rectangle( midx - 50 , midy + 30 , midx + 60 , midy + 55 ) ;
	rectangle( midx - 50 , midy + 65 , midx + 30 , midy + 95 ) ;
	setfillstyle( 1 , 8 ) ;
	floodfill( midx - 49 , midy - 24 , 15 ) ;
	floodfill( midx - 49 , midy + 31 , 15 ) ;
	setfillstyle( 1 , 2 ) ;   //green
	floodfill( midx - 49 , midy + 66 , 15 ) ;
	setcolor( 0 ) ;   //black
	settextstyle( 1 , 0 , 3 ) ; // large
	outtextxy( midx - 45 , midy + 70 , "DONE" ) ;
	settextstyle( 0 , 0 , 1 ) ; //small
	setcolor( 2 ) ; // green
	setfillstyle( 1 , 8 ) ; //grey
	outtextxy( 1 , midy + 150 , "1.Only lowercase alphabets & numbers are allowed " ) ;
	outtextxy( 1 , midy + 170 , "2.Max 12 characters " ) ;
	setcolor( 5 ) ; //
	outtextxy( 1 , midy + 200, "Press ESC to go back" ) ;
	setcolor( 2 ) ;
	outtextxy( 1 , midy - 200, "Default password: doctor" ) ;

	char str[ 3 ][ 30 ] ;// 1st str = id_str
				///2nd str = pass
				//3rd str = "DONE"
	int id ;//for doc id
		//doc id is 1st inputted in a string and then by using
		//atoi is converted into int

	strcpy( str[ 2 ] , "DONE" ) ;
	int x[ 3 ] , y[ 3 ] ;
	x[ 0 ] = midx - 45 , y[ 0 ] = midy - 20 ;  //coordinates of text
	x[ 1 ] = midx - 45 , y[ 1 ] = midy + 35 ;  //
	x[ 2 ] = midx - 45 , y[ 2 ] = midy + 70 ;  //
	char n ;//To scan character by character and store in str
	int b = 0 ;// when b = 1 implies n = backspace
	int i[ 2 ] = { 0 , 0 } ;// Keeps a track of the posn of the letter
	setcolor( 1 ) ;//blue
	int ch1 = 0 , ch2 = 0 ; // for checking the correctness of old pass
				// & comparing new and confirmed
	int chk[ 2 ] = { 0 , 0 } ;
	// Checks whether user has started typing in a particular block
	int d = 0 ;//if enter, down key or tab is pressed d = 1
	char c;
	while( 1 )
	{
		if( j < 2 ) //fills current block with yellow color
		{
			setfillstyle( 1 , 14 ) ;
			floodfill( x[ j ] , y[ j ] , 15 ) ;
			if( chk[ j ] ) // if str contains sth chk = 1
			{
			if( j == 1 )
			{
			for( int v = 0 ; v < strlen( str[ j ] ) ; ++ v )
			stars[ v ] = '*' ;
			stars[ v ] = '\0' ;
			outtextxy( x[ j ] , y[ j ] , stars ) ;
			}
			else
			outtextxy( x[ j ] , y [ j ] , str[ j ] ) ;
			}
		}
		d = 0 ;
	while( 1 )
	{
		n = getch( ) ;
		if( n == ESC )
		{
			cleardevice( ) ;
			return -1 ;
		}
		if( n == '\0' )
		{
			c = getch( );
			if( c == DOWN )
				n = '\t';
		}
		if( j == 2 ) // done block
		{
			if( n == ENTER )
			{
				setcolor( 3 ) ;
				id = atoi( str[ 0 ] ) ;
				while( fi.read( ( char * )&d1 , sizeof( d1 ) ) )
				{
					if( id == d1.getdoc_id( ) )
					{
						ch1 = 1 ;
						break ;
					}
				}
				if( !ch1 )
				{
					outtextxy( 150 , midy - 170, "Incorrect id!" ) ;
					getch( ) ;
					fi.close( ) ;
					return 0 ;
				}
				for( int v = 0 ; v < 2 ; ++ v )
				{
					if( chk[ v ] == 0 )
					{
					outtextxy( 150 , midy - 170, "Incorrect id!" ) ;
					getch( ) ;
					fi.close( ) ;
					return 0 ;
					}
				}

				if( !strcmp( str[ 1 ] , d1.getpassword( ) ) )
				ch2 = 1 ;
				setcolor( 3 ) ;
				if( ch1 && ch2 )
				{
					fi.close( ) ;
					return id ;
				}
				else
				{
					if( !ch2 )
					{
						outtextxy( 150 , midy - 170, "Incorrect password!" ) ;
						fi.close( ) ;
						getch( ) ;
						return 0 ;
					}
				}
			}
		}

		if( n == '\0' && c == UP )
		{
			if( j == 2 ) //To restore done block to its previous color
			{
			setfillstyle( 1 , 2 ) ;
			setcolor( 0 ) ;
			settextstyle( 1 , 0 , 3 ) ;
			floodfill( x[ j ] + 1 , y[ j ] + 1 , 15 ) ;
			outtextxy( x[ j ] , y[ j ] , str[ j ] ) ;
			settextstyle( 0 , 0 , 1 ) ;
			setcolor( 1 ) ;
			setfillstyle( 1 , 8 ) ;
			}

			if( j < 2 )//as the user is changing the block
				   // it turns grey
			{
				setfillstyle( 1 , 8 ) ;
				floodfill( x[ j ] , y[ j ] , 15 ) ;
				if( chk[ j ] )
				{
				if( j == 1 )
				{
					for( int v = 0 ; v < strlen( str[ j ] ) ; ++ v )
					stars[ v ] = '*' ;
					stars[ v ] = '\0' ;
					outtextxy( x[ j ] , y[ j ] , stars ) ;
				}
				else
				{
				outtextxy( x[ j ] , y [ j ] , str[ j ] ) ;
				}
				}
			}
			if( j == 0 )//highlights done block
			{
				j = 1 ;// j = 1 bcz it will get incremented
				setfillstyle( 1 , 14 ) ;// yellow
				settextstyle( 1 , 0 , 3 ) ;//big font
				floodfill( x[ 2 ] , y[ 2 ] , 15 ) ;
				outtextxy( x[ 2 ] , y[ 2 ] , "DONE" ) ;
				settextstyle( 0 , 0 , 1 ) ; // small font
				setfillstyle( 1 , 8 ) ; // grey
				break ;
			}
			else
			{
				j -= 2 ; // j - 2 as it gets incremented at the end
				break ;
			}
		}
		else
		if( ( n == '\0' && c == DOWN ) || n == ENTER || n == '\t' )
		{

			d = 1 ;
			if( j == 2 )
			{
				setfillstyle( 1 , 2 ) ;
				setcolor( 0 ) ;
				settextstyle( 1 , 0 , 3 ) ;
				floodfill( x[ j ] + 1 , y[ j ] + 1 , 15 ) ;
				outtextxy( x[ j ] , y[ j ] , str[ j ] ) ;
				settextstyle( 0 , 0 , 1 ) ;
				setcolor( 1 ) ;
				setfillstyle( 1 , 8 ) ;
				j = -1 ;
				break ;
			}
			else
			if( j == 1 )
			{
				setfillstyle( 1 , 14 ) ;//yellow
				settextstyle( 1 , 0 , 3 ) ;//large
				setcolor( 0 ) ; //black
				floodfill( x[ 2 ] , y[ 2 ] , 15 ) ;
				outtextxy( x[ 2 ] , y[ 2 ] , "DONE" ) ;
				settextstyle( 0 , 0 , 1 ) ;// small
				setcolor( 1 ) ;//blue
				setfillstyle( 1 , 8 ) ;//grey
				break ;
			}
			else
				break ;
		}
		b = 0 ; //Bcz if '\b' was pressed before b would have
			// got the value 1
		if( j != 2 && ( ( j == 1 ) ? ( isdigit( n ) || islower( n ) ) : ( isdigit( n ) )) && i[ j ] != max ) // Store only al & num
		str[ j ][ i[ j ] ] = n ;//if not done block and if j=1 letters and digits else i.e. j=0 only digits and i!=max
		else
		if( n == '\b' )
		{
			if( i[ j ] == 0 )
			continue ;
			else
			{
				-- i[ j ] ;
				b = 1 ;
			}
		}
		else
		if( i[ j ] == max )
		{
			if( ( ( j == 1 ) ? ( isdigit( n ) || islower( n ) ) : ( isdigit( n ) ) ) )
			{
			sound( 520 ) ;
			delay( 5 ) ;  // only gives sound when the desired
			nosound( ) ;  //charater is entered
			}
			continue ;
		}
		else
		continue ;

		if( !b )
		str[ j ][ i[ j ] + 1 ] = '\0' ;
		else
		str[ j ][ i[ j ] ] = '\0' ;
		if( j == 2 )
		{
			setfillstyle( 1 , 2 ) ;
			setcolor( 0 ) ;
			settextstyle( 1 , 0 , 3 ) ;
			floodfill( x[ j ] + 1 , y[ j ] + 1 , 15 ) ;
			outtextxy( x[ j ] , y[ j ] , str[ j ] ) ;
			settextstyle( 0 , 0 , 1 ) ;
			setcolor( 1 ) ;
			setfillstyle( 1 , 8 ) ;
		}
		else
		{
			floodfill( x[ j ] + 1 , y[ j ] + 1 , 15 ) ;
			if( j == 1 )
			{
				for( int v = 0 ; v < strlen( str[ j ] ) ; ++ v )
				stars[ v ] = '*' ;
				stars[ v ] = '\0' ;
				outtextxy( x[ j ] , y[ j ] , stars ) ;
			}
			else
			{
				outtextxy( x[ j ] , y[ j ] , str[ j ] ) ;
			}
			chk[ j ] = 1 ;
		}
		if( !b )
		++ i[ j ] ;
	}
	if( j < 2 && d )
	{
		setfillstyle( 1 , 8 ) ;//Turns the block back to grey
		floodfill( x[ j ] , y[ j ] , 15 ) ;
		if( chk[ j ] )
		{
		if( j == 1 )
		{
			for( int v = 0 ; v < strlen( str[ j ] ) ; ++ v )
			stars[ v ] = '*' ;
			stars[ v ] = '\0' ;
			outtextxy( x[ j ] , y[ j ] , stars ) ;
		}
		else
		{
			outtextxy( x[ j ] , y [ j ] , str[ j ] ) ;
		}
		}
	}

	++ j ;

	}

}

void createfile( )
{
	ofstream fo( "DOCTORS.mih" , ios :: app | ios :: binary ) ;
	ifstream fi( "DOCTORS.mih" , ios :: in | ios :: binary ) ;
	if( !fi )
	{
		cout << "No records in the database!" ;
		getch( ) ;
		cleardevice( ) ;
		return ;
	}
	ifstream dn2( "dn.mih" , ios :: in | ios :: binary ) ;
	// To get doc id
	if( !dn2 )
	{
		gotoxy( 1 , 1 ) ;
		cout << "An error occured while opening the file dn.mih!" ;
		getch( ) ;
		cleardevice( ) ;
		closegraph( ) ;
		restorecrtmode( ) ;
		exit( 0 ) ;
	}
	dn2 >> doc_no ;
	dn2.close( ) ;
	ifstream no2 ;  //To get no of doc
	no2.open( "no.mih" , ios :: in | ios :: binary ) ;
	if( !no2 )
	{
		gotoxy( 1 , 1 ) ;
		cout << "An error occured while opening the file no.mih!" ;
		getch( ) ;
		cleardevice( ) ;
		closegraph( ) ;
		restorecrtmode( ) ;
		exit( 0 ) ;
	}
	no2 >> dno ;
	no2.close( ) ;
	doctor d , d1 ;
	ofstream dn , no ; //To write new values of doc_no and dno in them
	char n ;
	dn.open( "dn.mih" , ios :: out | ios :: binary ) ;
	no.open( "no.mih" , ios :: out | ios :: binary ) ;
	gotoxy( 1 , 1 ) ;
	++ doc_no ;
	++ dno ;
	d.d_id( doc_no ) ;
	d.getdata( ) ;
	d.d_id( doc_no ) ;
	d.d_pass( "doctor" ) ;
	d.l = 0 ;
	for( int i = 0 ; i < 5 ; ++ i )
	d.assign_cn( i , 0 ) ;
	d.fdoa = 0 ;
	fo.write( ( char * )&d , sizeof( d ) ) ;
	dn << doc_no ;
	no << dno ;
	fo.close( ) ;
	fi.close( ) ;
	dn.close( ) ;
	no.close( ) ;
	cout << "Press any key to go back." ;
	getch( ) ;
	cleardevice( ) ;
}

void displayfile( )
{
	int id ;
	gotoxy( 1 , 1 ) ;
	ifstream fi ;
	fi.open( "DOCTORS.mih" , ios :: app | ios :: binary ) ;

	if( !fi )
	{
		cout << "No records in the database!" ;
		cleardevice( ) ;
		return ;
	}
	cout << "Enter doctor id:\n" ;
	cin >> id ;
	doctor d ;
	int f = 0 ;
	while( fi.read( ( char * )&d , sizeof( d ) ) )
	{
		if( id == d.getdoc_id( ) )
		{
			cleardevice( ) ;
			gotoxy( 1 , 1 ) ;
			d.putdata( ) ;
			f = 1 ;
		}
	}
	if( !f )
	cout << "The record doesn't exist!" ;
	fi.close( ) ;

	cout << "\nPress any key to go back." ;
	getch( ) ;
}

void modifyfile( )
{
	int id ;
	gotoxy( 1 , 1 ) ;
	int chk = 0 ;
	char temp[ 30 ] ;
	cout << "Enter id of the doctor whose details are to be modified:\n" ;
	do
	{
	if( chk )
	cout << "Enter a valid id:\t" ;
	gets( temp ) ;
	chk = onlynum( temp ) ;

	}while( chk ) ;
	id = atoi( temp ) ;
	fstream f1 ;
	f1.open( "DOCTORS.mih" , ios :: in | ios :: out | ios :: binary ) ;


	if( !f1 )
	{
		cout << "No records in the database!" ;
		getch( ) ;
		cleardevice( ) ;
		return ;
	}
	doctor d ;
	int t = 0 , rec = 0 ;
	while( f1.read( ( char * )&d , sizeof( d ) ) )
	{
		++ rec ;

		if( id == d.getdoc_id( ) )
		{
			d.modify( ) ;
			f1.seekp( sizeof( d ) * ( rec - 1 ) , ios :: beg ) ;
			f1.write( ( char * )&d , sizeof( d ) ) ;
			t = 1 ;
			break ;
		}
	}
	f1.close( ) ;
	if( !t )
	cout << "\nRecord doesn't exist.\n" ;
	else
	cout << "\nModification successful.\n" ;
	getch( ) ;
}

void deletefile( )
{
	ifstream fi ;
	ofstream fo ;
	ifstream no2 ;
	gotoxy( 1 , 1 ) ;
	no2.open( "no.mih" , ios :: in | ios :: binary ) ;
	no2 >> dno ;
	no2.close( ) ;
	ofstream no ;
	doctor d ;
	char n ;
	int f , id ;
	fi.open( "DOCTORS.mih" , ios :: in | ios :: binary ) ;
	if( !fi )
	{
		cout << "No records in the database!" ;
		getch( ) ;
		cleardevice( ) ;
		return ;
	}
	fo.open( "copy.mih" , ios :: out | ios :: binary ) ;
	cout << "Enter id of record to be deleted:\n" ;
	cin >> id ;
	f = 0 ;// flag
	while( fi.read( ( char * )&d , sizeof( d ) ) )
	{
		if( id == d.getdoc_id( ) )
		{
			f = 1 ;
			break ;
		}
		else
		fo.write( ( char * )&d , sizeof( d ) ) ;
	}
	if( !f ) // if the record is not there
	{
		cout << "Record not present.\n" ;
		fi.close( ) ;
		fo.close( ) ;
		remove( "copy.mih" ) ;
	}
	else
	{
	int i , yes = 0 ;
	for( i = 0 ; i < 5 ; ++ i )
	{
		if( d.getcn( i ) > 0 )
		{
			yes = 1 ;
			break ;
		}
	}
	if( yes == 1 )
	{
		char ch ;
		cout << "Patients have appointment with the doctor.\n"
		     << "To delete doctor's record either assign all his patients to other doctors\n( feature available in update patients record ) or "
		     << "cancel all\nhis appointments( By deleting records of his patients ) \nDo you want to delete records of all patients associated with the doctor?( y/n )" ;
		do
		{
		ch = getch( ) ;
		ch = tolower( ch ) ;
		}while( ch != 'y' && ch != 'n' ) ;
		if( ch == 'n' )
			fo.write( ( char * )&d , sizeof( d ) ) ;
		else
		{
			patient p ;
			ifstream fi( "PATIENTS.mih" , ios :: in | ios ::binary ) ;
			ofstream fo( "COPY3.mih" , ios :: out | ios :: binary ) ;
			int f = 0 ;
			while( fi.read( ( char * )&p , sizeof( p ) ) )
			{
				if( p.getcdid( ) != id )
				{
					fo.write( ( char * )&p , sizeof( p ) ) ;
					++ f ;
				}
			}
			fi.close( ) ;
			fo.close( ) ;
			remove( "PATIENTS.mih" ) ;
			if( !f )
			{
				remove( "COPY3.mih" ) ;
				remove( "pid.mih" ) ;
				remove( "pno.mih" ) ;
				p_no = 0 ;
				pno = 0 ;
			}
			else
			{
				rename( "COPY3.mih" , "PATIENTS.mih" ) ;
				ofstream fo2 ;
				//fo1.open( "pid.mih" , ios :: out | ios :: binary ) ;
				fo2.open( "pno.mih" , ios :: out | ios :: binary ) ;
				//fo1 << last_id ;
				fo2 << f ;
				//fo1.close( ) ;
				pno = f ;
				fo2.close( ) ;
			}
			no.open( "no.mih" , ios :: out | ios :: binary ) ;
			-- dno ;
			no << dno ;
			no.close( ) ;
		}
	}
	else
	{
	no.open( "no.mih" , ios :: out | ios :: binary ) ;
	-- dno ;
	no << dno ;
	no.close( ) ;
	}
	while( fi.read( ( char * )&d , sizeof( d ) ) )
	fo.write( ( char * )&d , sizeof( d ) ) ;

	fi.close( ) ;
	fo.close( ) ;

	remove( "DOCTORS.mih" ) ;
	rename( "copy.mih" , "DOCTORS.mih" ) ;
	if( !yes )
	cout << "Record deleted.\n" ;
	}
}

void disp_all( )
{
	ifstream fi ;
	fi.open( "DOCTORS.mih" , ios :: in | ios :: binary ) ;

	int x , y ;
	char n ;
	doctor d ;
	int nrec ;
	nrec = ( fsizeof( "DOCTORS.mih" ) / sizeof( d ) ) ;
	//no. of records in file
	int rec = 1 , lt = ( nrec + 1 ) - 22 ;
	// rec gives the number of times u have pressed down arrow
	// lt gives is the no. of times you can scroll in one go


	setfillstyle( 1 , 0 ) ;
	do
	{
	cleardevice( ) ;
	x = 1 , y = 2 ;
	gotoxy( x , y ) ;
	cout << "ID" ;
	x = 10 ;
	gotoxy( x , y ) ;
	cout << "NAME" ;
	x = 50 ;
	gotoxy( x , y ) ;
	cout << "SPECIALIZATION" ;
	x = 70 ;
	gotoxy( x , y ) ;
	cout << "EXPERIENCE" ;
	y = 4 ;
	setcolor( 15 ) ;
	line( 0 , 32 , getmaxx( ) , 32 ) ;
	gotoxy( 1 , 1 ) ;
	cout << "Press ESC to go back & arrows for scrolling." ;
	y = 4 ;
	fi.seekg( sizeof( d ) * ( rec - 1 ) , ios :: beg ) ;
	while( fi.read( ( char * )&d , sizeof( d ) ) )
	{
		x = 1 ;
		gotoxy( x , y ) ;
		cout << d.getdoc_id( ) ;
		x = 10 ;
		gotoxy( x , y ) ;
		cout << d.getname( ) ;
		x = 50 ;
		gotoxy( x , y ) ;
		cout << d.getspec( ) ;
		x = 70 ;
		gotoxy( x , y ) ;
		cout << d.getexp( ) ;
		++ y ;
		if( y == 26 )//max y
		break ;
	}

	char c;
	n = getch( ) ;
	if( n == '\0' )
	c = getch( );
	if( nrec > 22 )
	{
		if( c == UP )
		{
			if( rec == 1 )
			{
			continue ;
			}
			else
			-- rec ;
			continue ;
		}
		else
		if( c == DOWN )
		{
			if( ( rec + 1 ) <= lt )
			++ rec ;
			continue ;
		}
		else
		if( n == ESC )
		{
			fi.close( ) ;
			return ;
		}
	}
	else
	{
		while( n != ESC )
		n = getch( ) ;
		fi.close( ) ;
		return ;
	}

	}while( 1 ) ;
}

int fsizeof( char *file )
{
	ifstream fi( file , ios :: ate | ios :: binary ) ;
	int epos = fi.tellg( ) ;
	fi.close( ) ;
	return ( epos ) ;
}
void createfile_p( )
{
	gotoxy( 1 , 1 ) ;
	ofstream fo( "PATIENTS.mih" , ios :: app | ios :: binary ) ;
	ofstream fo2( "IPATIENTS.mih" , ios :: app | ios :: binary ) ;
	ifstream pid( "pid.mih" , ios :: in | ios :: binary ) ;
	pid >> p_no ;
	pid.close( ) ;
	ifstream Pno ;  //To get no of patients
	Pno.open( "pno.mih" , ios :: in | ios :: binary ) ;
	Pno >> pno ;
	Pno.close( ) ;
	ofstream Pid , PNo ; //To write new values of p_no and pno in them
	patient p ;
	char n ;
	int o ;
	Pid.open( "pid.mih" , ios :: out | ios :: binary ) ;
	PNo.open( "pno.mih" , ios :: out | ios :: binary ) ;
	o = p.getdata( p_no + 1 ) ;
	if( o == 1 )
	{
	++ p_no ;
	++ pno ;
	p.pat_id( p_no ) ;
	if( p.getp_type( ) == 2 )
	fo.write( ( char * )&p , sizeof( p ) ) ;
	else
	fo2.write( ( char * )&p , sizeof( p ) ) ;
	}
	Pid << p_no ;
	PNo << pno ;
	fo.close( ) ;
	fo2.close( ) ;
	Pid.close( ) ;
	PNo.close( ) ;
	cout << "Press any key to go back." ;
	getch( ) ;
	cleardevice( ) ;
}

void displayfile_p( )
{
	gotoxy( 1 , 1 ) ;
	int id ;
	ifstream fi( "PATIENTS.mih" , ios :: in | ios :: binary ) ;
	ifstream fi2( "IPATIENTS.mih" , ios :: in | ios :: binary ) ;

	if( !fi && !fi2 )
	{
		cout << "No records in the database!" ;
		getch( ) ;
		cleardevice( ) ;
		return ;
	}
	cout << "Enter patient id:\n" ;
	char temp[ 30 ] ;
	int chk = 0 ;
	do
	{
	if( chk )
	cout << "Enter a valid no.:\t" ;
	gets( temp ) ;
	chk = onlynum( temp ) ;

	}while( chk ) ;
	id = atoi( temp ) ;
	patient p ;
	int f = 0 ;
	while( fi.read( ( char * )&p , sizeof( p ) ) )
	{
		if( id == p.getp_id( ) )
		{
			cleardevice( ) ;
			p.putdata( ) ;
			f = 1 ;
			break ;
		}
	}
	if( !f )
	{
	while( fi2.read( ( char * )&p , sizeof( p ) ) )
	{
		if( id == p.getp_id( ) )
		{
			cleardevice( ) ;
			p.putdata( ) ;
			f = 1 ;
			break ;
		}
	}
	}
	if( !f )
	cout << "\nThe record doesn't exist!" ;
	fi.close( ) ;
	fi2.close( ) ;
	cout << "\nPress any key to go back." ;
	getch( ) ;
}

void modifyfile_p( )
{
	gotoxy( 1 , 1 ) ;
	int id ;

	cout << "Enter id of the patient whose details are to be modified:\n" ;
	cin >> id ;
	fstream f1( "PATIENTS.mih" , ios :: in | ios :: out | ios :: binary ) ;
	fstream f2( "IPATIENTS.mih" , ios :: in | ios :: out | ios :: binary ) ;

	if( !f1 && !f2 )
	{
		cout << "No records in the database!" ;
		getch( ) ;
		cleardevice( ) ;
		return ;
	}
	patient p ;
	int t = 0 , rec = 0 ;
	while( f1.read( ( char * )&p , sizeof( p ) ) )
	{
		++ rec ;

		if( id == p.getp_id( ) )
		{
			p.modify( ) ;
			f1.seekp( sizeof( p ) * ( rec - 1 ) , ios :: beg ) ;
			f1.write( ( char * )&p , sizeof( p ) ) ;
			t = 1 ;
			break ;
		}
	}
	rec = 0 ;
	if( !t )
	{
	while( f2.read( ( char * )&p , sizeof( p ) ) )
	{
		++ rec ;

		if( id == p.getp_id( ) )
		{
			p.modify( ) ;
			f2.seekp( sizeof( p ) * ( rec - 1 ) , ios :: beg ) ;
			f2.write( ( char * )&p , sizeof( p ) ) ;
			t = 1 ;
			break ;
		}
	}
	}
	f1.close( ) ;
	f2.close( ) ;
	if( !t )
	cout << "\nRecord doesn't exist.\n" ;
	else
	cout << "\nModification successful.\n" ;
	getch( ) ;
}

void deletefile_p( int ID )
{
	ifstream fi , fi2 ;
	fstream dfi , wd ;
	ofstream fo , fo2 ;
	ifstream Pno ;
	gotoxy( 1 , 1 ) ;
	Pno.open( "pno.mih" , ios :: in | ios :: binary ) ;
	Pno >> pno ;
	Pno.close( ) ;
	ofstream PNo ;
	patient p ;
	doctor d ;
	int f , id , did , flag , wrd , typ ;
	char n ;
	if( ID )
	id = ID ;
	fi.open( "PATIENTS.mih" , ios :: in | ios :: binary ) ;
	fi2.open( "IPATIENTS.mih" , ios :: in | ios :: binary ) ;
	if( !fi && !fi2 )
	{
		cout << "No records in the database!" ;
		getch( ) ;
		cleardevice( ) ;
		return ;
	}
	fo.open( "copy.mih" , ios :: out | ios :: binary ) ;
	fo2.open( "copy2.mih" , ios :: out | ios :: binary ) ;
	if( !ID )
	{
	cout << "Enter id of record to be deleted:\n" ;
	cin >> id ;
	}
	f = 0 ;// flag
	while( fi.read( ( char * )&p , sizeof( p ) ) )
	{
		if( id == p.getp_id( ) )
		{
			f = 1 ;
			did = p.getcdid( ) ;
			break ;
		}
		else
		fo.write( ( char * )&p , sizeof( p ) ) ;
	}
	flag = 0 ;
	if( !f )
	{
	while( fi2.read( ( char * )&p , sizeof( p ) ) )
	{
		if( id == p.getp_id( ) )
		{
			flag = 1 ;
			wrd = p.getward( ) ;
			typ = p.getwardtype( ) ;
			break ;
		}
		else
		fo2.write( ( char * )&p , sizeof( p ) ) ;
	}
	}
	if( !f && !flag ) // if the record is not there
	{
		cout << "Record not present.\n" ;
		fi2.close( ) ;
		fo2.close( ) ;
		fi.close( ) ;
		fo.close( ) ;
	}
	else
	{
	PNo.open( "pno.mih" , ios :: out | ios :: binary ) ;
	-- pno ;
	PNo << pno ;
	PNo.close( ) ;
	if( !ID && f == 1 )
	{
	int cnt = 0 ;
	dfi.open( "DOCTORS.mih" , ios :: in | ios :: out | ios :: binary ) ;
	while( dfi.read( ( char * )&d , sizeof( d ) ) )
	{
		++ cnt ;
		if( did == d.getdoc_id( ) )
		{
			break ;
		}
	}
	int h , g , gmax , u ;

	for( h = 0 ; h <= 4 ; ++ h )
	{
		gmax = d.getcn( h ) ;//No of patients that day
		for( g = 0 ; g < gmax ; ++ g )
		{
			if( d.getapid( h , g ) == p.getp_id( ) )
			{
				for( u = g ; u < ( gmax - 1 ) ; ++ u )
				d.assign_apid( h , u , d.getapid( h , u + 1 ) ) ;
				d.s_cn( h ) ;//Deletion
				h = d.l ;//to come out of loop
				break ;
			}
		}
	}
	dfi.seekp( sizeof( d ) * ( cnt - 1 ) , ios :: beg ) ;
	dfi.write( ( char * )&d , sizeof( d ) ) ;
	dfi.close( ) ;
	}
	if( !ID && flag == 1 )
	{
		wd.open( "WARD.mih" , ios :: in | ios :: out | ios :: binary ) ;
		ward w ;
		wd.seekg( sizeof( w ) * ( wrd ) , ios :: beg ) ;
		int g , gmax , u ;
		wd.read( ( char * )&w , sizeof( w ) ) ;
		gmax = w.getno( typ ) ;//No of patients
		for( g = 0 ; g < gmax ; ++ g )
		{
			if( w.getpat_no( typ , g ) == p.getp_id( ) )
			{
				for( u = g ; u < ( gmax - 1 ) ; ++ u )
				w.assign_pat_no( typ , u , w.getpat_no( typ , u + 1 ) ) ;
				w.s_no( typ ) ;//Deletion
				break ;
			}
		}
		wd.seekp( sizeof( w ) * ( wrd ) , ios :: beg ) ;
		wd.write( ( char * )&w , sizeof( w ) ) ;
		wd.close( ) ;
	}
	if( f == 1 )
	{
	while( fi.read( ( char * )&p , sizeof( p ) ) )
	fo.write( ( char * )&p , sizeof( p ) ) ;
	}
	else
	if( flag == 1 )
	{
	while( fi2.read( ( char * )&p , sizeof( p ) ) )
	fo2.write( ( char * )&p , sizeof( p ) ) ;
	}
	fi.close( ) ;
	fi2.close( ) ;
	fo2.close( ) ;
	fo.close( ) ;

	if( f == 1 )
	{
	remove( "PATIENTS.mih" ) ;
	rename( "copy.mih" , "PATIENTS.mih" ) ;
	remove( "copy2.mih" ) ;
	}
	else
	if( flag == 1 )
	{
	remove( "IPATIENTS.mih" ) ;
	rename( "copy2.mih" , "IPATIENTS.mih" ) ;
	remove( "copy.mih" ) ;
	}
	if( !ID )
	cout << "Record deleted.\n" ;
	}
}

void disp_all_p( )
{
	gotoxy( 1 , 1 ) ;
	ifstream fi( "PATIENTS.mih" , ios :: in | ios :: binary ) ;
	int x , y ;
	char n ;
	patient p ;
	int nrec = ( fsizeof( "PATIENTS.mih" ) / sizeof( p ) ) ;
	//no. of records in file
	int rec = 1 , lt = ( nrec + 1 ) - 22 ;
	// rec gives the number of times u have pressed down arrow
	// lt gives is the no. of times you can scroll in one go
	do
	{

	x = 1 , y = 2 ;
	gotoxy( x , y ) ;
	cout << "ID" ;
	x = 5 ;
	gotoxy( x , y ) ;
	cout << "NAME" ;
	x =  50;
	gotoxy( x , y ) ;
	cout << "CONSULTING DOC id" ;
	y = 4 ;
	gotoxy( 1 , 3 ) ;
	setcolor( 15 ) ;
	line( 0 , 32 , getmaxx( ) , 32 ) ;
	gotoxy( 1 , 1 ) ;
	Date d1 ;
	cout << "Press ESC to go back & arrows for scrolling." ;
	fi.seekg( sizeof( p ) * ( rec - 1 ) , ios :: beg ) ;
	while( fi.read( ( char * )&p , sizeof( p ) ) )
	{
		x = 1 ;
		gotoxy( x , y ) ;
		cout << p.getp_id( ) ;
		x = 5 ;
		gotoxy( x , y ) ;
		puts( p.getname( ) ) ;
		x = 50 ;
		gotoxy( x , y ) ;
		cout << p.getcdid( ) ;
		++ y ;
		if( y == 26 )//max y
		break ;
	}
	char c;
	n = getch( ) ;
	if( n == '\0' )
	c = getch( );
	if( nrec > 22 )
	{
		if( c == UP )
		{
			if( rec == 1 )
			continue ;
			else
			-- rec ;
			continue ;
		}
		else
		if( c == DOWN )
		{
			if( ( rec + 1 ) <= lt )
			++ rec ;
			continue ;
		}
		else
		if( n == ESC )
		{
			fi.close( ) ;
			return ;
		}
	}
	else
	{
		while( n != ESC )
		n = getch( ) ;
		fi.close( ) ;
		return ;
	}

	}while( 1 ) ;
}

void disp_all_ip( )
{
	gotoxy( 1 , 1 ) ;
	ifstream fi( "IPATIENTS.mih" , ios :: in | ios :: binary ) ;
	int x , y ;
	char n ;
	patient p ;
	int nrec = ( fsizeof( "IPATIENTS.mih" ) / sizeof( p ) ) ;
	//no. of records in file
	int rec = 1 , lt = ( nrec + 1 ) - 22 ;
	// rec gives the number of times u have pressed down arrow
	// lt gives is the no. of times you can scroll in one go
	do
	{

	x = 1 , y = 2 ;
	gotoxy( x , y ) ;
	cout << "ID" ;
	x = 5 ;
	gotoxy( x , y ) ;
	cout << "Name" ;
	x =  35;
	gotoxy( x , y ) ;
	cout << "AdmitDate" ;
	x = 52 ;
	gotoxy( x , y ) ;
	cout << "DischargeDate" ;
	y = 4 ;
	gotoxy( 1 , 3 ) ;
	setcolor( 15 ) ;
	line( 0 , 32 , getmaxx( ) , 32 ) ;
	gotoxy( 1 , 1 ) ;
	Date d1 ;
	cout << "Press ESC to go back & arrows for scrolling." ;
	fi.seekg( sizeof( p ) * ( rec - 1 ) , ios :: beg ) ;
	while( fi.read( ( char * )&p , sizeof( p ) ) )
	{
		x = 1 ;
		gotoxy( x , y ) ;
		cout << p.getp_id( ) ;
		x = 5 ;
		gotoxy( x , y ) ;
		cout << p.getname( ) ;
		x = 35 ;
		gotoxy( x , y ) ;
		char dat[ 30 ] ;
		char str[ 30 ] ;
		time_t t ;
		t = p.getad( ) ;
		strcpy( dat , convert( t ) ) ;
		puts( dat ) ;
		x = 52 ;
		gotoxy( x , y ) ;
		if( p.done == 1 )
		{
		char dat[ 30 ] ;
		char str[ 30 ] ;
		time_t t ;
		t = p.getdd( ) ;
		strcpy( dat , convert( t ) ) ;
		puts( dat ) ;
		}
		else
		cout << '-' ;
		++ y ;
		if( y == 26 )//max y
		break ;
	}
	char c;
	n = getch( ) ;
	if( n == '\0' )
	c = getch( );
	if( nrec > 22 )
	{
		if( c == UP )
		{
			if( rec == 1 )
			continue ;
			else
			-- rec ;
			continue ;
		}
		else
		if( c == DOWN )
		{
			if( ( rec + 1 ) <= lt )
			++ rec ;
			continue ;
		}
		else
		if( n == ESC )
		{
			fi.close( ) ;
			return ;
		}
	}
	else
	{
		while( n != ESC )
		n = getch( ) ;
		fi.close( ) ;
		return ;
	}

	}while( 1 ) ;
}

void p_manage( int rec )
{
	cleardevice( ) ;
	doctor d ;
	ifstream fi( "DOCTORS.mih" , ios :: in | ios :: binary ) ;
	fi.seekg( sizeof( d ) * ( rec - 1 ) , ios :: beg ) ;
	fi.read( ( char * )&d , sizeof( d ) ) ;
	char str[ 5 ][ 50 ] ;
	strcpy( str[ 0 ] , d.getnextd( 0 ) ) ;
	strcpy( str[ 1 ] , d.getnextd( 1 ) ) ;
	strcpy( str[ 2 ] , d.getnextd( 2 ) ) ;
	strcpy( str[ 3 ] , d.getnextd( 3 ) ) ;
	strcpy( str[ 4 ] , d.getnextd( 4 ) ) ;

	int ch ;
	int a = 1 ;

	while( a == 1 )
	{
	ch = page( 11 , 12 , 1 , 5 , d.getname( ) , 15 , 9 , 300 , str ) ;

	fi.close( ) ;
	if( !ch )
	{
		cleardevice( ) ;
		return ;
	}

	switch( ch )
	{
		case 1 :
			disp_all_p_date( rec , 0 ) ;
			break ;
		case 2 :
			disp_all_p_date( rec , 1 ) ;
			break ;
		case 3 :
			disp_all_p_date( rec , 2 ) ;
			break ;
		case 4 :
			disp_all_p_date( rec , 3 ) ;
			break ;
		case 5 :
			disp_all_p_date( rec , 4 ) ;
			break ;
	}
	cleardevice( ) ;
	}
}

void disp_all_p_date( int rec , int no )
{
	gotoxy( 1 , 1 ) ;
	doctor d ;
	ifstream fi( "DOCTORS.mih" , ios :: in | ios :: binary ) ;
	fi.seekg( sizeof( d ) * ( rec - 1 ) , ios :: beg ) ;
	fi.read( ( char * )&d , sizeof( d ) ) ;
	fi.close( ) ;
	fi.open( "PATIENTS.mih" , ios :: in | ios :: binary ) ;
	int x , y ;
	char n ;
	patient p ;
	x = 1 , y = 2 ;
	gotoxy( x , y ) ;
	cout << "PatientID" ;
	x = 20 ;
	gotoxy( x , y ) ;
	cout << "SYMPTOMS" ;
	x = 45 ;
	gotoxy( x , y ) ;
	cout << "DISEASE" ;
	y = 4 ;
	gotoxy( 1 , 3 ) ;
	setcolor( 15 ) ;
	line( 0 , 32 , getmaxx( ) , 32 ) ;
	gotoxy( 1 , 1 ) ;
	int u , yes = 0 , v = d.getcn( no ) ;
	cout << "Press ESC to go back & arrows for scrolling." ;
	while( fi.read( ( char * )&p , sizeof( p ) ) )
	{
		for( u = 0 ; u < v ; ++ u )
		{
			if( p.getp_id( ) == d.getapid( no , u ) )
			{
				yes = 1 ;
				break ;
			}
		}


		if( yes == 1 )
		{
		x = 1 ;
		gotoxy( x , y ) ;
		cout << p.getp_id( ) ;
		x = 20 ;
		gotoxy( x , y ) ;
		puts( p.getsym( ) ) ;
		x = 45 ;
		gotoxy( x , y ) ;
		puts( p.getdis( ) ) ;
		++ y ;
		}
		yes = 0 ;
		if( y == 26 )//max y
		break ;
	}
	n = getch( ) ;
	while( n != ESC )
	n = getch( ) ;
	fi.close( ) ;
	return ;
}
