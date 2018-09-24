#include "Headers/App.h"

void App::initGLFW() {
	//Inicial GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}
	//Fijar los valores para asociar glfw con la versión de opengl, en este caso, opengl 4.5
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//Se crea la ventana y se inicia el contexto
	window = glfwCreateWindow(screenWidth, screenHeight, windowTitle.c_str(), nullptr, nullptr);
	if (window == nullptr) {
		std::cerr
			<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 4.0+"
			<< std::endl;
		shutdown();
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	//Iniciar método para el manejo de eventos de reshape de ventana
	glfwSetWindowSizeCallback(window, reshapeCallback);
	//Iniciar el método para el manejo del teclado
	glfwSetKeyCallback(window, keyCallback);
	//Iniciar método para el manejo de callbacks de botones del mouse
	glfwSetCursorPosCallback(window, mouseCallback);
	//Iniciar método para el manejo de callbacks de movimientos del mouse
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

}

void App::initGLEW() {
	//estableciendo el uso de glew a verdadero
	glewExperimental = GL_TRUE;
	//iniciando glew
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}
	//fijando el puerto de vista
	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	shader.initialize("../Shaders/mvpColor.vs", "../Shaders/mvpColor.fs");
	glEnable(GL_CULL_FACE);

	cube.init();
	cube.load();
}

void App::startup() {
	initGLFW();
	initGLEW();
}

void App::run() {
	//Loop principal
	while (!glfwWindowShouldClose(window)) {
		//llamar a la funcion para manejar eventos
		glfwPollEvents();
		//Dibujar sobre la ventana con comandos de opengl
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		shader.turnOn();
			// Create transformations
			glm::mat4 view;
			glm::mat4 model;
			glm::mat4 projection;
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			projection = glm::perspective(45.0f, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
			// Get their uniform location
			shader.getUniformLocation("model");
			GLint modelLoc = shader.getUniformLocation("model");
			GLint viewLoc = shader.getUniformLocation("view");
			GLint projLoc = shader.getUniformLocation("projection");
			// Pass the matrices to the shader
			model = glm::toMat4(rotacion);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			cube.render();
		shader.turnOff();
		//Limpieza de buffers
		glfwSwapBuffers(window);

	}
	shutdown();
}

void App::shutdown() {
	cube.~Cube();
	shader.~Shader();
	//Destruir ventana
	glfwDestroyWindow(window);
	//Terminar glfw
	glfwTerminate();
}
 
void App::reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes) {
	App a;
	a.screenWidth = widthRes;
	a.screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}


void App::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//Detectar si se presiono la tecla ESC para cerrar la ventana
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void App::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	//inputManager.mouseMoved(xpos, ypos);
	App a;
	double xoffset = xpos - a.xant;
	double yoffset = ypos - a.yant;
	if (a.inputManager.clicked)
		a.rotacion = glm::angleAxis<float>(xoffset*0.02, glm::vec3(0.0f, 1.0f, 0.0f))*glm::angleAxis<float>(yoffset*0.02, glm::vec3(1.0f, 0.0f, 0.0f))*a.rotacion;
	a.xant = xpos;
	a.yant = ypos;
}

void App::mouseButtonCallback(GLFWwindow* window, int button, int state, int mod) {
	App a;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && state == GLFW_PRESS)
		a.inputManager.mouseClicked(InputManager::MouseCodes::button_right);
	else if (button == GLFW_MOUSE_BUTTON_LEFT && state == GLFW_PRESS)
		a.inputManager.mouseClicked(InputManager::MouseCodes::button_left);
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE && state == GLFW_PRESS)
		a.inputManager.mouseClicked(InputManager::MouseCodes::button_middle);
	if (button == GLFW_MOUSE_BUTTON_LEFT && state == GLFW_PRESS)
		a.inputManager.clicked = true;
	else if (button == GLFW_MOUSE_BUTTON_LEFT && state == GLFW_RELEASE)
		a.inputManager.clicked = false;
}