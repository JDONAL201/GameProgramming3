#include <iostream>
#include "Logger.h"
int main()
{
	std::cout << "Hello World!\n";
	LOG_ERROR("You it worked?!!");
	LOG_WARNING("You it worked?!!");
	LOG_DEBUG("You it worked?!!");
	LOG_INFO("hello");
}

