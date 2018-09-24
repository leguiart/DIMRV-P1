#ifndef CYLINDER_H_
#define CYLINDER_H_

#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

#include "definition.h"

class Cylinder {
public:
	Cylinder(float ratio, float height, int slices, MODEL_MODE mode);
	void init();
	void load();
	void render();
	virtual ~Cylinder();
private:
	std::vector<VertexColor> vertexC;
	std::vector<VertexLightColor> vertexLC;
	std::vector<VertexLightTexture> vertexLT;
	std::vector<GLuint> index;
	float ratio, height;
	int slices;
	MODEL_MODE mode;

	GLuint VAO, VBO, EBO;
};

#endif /* SPHERE_H_ */

