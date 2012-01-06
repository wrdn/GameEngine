#pragma once

#include <string>

class Namable // Debug functionality - inherited item can be given a name (useful for debugging)
{
#ifdef _DEBUG
private:
	std::string name;
public:
	inline void SetName(const std::string &m) { name = m; };
	inline const std::string &GetName() { return name; };
#else
public:
	inline void SetName(const std::string &m) { if(m.size()){} };
	inline const std::string GetName() { return ""; };
#endif
};