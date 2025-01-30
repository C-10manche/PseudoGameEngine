#pragma once

#include "Scene/Scene.h"

struct GLFWwindow;

class Engine {
public:

	Scene* scene;
	GLFWwindow* window;

	float last_frame_time;
	float delta_time;


	Engine();
	~Engine();

	bool init();
	void load_scene(Scene* scene);
	void run();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void set_max_fps(int fps);

private:
	float frame_time;
};