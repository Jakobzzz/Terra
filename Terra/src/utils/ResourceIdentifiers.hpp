#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>

namespace Textures
{
	enum ID
	{
		Icon,
		Background,
		HealthbarBackground,
		Healthbar,
		Monk,
		SpearOrc
	};
}

namespace Fonts
{
	enum ID
	{
		Game
	};
}

namespace px
{
	namespace utils
	{
		template <typename Resource, typename Identifier>
		class ResourceHolder;
	}
}

using TextureHolder = px::utils::ResourceHolder<sf::Texture, Textures::ID>;
using ImageHolder = px::utils::ResourceHolder<sf::Image, Textures::ID>;
using FontHolder = px::utils::ResourceHolder<sf::Font, Fonts::ID>;