
#include "Logger.h"


bool Logger::CheckGLError(const char* file, int line)
{
	GLenum err;
	bool errorFound = false;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "GL ERROR(" << file << ", " << line << "): " <<
			glewGetErrorString(err) << std::endl;
		errorFound = true;
	}
	return errorFound;
}

void Logger::OutputLog(Severity sev, const std::string& msg, const char* file, int line)
{
	std::string log = msg + " [LOCATION]: " + std::string(file) + " [LINE] : " + std::string(std::to_string(line));

	switch (sev)
	{
	case Severity::ERROR:
		log.insert(0, "\x1B[31m[LOG ERROR] ");
		break;
	case Severity::INFO:
		log.insert(0, "\x1B[32m[LOG: INFO] ");
		break;
	case Severity::WARNING:
		log.insert(0, "\x1B[33m[LOG: WARNING] ");
		break;
	case Severity::DEBUG:
		log.insert(0, "\x1B[36m[LOG: DEBUG] ");
		break;
	
	case Severity::RESOURCE:
		log = "\x1B[39m" + msg;

	}
	std::cout << log << std::endl;
}
