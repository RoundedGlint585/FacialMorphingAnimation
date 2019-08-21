//
// Created by roundedglint585 on 8/16/19.
//

#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H


#include <glm/glm.hpp>

class Camera {
public:
    explicit Camera(glm::vec3 pos = {0.0f,0.0f,7.0f} , glm::vec3 up = {0.0f,1.0f,0.0f} );
    [[nodiscard]] glm::mat4 getViewMatrix() const;
    [[nodiscard]] glm::vec3 getPos() const;
private:
    void update();
private:
    glm::vec3 pos_;
    glm::vec3 up_;
    glm::vec3 worldUp_;
    glm::vec3 right_;
    glm::vec3 destination_;

};


#endif //OPENGL_CAMERA_H
