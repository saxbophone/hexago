#include <cstdint>
#include <cstdio>

#include "hexagon.hpp"


int main() {
    hexago::Hexagon hexagon = hexago::Hexagon(0, 0, 1000, 100, 0);
    for(uint32_t time = 0; time < 10000; time += 500) {
        hexagon.update(time);
        hexago::hexagon_points_t hexagon_points = hexagon.points();
        for(uint8_t i = 0; i < 6; i++) {
            printf(
                "(%i, %i) ", hexagon_points.points[i].x, hexagon_points.points[i].y
            );
        }
        printf("\n");
        if(hexagon.is_dead()) {
            break;
        }
    }
    return 0;
}
