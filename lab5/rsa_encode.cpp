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
	string text ;
	ifstream fin ;
	fin .open( "M.txt" ) ;
	getline( fin , text ) ;
	fin .close() ;

	int e , n ;
	fin .open( "pubK.txt" ) ;
	fin >> e >> n ;
	fin .close() ;

	ofstream fout ;
	fout .open( "C.txt" ) ;
	for ( int i = 0 ; i < text .length() ; i ++ )
		fout << fact( text[ i ] , e , n ) << endl;
}
