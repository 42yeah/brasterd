#pragma once

#include <glad/glad.h>
#include "linalg.h"

#define THING_CHANNELS 4  // four channels, R, G, B & A


// Thing is a piece of texture with a GL_TEXTURE_2D handle because I don't like "canvas". Sounds bad.
class Thing {
public:
    Thing(int width, int height);

    ~Thing();

    void clear();
    
    // Apply changes to texture
    void swap();

    void draw_point(ivec2 pos, u8vec4 color);

    void draw_line(ivec2 begin, ivec2 end, u8vec4 color);

    void draw_triangle(ivec2 a, ivec2 b, ivec2 c);

    // NO BOUNDARY check pixel_at. DANGEROUS OPERATION! DANGER DANGER!
    u8vec4 &pixel_at(int x, int y);

    int width();

    int height();

private:
    bool boundary_check(int x, int y);

    unsigned char* raw_color_buffer;
    int thing_width, thing_height;
    
    // Front/back buffer to perform buffer swaps.
    // Rendering will be done to back buffer, while the front buffer will be used
    // as a uniform to display.
    GLuint hardware_handles[2];
    int current_hardware_handle;

    friend class Display;
};

