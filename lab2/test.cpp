#include <iostream>
#include <fstream>
#include <string>
#include "Diffie_Hellman.h"
using namespace std;

bool is_primitive_root( int prime , int root )
{
	int cici = 1 ;
	for ( int i = 1 ; i < prime - 1 ; i ++ )
	{
		cici = ( cici * root ) % prime ;
		if ( cici == 1 ) return false ;
	}
	cici = ( cici * root ) % prime ;
	return cici == 1 ;
}

int get_primitive_root( int prime ) 
{
	for ( int p = 2 ; p * p < prime ; p ++ )
		if ( prime % p == 0 ) return -1 ;
	for ( int p = 2 ; p < prime ; p ++ )
		if ( is_primitive_root( prime , p ) ) return p ;
	return -1 ;
}

int main()
{
	ifstream fin( "prime.txt" ) ;
	fin >> prime ;
	a = get_primitive_root( prime ) ;

	Diffie_hellman person_a( 36 ) , person_b( 58 ) ;
	cout << "A has a key for B is : " 
	<< person_a .get_key( person_b .public_key ) << endl;
	cout << "B has a key for A is : "
	<< person_b .get_key( person_a .public_key ) << endl;
}
