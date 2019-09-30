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
	float time; // frame time for animation

	/* * * * * * * * * * * * * * * * * * * * * * 
	 *                   NOTE                  *
	 *         x-axis is left and right        *
	 *         y-axis is up and down           *
	 *         z-axis is front and back        *
	 *                                         *
	 * * * * * * * * * * * * * * * * * * * * * */

	
	float size = 0.1;
	vec3 location = vec3(0);

	// ----------- head variables -------------- //
	float headRadius = 0.7; // radius of head from top-down view
	float headHeight = headRadius / 2; // distance from center of head to top

	// ----------- eye variables ------------- //
	float eyeToHeadDistance = headRadius; // -0.15; // random adjustment to align eyes to surface of head.
	float eyeOffset = 0.1; // offset from center horizontal line of spider head to center of eyes
	float eyeSize = 0.025;
	float eyeDistances = eyeSize / 2; // distance between each eye

	// ----------- leg variables ------------- //
	vec3 sphereToLegScale = vec3(0.05, 0.05, 1);
	float legBendAngle = M_PI_2; // angle of leg joint
	vec3 legOrigin = vec3(-1, 0, 0); // center point where left legs come out of


	// ----------- Functions -------------- //
	void initialize(shared_ptr<Shape> sphere);
	void draw(shared_ptr<Program> prog, shared_ptr<MatrixStack> M);
	void drawEyes(shared_ptr<Program> prog, shared_ptr<MatrixStack> M);
	void drawLegs(shared_ptr<Program> prog, shared_ptr<MatrixStack> M);
	void drawLeg(shared_ptr<Program> prog, shared_ptr<MatrixStack> M,
		vec3 rotations, vec3 translate);

	vec3 defaultLegRotations(int legNum);
};