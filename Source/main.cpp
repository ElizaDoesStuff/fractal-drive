#include "../Dependencies/glad/include/glad/glad.h"
#include "../Dependencies/glfw/include/glfw/glfw3.h"
#include <unordered_map>

GLFWwindow* window;
int width, height;
bool shouldExit = false;

const int heightMapResolution = 256;
unsigned int vbo, vao;
float vertices[heightMapResolution * heightMapResolution * 3] = {0};

std::unordered_map<int, bool> keyStates;

void setUpWindow() {
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	window = glfwCreateWindow(1, 1, "Fractal Drive", nullptr, nullptr);
	glfwMaximizeWindow(window);
	
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

void computeHeightMap() {}

void generateBuffers() {
	float positions[] = {
		0.0, 0.5,
		0.5, 0.0,
		-0.5, 0.0
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), &positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
}

void onPress(int key) {
	switch (key) {
		case GLFW_KEY_ESCAPE: shouldExit = true; break;
	}
}

void onInput(GLFWwindow* eventWindow, int key, int _, int action, int mods) {
	if (eventWindow != window) return;
	if (action == GLFW_PRESS) onPress(key);
	keyStates[key] = !(action == GLFW_RELEASE);
}

void onFrame() {
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glfwSwapBuffers(window);
	glfwPollEvents();
}

int main() {
	glfwInit();
	
	setUpWindow();
	glfwSetKeyCallback(window, &onInput);

	generateBuffers();
	
	while (!glfwWindowShouldClose(window) && !shouldExit) onFrame();
	
	glfwDestroyWindow(window);
	glfwTerminate();
}