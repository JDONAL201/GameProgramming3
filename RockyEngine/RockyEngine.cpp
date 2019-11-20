#include <iostream>
#include "Logger.h"
#include "Application.h"

int main(int argc,char* argv[])
{
	Application::Instance()->Run();
	return 0;
}

