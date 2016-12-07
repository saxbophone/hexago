#ifndef SAXBOPHONE_HEXAGO_PARAMETER_RANGE_HPP
#define SAXBOPHONE_HEXAGO_PARAMETER_RANGE_HPP


namespace hexago {

    /*
     * A simple data struct for representing a parameter range for the variable
     * settings of a Hexago screensaver. The data type used to instantiate the
     * template should be the type of the variable for which the range is being
     * represented.
     */
    template<typename type>
    struct ParameterRange {
        // default constructor
        ParameterRange() {}
        // this constructor sets both min and max to the value given
        ParameterRange(type value) : ParameterRange(value, value) {}
        // this constructor sets min and max to separate respective values
        ParameterRange(type min, type max) : min(min), max(max) {}
        // this method validates the struct (min <= max)
        bool valid() {
            return (this->min <= this->max);
        }
        type min;
        type max;
    };

}

#endif // include guard
