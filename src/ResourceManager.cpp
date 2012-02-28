#include "ResourceManager.h"
ResourceManager* ResourceManager::resMan = 0;
i32 ResourceManager::idProvider = 0;

ResourceManager& ResourceManager::get() // returns reference to help avoid mucking with pointers
{
	if(!ResourceManager::resMan)
	{
		ResourceManager::resMan = new ResourceManager();
	}
	return *ResourceManager::resMan;
};

void ResourceManager::AddResource(i32 id, const char *name, Resource *r)
{
	r->SetResourceID(id);
	r->SetName(name);
	resourceMap[id] = shared_ptr<Resource>(r);
};