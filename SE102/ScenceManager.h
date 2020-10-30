#pragma once
#include "Scence.h"
#include <unordered_map>


class CScences
{
	static CScences* __instance;
	
	std::unordered_map<std::string, LPSCENE> scences; //bi loi xong search ngta chi z

public:
	CScences();
	void Add(std::string id, LPSCENE scence);
	LPSCENE Get(std::string id);
	void Clear();
	static CScences* GetInstance();
};