#pragma once

#include <iostream>
#include <glad/glad.h>
#include <time.h>

#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"
#include "Shape.h"
#include "WindowManager.h"
#include "GLTextureWriter.h"

// value_ptr for glm
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "stb_image.h"


using namespace std;
using namespace glm;

class Spider
{
public:
	Spider();
	~Spider();

	shared_ptr<Shape> sphere;
	shared_ptr<MatrixStack> M;


	void initialize(shared_ptr<Shape> sphere);
	void draw(shared_ptr<Program> prog, shared_ptr<MatrixStack> M, float time);
	void drawEyes(shared_ptr<Program> prog, shared_ptr<MatrixStack> M, float headRadius, float offset);
	void drawLegs(shared_ptr<Program> prog, shared_ptr<MatrixStack> M, float time);
	void drawLeg(shared_ptr<Program> prog, shared_ptr<MatrixStack> M,
		vec3 rotations, vec3 translate, vec3 scale);
};