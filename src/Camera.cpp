//
// Created by roundedglint585 on 8/16/19.
//

#include <glm/gtc/matrix_transform.hpp>
#include "../include/Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up) : pos_(pos), up_(up), destination_({0.0f,0.0f,-1.0f}){

}

glm::mat4 Camera::getViewMatrix() const{
    return glm::lookAt(pos_,pos_+destination_, up_);
}

glm::vec3 Camera::getPos() const {
    return pos_;
}
