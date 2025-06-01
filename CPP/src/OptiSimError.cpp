#include "OptiSimError.h"

OptiSimError::OptiSimError(const string& msg):message(msg){}

const char* OptiSimError::what() const noexcept {
    return message.c_str();
}