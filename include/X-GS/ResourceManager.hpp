// Modified version of ResourceManager.hpp from SFML Game Development Book

#ifndef XGS_RESOURCEMANAGER_HPP
#define XGS_RESOURCEMANAGER_HPP

/*
 ResourcePath.hpp is not provided with X-GS because its
 implementation is OS-dependent.
 You can easily create your own as an envelop of the OS specific
 function to reach the resource folder.
 You can also use the implementation provided with SFML templates
 for specific platforms-OSs (for example, they provide one for
 Xcode in their downloads section of SFML webpage).
 */
#include "ResourcePath.hpp"

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

namespace xgs {
	
	/* Class template to store and manage resources: Textures, sounds, fonts, etc.
	 
	 You can create instances of this resource manager, each of
	 which will store their own resources and have no relation or
	 communication. But there is a static resource map too which
	 can be accessed adding another argument to each method with
	 the value Global (from the enum Scope). This is recommended
	 for storing shared resources among different objects (scenes,
	 entities...) in the game.
	 
	 Local version instances at scenes ensures that each scene will load / free
	 from memory their required resources on creation / destruction
	 of the scene (RAII), while the general (static) resources will last
	 until the game ends or specific unload is invoked.
	 */
	template <typename Resource, typename Identifier>
	class ResourceManager
	{
	public:
		enum Scope
		{
			Global,
			Local
		};
		
		typedef	std::unique_ptr<ResourceManager<Resource, Identifier>> Ptr;
		
		void						load(Identifier id, const std::string& filename, enum Scope = Local);
		
		template <typename Parameter>
		void						load(Identifier id, const std::string& filename, const Parameter& secondParam, enum Scope = Local);
		
		void						unload(Identifier id, enum Scope = Local);
		
		Resource&					get(Identifier id, enum Scope = Local);
		const Resource&				get(Identifier id, enum Scope = Local) const;
				
	private:
		void						insertResource(Identifier id, std::unique_ptr<Resource> resource, enum Scope = Local);
		
		
	private:
		std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap; // Local scope
		static std::map<Identifier, std::unique_ptr<Resource>>	GeneralResourceMap; // Global scope
	};
	
	// Static member definition
	template <typename Resource, typename Identifier>
	std::map<Identifier, std::unique_ptr<Resource>> ResourceManager<Resource, Identifier>::GeneralResourceMap;
	
	
	/////////////////////////////
	// Template implementation //
	/////////////////////////////

	template <typename Resource, typename Identifier>
	void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename, enum Scope scope)
	{
		// Create and load resource
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(resourcePath() + filename))
			throw std::runtime_error("ResourceManager::load - Failed to load " + resourcePath() + filename);
		
		// If loading successful, insert resource to map
		insertResource(id, std::move(resource), scope);
	}
	
	template <typename Resource, typename Identifier>
	template <typename Parameter>
	void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam, enum Scope scope)
	{
		// Create and load resource
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(resourcePath() + filename, secondParam))
			throw std::runtime_error("ResourceManager::load - Failed to load " + resourcePath() + filename);
		
		// If loading successful, insert resource to map
		insertResource(id, std::move(resource), scope);
	}
	
	/* Use unload for special resource management. For general purpose, see description at the beggining of this file. */
	template <typename Resource, typename Identifier>
	void ResourceManager<Resource, Identifier>::unload(Identifier id, enum Scope scope)
	{
		auto found = scope == Local ? mResourceMap.find(id) : GeneralResourceMap.find(id);
		assert(found != (scope == Local ? mResourceMap.end() : GeneralResourceMap.end()));
		mResourceMap.erase(found);
	}
	
	template <typename Resource, typename Identifier>
	Resource& ResourceManager<Resource, Identifier>::get(Identifier id, enum Scope scope)
	{
		auto found = scope == Local ? mResourceMap.find(id) : GeneralResourceMap.find(id);
		assert(found != (scope == Local ? mResourceMap.end() : GeneralResourceMap.end()));
		
		return *found->second;
	}
	
	template <typename Resource, typename Identifier>
	const Resource& ResourceManager<Resource, Identifier>::get(Identifier id, enum Scope scope) const
	{
		auto found = scope == Local ? mResourceMap.find(id) : GeneralResourceMap.find(id);
		assert(found != (scope == Local ? mResourceMap.end() : GeneralResourceMap.end()));
		
		return *found->second;
	}
	
	template <typename Resource, typename Identifier>
	void ResourceManager<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource, enum Scope scope)
	{
		// Insert and check success
		auto inserted = scope == Local ? mResourceMap.insert(std::make_pair(id, std::move(resource))) : GeneralResourceMap.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second);
	}
	
} // namespace xgs

#endif // XGS_RESOURCEMANAGER_HPP
