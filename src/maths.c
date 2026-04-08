#include <math.h>
#include <stdio.h>
#include <threads.h>
#include "maths.h"



float sqr(float num) {
    return num * num;
}

char zero(float num) {
    if ((num < 0.0001f) && (num > -0.0001f))
        return 1;
    else
     return 0;
}
// normalise the float number to be from 0.0 - 1.0
float norm_float(float max, float value) { 
    return value / max;
}

struct Vec3 Vec3(float x, float y, float z) {
    struct Vec3 vector;
    vector.x = x;
    vector.y = y;
    vector.z = z;
    return vector;
}

struct Vec3 Vec3_add(struct Vec3 vector1, struct Vec3 vector2) {
    vector1.x = vector1.x + vector2.x; vector1.y = vector1.y + vector2.y; vector1.z = vector1.z + vector2.z; return vector1;
}

struct Vec3 Vec3_sub(struct Vec3 vector1, struct Vec3 vector2) {
    vector1.x = vector1.x - vector2.x; vector1.y = vector1.y - vector2.y; vector1.z = vector1.z - vector2.z; return vector1;
}

struct Vec3 Vec3_mul(struct Vec3 vector1, struct Vec3 vector2) {
    vector1.x = vector2.x * vector1.x; vector1.y = vector2.y * vector1.y; vector1.z = vector2.z * vector1.z; return vector1;
}

struct Vec3 Vec3_div(struct Vec3 vector1, struct Vec3 vector2) {
    vector1.x = vector1.x / vector2.x; vector1.y = vector1.y / vector2.y; vector1.z = vector1.z / vector2.z; return vector1;
}

struct Vec3 Vec3_float_add(struct Vec3 vector, float num) {
    vector.x = vector.x + num; vector.y = vector.y + num; vector.z = vector.z + num; return vector;
}

struct Vec3 Vec3_float_sub(struct Vec3 vector, float num) {
    vector.x = vector.x - num; vector.y = vector.y - num; vector.z = vector.z - num; return vector;
}

struct Vec3 Vec3_float_mul(struct Vec3 vector, float num) {
    vector.x = vector.x * num; vector.y = vector.y * num; vector.z = vector.z * num; return vector;
}

struct Vec3 Vec3_float_div(struct Vec3 vector, float num) {
    vector.x = vector.x / num; vector.y = vector.y / num; vector.z = vector.z / num; return vector;
}

struct Vec3 Vec3_rot_x(struct Vec3 vec, struct Vec3 origin, float angle) {
    struct Vec3 vec_rel = Vec3_sub(vec, origin);
    vec.y = vec_rel.y*cos(angle) - vec_rel.z*sin(angle);
    vec.z = vec_rel.y*sin(angle) + vec_rel.z*cos(angle);
    return vec;
}

struct Vec3 Vec3_rot_y(struct Vec3 vec, struct Vec3 origin, float angle) {
    struct Vec3 vec_rel = Vec3_sub(vec, origin);
    vec.x = vec_rel.x*cos(angle) - vec_rel.z*sin(angle);
    vec.z = -vec_rel.x*sin(angle) + vec_rel.z*cos(angle);
    return vec;
}

struct Vec3 Vec3_rot_z(struct Vec3 vec, struct Vec3 origin, float angle) {
    struct Vec3 vec_rel = Vec3_sub(vec, origin);
    vec.x = vec_rel.x*cos(angle) - vec_rel.y*sin(angle);
    vec.y = vec_rel.x*sin(angle) + vec_rel.y*cos(angle);
    return vec;
}
struct Vec3 cross_product(struct Vec3 vec1, struct Vec3 vec2) {
    struct Vec3 result;
    result.x = (vec1.y*vec2.z)-(vec1.z*vec2.y);
    result.y = (vec1.z*vec2.x)-(vec1.x*vec2.z);
    result.z = (vec1.x*vec2.y)-(vec1.y*vec2.x);
    return result;
}

