#include <math.h>
#include <string.h>
#include "maths.h"



float sqr(float num) {
    return num * num;
}

struct Vec3 Vec3(float x, float y, float z) {
    struct Vec3 vector;
    vector.x = x;
    vector.y = y;
    vector.z = z;
    return vector;
}

struct Vec3 Vec3_sub(struct Vec3 vector1, struct Vec3 vector2) {
    vector1.x = vector2.x - vector1.x;
    vector1.y = vector2.y - vector1.y;
    vector1.z= vector2.z - vector1.z;
    return vector1;
}

struct Vec3 Vec3_add(struct Vec3 vector1, struct Vec3 vector2) {
    vector1.x = vector2.x + vector1.x;
    vector1.y = vector2.y + vector1.y;
    vector1.z= vector2.z + vector1.z;
    return vector1;
}

struct Vec3 Vec3_mul(struct Vec3 vector1, struct Vec3 vector2) {
    vector1.x = vector2.x * vector1.x;
    vector1.y = vector2.y * vector1.y;
    vector1.z= vector2.z * vector1.z;
    return vector1;
}

struct Vec3 Vec3_div(struct Vec3 vector1, struct Vec3 vector2) {
    vector1.x = vector2.x / vector1.x;
    vector1.y = vector2.y / vector1.y;
    vector1.z= vector2.z / vector1.z;
    return vector1;
}

struct Vec3 cross_product(struct Vec3 vec1, struct Vec3 vec2) {
    struct Vec3 result;
    result.x = (vec1.y*vec2.z)-(vec1.z*vec2.y);
    result.y = (vec1.z*vec2.x)-(vec1.x*vec2.z);
    result.z = (vec1.x*vec2.y)-(vec1.y*vec2.x);
    return result;
}

float dot_product(struct Vec3 vec1, struct Vec3 vec2) {
    return ((vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z));
}

float length(struct Vec3 vector) {
    return sqrtf(sqr(vector.x) + sqr(vector.y) + sqr(vector.z));
}

struct Vec3 rotate(struct Vec3 point, struct Vec3 origin) {
    return Vec3(0, 0, 0); //TOTO
}

void transform(struct Vec3* point, struct Vec3 translate) {
    point->x += translate.x;
    point->y += translate.y;
    point->z += translate.z;
}

struct Vec3 normalize(struct Vec3 vector) {
    float len = length(vector);
    vector.x = vector.x/len;
    vector.y = vector.y/len;
    vector.z = vector.z/len;
    return vector;
}

struct Triangle mk_triangle(struct Vec3 a, struct Vec3 b, struct Vec3 c) {
    struct Triangle triangle;
    triangle.a = a;
    triangle.b = b;
    triangle.c = c;
    triangle.normal = normalize(cross_product(Vec3_sub(b, a), Vec3_sub(c, a)));
    return triangle;
}
