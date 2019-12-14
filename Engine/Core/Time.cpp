#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Core/Time.hpp>

using namespace Engine;

Time Time::time;

void Time::Init() {

}

void Time::Update() {
	double curr = glfwGetTime();
	time.dt = curr - time.prev;
	time.prev = curr;
}

Time::Time() {

}

Time::~Time() {

}