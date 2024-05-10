
#pragma once

#include "ThreadMutex.h"
#include "SmartPtr.h"

namespace Utility
{
	//Singleton
	template<typename T>
	class Singleton
	{
	public:
		static inline T* instance()
		{
			if (0 == m_sInstance)
			{
				CThreadMutex::Lock guard(m_sMutex);
				if (0 == m_sInstance)
				{
					m_sInstance = new T;
				}
			}
			return m_sInstance;
		}

		static inline void free()
		{
			if (m_sInstance != 0)
			{
				CThreadMutex::Lock guard(m_sMutex);
				if (m_sInstance != 0)
				{
					delete m_sInstance;
					m_sInstance = 0;
				}
			}
		}

	protected:
		Singleton() {}
		virtual ~Singleton() {}
	private:
		Singleton(const Singleton&) {}
		Singleton& operator=(const Singleton&) {}

	private:
		static T* m_sInstance;
		static CThreadMutex m_sMutex;
	};

	template<typename T>
	T* Singleton<T>::m_sInstance = 0;

	template<typename T>
	CThreadMutex Singleton<T>::m_sMutex;


	//SmartSingleton
	template<typename T>
	class SmartSingleton
	{
	public:
		static inline SmartPtr<T>& instance()
		{
			if (m_sInstance.get() == 0)
			{
				CThreadMutex::Lock guard(m_sMutex);

				if (m_sInstance.get() == 0)
				{
					m_sInstance = new T;
				}
			}
			return m_sInstance;
		}

		static inline void free()
		{
			if (m_sInstance.get() != 0)
			{
				CThreadMutex::Lock guard(m_sMutex);

				if (m_sInstance.get() != 0)
				{
					m_sInstance = 0;
				}
			}
		}

	protected:
		SmartSingleton() {}
		virtual ~SmartSingleton()
		{
			// Don't free again
		}
	private:
		SmartSingleton(const SmartSingleton&) {}
		SmartSingleton& operator=(const SmartSingleton&) {}

	private:
		static SmartPtr<T> m_sInstance;
		static CThreadMutex m_sMutex;
	};

	template<typename T>
	SmartPtr<T> SmartSingleton<T>::m_sInstance = 0;

	template<typename T>
	CThreadMutex SmartSingleton<T>::m_sMutex;

} //namespace Utility
