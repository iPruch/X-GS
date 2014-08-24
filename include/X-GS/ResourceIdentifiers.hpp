#ifndef XGS_RESOURCEIDENTIFIERS_HPP
#define XGS_RESOURCEIDENTIFIERS_HPP

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

// Forward declaration and a few type definitions
//template <typename Resource, typename Identifier>
//class ResourceManager; Not included and doesn't need forward declaration??

typedef ResourceManager<sf::Texture, Textures::ID>	TextureManager;
typedef ResourceManager<sf::Font, Fonts::ID>		FontManager;
// Create new typedefs for new resource types

#endif // XGS_RESOURCEIDENTIFIERS_HPP