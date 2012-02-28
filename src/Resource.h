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

	// if statement gets rid of code warning about unused variable
	// All resources have a load function so we can load thru the resourcemanager
	virtual bool Load(const char* filename) { if(filename){} return true; };
};

typedef std::shared_ptr<Resource> ResourceHandle; // use this format to create handles for other resource types e.g. Texture