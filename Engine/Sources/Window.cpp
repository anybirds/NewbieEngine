#include <Window.hpp>
#include <Debug.hpp>

using namespace std;
using namespace Engine;

void Window::Initialize() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
#ifdef DEBUG_GRAPHICS
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	GLint flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(Debug::GraphicsErrorLog, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
#endif
}

void Window::Terminate() {
	glfwTerminate();
}

void Window::glewInit() {
	GLenum glew_error = ::glewInit();
	if (glew_error != GLEW_OK) {
		// Initializing GLEW failed
		cout << "[glewInit] message: " << glewGetErrorString(glew_error) << '\n';
		exit(1);
	}
}

Window::Window() {
	monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);
	window = glfwCreateWindow(mode->width, mode->height, "No Title", monitor, NULL);
	glfwMakeContextCurrent(window);

	Window::glewInit();
}

Window::Window(const std::string &name) 
	: name(name) {
	monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);
	window = glfwCreateWindow(mode->width, mode->height, name.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);

	Window::glewInit();
}

Window::Window(int width, int height, std::string name) 
	: width(width), height(height), name(name) {
	monitor = glfwGetPrimaryMonitor();
	window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);

	Window::glewInit();
}

Window::~Window() {
	glfwDestroyWindow(window);
}

void Window::SetActive() {
	glfwMakeContextCurrent(window);
}

void Window::Viewport(int viewport_x, int viewport_y, int viewport_width, int viewport_height) {
	this->viewport_x = viewport_x;
	this->viewport_y = viewport_y;
	this->viewport_width = viewport_width;
	this->viewport_height = viewport_height;

	glViewport(viewport_x, viewport_y, viewport_width, viewport_height);
}

bool Window::Closed() {
	return static_cast<bool>(glfwWindowShouldClose(window));
}

void Window::SwapBuffers() {
	glfwSwapBuffers(window);
}