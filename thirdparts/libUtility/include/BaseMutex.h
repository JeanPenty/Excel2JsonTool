#pragma once

#include "Base.h"
#include "Lock.h"

namespace Utility
{

	class CBaseMutex
	{
	public:

		typedef LockT<CBaseMutex> Lock;
		typedef TryLockT<CBaseMutex> TryLock;

		CBaseMutex() {};
		virtual ~CBaseMutex() {};

		virtual void lock() const = 0;

		virtual bool tryLock() const = 0;

		virtual void unlock() const = 0;

	private:

		// noncopyable
		CBaseMutex(const CBaseMutex&) = delete;
		void operator=(const CBaseMutex&) = delete;
	};

	class CNullMutex : public CBaseMutex
	{
	public:

		typedef LockT<CNullMutex> Lock;
		typedef TryLockT<CNullMutex> TryLock;

		CNullMutex() {};
		~CNullMutex() {};

		void lock() const {};

		bool tryLock() const { return true; };

		void unlock() const {};

	private:

		// noncopyable
		CNullMutex(const CNullMutex&) = delete;
		void operator=(const CNullMutex&) = delete;
	};

} // End namespace Utility

