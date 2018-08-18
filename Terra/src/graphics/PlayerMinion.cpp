////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/PlayerMinion.hpp>
#include <graphics/Scene.hpp>
#include <utils/Utility.hpp>

namespace px
{
	PlayerMinion::PlayerMinion(Scene & scene) : m_scene(scene), m_isAttacking(false)
	{
		m_minion = m_scene.createEntity("Monk", Textures::Monk, PLAYER_BASE_POSITION, 1);
		m_minion.assign<Animation>();
	}

	void PlayerMinion::attack()
	{
		if (m_minion.component<Render>()->sprite->getPosition().x < 100.f) // 100.f is a test for now
			m_minion.component<Render>()->sprite->move(sf::Vector2f(60.f, 0.f) * (1.f / 60.f));
		else
		{
			if (!m_isAttacking)
			{
				m_minion.component<Animation>()->animator.stop();
				playAnimation(Animations::Player_Monk_Attack_Right, true);
				m_isAttacking = true;
			}
		}
	}

	void PlayerMinion::addAnimation(Animations::ID id, int row, int frames, sf::Time duration)
	{
		thor::FrameAnimation frameAnim;
		m_minion.component<Animation>()->animations.addAnimation(id, utils::addFrames(frameAnim, row, frames), duration);
	}

	void PlayerMinion::playAnimation(Animations::ID id, bool repeat)
	{
		repeat ? m_minion.component<Animation>()->animator.play() << id << thor::Playback::loop(id) : m_minion.component<Animation>()->animator.play();
	}
}