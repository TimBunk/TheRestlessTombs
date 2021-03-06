#ifndef WINDOW_H
#define WINDOW_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <math.h>
#include <vector>

#include "resourceManager.h"
#include "scene.h"
#include "camera.h"
#include "text.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Window {
public:
	Window(int screenWidth, int screenHeight, const char* screenName, bool fullScreen);
	virtual ~Window();

	static float m2p;
	static float p2m;

	void Update();
	void ClearWindow();
	void SwapBuffers();

	Camera* GetCamera();
	Input* GetInput();
	ResourceManager* GetResourceManager();
	double GetDeltaTime();

	// The color ranges from 0 to 1
	void SetBackgroundColor(glm::vec3 backgroundColor);

private:
	void CalculateFrameRate();

	SDL_Window* window;
	SDL_GLContext glContext;
	glm::vec3 backgroundColor;

	Camera* camera;
	Input* input;
	ResourceManager* rm;

	double deltaTime;
	Uint64 lastFrame;
	double totalTime;
	int fpsCount;
};

#endif // !WINDOW_H
