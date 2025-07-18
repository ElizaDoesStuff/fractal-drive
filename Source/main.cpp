// This code is free for all use, provided it is properly attributed to the author, Eliza Toucan-Ostrich.
// For more information, please visit https://github.com/users/ElizaDoesStuff/ElizaDoesStuff/using-my-code.txt
/////////////////////////////////////////////////

#include "../Dependencies/glad/include/glad/glad.h"
#include "../Dependencies/glfw/include/glfw/glfw3.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

/////////////////////////////////////////////////

// Config Option Enums
enum fsModes { BORDERLESS, FULLSCREEN, WINDOWED };

// Configuration Settings
const int fullScreenMode = fsModes::WINDOWED;
const int heightMapResolution = 10;

/////////////////////////////////////////////////

// Window Globals
GLFWwindow* window;
GLFWmonitor* monitor;
int width, height;
bool shouldExit = false;

// HeightMap Globals
float heightMapVertices[heightMapResolution * heightMapResolution];
const int heightMapTriCount = (heightMapResolution - 1) * (heightMapResolution - 1) * 2;
int heightMapMesh[heightMapTriCount];

// Vertex Buffer / Vertex Array Globals
unsigned int vbo, vao;

// Shader Globals
unsigned int shaderProgram, vertShader, fragShader;

// Event Globals
std::unordered_map<int, bool> keyStates;

/////////////////////////////////////////////////

// Creates a new window and 
void setUpWindow() {
	monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	width = mode->width;
	height = mode->height;

	if (fullScreenMode == fsModes::BORDERLESS) glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	window = glfwCreateWindow(width, height, "Fractal Drive", fullScreenMode != fsModes::FULLSCREEN ? nullptr : monitor, nullptr);
	if (fullScreenMode != fsModes::FULLSCREEN) glfwMaximizeWindow(window);
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, width, height);
}

void generateHeightMapMesh() {
	for (int i = 0; i < heightMapResolution; i++) {
		for (int j = 0; j < heightMapResolution; j++) {
			int v = i * heightMapResolution + j;
			heightMapVertices[v] = i / heightMapResolution + 1.0;
			heightMapVertices[v + 1] = -0.5;
			heightMapVertices[v + 2] = j / heightMapResolution + 1.0;
		}
	}

	for (int i = 0; i < heightMapResolution - 1; i++) {
		for(int j = 0; j < heightMapResolution - 1) {
			int v = (i * (heightMapResolution - 1) + j) * 6;
			//heightMapMesh[v] =
		}
	}
}

void generateBuffers() {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (heightMapResolution * heightMapResolution) * (sizeof(float) * 3), &heightMapMesh, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
}

void compileShaders() {
	shaderProgram = glCreateProgram();
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertSource = 
	"#version 440 core\n"
	"layout(location = 0)in vec3 vertexPosition;\n"
	"void main() {\n"
	"	gl_Position = vec4(vertexPosition.xy / vertexPosition.z, vertexPosition.z, 1.0);\n"
	"};\n";
	glShaderSource(vertShader, 1, &vertSource, NULL);
	glCompileShader(vertShader);

	int vertCompiled;
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled == GL_FALSE) {
		int logLength;
		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> infoLog(logLength);
		glGetShaderInfoLog(vertShader, logLength, nullptr, &infoLog.front());
		std::string infoLogString(infoLog.begin(), infoLog.end());
		std::cout << infoLogString << std::endl;
	} else { std::cout << "Successfully compiled vertex shader :3" << std::endl; }
	glAttachShader(shaderProgram, vertShader);

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragSource = 
	"#version 440 core\n"
	"out vec4 fragColor;\n"
	"void main() {\n"
	"	fragColor = vec4(1.0,0.0,0.0,1.0);\n"
	"}";
	glShaderSource(fragShader, 1, &fragSource, NULL);
	glCompileShader(fragShader);
	glAttachShader(shaderProgram, fragShader);

	int fragCompiled;
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &fragCompiled);
	if (vertCompiled == GL_FALSE) {
		int logLength;
		glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> infoLog(logLength);
		glGetShaderInfoLog(fragShader, logLength, nullptr, &infoLog.front());
		std::string infoLogString(infoLog.begin(), infoLog.end());
		std::cout << infoLogString << std::endl;
	} else { std::cout << "Successfully compiled fragment shader :3" << std::endl; }

	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);
}

/////////////////////////////////////////////////

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
	
	glDrawArrays(GL_POINTS, 0, heightMapTriCount * 3);
	
	glfwSwapBuffers(window);
	glfwPollEvents();
}

/////////////////////////////////////////////////

int main() {
	glfwInit();
	
	setUpWindow();
	glfwSetKeyCallback(window, &onInput);
	
	generateHeightMapMesh();

	generateBuffers();
	compileShaders();
	
	while (!glfwWindowShouldClose(window) && !shouldExit) onFrame();
	
	glfwDestroyWindow(window);
	glfwTerminate();
}

/////////////////////////////////////////////////