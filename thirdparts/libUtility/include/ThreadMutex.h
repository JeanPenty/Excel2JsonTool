
#pragma once

#include "Base.h"
#include "Lock.h"
#include "BaseMutex.h"

namespace Utility
{

	//
	// Forward declaration for friend.
	//
	class Cond;

	class CThreadMutex : public CBaseMutex
	{
	public:

		//
		// Lock & TryLock typedefs.
		//
		typedef LockT<CThreadMutex> Lock;
		typedef TryLockT<CThreadMutex> TryLock;

		inline CThreadMutex();
		~CThreadMutex();

		//
		// Note that lock/tryLock & unlock in general should not be used
		// directly. Instead use Lock & TryLock.
		//

		void lock() const;

		//
		// Returns true if the lock was acquired, and false otherwise.
		//
		bool tryLock() const;

		void unlock() const;

		//
		// Returns true if the mutex will unlock when calling unlock()
		// (false otherwise). For non-recursive mutexes, this will always
		// return true. 
		// This function is used by the Monitor implementation to know whether 
		// the Mutex has been locked for the first time, or unlocked for the 
		// last time (that is another thread is able to acquire the mutex).
		// Pre-condition: the mutex must be locked.
		//
		bool willUnlock() const;

	private:

		// noncopyable
		CThreadMutex(const CThreadMutex&) = delete;
		void operator=(const CThreadMutex&) = delete;

		//
		// LockState and the lock/unlock variations are for use by the
		// Condition variable implementation.
		//
#ifdef JP_WIN32
		struct LockState
		{
		};
#endif

		void unlock(LockState&) const;
		void lock(LockState&) const;

		friend class Cond;

#ifdef JP_WIN32
		mutable CRITICAL_SECTION _mutex;
#endif
	};

	//
	// For performance reasons the following functions are inlined.
	//

#ifdef JP_WIN32

	inline
		CThreadMutex::CThreadMutex()
	{
		InitializeCriticalSection(&_mutex);
	}

	inline
		CThreadMutex::~CThreadMutex()
	{
		DeleteCriticalSection(&_mutex);
	}

	inline void
		CThreadMutex::lock() const
	{
		EnterCriticalSection(&_mutex);
		assert(_mutex.RecursionCount == 1);
	}

	inline bool
		CThreadMutex::tryLock() const
	{
		if (!TryEnterCriticalSection(&_mutex))
		{
			return false;
		}
		if (_mutex.RecursionCount > 1)
		{
			LeaveCriticalSection(&_mutex);
			assert(false);
		}
		return true;
	}

	inline void
		CThreadMutex::unlock() const
	{
		assert(_mutex.RecursionCount == 1);
		LeaveCriticalSection(&_mutex);
	}

	inline void
		CThreadMutex::unlock(LockState&) const
	{
		LeaveCriticalSection(&_mutex);
	}

	inline void
		CThreadMutex::lock(LockState&) const
	{
		EnterCriticalSection(&_mutex);
	}

#endif    

	inline bool
		CThreadMutex::willUnlock() const
	{
		return true;
	}

} // End namespace Utility

