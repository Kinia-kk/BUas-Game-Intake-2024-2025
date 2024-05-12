#include "animator.h"

	void Animator::Update(float deltaTime)
	{
		totalTime += deltaTime;
	}

	unsigned Animator::GetCurrentFrame()
	{
		if(animsprite)
		{
			return static_cast<unsigned int> (totalTime * fps) % animsprite->Frames();
		}
		return 0;
	}

	int Animator::Draw(Tmpl8::Surface* screen, int x, int y)
	{
		if (animsprite && screen)
		{
			animsprite->SetFrame(GetCurrentFrame());
			animsprite->Draw(screen, x, y);
			if (GetCurrentFrame() == animsprite->Frames() - 1)
			{
				totalTime = 0;
				return 1;
			}
		}
		return 0;
	}

	void Animator::ResetAnimation()
	{
		totalTime = 0;
	}


