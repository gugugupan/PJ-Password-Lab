#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

int fact( int a , int b , int m )
{
	int cici = 1 ;
	for ( ; b ; b -- )
		cici = ( cici * a ) % m ;
	return cici ;
}

int main()
{
	int d , n ;
	ifstream fin ;
	fin .open( "privK.txt" ) ;
	fin >> d >> n ;
	fin .close() ;

	fin .open( "C.txt" ) ;
	int c ;
	while ( fin >> c )
		cout << ( char ) fact( c , d , n ) ;
	cout << endl;

	fin .close() ;
}
