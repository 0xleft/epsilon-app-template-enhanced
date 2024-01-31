#ifndef EADKPP_3D_H
#define EADKPP_3D_H

#include <cmath>
#include "eadkpp.h"

namespace EADK {
namespace Graphics {

class Vector3 {
    private:
        float x, y, z;
    public:
        Vector3(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        };
        float inline getX() { return this->x; };
        float inline getY() { return this->y; };
        float inline getZ() { return this->z; };
        void inline setX(float x) { this->x = x; };
        void inline setY(float y) { this->y = y; };
        void inline setZ(float z) { this->z = z; };

        Vector3 operator+(Vector3 p) {
            return Vector3(this->x + p.getX(), this->y + p.getY(), this->z + p.getZ());
        };
        Vector3 operator-(Vector3 p) {
            return Vector3(this->x - p.getX(), this->y - p.getY(), this->z - p.getZ());
        };
        Vector3 operator*(Vector3 p) {
            return Vector3(this->x * p.getX(), this->y * p.getY(), this->z * p.getZ());
        };
        Vector3 operator/(Vector3 p) {
            return Vector3(this->x / p.getX(), this->y / p.getY(), this->z / p.getZ());
        };
        
        Vector3 operator+(float f) {
            return Vector3(this->x + f, this->y + f, this->z + f);
        };
        Vector3 operator-(float f) {
            return Vector3(this->x - f, this->y - f, this->z - f);
        };
        Vector3 operator*(float f) {
            return Vector3(this->x * f, this->y * f, this->z * f);
        };
        Vector3 operator/(float f) {
            return Vector3(this->x / f, this->y / f, this->z / f);
        };

        // dot
        float operator|(Vector3 p) {
            return this->x * p.getX() + this->y * p.getY() + this->z * p.getZ();
        };

        // cross
        Vector3 operator^(Vector3 p) {
            return Vector3(this->y * p.getZ() - this->z * p.getY(), this->z * p.getX() - this->x * p.getZ(), this->x * p.getY() - this->y * p.getX());
        };

        // magnitude
        float operator~() {
            return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
        };

        // normalize
        Vector3 operator!() {
            return Vector3(this->x / ~(*this), this->y / ~(*this), this->z / ~(*this));
        };
};

class Vector4 {
    private:
        float x, y, z, w;
    public:
        Vector4(float x, float y, float z, float w) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        };
        float inline getX() { return this->x; };
        float inline getY() { return this->y; };
        float inline getZ() { return this->z; };
        float inline getW() { return this->w; };
        void inline setX(float x) { this->x = x; };
        void inline setY(float y) { this->y = y; };
        void inline setZ(float z) { this->z = z; };
        void inline setW(float w) { this->w = w; };

        Vector4 operator+(Vector4 p) {
            return Vector4(this->x + p.getX(), this->y + p.getY(), this->z + p.getZ(), this->w + p.getW());
        };
        Vector4 operator-(Vector4 p) {
            return Vector4(this->x - p.getX(), this->y - p.getY(), this->z - p.getZ(), this->w - p.getW());
        };
        Vector4 operator*(Vector4 p) {
            return Vector4(this->x * p.getX(), this->y * p.getY(), this->z * p.getZ(), this->w * p.getW());
        };
        Vector4 operator/(Vector4 p) {
            return Vector4(this->x / p.getX(), this->y / p.getY(), this->z / p.getZ(), this->w / p.getW());
        };
        
        Vector4 operator+(float f) {
            return Vector4(this->x + f, this->y + f, this->z + f, this->w + f);
        };
        Vector4 operator-(float f) {
            return Vector4(this->x - f, this->y - f, this->z - f, this->w - f);
        };
        Vector4 operator*(float f) {
            return Vector4(this->x * f, this->y * f, this->z * f, this->w * f);
        };
        Vector4 operator/(float f) {
            return Vector4(this->x / f, this->y / f, this->z / f, this->w / f);
        };

        // dot
        float operator|(Vector4 p) {
            return this->x * p.getX() + this->y * p.getY() + this->z * p.getZ() + this->w * p.getW();
        };

        // cross
        Vector4 operator^(Vector4 p) {
            return Vector4(this->y * p.getZ() - this->z * p.getY(), this->z * p.getX() - this->x * p.getZ(), this->x * p.getY() - this->y * p.getX(), 0);
        };

        // magnitude
        float operator~() {
            return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
        };

