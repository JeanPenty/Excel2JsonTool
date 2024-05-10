#pragma once

#include "Base.h"
#include "ThreadMutex.h"
#include "JPTime.h"
#include "SmartPtr.h"
namespace Utility
{

	class JP_UTIL_API CThreadBase : public CSharedObject
	{
	public:
		CThreadBase();
		virtual ~CThreadBase();

		virtual bool start(size_t stackSize = 0);

		//等待线程退出，join内部会调用detach
		void join();

		//解除对线程的控制权
		void detach();

		static void sleep(const CJPTime&);
		static void yield();

	public:
		DWORD getThreadId() const;
		bool isAlive() const;
		void	_done();

	protected:
		//线程执行函数
		virtual void run() = 0;
	private:
		CThreadBase(const CThreadBase&) = delete;
		CThreadBase& operator=(const CThreadBase&) = delete;

		static unsigned int __stdcall threadFunc(void* arg);

	protected:
		CThreadMutex  m_mtxState;

		bool				m_bStarted;
		bool				m_bRunning;

		HANDLE			m_hThread;
		DWORD			m_dwThreadID;
	};

	typedef SmartPtr<CThreadBase> ThreadBasePtr;
}

