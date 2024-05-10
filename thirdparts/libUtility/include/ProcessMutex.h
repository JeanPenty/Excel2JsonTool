
#pragma once

#include "Base.h"

namespace Utility
{
	template<typename T>
	class LockHelperT
	{
	public:
		LockHelperT(const T& mutex) :m_mutex(mutex)
		{
			m_mutex.lock();
		}

		~LockHelperT()
		{
			m_mutex.unlock();
		}

	private:
		LockHelperT(const LockHelperT&);
		LockHelperT& operator=(const LockHelperT&);

		const T& m_mutex;
	};

	class CKfProcessMutex
	{
	public:
		typedef LockHelperT<CKfProcessMutex> Lock;

		CKfProcessMutex(const std::string& name)
		{
			m_hMutex = CreateMutexA(NULL, FALSE, name.c_str());
			assert(m_hMutex != NULL);
		}

		~CKfProcessMutex()
		{
			CloseHandle(m_hMutex);
			m_hMutex = NULL;
		}

	public:
		void	lock() const
		{
			assert(m_hMutex != NULL);
			WaitForSingleObject(m_hMutex, INFINITE);
		}

		void	unlock() const
		{
			assert(m_hMutex != NULL);
			ReleaseMutex(m_hMutex);
		}

	public:
		HANDLE	m_hMutex;
	};

} // End namespace Utility

