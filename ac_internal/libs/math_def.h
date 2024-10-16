#ifndef math_def_h
#define math_def_h

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <math.h>
#include <utility.hpp>
#include <flogger.hpp>
#define M_PI 3.14159265f
#define RAD_TO_DEG(x) (x * (180.0f / M_PI))
#define DEG_TO_RAD(x) (x * (M_PI / 180.0f))

struct vec4
{
    float x, y, z, w;

    vec4 operator-(const vec4& ape) const { return { x - ape.x, y - ape.y, z - ape.z, w - ape.w }; }
    vec4 operator+(const vec4& ape) const { return { x + ape.x, y + ape.y, z + ape.z, w + ape.w }; }
    vec4 operator*(float ape) const { return { x * ape, y * ape, z * ape, w * ape }; }
    vec4 operator/(float ape) const { return { x / ape, y / ape, z / ape, w / ape }; }

    vec4& operator/=(float ape) { x /= ape; y /= ape; z /= ape; w /= ape; return *this; }
    vec4& operator+=(const vec4& ape) { x += ape.x; y += ape.y; z += ape.z; w += ape.w; return *this; }
    vec4& operator-=(const vec4& ape) { x -= ape.x; y -= ape.y; z -= ape.z; w -= ape.w; return *this; }

    void normalize() {
        float nLength = length();
        if (nLength != 0) { x /= nLength; y /= nLength; z /= nLength; w /= nLength; }
    }

    float length() const { return sqrt(x * x + y * y + z * z + w * w); }

    float distTo(const vec4& ape) const { return (*this - ape).length(); }

    float dotProduct(const vec4& ape) const { return (x * ape.x + y * ape.y + z * ape.z + w * ape.w); }

    vec4 crossProduct(const vec4& ape) const {
        return { y * ape.z - z * ape.y, z * ape.x - x * ape.z, x * ape.y - y * ape.x, 0.0f };
    }
};

struct vec3
{
    float x, y, z;

    vec3 operator-(const vec3& ape) const { return { x - ape.x, y - ape.y, z - ape.z }; }
    vec3 operator+(const vec3& ape) const { return { x + ape.x, y + ape.y, z + ape.z }; }
    vec3 operator*(float ape) const { return { x * ape, y * ape, z * ape }; }
    vec3 operator/(float ape) const { return { x / ape, y / ape, z / ape }; }

    vec3& operator/=(float ape) { x /= ape; y /= ape; z /= ape; return *this; }
    vec3& operator+=(const vec3& ape) { x += ape.x; y += ape.y; z += ape.z; return *this; }
    vec3& operator-=(const vec3& ape) { x -= ape.x; y -= ape.y; z -= ape.z; return *this; }

    void normalize() {
        float nLength = length();
        if (nLength != 0) { x /= nLength; y /= nLength; z /= nLength; }
    }

    float length() const { return sqrt(x * x + y * y + z * z); }

    float length2D() const { return sqrt(x * x + y * y); }

    float distTo(const vec3& ape) const { return (*this - ape).length(); }

    float dist2D(const vec3& ape) const { return (*this - ape).length2D(); }
};

struct vec2
{
    float x, y;

    vec2 operator-(const vec2& ape) const { return { x - ape.x, y - ape.y }; }
    vec2 operator+(const vec2& ape) const { return { x + ape.x, y + ape.y }; }
    vec2 operator*(float ape) const { return { x * ape, y * ape }; }
    vec2 operator/(float ape) const { return { x / ape, y / ape }; }

    vec2& operator/=(float ape) { x /= ape; y /= ape; return *this; }
    vec2& operator+=(const vec2& ape) { x += ape.x; y += ape.y; return *this; }
    vec2& operator-=(const vec2& ape) { x -= ape.x; y -= ape.y; return *this; }

    void normalize() {
        float length = length2D();
        if (length != 0) { x /= length; y /= length; }
    }

    float length2D() const { return sqrt(x * x + y * y); }

    float dist2D(const vec2& ape) const { return (*this - ape).length2D(); }
};


class viewMatrix
{
public:
    float* matrix = *reinterpret_cast<float**>(cUtility.signatureScanner("ac_client.exe", "50 68 ? ? ? ? E8 42 CE FF FF 8B C1 8D 54 24") + 2);

    int windowHeight = **reinterpret_cast<int**>(cUtility.signatureScanner("ac_client.exe", "03 0D ? ? ? ? 8B 35 ? ? ? ? D3 E3 8B 0D ? ? ? ? 90") + 8);
    int windowWidth = **reinterpret_cast<int**>(cUtility.signatureScanner("ac_client.exe", "03 0D ? ? ? ? 8B 35 ? ? ? ? D3 E3 8B 0D ? ? ? ? 90") + 16);

    bool WorldToScreen(vec3 pos, vec2& screen)
    {
        vec4 clipCoords;
        clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];
        if (clipCoords.w < 0.1f)
            return false;

        clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
        clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
        clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];

        screen.x = (windowWidth / 2.0f) * (clipCoords.x / clipCoords.w + 1.0f);
        screen.y = (windowHeight / 2.0f) * (1.0f - clipCoords.y / clipCoords.w);

        return true;
    }

}; inline viewMatrix vMatrix;

#endif // !math_def_h
