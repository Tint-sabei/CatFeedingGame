#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

class FullnessTooHighException : public std::runtime_error {
public:
    FullnessTooHighException()
        : std::runtime_error("Fullness Level cannot exceed 100! Overfeeding alert.") {}
};

#endif // EXCEPTIONS_HPP

