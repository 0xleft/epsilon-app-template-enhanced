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

    glm::mat4 getProjectionMatrix() const {
        return projectionMatrix;
    }

    glm::mat4 getViewMatrix() const {
        return viewMatrix;
    }

    void setPosition(const glm::vec3& position) {
        viewMatrix = glm::lookAt(position, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
        this->position = position;
    }

    void setRotation(const glm::vec3& rotation) {
        viewMatrix = glm::lookAt(position, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
        this->rotation = rotation;
    }

    void move(const glm::vec3& offset) {
        position += offset;
        viewMatrix = glm::lookAt(position, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void rotate(const glm::vec3& offset) {
        rotation += offset;
        viewMatrix = glm::lookAt(position, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    Point project(const glm::vec3& worldPos) {
        glm::vec4 clipSpacePos = projectionMatrix * viewMatrix * glm::vec4(worldPos, 1.0);
        glm::vec3 ndcPos = glm::vec3(clipSpacePos) / clipSpacePos.w;
        glm::vec2 screenPos = glm::vec2(ndcPos.x, ndcPos.y);
        return Point(screenPos.x * Screen::Width, screenPos.y * Screen::Height);
    }

    std::vector<Point> project(const std::vector<glm::vec3>& worldPos) {
        std::vector<Point> screenPos;
        for (const auto& pos : worldPos) {
            screenPos.push_back(project(pos));
        }
        return screenPos;
    }

    glm::vec3 unproject(const Point& screenPos, float depth) {
        glm::vec2 ndcPos = glm::vec2(screenPos.x() / Screen::Width, screenPos.y() / Screen::Height);
        glm::vec4 clipSpacePos = glm::vec4(ndcPos.x, ndcPos.y, depth, 1.0);
        glm::vec4 eyeSpacePos = glm::inverse(projectionMatrix) * clipSpacePos;
        glm::vec3 worldPos = glm::vec3(glm::inverse(viewMatrix) * eyeSpacePos);
        return worldPos;
    }

    std::vector<glm::vec3> unproject(const std::vector<Point>& screenPos, float depth) {
        std::vector<glm::vec3> worldPos;
        for (const auto& pos : screenPos) {
            worldPos.push_back(unproject(pos, depth));
        }
        return worldPos;
    }

    void render(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> indices, Color color) {
        std::vector<Point> screenPos = project(vertices);
        for (const auto& index : indices) {
            Display::drawLine(screenPos[index.x], screenPos[index.y], color);
            Display::drawLine(screenPos[index.y], screenPos[index.z], color);
            Display::drawLine(screenPos[index.z], screenPos[index.x], color);
        }
    }
};

} // namespace Graphics
} // namespace EADK

#endif // EADKPP_3D_H