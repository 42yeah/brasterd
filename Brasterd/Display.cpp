#include "Display.h"


const char* DEFAULT_VERTEX_SHADER = R"glsl(
#version 330 core

layout (location = 0) in vec3 aPos;
out vec2 uv;

void main() {
    gl_Position = vec4(aPos, 1.0);
    uv = aPos.xy * 0.5 + 0.5;
}
)glsl";

const char* DEFAULT_FRAGMENT_SHADER = R"glsl(
#version 330 core

in vec2 uv;

uniform sampler2D tex;

out vec4 color;

void main() {
    color = texture(tex, uv);
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

Display::Display(std::string title, int width, int height) : window_title(title), window_width(width), window_height(height), window_handle(nullptr) {

}


void Display::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_handle = glfwCreateWindow(window_width, window_height, window_title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window_handle);

    if (!gladLoadGL()) {
        std::cerr << "FATAL! Failed to load OpenGL functions." << std::endl;
        return;
    }

    GLuint vbo;
    float data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f
    };
    glGenVertexArrays(1, &texture_quad_vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(texture_quad_vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    texture_program = link(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER);
    texture_uniform_location = glGetUniformLocation(texture_program, "tex");
}

void Display::poll_events() {
    glfwPollEvents();

    glfwGetWindowSize(window_handle, &window_width, &window_height);
    glViewport(0, 0, window_width, window_height);
}

bool Display::should_close() {
    return glfwWindowShouldClose(window_handle);
}

void Display::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Display::draw(Thing &thing) {
    glUseProgram(texture_program);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, thing.hardware_handles[thing.current_hardware_handle]);
    glUniform1i(texture_uniform_location, 0);
    glBindVertexArray(texture_quad_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Display::render() {
    glfwSwapBuffers(window_handle);
}