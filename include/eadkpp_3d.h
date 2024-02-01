#ifndef EADKPP_3D_H
#define EADKPP_3D_H

#include "eadkpp.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace EADK {
namespace Graphics {



class Camera {
private:
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    glm::vec3 position;
    glm::vec3 rotation;
public:
    Camera(float fov, float aspectRatio, float near, float far) {
        projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, near, far);
    }

    void setPosition(const glm::vec3& position) {
        viewMatrix = glm::lookAt(position, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void setRotation(const glm::vec3& rotation) {
        viewMatrix = glm::lookAt(position, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void rotate(const glm::vec3& delta) {
        rotation += delta;
        viewMatrix = glm::lookAt(position, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void move(const glm::vec3& delta) {
        position += delta;
        viewMatrix = glm::lookAt(position, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    Point project(const glm::vec3& worldPos) {
        glm::vec4 clipSpacePos = projectionMatrix * viewMatrix * glm::vec4(worldPos, 1.0);
        glm::vec3 ndcPos = glm::vec3(clipSpacePos) / clipSpacePos.w;
        glm::vec2 screenPos = glm::vec2(ndcPos.x, ndcPos.y);
        return Point(screenPos.x * Screen::Width, screenPos.y * Screen::Height);
    }
};

} // namespace Graphics
} // namespace EADK

#endif // EADKPP_3D_H