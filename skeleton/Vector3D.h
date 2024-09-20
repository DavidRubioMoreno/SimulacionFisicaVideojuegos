#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <cmath> // Para sqrt

class Vector3D {
private:
    float x, y, z;
    float module;

public:
    // Constructor por defecto
    Vector3D() : x(0), y(0), z(0), module(0) {}

    // Constructor con parámetros
    Vector3D(float x, float y, float z) : x(x), y(y), z(z), module(0) {}

    // Sobrecarga del operador = (asignación)
    Vector3D& operator=(const Vector3D& v) {
        if (this != &v) { // Evitar la autoasignación
            x = v.x;
            y = v.y;
            z = v.z;
        }
        return *this;
    }

    // Sobrecarga del operador + (suma)
    Vector3D operator+(const Vector3D& v) const {
        return Vector3D(x + v.x, y + v.y, z + v.z);
    }

    // Sobrecarga del operador - (resta)
    Vector3D operator-(const Vector3D& v) const {
        return Vector3D(x - v.x, y - v.y, z - v.z);
    }

    // Sobrecarga del operador * (multiplicación por escalar)
    Vector3D operator*(const Vector3D& v) const {
        return Vector3D(y * v.z - z * v.y, -(x * v.z - z * v.y), x*v.y - y*v.x);
    }

    // Método para normalizar el vector
    void normalize() {
        float magnitude = getMagnitude();
        if (magnitude != 0) {
            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
        }
    }

    // Método para obtener el módulo (magnitud) del vector
    float getMagnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Método para realizar el producto escalar con otro vector
    float dotProduct(const Vector3D& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    Vector3D scalar(float scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    // Método para imprimir el vector
    void print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
    }

    // Métodos para obtener y establecer valores de x, y, z
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }
    void setX(float xVal) { x = xVal; }
    void setY(float yVal) { y = yVal; }
    void setZ(float zVal) { z = zVal; }
};

#endif // VECTOR3D_H
