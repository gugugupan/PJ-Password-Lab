#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include "vigenre.h"
using namespace std;

string text , cipher , key ;
int main()
{
	ifstream fin ;
	fin .open( "M.txt" ) ;
	getline( fin , text ) ;
	fin .close() ;

	fin .open( "key_vigenre.txt" ) ;
	fin >> key ;
	fin .close() ;

	Vigenre machine( key ) ;
	cipher = machine .encode( text ) ;

	cout << cipher << endl;

	ofstream fout ;
	fout .open( "C.txt" ) ;
	fout << cipher << endl;
	fout .close() ;
}