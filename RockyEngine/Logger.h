#pragma once

enum Severity
{
	INFO,
	WARNING,
	ERROR,
	DEBUG
};

#ifdef _DEBUG
#define LOG_ERROR(msg) Logger::OutputLog(ERROR,msg,__FILE__,__LINE__)
#define LOG_WARNING(msg) Logger::OutputLog(WARNING,msg,__FILE__,__LINE__)
#define LOG_INFO(msg) Logger::OutputLog(INFO,msg,__FILE__,__LINE__)
#define LOG_DEBUG(msg) Logger::OutputLog(DEBUG,msg,__FILE__,__LINE__);
#define GL_ATTEMPT(func) func; \
if (Logger::CheckGLError(__FILE__, __LINE__)) __debugbreak()
#define CHECK_GL_ERROR() Logger::CheckGLError(__FILE__, __LINE__)
#else
#define LOG_ERROR(msg)
#define LOG_WARNING(msg)
#define LOG_INFO(msg)
#define LOG_DEBUG(msg)
#define GL_ATTEMPT(func) func
#define CHECK_GL_ERROR()
#endif

// TODO: implement different log levels (use bitmasking??
class Logger
{
private:
	Logger();
public:
	static void OutputLog(Severity sev,const std::string& msg, const char* file, int line);
	static bool CheckGLError(const char* file, int line);
};


