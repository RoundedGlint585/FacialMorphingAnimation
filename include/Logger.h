//
// Created by roundedglint585 on 8/1/19.
//

#ifndef OPENGL_LOGGER_H
#define OPENGL_LOGGER_H
#include <iostream>
template <typename T>
void inline INFO(const T &message) {
    std::cout << "\033[32m" << "INFO: " << message << "\033[0m" << std::endl;
}
template <typename T>
void inline WARNING(const T &message){
    std::cout << "\033[31m"  << "WARNING: " << message << "\033[0m" << std::endl;
}
template <typename T>
void inline ERROR(const T &message){
    std::cout << "\033[31m"  << "ERROR: " << message << "\033[0m" << std::endl;
}
#endif //OPENGL_LOGGER_H
