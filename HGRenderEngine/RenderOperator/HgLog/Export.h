#ifndef HGLOG_EXPORT_H
#define HGLOG_EXPORT_H 1


#pragma warning( disable : 4251 )


#if defined( HGLOG_LIB )
	#define HGLOG_EXPORT   __declspec(dllexport)
#else
	#define HGLOG_EXPORT   __declspec(dllimport)
#endif

#endif