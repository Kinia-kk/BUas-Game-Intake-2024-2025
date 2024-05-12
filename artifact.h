#pragma once
#include "item.h"
#include "animator.h"
class Artifact :
    public Item
{
public:
    Animator* Animation;
    Artifact(int xx, int yy) {
        ItemSprite =  new Tmpl8::Sprite(new Tmpl8::Surface("assets/artefact.png"), 8);
        Animation = new Animator(ItemSprite, 10.0f);
        x = xx;
        x2 = ItemSprite->GetWidth() + xx;
        y = yy;
        y2 = ItemSprite->GetHeight() + yy;
    }
    ~Artifact() {
       delete ItemSprite;
       ItemSprite = nullptr;
    }
    bool Manage(Tmpl8::Surface* screen, Player& player, int& click, float deltaTime, int mousex, int mousey);
};

