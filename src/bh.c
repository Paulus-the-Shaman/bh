#include "stdio.h"
#include <stdlib.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


#include "maths.h"
#include "bh.h"


void write_render(struct Scene* scn) {
    int result = stbi_write_png(scn->file, scn->width, scn->height, 3, scn->image, scn->width * 3);
    if (result == 1) {
        printf("[---] rendered result with code: %i\n", result);
    } else {
        printf("[***] At Generating Image\n[***] Error Code: %i\n[***] Scene: %s", result, scn->name);
    }
}

void scene_add_tri(struct Scene* scn, struct Triangle tri) {
    struct Object obj;
    obj.capacity=1;
    obj.polygon=malloc(sizeof(struct Triangle));
    obj.polygon[0] = tri;
    scn->objects[scn->obj_num] = obj;
    scn->obj_num += 1;
}

struct Scene mk_scene(const char* name, unsigned int width, unsigned int height, const char* file, unsigned int obj_capacity, struct Vec3 bg) {
    struct Scene scn;
    scn.name    = name;
    scn.width   = width;
    scn.height  = height;
    scn.file    = file;
    scn.obj_cap = obj_capacity;
    scn.obj_num = 0;
    scn.objects = malloc(sizeof(struct Object)*scn.obj_cap);
    if (scn.objects == NULL) {
        printf("[***] Error allocating memory for objects\n[***] Scene: %s\n", scn.name);
        exit(-1);
    }
    scn.camera  = mk_camera(Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(0, 0, 1.0), 1.0);
    scn.image   = malloc(scn.width * scn.height * 3);
    if (scn.image == NULL) {
        printf("[***] Error allocating memory for image\n[***] Scene: %s\n", scn.name);
        exit(-1);
    }
    scn.bg = bg;
    return scn;
}

struct Camera mk_camera(struct Vec3 location, struct Vec3 rotation, struct Vec3 direction, int focal_length) {
    struct Camera cam;
    cam.loc             = location;
    cam.rot             = rotation;
    cam.dir             = direction;
    cam.focal_length    = focal_length;
    return cam;
}

void render(struct Scene* scn) {
    struct Vec3 bg = scn->bg;
    for (int y=0;y<scn->height;y++) {
        for (int x=0;x<scn->width;x++) {
            for (int i=0; i < scn->obj_num; i++){
                struct Triangle tri = scn->objects[0].polygon[0];
                struct Vec3 ray = Vec3(
                    (2.0f * x / (scn->height - 1)) - 1.0f,
                    (2.0f * y / (scn->height - 1)) - 1.0f,
                    scn->camera.focal_length
                );
    
                if (tri_ray_collision(tri, ray, scn->camera.loc) > 0) {
                    camera_write_pixel(scn, x, y, tri.color);
                } else {
                    camera_write_pixel(scn, x, y, bg);
                }
            }
        }
    }
}

void render_obj();

void camera_write_pixel(struct Scene* scn, int x, int y, struct Vec3 color) {
    int flipped_y = scn->height - 1 - y;
    int i = ((flipped_y * scn->width) + x) * 3;
    scn->image[i]        = color.x; // R
    scn->image[i + 1]    = color.y; // G
    scn->image[i + 2]    = color.z; // B
}
