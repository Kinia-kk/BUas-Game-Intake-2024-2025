#pragma once
#include "surface.h"
	class Animator //based on animator class I saw during C++ Fast Track discord events 
	{
		Tmpl8::Sprite* animsprite = nullptr;
		float totalTime = 0.0f;
		float fps;
	public:
		Animator(Tmpl8::Sprite *sprite, float ffps = 30.0f)
		{
			animsprite = sprite;
			fps = ffps;
		}
		void Update(float deltaTime);
		int Draw(Tmpl8::Surface* screen, int x, int y);
		unsigned int GetCurrentFrame();
		void ResetAnimation();
	};


