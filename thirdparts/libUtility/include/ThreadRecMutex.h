
#pragma once

#include "Base.h"
#include "Lock.h"
#include "BaseMutex.h"

namespace Utility
{

	//
	// Forward declarations for friend.
	//
	class Cond;

	//
	// Recursive Mutex implementation.
	//
	class JP_UTIL_API CThreadRecMutex : public CBaseMutex
	{
	public:

		//
		// Lock & TryLock typedefs.
		//
		typedef LockT<CThreadRecMutex> Lock;
		typedef TryLockT<CThreadRecMutex> TryLock;

		CThreadRecMutex();
		~CThreadRecMutex();

		//
		// Note that lock/tryLock & unlock in general should not be used
		// directly. Instead use Lock & TryLock.
		//

		void lock() const;

		//
		// Returns true if the lock was acquired or was already acquired
		// by the calling thread, and false otherwise.
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
		CThreadRecMutex(const CThreadRecMutex&) = delete;
		void operator=(const CThreadRecMutex&) = delete;

		//
		// LockState and the lock/unlock variations are for use by the
		// Condition variable implementation.
		//
#ifdef JP_WIN32
		struct LockState
		{
			int count;
		};
#endif

		void unlock(LockState&) const;
		void lock(LockState&) const;

		friend class Cond;

#ifdef JP_WIN32
		mutable CRITICAL_SECTION _mutex;
#endif    

		mutable int _count;
	};

} // End namespace Utility

