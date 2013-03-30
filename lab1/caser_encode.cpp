#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include "caser.h"
using namespace std;

string text , cipher ;
int key ;
int main()
{
	ifstream fin ;
	fin .open( "M.txt" ) ;
	getline( fin , text ) ;
	fin .close() ;

	fin .open( "key.txt" ) ;
	fin >> key ;
	fin .close() ;

	Caser machine( key ) ;
	cipher = machine .encode( text ) ;

	cout << cipher << endl;

	ofstream fout ;
	fout .open( "C.txt" ) ;
	fout << cipher << endl;
	fout .close() ;
}