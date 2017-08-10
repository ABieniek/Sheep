#ifndef COLLISION_UTIL_H
#define COLLISION_UTIL_H

#include "Unit.h"

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif //_USE_MATH_DEFINES
#include <math.h>

using namespace std;

// I'm gonna handle Unit Collision by using circular hurtboxes for the units
// the radius will just be half of one of their sides


GLboolean doesPenetrate(glm::vec2 position1, GLfloat radius1, glm::vec2 position2, GLfloat radius2);
GLboolean doesPenetrate(Unit* unit1, Unit* unit2);
glm::vec2 penetrationVector(glm::vec2 position1, GLfloat radius1, glm::vec2 position2, GLfloat radius2);
glm::vec2 penetrationVector(Unit* unit1, Unit* unit2);

GLfloat norm(glm::vec2 vec);
GLfloat norm(glm::vec3 vec);

// angle stuff
GLfloat AngleDiff(GLfloat argAngle1, GLfloat argAngle2);
GLfloat boundNegPiToPi(GLfloat argAngle);

#endif
