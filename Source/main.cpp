#include "../Dependencies/glad/include/glad/glad.h"
#include "../Dependencies/glfw/include/glfw/glfw3.h"

GLFWwindow* window;

void setUpWindow() {
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);
}

void onFrame() {
	
}

int main() {
	glfwInit();
	setUpWindow();
	
	while (!glfwWindowShouldClose(window)) onFrame();
	glfwTerminate();
}