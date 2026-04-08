#pragma once
#include "maths.h"


struct Camera {
    struct Vec3 loc;
    struct Vec3 rot;
    struct Vec3 dir;
    float  focal_length;
};

struct Scene {
    const char* name;
    int width;
    int height;
    unsigned char *image; //file name to save render at
    struct Vec3 bg;
    const char *file; //file name to save render at
    int obj_num;
    int obj_cap;
    struct Object* objects;
    struct Camera camera; // camera is like its own object in the scene
};


// Functions

void write_render(struct Scene* scn);
void render(struct Scene* scn);
void scene_add_tri(struct Scene*, struct Triangle);
struct Scene mk_scene(const char* name, unsigned int width, unsigned int height, const char* file, unsigned int obj_capacity, struct Vec3 bg);

struct Camera mk_camera(struct Vec3 location, struct Vec3 rotation, struct Vec3 direction, int focal_length);
void camera_write_pixel(struct Scene* scn, int x, int y, struct Vec3 color);
