#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Thing.h"


class Display {
public:
    Display(std::string title, int width, int height);

    void init();

    void poll_events();

    bool should_close();

    void clear();

    void render();

    void draw(Thing &thing);

private:
    std::string window_title;
    int window_width, window_height;
    GLFWwindow *window_handle;

    GLuint texture_program; // Program to sample texture
    GLuint texture_quad_vao; // A quad containing texture coordinates
    GLuint texture_uniform_location;  
};

