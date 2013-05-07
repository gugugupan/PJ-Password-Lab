#include <cstdio>
#include "lfsr.h"
using namespace std;

char tmp[ 100 ] ;
unsigned char text[ 100 ] ;
int len ;
int main()
{
	FILE *Min = fopen( "M.txt" , "r" ) ;
	FILE *Kin = fopen( "K.txt" , "r" ) ;
	fgets( tmp , 100 , Min ) ;
	len = strlen( tmp ) ;
	memcpy( text , tmp , sizeof( char ) * len ) ;
	fscanf( Kin , "%c" , &cypher ) ;

	for ( int i = 0 ; i < len ; i ++ )
	{
		text[ i ] = text[ i ] ^ cypher ;
		around() ;
	}

	FILE *Cout = fopen( "C.txt" , "w" ) ;
	for ( int i = 0 ; i < len ; i ++ )
		fprintf( Cout , "%x%x" , text[ i ] >> 4 , text[ i ] & 15 ) ;
}
