#pragma once

#include "SmartPtr.h"

namespace Utility
{
	class CTask : public CSharedObject
	{
	public:
		CTask() {}
		virtual ~CTask() {}

	public:
		virtual int dotask() = 0;

	private:
		/* not allow copying and assignment. */
		CTask(const CTask&) = delete;
		void operator= (const CTask&) = delete;
	};
	typedef SmartPtr<CTask> TaskPtr;

	class CTaskEx : virtual public CTask
	{
	public:
		CTaskEx()
			: taskType_(0), result_(0)
		{
		}
		virtual ~CTaskEx() {}

	public:
		virtual int dotask() { return 0; }

	public:
		int taskType_;		/**< ��ʶ */
		int result_;		/**< ��� */
	};
	typedef SmartPtr<CTaskEx> TaskExPtr;
}

