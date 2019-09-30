#include "Spider.h"
#include "Constants.h"


using namespace std;
using namespace glm;



Spider::Spider()
{
}


Spider::~Spider()
{
}

void Spider::initialize(shared_ptr<Shape> sphere)
{
	this->sphere = sphere;
}

void Spider::draw(shared_ptr<Program> prog, shared_ptr<MatrixStack> M)
{
	M->pushMatrix();
		M->translate(location);
		M->scale(size);

		M->pushMatrix(); // body
			M->translate(vec3(0, 0, 1));
			M->scale(vec3(1, 0.7, 1));
			glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
			sphere->draw(prog);
		M->popMatrix();
		M->pushMatrix(); // head
			M->translate(vec3(0, 0, -0.2));
			drawEyes(prog, M);
			M->scale(vec3(headRadius, headHeight, headRadius));
			glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
			sphere->draw(prog);
			M->popMatrix();
		drawLegs(prog, M);
	M->popMatrix();
}

void Spider::drawEyes(shared_ptr<Program> prog, shared_ptr<MatrixStack> M)
{
	M->pushMatrix();
	M->translate(vec3(0, 0, -eyeToHeadDistance));
	for (int i = 0; i < 4; ++i) {
		float x = i * 2 * eyeSize - eyeDistances * 3;
		M->pushMatrix();
			M->translate(vec3(x, eyeSize + eyeOffset, 0));
			M->scale(vec3(eyeSize));
			glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
			sphere->draw(prog);
		M->popMatrix();
		M->pushMatrix();
			M->translate(vec3(x, -eyeSize + eyeOffset, -eyeOffset / 2));
			M->scale(vec3(eyeSize));
			glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
			sphere->draw(prog);
		M->popMatrix();
	}
	M->popMatrix();
}

void Spider::drawLegs(shared_ptr<Program> prog, shared_ptr<MatrixStack> M)
{
	float adjustment = M_PI_4 / 2;
	float delta = -M_PI_4 / 2;
	vec3 rotations;
	M->pushMatrix();
	for (int i = 0; i < 4; ++i) {
		rotations = defaultLegRotations(i);
		drawLeg(prog, M, rotations, legOrigin); // left leg
		drawLeg(prog, M, vec3(rotations.x, -rotations.y, -rotations.z), -legOrigin); // right leg
	}
	M->popMatrix();
}

void Spider::drawLeg(shared_ptr<Program> prog, shared_ptr<MatrixStack> M,
	vec3 rotations, vec3 translate)
{
	M->pushMatrix();
		M->rotate(rotations.y, YAXIS);
		M->rotate(rotations.x, XAXIS);
		M->rotate(rotations.z, ZAXIS);
		M->translate(translate);
		M->pushMatrix();
			M->rotate(M_PI_2, YAXIS);
			M->rotate(M_PI_2, XAXIS);
			M->translate(vec3(0, translate.x, 1));
			M->scale(sphereToLegScale);
			glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
			sphere->draw(prog);
		M->popMatrix();
		M->rotate(legBendAngle, YAXIS);
		M->scale(sphereToLegScale);
		glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
		sphere->draw(prog);
	M->popMatrix();
}

vec3 Spider::defaultLegRotations(int legNum)
{
	float adjustment = M_PI / 8;
	float delta = -M_PI / 8;
	float leg = (legNum % 2 - 0.5) * 2;
	float timeAdjust = time + delta * legNum;
	float distanceAdjust = 4.0;

	// default rotation formula
	float xRot = 0;
	float yRot = (sin(timeAdjust) / 8 - adjustment * legNum) * leg / distanceAdjust;
	float zRot = -abs(cos(timeAdjust)) / distanceAdjust;
	return vec3(xRot, yRot, zRot);
}
