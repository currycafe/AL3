#pragma once
#include<Matrix4x4.h>
#include<Vector3.h>
#include<math.h>

Vector3 TransformNomal(const Vector3& v, const Matrix4x4& m);
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);
Vector3 Normalize(Vector3 v2);
Vector3& operator-=(Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3& operator*=(Vector3& v, const float& f);
Vector3 operator*(Vector3& v, const float& f);


Vector3& operator+=(Vector3& v1, const Vector3& v2);
Vector3 operator+(const Vector3& v1, const Vector3& v2);