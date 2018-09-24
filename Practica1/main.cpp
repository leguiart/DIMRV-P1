//glew include
#include <GL/glew.h>

//std includes
#include <string>
#include <iostream>

//glfw include
#include <GLFW/glfw3.h>

// program include
#include "Headers/InputManager.h"
#include "Headers/TimeManager.h"
#include "Headers/Shader.h"
#include "Headers/Sphere.h"
#include "Headers/Cube.h"
#include "Headers/Pyramid.h"
#include "Headers/Cylinder.h"

GLuint VBO, VAO;
Shader shader;

int screenWidth;
int screenHeight;

double xant, yant, deltaTime;
glm::quat rotacion;

GLFWwindow * window;
InputManager inputManager;
float rot = 0;
bool activa_anim = true, cambia_color = true, activa_esfera = false,  activa_piramide = true, activa_cubo = false, activa_cilindro = false;
glm::vec3 color;
Sphere sp = Sphere(1.0, 40, 40, MODEL_MODE::VERTEX_COLOR);
Cube cube;
Pyramid p;
Cylinder c = Cylinder(1.0, 2.4, 40, MODEL_MODE::VERTEX_COLOR);

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod);
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroyWindow();
void destroy();
bool processInput(bool continueApplication = true);

// Implementacion de todas las funciones.
void init(int width, int height, std::string strTitle, bool bFullScreen) {

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	screenWidth = width;
	screenHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(),
			glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr,
			nullptr);

	if (window == nullptr) {
		std::cerr
			<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
			<< std::endl;
		destroyWindow();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetWindowSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	shader.initialize("../Shaders/mvpColor.vs", "../Shaders/mvpColor.fs");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	sp.init();
	sp.load();
	c.init();
	c.load();
	cube.load();
	p.load();

}
void destroyWindow() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void destroy() {
	destroyWindow();
	shader.destroy();
	sp.~Sphere();
	cube.~Cube();
	p.~Pyramid();
	c.~Cylinder();
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	inputManager.keyPressed(inputManager.toApplicationKey(key), deltaTime,
		inputManager.toApplicationState(action));
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
		activa_anim = !activa_anim;
	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
		cambia_color = true;
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		activa_esfera = true; activa_cubo = false; activa_piramide = false; activa_cilindro = false;
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		activa_cubo = true; activa_esfera = false; activa_piramide = false; activa_cilindro = false;
	}
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		activa_piramide = true; activa_cubo = false; activa_esfera = false; activa_cilindro = false;
	}
	if (key == GLFW_KEY_O && action == GLFW_PRESS) 
	{
		activa_esfera = false; activa_cubo = false; activa_piramide = false; activa_cilindro = true;
	}
	
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	//inputManager.mouseMoved(xpos, ypos);

	double xoffset = xpos - xant;
	double yoffset = ypos - yant;
	if (inputManager.clicked)
		rotacion = glm::angleAxis<float>(xoffset*0.02, glm::vec3(0.0f, 1.0f, 0.0f))*glm::angleAxis<float>(yoffset*0.02, glm::vec3(1.0f, 0.0f, 0.0f))*rotacion;
	xant = xpos;
	yant = ypos;
}

void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT && state == GLFW_PRESS)
		inputManager.mouseClicked(InputManager::MouseCodes::button_right);
	else if (button == GLFW_MOUSE_BUTTON_LEFT && state == GLFW_PRESS)
		inputManager.mouseClicked(InputManager::MouseCodes::button_left);
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE && state == GLFW_PRESS)
		inputManager.mouseClicked(InputManager::MouseCodes::button_middle);
	if (button == GLFW_MOUSE_BUTTON_LEFT && state == GLFW_PRESS)
		inputManager.clicked = true;
	else if (button == GLFW_MOUSE_BUTTON_LEFT && state == GLFW_RELEASE)
		inputManager.clicked = false;
}

bool processInput(bool continueApplication) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
		|| glfwWindowShouldClose(window) != 0) {
		return false;
	}
	deltaTime = 1 / TimeManager::Instance().CalculateFrameRate(false);
	glfwPollEvents();
	inputManager.do_movement(deltaTime);
	return continueApplication;
}

void applicationLoop() {
	bool psi = true;
	double lastTime = TimeManager::Instance().GetTime();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (psi) {
		psi = processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(activa_anim)
			rot += 0.001;
		GLfloat timeValue = TimeManager::Instance().GetTime() - lastTime;
		
		shader.turnOn();

		//GLfloat timeValue = TimeManager::Instance().GetTime() - lastTime;

		// Create transformations
		glm::mat4 view;
		glm::mat4 model;
		glm::mat4 projection;
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f + inputManager.zoom));
		projection = glm::perspective(45.0f, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		// Get their uniform location
		shader.getUniformLocation("model");
		GLint modelLoc = shader.getUniformLocation("model");
		GLint viewLoc = shader.getUniformLocation("view");
		GLint projLoc = shader.getUniformLocation("projection");
		if (cambia_color) {
			color = glm::vec3(glm::cos(timeValue * 5 + deltaTime) + 0.2, glm::sin(timeValue * 10) + 0.2, glm::sin(timeValue * 5 + deltaTime) + 0.2);
			cambia_color = false;
		}
		
		// Pass the matrices to the shader
		model = glm::rotate(glm::toMat4(rotacion), rot, glm::vec3(1.0, 0.5, 0.3));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3fv(shader.getUniformLocation("color"), GL_TRUE, glm::value_ptr(color));
		if (activa_esfera)
		{
			sp.render();
		}
		else if (activa_cubo) {
			cube.render();
		}
		else if (activa_piramide)
		{
			p.render();
		}
		else if (activa_cilindro)
		{
			c.render();
		}
		
			

		shader.turnOff();

		glfwSwapBuffers(window);

	}
}

int main(int argc, char ** argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}



/*#include "Headers/App.h"

int main(int argc, char ** argv) {
	App app = App(800, 700, "Window GLFW", false);
	app.run();
	app.shutdown();
	return 1;
}
*/

