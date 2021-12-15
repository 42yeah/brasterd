#include <iostream>
#include "Display.h"
#include "Thing.h"
#include "standards.h"
#include "linalg.h"


int main() {
    Display display("display", SCR_W, SCR_H);
    display.init();

    Thing thing(SCR_W, SCR_H);

    while (!display.should_close()) {
        display.poll_events();
        display.clear();

        // === Software render part ===
        thing.clear();
        thing.draw_line(ivec2(1000, 720), ivec2(10, 10), u8vec4(255, 125, 0, 255));
        thing.swap();
        // === Software render end ===
        
        display.draw(thing);
        display.render();
    }

    return 0;
}