        // normalize
        Vector4 operator!() {
            return Vector4(this->x / ~(*this), this->y / ~(*this), this->z / ~(*this), this->w / ~(*this));
        };
};

class Mat4 {
    private:
        float m[4][4];
    public:
        Mat4() = default;
        Mat4(float m[4][4]) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; i < 4; i++) {
                    this->m[i][j] = m[i][j];
                }
            }
        };

        Mat4 operator+(Mat4 m) {
            float r[4][4];
            for (int i = 0; i < 4; i++) {
                for (int j = 0; i < 4; i++) {
                    r[i][j] = this->m[i][j] + m.m[i][j];
                }
            }
            return Mat4(r);
        };

        Mat4 operator-(Mat4 m) {
            float r[4][4];
            for (int i = 0; i < 4; i++) {
                for (int j = 0; i < 4; i++) {
                    r[i][j] = this->m[i][j] - m.m[i][j];
                }
            }
            return Mat4(r);
        };

        Mat4 operator*(Mat4 m) {
            float r[4][4];
            for (int i = 0; i < 4; i++) {
                for (int j = 0; i < 4; i++) {
                    r[i][j] = this->m[i][j] * m.m[i][j];
                }
            }
            return Mat4(r);
        };

        Mat4 operator/(Mat4 m) {
            float r[4][4];
            for (int i = 0; i < 4; i++) {
                for (int j = 0; i < 4; i++) {
                    r[i][j] = this->m[i][j] / m.m[i][j];
                }
            }
            return Mat4(r);
        };

        Mat4 operator+(float f) {
            float r[4][4];
            for (int i = 0; i < 4; i++) {
                for (int j = 0; i < 4; i++) {
                    r[i][j] = this->m[i][j] + f;
                }
            }
            return Mat4(r);
        };

        Mat4 operator-(float f) {
            float r[4][4];
            for (int i = 0; i < 4; i++) {
                for (int j = 0; i < 4; i++) {
                    r[i][j] = this->m[i][j] - f;
                }
            }
            return Mat4(r);
        };

        Mat4 operator*(float f) {
            float r[4][4];
            for (int i = 0; i < 4; i++) {
                for (int j = 0; i < 4; i++) {
                    r[i][j] = this->m[i][j] * f;
                }
            }
            return Mat4(r);
        };

        Mat4 operator/(float f) {
            float r[4][4];
            for (int i = 0; i < 4; i++) {
                for (int j = 0; i < 4; i++) {
                    r[i][j] = this->m[i][j] / f;
                }
            }
            return Mat4(r);
        };

        Vector4 operator*(Vector4 v) {
            float r[4];
            for (int i = 0; i < 4; i++) {
                r[i] = this->m[i][0] * v.getX() + this->m[i][1] * v.getY() + this->m[i][2] * v.getZ() + this->m[i][3] * v.getW();
            }
            return Vector4(r[0], r[1], r[2], r[3]);
        };

        Vector3 operator*(Vector3 v) {
            float r[3];
            for (int i = 0; i < 3; i++) {
                r[i] = this->m[i][0] * v.getX() + this->m[i][1] * v.getY() + this->m[i][2] * v.getZ() + this->m[i][3];
            }
            return Vector3(r[0], r[1], r[2]);
        };
};

class Camera {
    private:
        Vector3 position = Vector3(0, 0, 0);
        Vector3 rotation = Vector3(0, 0, 0);
        Mat4 view;
        Mat4 projection;
        float fov, aspect, near, far;
    public:
        Camera(Vector3 position, Vector3 rotation, float fov, float aspect, float near, float far) {
            this->position = position;
            this->rotation = rotation;
            this->fov = fov;
            this->aspect = aspect;
            this->near = near;
            this->far = far;

            this->generateView();
            this->generateProjection();
        };
        Vector3 inline getPosition() { return this->position; };
        Vector3 inline getRotation() { return this->rotation; };
        void inline setPosition(Vector3 position) { this->position = position; };
        void inline setRotation(Vector3 rotation) { this->rotation = rotation; };

        void inline move(Vector3 position) {
            this->position = this->position + position;
            this->generateView();
        };
        void inline rotate(Vector3 rotation) {
            this->rotation = this->rotation + rotation;
            this->generateView();
        };

        void inline generateView() {
            float x = this->rotation.getX();
            float y = this->rotation.getY();
            float z = this->rotation.getZ();

            float rotationMatrix[4][4] = {
                {cos(y) * cos(z), cos(x) * sin(z) + sin(x) * sin(y) * cos(z), sin(x) * sin(z) - cos(x) * sin(y) * cos(z), 0},
                {-cos(y) * sin(z), cos(x) * cos(z) - sin(x) * sin(y) * sin(z), sin(x) * cos(z) + cos(x) * sin(y) * sin(z), 0},
                {sin(y), -sin(x) * cos(y), cos(x) * cos(y), 0},
                {0, 0, 0, 1}
            };

            float translationMatrix[4][4] = {
                {1, 0, 0, -this->position.getX()},
                {0, 1, 0, -this->position.getY()},
                {0, 0, 1, -this->position.getZ()},
                {0, 0, 0, 1}
            };

            this->view = Mat4(rotationMatrix) * Mat4(translationMatrix);
        }

        // fov in degrees
        void inline generateProjection() {
            float fovRad = 1.0f / tan(fov * 0.5f / 180.0f * 3.14159f);
            float zRange = near - far;

            float projection[4][4] = {
                {aspect * fovRad, 0, 0, 0},
                {0, fovRad, 0, 0},
                {0, 0, far / zRange, -1},
                {0, 0, near * far / zRange, 0}
            };

            this->projection = Mat4(projection);
        }

        // project a 3d point to a 2d point
        Point inline project(Vector3 point) {
            Vector4 v = this->projection * this->view * Vector4(point.getX(), point.getY(), point.getZ(), 1.0f);
            return Point(v.getX() / v.getW(), v.getY() / v.getW());
        }
};

} // namespace Graphics
} // namespace EADK

#endif // EADKPP_3D_H