float dot_product(struct Vec3 vec1, struct Vec3 vec2) {
    float val = ((vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z));
    //printf("-- %f\n", val); //test
    return val;
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

// This is just to calculate the vector after rotation
struct Vec3 matrix_mul(struct matrix a, struct Vec3 b) {
    b.x = (a.a.x*b.x) + (a.a.y*b.y) + (a.a.z*b.z);
    b.y = (a.b.x*b.x) + (a.b.y*b.y) + (a.b.z*b.z);
    b.z = (a.c.x*b.x) + (a.c.y*b.y) + (a.c.z*b.z);
    return b;
}

struct Triangle mk_triangle(struct Vec3 a, struct Vec3 b, struct Vec3 c, struct Vec3 color) {
    struct Triangle triangle;
    triangle.a = a;
    triangle.b = b;
    triangle.c = c;
    triangle.normal = cross_product(Vec3_sub(b, a), Vec3_sub(c, a));
    triangle.color = color;
    return triangle;
}

void tri_rot_x(struct Triangle* tri, float angle) {
    struct Vec3 mid = Vec3_float_div(Vec3_add(Vec3_add(tri->a, tri->b), tri->c), 3.0);
    tri->a = Vec3_rot_x(tri->a, mid, angle);
    tri->b = Vec3_rot_x(tri->b, mid, angle);
    tri->c = Vec3_rot_x(tri->c, mid, angle);
}
void tri_rot_y(struct Triangle* tri, float angle) {
    struct Vec3 mid = Vec3_float_div(Vec3_add(Vec3_add(tri->a, tri->b), tri->c), 3.0);
    tri->a = Vec3_rot_y(tri->a, mid, angle);
    tri->b = Vec3_rot_y(tri->b, mid, angle);
    tri->c = Vec3_rot_y(tri->c, mid, angle);
}
void tri_rot_z(struct Triangle* tri, float angle) {
    struct Vec3 mid = Vec3_float_div(Vec3_add(Vec3_add(tri->a, tri->b), tri->c), 3.0);
    tri->a = Vec3_rot_z(tri->a, mid, angle);
    tri->b = Vec3_rot_z(tri->b, mid, angle);
    tri->c = Vec3_rot_z(tri->c, mid, angle);
}

char tri_ray_collision(struct Triangle tri, struct Vec3 ray, struct Vec3 cam_loc) {
    float n_dot_t = dot_product(tri.normal, ray);
    if (zero(n_dot_t)) {
        return 0;
    }
    float n_dot_ps = dot_product(tri.normal, Vec3_sub(tri.a, cam_loc));
    float t = n_dot_ps / n_dot_t;
    struct Vec3 planePoint = Vec3_add(cam_loc, Vec3_float_mul(ray, t));
    
    struct Vec3 A2B = Vec3_sub(tri.b, tri.a);
    struct Vec3 B2C = Vec3_sub(tri.c, tri.b);
    struct Vec3 C2A = Vec3_sub(tri.a, tri.c);

    struct Vec3 A2P = Vec3_sub(planePoint, tri.a);
    struct Vec3 B2P = Vec3_sub(planePoint, tri.b);
    struct Vec3 C2P = Vec3_sub(planePoint, tri.c);
    
    struct Vec3 A2T = cross_product(A2B, A2P);
    struct Vec3 B2T = cross_product(B2C, B2P);
    struct Vec3 C2T = cross_product(C2A, C2P);

    int test_A = (dot_product(A2T, tri.normal) > 0.0f);
    int test_B = (dot_product(B2T, tri.normal) > 0.0f);
    int test_C = (dot_product(C2T, tri.normal) > 0.0f);
    int result = (test_A > 0) && (test_B > 0) && (test_C > 0);
    return result;
}

void printVec3(struct Vec3 vector) {
    printf("%f | %f | %f\n", vector.x, vector.y, vector.z);
}
