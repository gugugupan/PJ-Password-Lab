#include <cstdio>
#include "lfsr.h"
using namespace std;

unsigned char char2int( char c )
{
	if ( 'a' <= c && c <= 'f' ) return 10 + c - 'a' ;
	return c - '0' ;
}

char tmp[ 100 ] ;
unsigned char text[ 100 ] ;
int len ;
int main()
{
	FILE *Cin = fopen( "C.txt" , "r" ) ;
	FILE *Kin = fopen( "K.txt" , "r" ) ;

	len = 0 ;
	char c1 , c2 ;
	while ( fscanf( Cin , "%c%c" , &c1 , &c2 ) != EOF )
		text[ len ++ ] = ( char2int( c1 ) << 4 ) + char2int( c2 ) ;
	fscanf( Kin , "%c" , &cypher ) ;

	for ( int i = 0 ; i < len ; i ++ )
	{
		text[ i ] = text[ i ] ^ cypher ;
		around() ;
	}

	memcpy( tmp , text , sizeof( char ) * len ) ;
	printf( "%s\n" , tmp ) ;
	//FILE *Mout = fopen( "M.txt" , "w" ) ;
	//fprintf( Mout , "%s" , tmp ) ;
}
