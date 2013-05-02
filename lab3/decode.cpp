#include "DES.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

short text[ DES_TEXT_LENGTH ] ;
string cipher ;
int main()
{
	ifstream fin( "C.txt" ) ;
	for ( int i = 0 ; i < DES_TEXT_LENGTH ; i ++ )
	{
		char c ;
		fin >> c ;
		text[ i ] = c - '0' ;
	}
	fin .close() ;
	fin .open( "K.txt" ) ;
	fin >> cipher ;
	fin .close() ;

	DES_machine D ;
	D .set_text( text ) ;
	D .set_cipher( cipher ) ;
	D .decode() ;

	for ( int i = 0 ; i < 16 ; i ++ )
	{
		int x = 0 ;
		for ( int j = i * 4 ; j < ( i + 1 ) * 4 ; j ++ )
			x = x * 2 + D .element( j ) ;
		cout << hex << x ;
	}
	cout << endl;

	ofstream fout( "M_decode.txt" ) ;
	for ( int i = 0 ; i < 64 ; i ++ )
		fout << D .element( i ) ;
	fout << endl;
	fout .close() ;
}
