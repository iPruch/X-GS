#ifndef YOURGAME_RESOURCEIDENTIFIERS_HPP
#define YOURGAME_RESOURCEIDENTIFIERS_HPP

#include <X-GS/ResourceManager.hpp>

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	// Add needed forward declarations here
}

// Fill this enumeration with IDs for your textures
namespace Textures
{
	enum ID
	{
		ExamplePlayer,
		ExampleBackground
	};
}

// Fill this enumeration with IDs for your fonts
namespace Fonts
{
	enum ID
	{
		Sansation,
	};
}

// Create new enumerations for new resource types here

typedef xgs::ResourceManager<sf::Texture, Textures::ID>	TextureManager;
typedef xgs::ResourceManager<sf::Font, Fonts::ID>		FontManager;
// Create new typedefs for new resource types here

#endif // YOURGAME_RESOURCEIDENTIFIERS_HPP