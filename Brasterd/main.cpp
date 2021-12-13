#include <iostream>
#include "Display.h"
#include "Thing.h"
#include "standards.h"


int main() {
    Display display("display", SCR_W, SCR_H);
    display.init();

    Thing thing(SCR_W, SCR_H);

    while (!display.should_close()) {
        display.poll_events();
        display.clear();

        // === Software render part ===
        thing.clear();
        for (int y = 0; y < 409; y++) {
            for (int x = 0; x < 109; x++) {
                thing.draw_point_at(ivec2(x, y), u8vec4(255, 125, 0, 255));
            }
        }
        thing.swap();
        // === Software render end ===
        
        display.draw(thing);
        display.render();
    }

    return 0;
}
