/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Application.h"
#include "Exception.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace bit;
using namespace std;


int main(int argc, const char *argv[])
{
	try
	{
		ApplicationPtr app(new Application());
		app->start();
	}
	catch (Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
