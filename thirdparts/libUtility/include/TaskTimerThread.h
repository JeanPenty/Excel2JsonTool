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

		//ÿ����һ�����񣨽���������⣩֮ǰ����
		virtual void beforeProcessTask() {};
		//ÿ����һ�����񣨽���������⣩֮�����
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

		//�������������߳̽���ʱ�����̱߳�������δ������Դ
		TaskPtr  exit_task_;
	};
}


