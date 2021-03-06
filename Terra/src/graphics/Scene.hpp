#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>
#include <graphics/components/Render.hpp>
#include <graphics/components/Animation.hpp>
#include <graphics/components/BoundingBox.hpp>
#include <graphics/components/Transform.hpp>
#include <graphics/components/Minion.hpp>
#include <graphics/components/Text.hpp>
#include <graphics/components/Healthbar.hpp>
#include <graphics/components/Particle.hpp>
#include <utils/ResourceHolder.hpp>
#include <utils/ResourceIdentifiers.hpp>

using namespace entityx;

namespace px
{
	namespace utils { struct GameManager; }

	class Scene : public EntityX
	{
	public:
		explicit Scene(sf::RenderTarget & target, TextureHolder & textures, FontHolder & fonts, utils::GameManager & gameManager,
					   bool & drawDebugData);
		~Scene() = default;

	public:
		Entity createEntity(const std::string & name, Textures::ID texID, const sf::Vector2f & position, 
							const sf::Vector2f & scale = sf::Vector2f(1.f, 1.f), const uint & layer = 0);
		Entity createText(const std::string & name, Fonts::ID fontID, const uint & fontSize, const sf::Vector2f & position, const sf::Color & color = sf::Color::White);
		Entity createParticleSystem(const std::string & filePath, const sf::Vector2f & position);
		void createMinion(const std::string & name, const std::string & type, Textures::ID texID);
		void destroyEntities();
		void updateRenderSystem(TimeDelta dt);
		void updateTransformSystems(TimeDelta dt);

	public:
		Entity getEntity(const std::string & name);

	private:
		void initSystems(sf::RenderTarget & target, bool & drawDebugData);
		void addHealthbars(Entity & entity, const sf::Vector2f & position);

	private:
		EntityManager m_entities;
		EventManager m_events;
		SystemManager m_systems;
		TextureHolder & m_textures;
		FontHolder & m_fonts;
		utils::GameManager & m_gameManager;
		std::vector<uint> m_layers;
	};
}