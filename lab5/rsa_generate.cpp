#include <cstdio>
#include <cstdlib>

int gcd( int a , int b )
{
	if ( b == 0 ) return a ;
	return gcd( b , a % b ) ;
}

int main()
{
	int p = 89 , q = 97 ;
	int n = p * q ;
	int phi_n = ( p - 1 ) * ( q - 1 ) ;
	int e = rand() % phi_n ;
	while ( gcd( e , phi_n ) != 1 )
		e = rand() % phi_n ;
	int d = 1 ;
	while ( d * e % phi_n != 1 ) d ++ ;

	FILE *fp = fopen( "K.txt" , "w" ) ;
	fprintf( fp , "%d %d\n" , p , q ) ;
	fclose( fp ) ;

	fp = fopen( "pubK.txt" , "w" ) ;
	fprintf( fp , "%d %d\n" , e , n ) ;
	fclose( fp ) ;

	fp = fopen( "privK.txt" , "w" ) ;
	fprintf( fp , "%d %d\n" , d , n ) ;
	fclose( fp ) ;
}