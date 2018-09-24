#ifndef _APP_H
#define _APP_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Sphere.h"
#include "Shader.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Cube.h"

class App {
	public:
		App(GLuint screenWidth, GLuint screenHeight, std::string windowTitle, bool fullScreen) : 
			screenWidth(screenWidth), screenHeight(screenHeight), windowTitle(windowTitle), fullScreen(fullScreen) {}
		App() {
			this;
		}
		void initGLFW();
		void initGLEW();
		void startup();
		void run();
		void shutdown();
		static void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes);
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
		static void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod);
		
	private:
		double deltaTime, xant, yant;
		GLuint screenWidth, screenHeight;
		std::string windowTitle;
		bool fullScreen;
		glm::quat rotacion;
		GLFWwindow * window;
		InputManager inputManager;
		Shader shader;
		Cube cube = Cube(MODEL_MODE::VERTEX_COLOR);

};
#endif // !_APP_H_


