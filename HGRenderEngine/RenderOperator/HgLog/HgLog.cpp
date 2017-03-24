// 这是主 DLL 文件。



#include "HgLog.h"

#include "HgLog/Appender.hh"
#include "HgLog/FileAppender.hh"
#include "HgLog/OstreamAppender.hh"
#include "HgLog/NTEventLogAppender.hh"
#include "HgLog/StringQueueAppender.hh"
#include "HgLog/RollingFileAppender.hh"
#include "HgLog/RemoteSyslogAppender.hh"
#include "HgLog/Layout.hh"
#include "HgLog/BasicLayout.hh"
#include "HgLog/SimpleLayout.hh"
#include "HgLog/PatternLayout.hh"
#include "HgLog/BasicConfigurator.hh"
#include "HgLog/PropertyConfigurator.hh"
#include "HgLog/Win32DebugAppender.hh"
#include "HgLog/Priority.hh"
#include "HgLog/NDC.hh"


namespace HgLog {

log4cpp::Category* HgLog::root = NULL;


log4cpp::Category* HgLog::Log()    
{
	if (!root)
	{
		try
		{
			initConfigLogCategoryThrow();
			Log()->info("init config logger success");
		}
		catch(std::runtime_error e)
		{
			initDebugLogCategory();
			Log()->warn("init config logger fail");
			Log()->warn(e.what());
			Log()->info("init debug logger success");
		}
		catch(...)
		{
			initDebugLogCategory();
			Log()->warn("init config logger fail");
			Log()->info("init debug logger success");
		}
	}
	return root;
}

void HgLog::newtLogCategory()
{
	initLogCategory();
	resetLogCategory();
}

bool HgLog::initDebugLogCategory()
{
	initLogCategory();
	resetLogCategory();
	setUdpLog();
#ifdef WIN32
	setVsConsole();
#endif // WIN32
	return true;
}
void HgLog::initConfigLogCategoryThrow(std::string configpath)
{
	initLogCategory();
	resetLogCategory();
	log4cpp::PropertyConfigurator::configure(configpath);
}
bool HgLog::initConfigLogCategory(std::string configpath)
{
	try
	{
		initConfigLogCategoryThrow(configpath);
		return true;
	}
	catch(std::runtime_error e)
	{
		return false;
	}
	catch(...)
	{
		return false;
	}

}


// 重置输出器
void HgLog::resetLogCategory()
{
	if (root)
	{
		root->removeAllAppenders();
	}
}

void HgLog::initLogCategory()
{
	if (!root)
	{
		root = &log4cpp::Category::getRoot();
	}
}
#ifdef WIN32
void HgLog::setVsConsole()
{
	initLogCategory();
	if (root)
	{
		log4cpp::Win32DebugAppender* appender = new log4cpp::Win32DebugAppender("Win32DebugAppender");
		log4cpp::Layout* layout = new log4cpp::BasicLayout();
		appender->setLayout(layout);
		root->setAdditivity(true);
		root->setAppender(appender);
		root->setPriority(log4cpp::Priority::DEBUG);
	}
}
#endif
void HgLog::setRollingFile(log4cpp::Priority::PriorityLevel level)
{
	if (root)
	{
		log4cpp::RollingFileAppender* appender = new log4cpp::RollingFileAppender("RollingFileAppender","D:\\log\\hgsoft.log");
		log4cpp::Layout* layout = new log4cpp::BasicLayout();
		appender->setLayout(layout);
		root->setAdditivity(true);
		root->setAppender(appender);
		root->setPriority(level);
	}
}
void HgLog::setUdpLog()
{
	initLogCategory();
	if (root)
	{
		log4cpp::Appender* appender = new log4cpp::RemoteSyslogAppender("RemoteSyslogAppender","127.0.0.1","",8,8080);
		log4cpp::Layout* layout = new log4cpp::BasicLayout();
		appender->setLayout(layout);
		root->setAdditivity(true);
		root->setAppender(appender);
		root->setPriority(log4cpp::Priority::DEBUG);
	}
}
#ifdef WIN32
void HgLog::setNTEventLogAppender()
{
	initLogCategory();
	if (root)
	{
		log4cpp::Appender* appender = new log4cpp::NTEventLogAppender("NTEventLogAppender","HgLog");
		log4cpp::Layout* layout = new log4cpp::BasicLayout();
		appender->setLayout(layout);
		root->setAdditivity(true);
		root->setAppender(appender);
		root->setPriority(log4cpp::Priority::DEBUG);
	}
}
#endif // WIN32
}