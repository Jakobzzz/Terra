#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Thor/Animations/FrameAnimation.hpp>

namespace px
{
	namespace utils
	{
		// Note: row starts from 0
		inline thor::FrameAnimation addFrames(thor::FrameAnimation & anim, int row, int frames, int pxSize = 64, float duration = 1.f)
		{
			for (int i = 0; i < frames * pxSize; i += pxSize)
				anim.addFrame(duration, sf::IntRect(i, row * pxSize, pxSize, pxSize));

			return anim;
		}
	}
}