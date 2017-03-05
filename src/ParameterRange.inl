#include "ParameterRange.hpp"


namespace hexago {

    /* Implementation of ParameterRange templated struct type */

    // default constructor
    template<typename type>
    ParameterRange<type>::ParameterRange() {}

    // this constructor sets both min and max to the value given
    template<typename type>
    ParameterRange<type>::ParameterRange(type value)
     : ParameterRange(value, value) {}

    // this constructor sets min and max to separate respective values
    template<typename type>
    ParameterRange<type>::ParameterRange(type min, type max)
     : min(min), max(max) {}

    // this method validates the struct (min <= max)
    template<typename type>
    bool ParameterRange<type>::valid() const {
        return (this->min <= this->max);
    }

}
