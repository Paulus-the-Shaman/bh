#include "stdio.h"
#include <stdlib.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


#include "maths.h"
#include "bh.h"


void write_render(struct Scene* scn) {
    int result = stbi_write_png(scn->file, scn->width, scn->height, 3, scn->image, 3);
    if (result == 1) {
        printf("[---] rendered result with code: %i\n", result);
    } else {
        printf("[***] At Generating Image\n[***] Error Code: %i\n[***] Scene: %s", result, scn->name);
    }
}

void scene_add_tri(struct Scene* scn, struct Triangle tri) {
    scn->objects[scn->obj_num] = tri;
    scn->obj_num += 1;
}

struct Scene mk_scene(const char* name, unsigned int width, unsigned int height, const char* file, unsigned int obj_capacity) {
    struct Scene scn;
    scn.name    = name;
    scn.width   = width;
    scn.height  = height;
    scn.file    = file;
    scn.obj_cap = obj_capacity;
    scn.obj_num = 0;
    scn.objects = malloc(sizeof(struct Triangle)*scn.obj_cap);
    if (scn.objects == NULL) {
        printf("[***] Error allocating memory for objects\n[***] Scene: %s\n", scn.name);
        exit(-1);
    }
    scn.camera  = mk_camera(Vec3(0, 0, 0), 10);
    scn.image   = malloc(scn.width * scn.height * 3);
    if (scn.image == NULL) {
        printf("[***] Error allocating memory for image\n[***] Scene: %s\n", scn.name);
        exit(-1);
    }
    return scn;
}

struct Camera mk_camera(struct Vec3 location, int focal_length) {
    struct Camera cam;
    cam.loc             = Vec3(0, 0, 0);
    cam.dir             = Vec3(0, 0, 1.0);
    cam.rot             = Vec3(0, 0, 0);
    cam.focal_length    = 10;
    return cam;
}

void render(struct Scene* scn) {
    for (int y=0;y<scn->height;y++) {
        for (int x=0;x<scn->width;x++) {
            struct Vec3 ray = Vec3(x-((float)x/2.0), (y-(float)y/2.0), scn->camera.focal_length);
            struct Vec3 color = Vec3(130, 70, 50);
            camera_write_pixel(scn, x, y, color);
            /*
            int i = ((y * scn->width) + x) * 3;
            scn->image[i]        = 70; // R
            scn->image[i + 1]    = 150; // G
            scn->image[i + 2]    = 30; // B
            */
        }
    }
}

void camera_write_pixel(struct Scene* scn, int x, int y, struct Vec3 color) {
    int i = ((y * scn->width) + x) * 3;
    scn->image[i]        = color.x; // R
    scn->image[i + 1]    = color.y; // G
    scn->image[i + 2]    = color.z; // B
}
