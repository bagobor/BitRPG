/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Application.h"
#include "Exception.h"

#include <iostream>
#include <string>
#include <boost/smart_ptr.hpp>

using boost::shared_ptr;
using namespace bit;
using namespace std;


int main(int argc, const char *argv[])
{
	try
	{
		shared_ptr<Application> app(new Application());
		app->start();
	}
	catch (Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
