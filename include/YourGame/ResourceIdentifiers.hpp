#ifndef XGS_RESOURCEIDENTIFIERS_HPP
#define XGS_RESOURCEIDENTIFIERS_HPP

#include <X-GS/ResourceManager.hpp>

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
}

// Fill this enumeration with your textures IDs
namespace Textures
{
	enum ID
	{
		ExamplePlayer,
	};
}

// Fill this enumeration with your fonts IDs
namespace Fonts
{
	enum ID
	{
		Sansation,
	};
}

// Create new enumerations for new resource types

typedef xgs::ResourceManager<sf::Texture, Textures::ID>	TextureManager;
typedef xgs::ResourceManager<sf::Font, Fonts::ID>		FontManager;
// Create new typedefs for new resource types

#endif // XGS_RESOURCEIDENTIFIERS_HPP