#ifndef PYRAMID_H_
#define PYRAMID_H_

#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

#include "definition.h"

class Pyramid {
public:
	Pyramid();
	void load();
	void render();
	virtual ~Pyramid();
	GLuint VAO, VBO;
};

#endif /* CUBE_H_ */


