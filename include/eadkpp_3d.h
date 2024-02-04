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
        glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        rotMatrix = glm::rotate(rotMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        rotMatrix = glm::rotate(rotMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

        viewMatrix = rotMatrix * glm::translate(glm::mat4(1.0f), -position);
        this->position = position;
    }

    void setRotation(const glm::vec3& rotation) {
        glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around x-axis
        rotMatrix = glm::rotate(rotMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around y-axis
        rotMatrix = glm::rotate(rotMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around z-axis

        viewMatrix = rotMatrix * glm::translate(glm::mat4(1.0f), -position);
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

    Point project(const glm::vec3& worldPos, const glm::mat4& modelMatrix) {
        glm::vec4 clipSpacePos = projectionMatrix * viewMatrix * modelMatrix * glm::vec4(worldPos, 1.0);
        glm::vec3 ndcPos = glm::vec3(clipSpacePos) / clipSpacePos.w;
        glm::vec2 screenPos = glm::vec2(ndcPos.x, ndcPos.y);
        return Point(screenPos.x * Screen::Width, screenPos.y * Screen::Height);
    }

    std::vector<Point> project(const std::vector<glm::vec3>& worldPos) {
        std::vector<Point> screenPos;
        for (glm::vec3 pos : worldPos) {
            screenPos.push_back(project(pos));
        }
        return screenPos;
    }

    std::vector<Point> project(const std::vector<glm::vec3>& worldPos, const glm::mat4& modelMatrix) {
        std::vector<Point> screenPos;
        for (glm::vec3 pos : worldPos) {
            screenPos.push_back(project(pos, modelMatrix));
        }
        return screenPos;
    }

    void render(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> indices, Color color) {
        std::vector<Point> screenPos = project(vertices);
        for (glm::uvec3 index : indices) {
            Display::drawLine(screenPos[index.x], screenPos[index.y], color);
            Display::drawLine(screenPos[index.y], screenPos[index.z], color);
            Display::drawLine(screenPos[index.z], screenPos[index.x], color);
        }
    }

    void render(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> indices, const glm::mat4& modelMatrix, Color color) {
        std::vector<Point> screenPos = project(vertices, modelMatrix);
        for (glm::uvec3 index : indices) {
            Display::drawLine(screenPos[index.x], screenPos[index.y], color);
            Display::drawLine(screenPos[index.y], screenPos[index.z], color);
            Display::drawLine(screenPos[index.z], screenPos[index.x], color);
        }
    }

    // since render is not working fine for now
    void pointRender(std::vector<glm::vec3> vertices, Color color) {
        std::vector<Point> points = project(vertices);
        for (Point point : points) {
            Display::drawPoint(point, color);
        }
    }

    void pointRender(std::vector<glm::vec3> vertices, const glm::mat4& modelMatrix, Color color) {
        std::vector<Point> points = project(vertices, modelMatrix);
        for (Point point : points) {
            Display::drawPoint(point, color);
        }
    }
};

} // namespace Graphics
} // namespace EADK

#endif // EADKPP_3D_H