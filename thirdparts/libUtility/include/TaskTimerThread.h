#pragma once

#include "ThreadBase.h"
#include "TTime.h"
#include "Monitor.h"
#include "ThreadMutex.h"
#include "SmartPtr.h"
#include "Task.h"

namespace Utility
{
	class JP_UTIL_API CTaskTimerThread : public CThreadBase
	{
	public:
		CTaskTimerThread(const std::string sThreadName = "Thread", int nMaxLen = 1024);
		virtual ~CTaskTimerThread();

		void terminate();

		int add_task(const TaskPtr& task);

		int set_exit_task(const TaskPtr& task);

		int get_task_size();

		void create_timer(const TimerPtr& timer);

		void destory_timer(const TimerPtr& timer);

		virtual bool process(TaskExPtr& task) { return false; };

	protected:
		virtual void run();

		//每处理一个任务（结束任务除外）之前调用
		virtual void beforeProcessTask() {};
		//每处理一个任务（结束任务除外）之后调用
		virtual void afterProcessTask() {};

	private:
		bool ProcessTimer();

	private:
		bool terminated_;
		CJPTime timeout_;
		CJPTime now_;
		CJPTime timestamp_;

		MonitorT<CThreadMutex> monitor_;
		std::deque<TaskPtr> deque_task_;
		std::list<TimerPtr> list_timer_;

		CThreadMutex lock_new_timer_;
		CThreadMutex lock_del_timer_;
		std::vector<TimerPtr> vt_new_timer_;
		std::vector<TimerPtr> vt_del_timer_;

		std::string m_sThreadName;
		int m_nMaxLen;

		//结束任务，用于线程结束时清理线程本身分配的未加锁资源
		TaskPtr  exit_task_;
	};
}


