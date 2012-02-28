#pragma once

#include "ctypes.h"
#include "Namable.h"

class Resource : public Namable
{
private:
	i32 id;
public:
	Resource() : id(-1) {};
	Resource(int _id) : id(_id) {};
	virtual ~Resource() {};

	void SetID(i32 _id) { id = _id; };
	i32 GetID() const { return id; };

	// All Resources forced to overload this function
	// This function should be added to the destructor of each Resource
	virtual void Unload()=0;
};