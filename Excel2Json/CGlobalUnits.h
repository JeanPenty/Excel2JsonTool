#pragma once

#include <string>
#include <vector>
#include <map>

class CGlobalUnits
{
public:
	CGlobalUnits(void);
	~CGlobalUnits(void);
public:

	std::map<SStringW, std::vector<SStringW>> m_mapTitleDatas;

public:
	static CGlobalUnits* GetInstance();
};

#define GlobalUnits		CGlobalUnits::GetInstance()