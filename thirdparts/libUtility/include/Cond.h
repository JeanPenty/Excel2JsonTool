#pragma once

#include "Base.h"
#include "JPTime.h"
#include "ThreadMutex.h"
#ifdef JP_WIN32

namespace UtilityInternal
{
	//
	// Needed for implementation.
	//
	class Semaphore
	{
	public:

		Semaphore(long = 0);
		JP_UTIL_API ~Semaphore();

		void wait() const;
		bool timedWait(const Utility::CJPTime&) const;
		void post(int = 1) const;

	private:

		mutable HANDLE _sem;
	};
}
#endif


namespace Utility
{

	//
	// Forward declaration (for friend declarations).
	//
	template <class T> class MonitorT;
	class CThreadRecMutex;
	class CThreadMutex;

	//
	// Condition variable implementation. Conforms to the same semantics
	// as a POSIX threads condition variable.
	//
	class Cond : private noncopyable
	{
	public:

		JP_UTIL_API Cond();
		JP_UTIL_API ~Cond();

		//
		// signal restarts one of the threads that are waiting on the
		// condition variable cond.  If no threads are waiting on cond,
		// nothing happens. If several threads are waiting on cond,
		// exactly one is restarted, but it is not specified which.
		//
		JP_UTIL_API void signal();

		//
		// broadcast restarts all the threads that are waiting on the
		// condition variable cond. Nothing happens if no threads are
		// waiting on cond.
		//
		JP_UTIL_API void broadcast();

		//
		// MSVC doesn't support out-of-class definitions of member
		// templates. See KB Article Q241949 for details.
		//

		//
		// wait atomically unlocks the mutex and waits for the condition
		// variable to be signaled. Before returning to the calling thread
		// the mutex is reaquired.
		//
		template <typename Lock> inline void
			wait(const Lock& lock) const
		{
			if (!lock.acquired())
			{
				assert(false);
			}
			waitImpl(lock._mutex);
		}

		//
		// wait atomically unlocks the mutex and waits for the condition
		// variable to be signaled for up to the given timeout. Before
		// returning to the calling thread the mutex is reaquired. Returns
		// true if the condition variable was signaled, false on a
		// timeout.
		//
		template <typename Lock> inline bool
			timedWait(const Lock& lock, const CJPTime& timeout) const
		{
			if (!lock.acquired())
			{
				assert(false);
			}
			return timedWaitImpl(lock._mutex, timeout);
		}

	private:

		friend class MonitorT<CThreadMutex>;
		friend class MonitorT<CThreadRecMutex>;

		//
		// The Monitor implementation uses waitImpl & timedWaitImpl.
		//
#ifdef JP_WIN32

		template <typename M> void
			waitImpl(const M& mutex) const
		{
			preWait();

			typedef typename M::LockState LockState;

			LockState state;
			mutex.unlock(state);

			try
			{
				dowait();
				mutex.lock(state);
			}
			catch (...)
			{
				mutex.lock(state);
				throw;
			}
		}
		template <typename M> bool
			timedWaitImpl(const M& mutex, const CJPTime& timeout) const
		{
			preWait();

			typedef typename M::LockState LockState;

			LockState state;
			mutex.unlock(state);

			try
			{
				bool rc = timedDowait(timeout);
				mutex.lock(state);
				return rc;
			}
			catch (...)
			{
				mutex.lock(state);
				throw;
			}
		}

#endif

#ifdef JP_WIN32
		JP_UTIL_API void wake(bool);
		JP_UTIL_API void preWait() const;
		JP_UTIL_API void postWait(bool) const;
		JP_UTIL_API bool timedDowait(const CJPTime&) const;
		JP_UTIL_API void dowait() const;

		CThreadMutex _internal;
		UtilityInternal::Semaphore _gate;
		UtilityInternal::Semaphore _queue;
		mutable long _blocked;
		mutable long _unblocked;
		enum State
		{
			StateIdle,
			StateSignal,
			StateBroadcast
		};
		mutable State _state;
#endif

	};

} // End namespace Utility
