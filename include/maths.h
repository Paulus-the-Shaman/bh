#pragma once



struct Vec3 {
    float x, y, z;
};


struct Triangle {
    struct Vec3 a;
    struct Vec3 b;
    struct Vec3 c;
    struct Vec3 normal;
};


// Functions

struct Vec3 Vec3(float, float, float);
struct Vec3 Vec3_sub(struct Vec3 vector1, struct Vec3 vector2);
struct Vec3 Vec3_add(struct Vec3 vector1, struct Vec3 vector2);
struct Vec3 Vec3_mul(struct Vec3 vector1, struct Vec3 vector2);
struct Vec3 Vec3_div(struct Vec3 vector1, struct Vec3 vector2);
struct Vec3 cross_product(struct Vec3, struct Vec3);
float dot_product(struct Vec3, struct Vec3);
float length(struct Vec3);
struct Vec3 rotate(struct Vec3 point, struct Vec3 origin);
void transform(struct Vec3* point, struct Vec3 translate);
struct Vec3 normalize(struct Vec3 vector);

struct Triangle mk_triangle(struct Vec3, struct Vec3, struct  Vec3);
