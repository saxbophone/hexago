#include "hexagon.hpp"


int main() {
    hexago::Hexagon h = hexago::Hexagon(0, 0, 100, 1, 0);
    return h.is_dead();
}
