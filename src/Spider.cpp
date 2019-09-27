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

void Spider::draw(shared_ptr<Program> prog, shared_ptr<MatrixStack> M, float time)
{
	float offset = 0.1;
	M->pushMatrix();
	M->translate(vec3(0, 0.15, 0));
	M->scale(0.1);
	M->pushMatrix(); // body
	M->translate(vec3(0, 0, 1));
	M->scale(vec3(1, 0.7, 1));
	glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
	sphere->draw(prog);
	M->popMatrix();
	float headRadius = 0.7;
	M->pushMatrix(); // head
	M->translate(vec3(0, 0, -0.2));
	drawEyes(prog, M, headRadius - 0.15, offset);
	M->scale(vec3(headRadius, 0.3, headRadius));
	glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
	sphere->draw(prog);
	M->popMatrix();
	drawLegs(prog, M, time);
	M->popMatrix();
}

void Spider::drawEyes(shared_ptr<Program> prog, shared_ptr<MatrixStack> M, float headRadius, float offset)
{
	float eyeSize = 0.025;
	float eyeOffset = eyeSize / 2;
	M->pushMatrix();
	M->translate(vec3(0, 0, -headRadius));
	for (int i = 0; i < 4; ++i) {
		float x = i * 2 * eyeSize - eyeOffset * 3;
		M->pushMatrix();
		M->translate(vec3(x, eyeSize + offset, 0));
		M->scale(vec3(eyeSize));
		glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
		sphere->draw(prog);
		M->popMatrix();
		M->pushMatrix();
		M->translate(vec3(x, -eyeSize + offset, -offset / 2));
		M->scale(vec3(eyeSize));
		glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
		sphere->draw(prog);
		M->popMatrix();
	}
	M->popMatrix();
}

void Spider::drawLegs(shared_ptr<Program> prog, shared_ptr<MatrixStack> M, float time)
{
	float adjustment = M_PI_4 / 2;
	float delta = -M_PI_4 / 2;
	vec3 scale = vec3(0.05, 0.05, 1);
	vec3 translate = vec3(-1, 0, 0);
	M->pushMatrix();
	for (int i = 0; i < 4; ++i) {
		float leg = (i % 2 - 0.5) * 2;
		float timeAdjust = time + delta * i;
		float distanceAdjust = 4.0;
		// float xRot = abs(cos(timeAdjust)) * leg / distanceAdjust;
		// float yRot = adjustment + i * delta + abs(sin(timeAdjust)) * leg / distanceAdjust;
		// float zRot = -adjustment - xRot;
		float xRot = 0;
		float yRot = (sin(timeAdjust) / 8 - adjustment * i) * leg / distanceAdjust;
		float zRot = -abs(cos(timeAdjust)) / distanceAdjust;
		drawLeg(prog, M, vec3(xRot, yRot, zRot), translate, scale);
		drawLeg(prog, M, vec3(xRot, -yRot, -zRot), -translate, scale);
	}
	M->popMatrix();
}

void Spider::drawLeg(shared_ptr<Program> prog, shared_ptr<MatrixStack> M,
	vec3 rotations, vec3 translate, vec3 scale)
{
	M->pushMatrix();
	M->rotate(rotations.y, YAXIS);
	M->rotate(rotations.x, XAXIS);
	M->rotate(rotations.z, ZAXIS);
	M->translate(translate);
	M->pushMatrix();
	M->rotate(M_PI_2, YAXIS);
	M->rotate(M_PI_2, XAXIS);
	M->translate(vec3(0, 0.8 * translate.x, 0.8));
	M->scale(scale);
	glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
	sphere->draw(prog);
	M->popMatrix();
	M->rotate(M_PI_2, YAXIS);
	M->scale(scale);
	glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
	sphere->draw(prog);
	M->popMatrix();
}
