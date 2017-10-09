#pragma once
//this will manage all of the resources in the game lilke textures, fonts, shaders or sounds
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;

public:
	void load(Identifier id, const std::string& filename);

	template<typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter secondParameter);

	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;

private:
	void insertResource(Identifier id, std::unique_ptr<Resource> resource);
};

#include "Resources.inl"