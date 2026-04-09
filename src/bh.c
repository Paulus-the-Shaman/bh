#include "stdio.h"
#include <stdlib.h>


#include "maths.h"
#include "bh.h"



void scene_add_tri(struct Scene* scn, struct Triangle tri, struct Vec3 color) {
    if (scn->obj_num == scn->obj_cap) {
        printf("[***] Too many objects in Scene: %s\n", scn->name);
    }
    struct Object obj;
    obj.capacity=1;
    obj.polygon=malloc(sizeof(struct Triangle));
    obj.polygon[0] = tri;
    obj.color = color;
    scn->objects[scn->obj_num] = obj;
    scn->obj_num += 1;
}

void scene_add_obj(struct Scene* scn, struct Object obj) {
    if (scn->obj_num == scn->obj_cap) {
        printf("[***] Too many objects in Scene: %s\n", scn->name);
    }
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


void camera_write_pixel(struct Scene* scn, int x, int y, struct Vec3 color) {
    int flipped_y = scn->height - 1 - y;
    int i = ((flipped_y * scn->width) + x) * 3;
    scn->image[i]        = color.x; // R
    scn->image[i + 1]    = color.y; // G
    scn->image[i + 2]    = color.z; // B
}
