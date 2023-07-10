#include "MathUtility.h"

Vector3 TransformNomal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]
	};
	return result;
}

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 temp = {};
	temp.x = (1 - t) * v1.x + t * v2.x;
	temp.y = (1 - t) * v1.y + t * v2.y;
	temp.z = (1 - t) * v1.z + t * v2.z;
	return temp;
}

Vector3 Normalize(Vector3 v2) {
	Vector3 result;
	result.x = v2.x / sqrtf(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
	result.y = v2.y / sqrtf(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
	result.z = v2.z / sqrtf(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
	return result;
}
Vector3& operator-=(Vector3& v1, const Vector3& v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;

	return v1;
}
Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	Vector3 result = v1;

	return result -= v2;
}
Vector3& operator*=(Vector3& v, const float& f) {
	Vector3 result;
	result.x = f * v.x;
	result.y = f * v.y;
	result.z = f * v.z;
	v = result;
	return v;

}
Vector3 operator*(Vector3& v, const float& f) {
	Vector3 result = v;
	return result *= f;
}






Vector3& operator+=(Vector3& v1, const Vector3& v2) {
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}
Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	Vector3 result = v1;
	return result += v2;
}