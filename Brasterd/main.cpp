#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "standards.h"


const char* DEFAULT_VERTEX_SHADER = R"glsl(
#version 330 core

layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1.0);
}
)glsl";

const char* DEFAULT_FRAGMENT_SHADER = R"glsl(
#version 330 core

out vec4 color;

void main() {
    color = vec4(1.0, 0.5, 0.0, 1.0);
}
)glsl";

GLuint compile(GLuint type, std::string src) {
    GLuint shader = glCreateShader(type);
    const char* raw = src.c_str();
    glShaderSource(shader, 1, &raw, nullptr);
    glCompileShader(shader);
    char log[512] = { 0 };
    glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
    std::cout << "Shader log: " << log << std::endl;
    return shader;
}

GLuint link(std::string v_src, std::string f_src) {
    GLuint program = glCreateProgram();
    glAttachShader(program, compile(GL_VERTEX_SHADER, v_src));
    glAttachShader(program, compile(GL_FRAGMENT_SHADER, f_src));
    glLinkProgram(program);

    char log[512] = { 0 };
    glGetProgramInfoLog(program, sizeof(log), nullptr, log);
    std::cout << "Program log: " << log << std::endl;
    return program;
}


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow *window = glfwCreateWindow(SCR_W, SCR_H, "display", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cerr << "FATAL! Failed to load OpenGL functions." << std::endl;
        return -1;
    }

    GLuint VAO, VBO;
    float data[] = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

    GLuint program = link(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }
    return 0;
}
