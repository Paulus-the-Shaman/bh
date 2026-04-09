#pragma once

#define PI 3.14159265358979323846

struct Vec3 {
    float x, y, z;
};

struct matrix {
    struct Vec3 a;
    struct Vec3 b;
    struct Vec3 c;
};

struct Triangle {
    struct Vec3 a;
    struct Vec3 b;
    struct Vec3 c;
    struct Vec3 normal;
};

struct Object {
    int capacity;
    struct Vec3 color;
    struct Triangle* polygon;
};

// Functions

float sqr(float);
char zero(float);
float norm_float(float max, float value);
struct Vec3 Vec3(float, float, float);
struct Vec3 Vec3_add(struct Vec3 vector1, struct Vec3 vector2);
struct Vec3 Vec3_sub(struct Vec3 vector1, struct Vec3 vector2);
struct Vec3 Vec3_mul(struct Vec3 vector1, struct Vec3 vector2);
struct Vec3 Vec3_div(struct Vec3 vector1, struct Vec3 vector2);
struct Vec3 Vec3_add_f(struct Vec3 vector, float num);
struct Vec3 Vec3_sub_f(struct Vec3 vector, float num);
struct Vec3 Vec3_mul_f(struct Vec3 vector, float num);
struct Vec3 Vec3_div_f(struct Vec3 vector, float num);
struct Vec3 Vec3_rot_x(struct Vec3 vec, struct Vec3 origin, float angle);
struct Vec3 Vec3_rot_y(struct Vec3 vec, struct Vec3 origin, float angle);
struct Vec3 Vec3_rot_z(struct Vec3 vec, struct Vec3 origin, float angle);
struct Vec3 cross_product(struct Vec3, struct Vec3);
float dot_product(struct Vec3, struct Vec3);
float length(struct Vec3);
struct Vec3 rotate(struct Vec3 point, struct Vec3 origin);
void transform(struct Vec3* point, struct Vec3 translate);
struct Vec3 normalize(struct Vec3 vector);

struct Vec3 matrix_mul(struct matrix a, struct Vec3 b);

struct Triangle Triangle(struct Vec3 a, struct Vec3 b, struct Vec3 c);
void tri_rot_x(struct Triangle* tri, float angle);
void tri_rot_y(struct Triangle* tri, float angle);
void tri_rot_z(struct Triangle* tri, float angle);
struct Collision tri_ray_collision(struct Triangle* tri, struct Vec3 ray, struct Vec3 cam_loc, struct Vec3 color);

struct Object Object(int capacity, struct Vec3 color, struct Triangle* polygons);

void printVec3(struct Vec3 vector);
