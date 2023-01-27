#include<iostream>
#include "iniParser.h"

using namespace std;

int main()
{
	iniParser p1;
	p1.load("./test.ini");

	p1.printini();

	return 0;
}