#pragma once

#include "JPTime.h"
#include "SmartPtr.h"

namespace Utility
{
	class CTaskTimerThread;
	class CTTimer : public CSharedObject
	{
		friend class CTaskTimerThread;
	public:
		CTTimer(const CJPTime& interval, const bool bLoop = true, const CJPTime delay = CJPTime())
			:m_delay(delay)
			, m_interval(interval)
			, m_bLoop(bLoop)
			, m_bTerminate(false)
			, m_bDelayed(false)
		{
			m_elapse.reset();
		}
		void resume() { m_elapse.reset(); };
		void terminate() { m_bTerminate = true; };
		virtual void timeout() { return; };
	protected:
		void set_interval(const CJPTime& interval) { m_interval = interval; };

	private:
		void inc_elapse(const CJPTime& elapse) { m_elapse += elapse; };
		bool is_terminate() const { return m_bTerminate; };
		bool is_loop() const { return m_bLoop; };
		bool is_delayed() const { return m_bDelayed; }
		void set_delayed(bool bDelay) { m_bDelayed = bDelay; }
		CJPTime get_delay() { return m_delay; };
		CJPTime get_interval() { return m_interval; };
		CJPTime get_elapse() { return m_elapse; };

	private:
		CJPTime m_delay;
		CJPTime m_interval;
		CJPTime m_elapse;
		const bool m_bLoop;	/**< 定时器循环 */
		bool m_bTerminate;	/**< 定时器终止 */
		bool m_bDelayed;//delay超时是否已经发生过
	};

	typedef SmartPtr<CTTimer> TimerPtr;

} //namespace Utility


