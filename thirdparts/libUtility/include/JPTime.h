
#pragma once

#include "Base.h"

namespace Utility
{

	class JP_UTIL_API CJPTime
	{
	public:

		CJPTime();

		// No copy constructor and assignment operator necessary. The
		// automatically generated copy constructor and assignment
		// operator do the right thing.

		static CJPTime now();
		static CJPTime makeTime(int year, int month, int day,
			int hour, int minute, int second, int milliSecond);
		static CJPTime seconds(int64);
		static CJPTime milliSeconds(int64);

		int64 toSeconds() const;
		int64 toMilliSeconds() const;

		std::string toDateTime() const;
		std::string toDateTimeAccuracy() const;

		void reset()
		{
			_msec = 0;
		}

		CJPTime operator-() const
		{
			return CJPTime(-_msec);
		}

		CJPTime operator-(const CJPTime& rhs) const
		{
			return CJPTime(_msec - rhs._msec);
		}

		CJPTime operator+(const CJPTime& rhs) const
		{
			return CJPTime(_msec + rhs._msec);
		}

		CJPTime& operator+=(const CJPTime& rhs)
		{
			_msec += rhs._msec;
			return *this;
		}

		CJPTime& operator-=(const CJPTime& rhs)
		{
			_msec -= rhs._msec;
			return *this;
		}

		bool operator<(const CJPTime& rhs) const
		{
			return _msec < rhs._msec;
		}

		bool operator<=(const CJPTime& rhs) const
		{
			return _msec <= rhs._msec;
		}

		bool operator>(const CJPTime& rhs) const
		{
			return _msec > rhs._msec;
		}

		bool operator>=(const CJPTime& rhs) const
		{
			return _msec >= rhs._msec;
		}

		bool operator==(const CJPTime& rhs) const
		{
			return _msec == rhs._msec;
		}

		bool operator!=(const CJPTime& rhs) const
		{
			return _msec != rhs._msec;
		}

		double operator/(const CJPTime& rhs) const
		{
			return (double)_msec / (double)rhs._msec;
		}

		CJPTime& operator*=(int rhs)
		{
			_msec *= rhs;
			return *this;
		}

		CJPTime operator*(int rhs) const
		{
			CJPTime t;
			t._msec = _msec * rhs;
			return t;
		}

		CJPTime& operator/=(int rhs)
		{
			_msec /= rhs;
			return *this;
		}

		CJPTime operator/(int rhs) const
		{
			CJPTime t;
			t._msec = _msec / rhs;
			return t;
		}

		CJPTime& operator*=(int64 rhs)
		{
			_msec *= rhs;
			return *this;
		}

		CJPTime operator*(int64 rhs) const
		{
			CJPTime t;
			t._msec = _msec * rhs;
			return t;
		}

		CJPTime& operator/=(int64 rhs)
		{
			_msec /= rhs;
			return *this;
		}

		CJPTime operator/(int64 rhs) const
		{
			CJPTime t;
			t._msec = _msec / rhs;
			return t;
		}

		CJPTime& operator*=(double rhs)
		{
			_msec = static_cast<int64>(static_cast<double>(_msec) * rhs);
			return *this;
		}

		CJPTime operator*(double rhs) const
		{
			CJPTime t;
			t._msec = static_cast<int64>(static_cast<double>(_msec) * rhs);
			return t;
		}

		CJPTime& operator/=(double rhs)
		{
			_msec = static_cast<int64>(static_cast<double>(_msec) / rhs);
			return *this;
		}

		CJPTime operator/(double rhs) const
		{
			CJPTime t;
			t._msec = static_cast<int64>(static_cast<double>(_msec) / rhs);
			return t;
		}

	private:

		CJPTime(int64);

		int64 _msec;//∫¡√Î
	};

} // End namespace Utility

