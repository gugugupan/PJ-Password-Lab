#include "DES.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

string text ;
string cipher ;
int main()
{
	ifstream fin( "M.txt" ) ;
	fin >> text ;
	fin .close() ;
	fin .open( "K.txt" ) ;
	fin >> cipher ;
	fin .close() ;

	DES_machine D ;
	D .set_text( text ) ;
	D .set_cipher( cipher ) ;
	D .encode() ;

	ofstream fout( "C.txt" ) ;
	for ( int i = 0 ; i < 64 ; i ++ )
		fout << D .element( i ) ;
	fout << endl;
	ofstream .close() ;
}
