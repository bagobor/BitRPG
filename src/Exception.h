/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_Exception_h
#define BitRPG_Exception_h

#include <string>


namespace bit
{
	class Exception
	{
	public:
		Exception() throw();
		Exception(std::string message) throw();
		
		std::string what() const throw();
		void throwV8Exception() const throw();
		
	private:
		std::string message;
	};
}

#endif
