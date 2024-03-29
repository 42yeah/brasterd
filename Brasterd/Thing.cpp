#include "Thing.h"


Thing::Thing(int width, int height) : thing_width(width), thing_height(height), current_hardware_handle(0) {
    raw_color_buffer = new unsigned char[width * height * THING_CHANNELS];

    for (int i = 0; i < 2; i++) {
        glGenTextures(1, &hardware_handles[i]);
        glBindTexture(GL_TEXTURE_2D, hardware_handles[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, raw_color_buffer);
    }
    
}

Thing::~Thing() {
    for (int i = 0; i < 2; i++) {
        glDeleteTextures(1, &hardware_handles[i]);
    }
    delete raw_color_buffer;
}

void Thing::clear() {
    for (int i = 0; i < thing_width * thing_height * THING_CHANNELS; i++) {
        raw_color_buffer[i] = (i + 1) % 4 == 0 ? 255 : 0;
    }
}

void Thing::swap() {
    glBindTexture(GL_TEXTURE_2D, hardware_handles[1 - current_hardware_handle]);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, thing_width, thing_height, GL_RGBA, GL_UNSIGNED_BYTE, raw_color_buffer);
    current_hardware_handle = 1 - current_hardware_handle;
}

void Thing::draw_point(ivec2 pos, u8vec4 color) {
    if (!boundary_check(pos.x, pos.y)) {
        return;
    }
    pixel_at(pos.x, pos.y) = color;
}

void Thing::draw_line(ivec2 begin, ivec2 end, u8vec4 color) {
    int dx = end.x - begin.x;
    int dy = end.y - begin.y;
    bool swap_xy = false;
    if (abs(dy) > abs(dx)) {
        swoop(begin.x, begin.y);
        swoop(end.x, end.y);
        swoop(dx, dy);
        swap_xy = true;
    }
    if (begin.x > end.x) {
        swoop(begin, end);
        dx = -dx;
        dy = -dy;
    }

    int sy = begin.y;
    int error = 0;
    
    for (int sx = begin.x; sx <= end.x; sx++) {
        if (!boundary_check(sx, sy)) {
            continue;
        }
        if (!swap_xy) {
            pixel_at(sx, sy) = color;
        } else {
            pixel_at(sy, sx) = color;
        }
        
        if (2 * error + 2 * dy >= dx) {
            sy++;
            error += dy - dx;
        } else {
            error += dy;
        }
    }
}

void Thing::draw_triangle(ivec2 a, ivec2 b, ivec2 c) {
    ivec2 ab = b - a;
}

u8vec4 &Thing::pixel_at(int x, int y) {
    return *(u8vec4 *) &raw_color_buffer[(y * thing_width + x) * THING_CHANNELS];
}

int Thing::width() {
    return thing_width;
}

int Thing::height() {
    return thing_height;
}

bool Thing::boundary_check(int x, int y) {
    return !(x < 0 || x >= thing_width || y < 0 || y >= thing_height);
}
