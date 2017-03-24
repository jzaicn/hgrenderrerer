// HgLog.h

#pragma once
#include "HgLog/Category.hh"
#include "Export.h"

# define HGLOG_DEBUG		HgLog::HgLog::Log()->debug
# define HGLOG_INFO			HgLog::HgLog::Log()->info
# define HGLOG_NOTIE		HgLog::HgLog::Log()->notice
# define HGLOG_WARN			HgLog::HgLog::Log()->warn
# define HGLOG_ERROR		HgLog::HgLog::Log()->error
# define HGLOG_CRIT			HgLog::HgLog::Log()->crit
# define HGLOG_ALERT		HgLog::HgLog::Log()->alert
# define HGLOG_EMERG		HgLog::HgLog::Log()->emerg
# define HGLOG_FATAL		HgLog::HgLog::Log()->fatal


# define HGLOG_DEBUG_MESSAGE(message)	{ HgLog::HgLog::Log()->debugStream() << message;}
# define HGLOG_INFO_MESSAGE(message)	{ HgLog::HgLog::Log()->infoStream() << message;}
# define HGLOG_NOTIE_MESSAGE(message)	{ HgLog::HgLog::Log()->noticeStream() << message;}
# define HGLOG_WARN_MESSAGE(message)	{ HgLog::HgLog::Log()->warnStream() << message;}
# define HGLOG_ERROR_MESSAGE(message)	{ HgLog::HgLog::Log()->errorStream() << message;}
# define HGLOG_CRIT_MESSAGE(message)	{ HgLog::HgLog::Log()->critStream() << message;}
# define HGLOG_ALERT_MESSAGE(message)	{ HgLog::HgLog::Log()->alertStream() << message;}
# define HGLOG_EMERG_MESSAGE(message)	{ HgLog::HgLog::Log()->emergStream() << message;}
# define HGLOG_FATAL_MESSAGE(message)	{ HgLog::HgLog::Log()->fatalStream() << message;}

namespace HgLog {

	class HGLOG_EXPORT HgLog
	{
	private:
		HgLog(){};
		static log4cpp::Category* root;

	public:
		//获得日志仓库
		static log4cpp::Category* Log();
		static const std::string CONFIGPATH;

	protected:
		static void resetLogCategory();
		static void initLogCategory();
		static void initConfigLogCategoryThrow(std::string configpath = ".\\HgLog.conf");
	public:
		static void newtLogCategory();
		static bool initDebugLogCategory();
		static bool initConfigLogCategory(std::string configpath = ".\\HgLog.conf");
#ifdef WIN32
		static void setVsConsole();
#endif
		static void setRollingFile(log4cpp::Priority::PriorityLevel level = log4cpp::Priority::PriorityLevel::ERROR);
		static void setUdpLog();
#ifdef WIN32
		static void setNTEventLogAppender();
#endif
	};
}