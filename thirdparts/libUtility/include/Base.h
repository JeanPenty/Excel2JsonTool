#pragma once

#include "Platform.h"
#include "UtilDefines.h"
#include "TypeDefines.h"
#include "ErrorDefines.h"

namespace Utility
{

	class noncopyable
	{
	protected:

		noncopyable() { }
		~noncopyable() { } // May not be virtual! Classes without virtual 
						   // operations also derive from noncopyable.

	private:
		noncopyable(const noncopyable&) = delete;
		const noncopyable& operator=(const noncopyable&) = delete;
	};

}
