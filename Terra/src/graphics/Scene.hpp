#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>
#include <graphics/components/Render.hpp>
#include <graphics/components/Animation.hpp>
#include <utils/ResourceHolder.hpp>
#include <utils/ResourceIdentifiers.hpp>

using namespace entityx;

namespace sf
{
	class RenderTarget;
}

namespace px
{
	class Scene : public EntityX
	{
	public:
		explicit Scene(sf::RenderTarget & target, TextureHolder & textures);
		~Scene() = default;

	public:
		Entity createEntity(const std::string & name, Textures::ID texID, const sf::Vector2f & position, const uint & layer = 0);
		void destroyEntities();
		void updateRenderSystem(TimeDelta dt);
		void updateAnimationSystem(TimeDelta dt);

	public:
		EntityManager & getEntities();
		Entity getEntity(const std::string & name);

	private:
		void initSystems(sf::RenderTarget & target);

	private:
		EntityManager m_entities;
		EventManager m_events;
		SystemManager m_systems;
		TextureHolder & m_textures;
		std::vector<uint> m_layers;
	};
}