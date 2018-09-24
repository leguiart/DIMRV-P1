#ifndef CUBE_H_
#define CUBE_H_

#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

#include "definition.h"

class Cube {
public:
	Cube();
	void load();
	void render();
	virtual ~Cube();
	GLuint VAO, VBO;
};

#endif /* CUBE_H_ */

