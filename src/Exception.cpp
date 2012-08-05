/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Exception.h"

#include <v8.h>

using namespace bit;
using std::string;


Exception::Exception() throw()
{
}


Exception::Exception(std::string message) throw()
{
	this->message = message;
}


string Exception::what() const throw()
{
	return message;
}


void Exception::throwV8Exception() const throw()
{
	v8::Local<v8::String> message = v8::String::New(what().c_str());
	v8::ThrowException(v8::Exception::Error(message));
}