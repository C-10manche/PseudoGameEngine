#pragma once   
class GameObject;

class Component {
public:
	GameObject* game_object;

	Component();

	virtual ~Component();

	virtual void ready();

	virtual void update(float delta_time);
};