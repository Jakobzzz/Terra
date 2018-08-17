////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/Game.hpp>
#include <graphics/Scene.hpp>
#include <utils/Helper.hpp>
#include <utils/Utility.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

namespace px
{
	double timestep = 1.0 / 60.0;
	float stopPosition = 100.f;
	bool stopped = false;

	Game::Game() : m_window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Terra", sf::Style::Close,
							sf::ContextSettings(0U, 0U, 8U)), m_animator(m_animations)
	{
		m_window.setVerticalSyncEnabled(true);
		loadResources();
		sf::Image icon = m_images.GetResource(Textures::Icon);
		m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		initScene();
	}

	Game::~Game()
	{
		m_scene->destroyEntities();
	}

	void Game::loadResources()
	{
		// Textures
		m_images.LoadResource(Textures::Icon, "src/res/icon/dragon.png");
		m_textures.LoadResource(Textures::Monk, "src/res/sprites/playerMonk.png");
		m_textures.LoadResource(Textures::Background, "src/res/sprites/wizardtower.png");

		// Animations
		m_animations.addAnimation(Animations::Player_Monk_Walk_Right, utils::addFrames(m_walkRight, 11, 9), sf::seconds(1.f));
		m_animations.addAnimation(Animations::Player_Monk_Attack_Right, utils::addFrames(m_attackRight, 15, 6), sf::seconds(0.8f));
		m_animator.play() << Animations::Player_Monk_Walk_Right << thor::Playback::loop(Animations::Player_Monk_Walk_Right);
	}

	void Game::initScene()
	{
		m_scene = std::make_unique<Scene>(m_window, m_textures);
		m_scene->createEntity("Background", Textures::Background, sf::Vector2f(0.f, 0.f), 0);
		m_scene->createEntity("Monk", Textures::Monk, PLAYER_BASE_POSITION, 1);
	}

	void Game::pollEvents()
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				m_window.close();
		}
	}

	void Game::update(sf::Time dt)
	{
		Entity monk = m_scene->getEntity("Monk");

		if (monk.component<Render>()->sprite->getPosition().x < stopPosition)
			monk.component<Render>()->sprite->move(sf::Vector2f(60.f, 0.f) * (1.f / 60.f));
		else
		{
			if (!stopped)
			{
				m_animator.stop();
				m_animator.play() << Animations::Player_Monk_Attack_Right << thor::Playback::loop(Animations::Player_Monk_Attack_Right);
				stopped = true;
			}
		}

		m_animator.update(dt);
		m_animator.animate(*monk.component<Render>()->sprite);
	}

	void Game::render()
	{
		m_window.clear();
		m_scene->updateSystems(timestep);
		m_window.display();
	}

	void Game::run()
	{
		sf::Clock clock;

		while (m_window.isOpen())
		{
			pollEvents();
			update(clock.restart());
			render();
		}
	}
}