#include "Headers/Cube.h"

Cube::Cube() {
}

Cube::~Cube() {

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);

	
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);

}

void Cube::load() {
	//index = new GLuint[36];
	// Set up vertex data (and buffer(s)) and attribute pointers
	VertexColor vertices[36] = {
		// Back face
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 1.0f) }, //P8
	{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f) },	//P7
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f) },//P6
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0) },	//P6
	{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f) },	//P5
	{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 1.0) },	//P8
																	// Front face
	{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) },	//P3
	{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 1.0f) },	//P4
	{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f) },	//P1
	{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0) },	//P1
	{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f) },//P2
	{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0) },	//P3
																	// Left face
	{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 1.0f) }, //P4
	{ glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec3(0.0f, 1.0f, 0.0f) }, //P5
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f) }, //P6
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0) }, //P6
	{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f) }, //P1
	{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 1.0) }, //P4
																  // Right face
	{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, //P3
	{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f) }, //P2
	{ glm::vec3(0.5f, -0.5f, -0.5f),glm::vec3(0.0f, 1.0f, 0.0f) }, //P7 
	{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 0.0) }, //P7
	{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 1.0f) }, //P8
	{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0) }, //P3
																 // Bottom face
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f) }, //P6
	{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f) }, //P7
	{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f) }, //P2
	{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f) }, //P2
	{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f) }, //P1
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f) }, //P6
																	 // Top face
	{ glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 0.0f) }, //P5
	{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 1.0f) },	//P4
	{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, //P3
	{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0) }, //P3
	{ glm::vec3(0.5f, 0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 1.0f) }, //P8
	{ glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 0.0) } //P5
	};
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
		(GLvoid*) sizeof(vertices[0].position));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}

void Cube::render() {

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);

}

