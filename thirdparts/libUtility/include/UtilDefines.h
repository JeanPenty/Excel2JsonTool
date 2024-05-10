#pragma once

#include "Platform.h"

#ifdef JP_WIN32

/* �趨select�Ⱥ������������Ϊ2048 - ԭ64 */
#ifdef FD_SETSIZE
#undef FD_SETSIZE
#endif	// FD_SETSIZE

	/*
	* VC6��, windwos.h��include winsock.h, winsock.h��
	* ����FD_SETSIZE, ����, ������include windows.h
	* ����FD_SETSIZE
	*/
#define FD_SETSIZE 2048L

	/* ������ΪVC6ʱ, include windows.h */
#if ( _MSC_VER == 1200 )
#include <windows.h>
#endif	// ( _MSC_VER == 1200 )

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#endif	// JP_WIN32

#ifdef JP_WIN32
#include <string.h>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stddef.h>
#include <stdarg.h>
#include <signal.h>
#include <errno.h>
#include <tchar.h>

#include <crtdbg.h>
#include <process.h>
#endif


#include <fcntl.h>
#include <memory>
#include <utility>
#include <algorithm>
#include <utility>
#include <set> 
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <cassert>
#include <iostream>
#include <sstream>

/*
 * export��import����
 */
#define __UTILITY_BUILD_DLL

#ifdef JP_WIN32
#if ( defined(_LIB) || defined(__UTILITY_USE_LIB) )
#define JP_UTIL_API
#else 
#if ( defined(_USRDLL) && defined(__UTILITY_BUILD_DLL) )
#define JP_UTIL_API __declspec( dllexport )
#else
#define JP_UTIL_API __declspec( dllimport )
#endif
#endif	// _LIB || SC_OS_BUILD_LIB

#endif	// JP_WIN32

 /*
  * �ָ�������
  */
#ifdef JP_WIN32
#define JP_OS_SEPARATE '\\'
#endif	// JP_WIN32

  /* ���ĳbit��û�б����� */
#ifndef JP_BIT_ENABLED
#define JP_BIT_ENABLED( dword, bit ) ( ((dword) & (bit)) != 0 )
#endif	// JP_BIT_ENABLED

/* ���ĳbit��û�б����� */
#ifndef JP_BIT_DISABLED
#define JP_BIT_DISABLED( dword, bit ) ( ((dword) & (bit)) == 0 )
#endif	// JP_BIT_DISABLED

/* ���ĳbit��ֵ�Ƿ���<mask>��� */
#ifndef JP_BIT_CMP_MASK
#define JP_BIT_CMP_MASK( dword, bit, mask ) ( ((dword) & (bit)) == mask )
#endif	// JP_BIT_CMP_MASK

/* ����ĳbit */
#ifndef JP_SET_BITS
#define JP_SET_BITS( dword, bits ) ( dword |= (bits) )
#endif	// JP_SET_BITS

/* ����ĳbit */
#ifndef JP_CLR_BITS
#define JP_CLR_BITS( dword, bits ) ( dword &= ~(bits) )
#endif	// JP_CLR_BITS

/* ɾ��һ��ָ�벢��ΪNULL */
#ifndef JP_DELETE
#define JP_DELETE( p )			\
	do								\
	{								\
		if ( NULL != (p) )			\
		{							\
			delete (p);				\
			(p) = NULL;				\
		}							\
	} while ( 0 )
#endif	// JP_DELETE

/* ɾ��һ��ָ�����鲢��ΪNULL */
#ifndef JP_ARRAY_DELETE
#define JP_ARRAY_DELETE( pArray )	\
	do									\
	{									\
		if ( NULL != (pArray) )			\
		{								\
			delete[] (pArray);			\
			(pArray) = NULL;				\
		}								\
	} while( 0 )
#endif	// JP_ARRAY_DELETE

/* ���<length>��'0' */
#define JP_ZERO( psz, length ) memset( psz, 0, length )

