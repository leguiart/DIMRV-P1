#include "Headers/Cylinder.h"

Cylinder::Cylinder(float ratio, float height, int slices, MODEL_MODE mode) :
	ratio(ratio), height(height) ,slices(slices), VAO(0), VBO(0), EBO(0), mode(
		mode) {
}

Cylinder::~Cylinder() {

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDeleteBuffers(1, &EBO);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);

}

void Cylinder::init() {
	if (mode == MODEL_MODE::VERTEX_COLOR)
		vertexC.resize((slices) * 2 + 2);
	index.resize((slices) * 12);
	//index2.resize(slices + 1);
	
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < slices; ++j) {
			float theta = j * 2 * M_PI / (float)slices;
			float Y;
			float X = ratio * cos(theta);
			if (i == 0)
				Y = -height/2;
			else
				Y = height/2;
			float Z = ratio * sin(theta);
			//std::cout << X << ", " << Y << ", " << Z << std::endl;
			if (mode == MODEL_MODE::VERTEX_COLOR) {
				vertexC[i * slices + j].position = glm::vec3(X, Y, Z);
				vertexC[i * slices + j].color = glm::sphericalRand(1.0);
			}
		}
	}

	vertexC[(slices) * 2].position = glm::vec3(0.0, -height/2, 0.0);
	vertexC[(slices) * 2 + 1].position = glm::vec3(0.0, height/2, 0.0);
	vertexC[(slices) * 2].color = glm::sphericalRand(1.0);
	vertexC[(slices) * 2 + 1].color = glm::sphericalRand(1.0);

	for (int i = 0; i < slices; ++i) {
		if (i < slices - 1) {
			index[i * 12] = i + 1; //+ 2;
			index[i * 12 + 1] = i; //+ 2;
			index[i * 12 + 2] = i + slices; //+ 3;
			index[i * 12 + 3] = i + slices; //+ 3;
			index[i * 12 + 4] = i + slices + 1; //+ 4;
			index[i * 12 + 5] = i + 1; //+ 2;
		}
		else {
			index[i * 12] = 0; //+ 2;
			index[i * 12 + 1] = i; //+ 2;
			index[i * 12 + 2] = i + slices; //+ 3;
			index[i * 12 + 3] = i + slices; //+ 3;
			index[i * 12 + 4] = slices; //+ 4;
			index[i * 12 + 5] = 0; //+ 2;
		}
		index[i * 12 + 6] = index[i * 12 + 1];
		index[i * 12 + 7] = index[i * 12];
		index[i * 12 + 8] = slices * 2;
		index[i * 12 + 9] = index[i * 12 + 2];
		index[i * 12 + 10] = slices * 2 + 1;
		index[i * 12 + 11] = index[i * 12 + 4];
		//std::cout << index[i * 6] << ", " << index[i * 6 + 1] << ", " << index[i * 6 + 2] << ", "<< index[i * 6 + 3] << ", " << index[i * 6 + 4] << ", " << index[i * 6 + 5] <<std::endl;
		//std::cout << index[i * 6 + 6] << ", " << index[i * 6 + 7] << ", " << index[i * 6 + 8] << ", " << index[i * 6 + 9] << ", " << index[i * 6 + 10] << ", " << index[i * 6 + 11] << std::endl;
	}

}

void Cylinder::load() {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	size_t stride;

	size_t offset1 = 0;
	size_t offset2 = 0;
	size_t offset3 = 0;

	if (mode == MODEL_MODE::VERTEX_COLOR) {
		glBufferData(GL_ARRAY_BUFFER, vertexC.size() * sizeof(glm::vec3) * 2,
			vertexC.data(),
			GL_STATIC_DRAW);
		stride = sizeof(vertexC[0]);
		offset1 = 0;
	}
	else if (mode == MODEL_MODE::VERTEX_LIGHT_COLOR) {
		glBufferData(GL_ARRAY_BUFFER, vertexLC.size() * sizeof(glm::vec3) * 3,
			vertexLC.data(),
			GL_STATIC_DRAW);
		stride = sizeof(vertexLC[0]);
		offset1 = 0;
		offset2 = sizeof(vertexLC[0].position);
		offset3 = sizeof(vertexLC[0].position) + sizeof(vertexLC[0].color);
	}
	else if (mode == MODEL_MODE::VERTEX_LIGHT_TEXTURE) {
		glBufferData(GL_ARRAY_BUFFER,
			vertexLT.size() * (sizeof(glm::vec3) * 2 + sizeof(glm::vec2)),
			vertexLT.data(),
			GL_STATIC_DRAW);
		stride = sizeof(vertexLT[0]);
		offset1 = 0;
		offset2 = sizeof(vertexLT[0].position);
		offset3 = sizeof(vertexLT[0].position) + sizeof(vertexLT[0].texture);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(GLuint),
		index.data(),
		GL_STATIC_DRAW);

	// First attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset1);
	glEnableVertexAttribArray(0);
	// Second attribute
	if (mode == MODEL_MODE::VERTEX_LIGHT_TEXTURE)
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride,
		(GLvoid*)offset2);
	else
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
		(GLvoid*)offset2);
	glEnableVertexAttribArray(1);
	// Thrid attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset3);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

}

void Cylinder::render() {

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_INT,
		(GLvoid*)(sizeof(GLuint) * 0));
	glBindVertexArray(0);

}

