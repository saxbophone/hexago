#include "types.hpp"


namespace hexago {

    // constructor with co-ords
    Point::Point(screen_size_t x, screen_size_t y) : x(x), y(y) {}

    // default constructor sets them both to 0
    Point::Point() : x(0), y(0) {}

    void Point::update(screen_size_t x, screen_size_t y) {
        this->x = x;
        this->y = y;
    }

}
