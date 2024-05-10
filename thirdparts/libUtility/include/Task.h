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
		int taskType_;		/**< 标识 */
		int result_;		/**< 结果 */
	};
	typedef SmartPtr<CTaskEx> TaskExPtr;
}

