////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/Scene.hpp>
#include <graphics/systems/RenderSystem.hpp>
#include <graphics/systems/AnimationSystem.hpp>
#include <graphics/systems/TransformSystem.hpp>
#include <graphics/systems/CollisionSystem.hpp>
#include <graphics/systems/MinionSystem.hpp>
#include <utils/GameManager.hpp>

namespace px
{
	Scene::Scene(sf::RenderTarget & target, TextureHolder & textures, FontHolder & fonts, utils::GameManager & gameManager) : m_entities(m_events),
				 m_systems(m_entities, m_events), m_textures(textures), m_fonts(fonts), m_gameManager(gameManager)
	{
		m_layers = { 0, 1 };
		initSystems(target);
	}

	Entity Scene::createEntity(const std::string & name, Textures::ID texID, const sf::Vector2f & position, const uint & layer)
	{
		auto entity = m_entities.create();
		auto sprite = std::make_unique<sf::Sprite>(m_textures.GetResource(texID));
		sprite->setPosition(position);
		entity.assign<Transform>(position);
		entity.assign<Render>(std::move(sprite), name, layer);
		return entity;
	}

	Entity Scene::createText(const std::string & name, Fonts::ID fontID, const uint & fontSize, const sf::Vector2f & position, const sf::Color & color)
	{
		// Change origin?
		auto entity = m_entities.create();
		auto text = std::make_unique<sf::Text>(name, m_fonts.GetResource(fontID), fontSize);
		text->setFillColor(color);
		text->setPosition(position);
		entity.assign<Transform>(position);
		entity.assign<Text>(std::move(text));
		return entity;
	}

	void Scene::createMinion(const std::string & name, Textures::ID texID)
	{
		// Better to store data in a json file instead?
		if (name == "Player")
		{
			auto entity = createEntity(name, texID, PLAYER_BASE_POSITION, 1);
			entity.assign<Animation>();
			entity.assign<BoundingBox>(sf::Vector2f(30.f, 52.f), sf::Vector2f(15.f, 11.f));
			entity.assign<Minion>(60.f, sf::Vector2f(60.f, 40.f));
			auto anim = entity.component<Animation>();

			if (texID == Textures::Monk)
			{
				anim->animations->addAnimation("idle", 11, 1);
				anim->animations->addAnimation("walk", 11, 9);
				anim->animations->addAnimation("attack", 15, 6, sf::seconds(0.8f));
				anim->animations->playAnimation("walk", true);
				m_gameManager.playerGold -= m_gameManager.playerMonkCost;
			}
		}
		else if (name == "Enemy")
		{
			auto entity = createEntity(name, texID, ENEMY_BASE_POSITION, 1);
			entity.assign<Animation>();
			entity.assign<BoundingBox>(sf::Vector2f(40.f, 54.f), sf::Vector2f(11.f, 10.f));
			entity.assign<Minion>(-60.f, sf::Vector2f(0.f, 0.f));
			auto anim = entity.component<Animation>();

			if (texID == Textures::SpearOrc)
			{
				anim->animations->addAnimation("idle", 9, 1);
				anim->animations->addAnimation("walk", 9, 9);
				anim->animations->addAnimation("attack", 5, 8, sf::seconds(0.8f));
				anim->animations->playAnimation("walk", true);
			}
		}
	}

	void Scene::destroyEntities()
	{
		ComponentHandle<Render> render;

		for (auto entity : m_entities.entities_with_components(render))
			entity.destroy();
	}

	void Scene::updateRenderSystem(TimeDelta dt)
	{
		m_systems.update<RenderSystem>(dt);
	}

	void Scene::updateTransformSystems(TimeDelta dt)
	{
		m_systems.update<MinionSystem>(dt);
		m_systems.update<TransformSystem>(dt);
		m_systems.update<AnimationSystem>(dt);
		m_systems.update<CollisionSystem>(dt);
	}

	Entity Scene::getEntity(const std::string & name)
	{
		ComponentHandle<Render> render;
		Entity found;

		for (Entity entity : m_entities.entities_with_components(render))
			if (render->name == name)
				found = entity;

		return found;
	}

	void Scene::initSystems(sf::RenderTarget & target)
	{
		m_systems.add<RenderSystem>(target, m_layers);
		m_systems.add<TransformSystem>();
		m_systems.add<AnimationSystem>();
		m_systems.add<CollisionSystem>();
		m_systems.add<MinionSystem>();
		m_systems.configure();
	}
}