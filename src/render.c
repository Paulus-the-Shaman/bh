#include <stdio.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "bh.h"
#include "maths.h"
#include "render.h"

void render(struct Scene* scn) {
    struct Vec3 bg = scn->bg;
    for (int y=0;y<scn->height;y++) {
        for (int x=0;x<scn->width;x++) {

            //making ray
            struct Vec3 ray = Vec3(
                (2.0f * x / (scn->width - 1)) - 1.0f,
                (2.0f * y / (scn->height - 1)) - 1.0f,
                scn->camera.focal_length
            );

            // looping through all objects with ray
            struct Collision collision;
            struct Collision new_col;
            if (scn->obj_num > 0) collision = render_obj(&scn->objects[0], ray, scn->camera.loc);
            if (scn->obj_num > 1) {
                for (int i=1; i < scn->obj_num; i++) {
                    new_col = render_obj(&scn->objects[i], ray, scn->camera.loc);
                    if (!(collision.Bool) && (new_col.Bool)) {collision = new_col;}
                    else if ((new_col.length < collision.length)) {
                        collision = new_col;
                    }
                }
            }

            //apply pixel color
            if (collision.Bool)
                camera_write_pixel(scn, x, y, collision.color);
            else
                camera_write_pixel(scn, x, y, bg);
        }
    }
}

struct Collision render_obj(struct Object* obj, struct Vec3 ray, struct Vec3 cam_loc) {
    struct Collision col;
    struct Collision new_col;
    col.Bool = 0;
    if (obj->capacity > 0) col = tri_ray_collision(&obj->polygon[0], ray, cam_loc, obj->color);
    if (obj->capacity > 1) {
        for (int i=1; i<obj->capacity; i++) {
            new_col = tri_ray_collision(&obj->polygon[i], ray, cam_loc, obj->color);
            if ((new_col.length < col.length) && (col.Bool)) new_col = col;
            if (!(col.Bool) && (new_col.Bool)) {col = new_col;}
            else if ((new_col.length < col.length)) {
                col = new_col;
            }
        }
    }
    return col;
}


void write_render(struct Scene* scn) {
    int result = stbi_write_png(scn->file, scn->width, scn->height, 3, scn->image, scn->width * 3);
    if (result == 1) {
        printf("[---] rendered result with code: %i\n", result);
    } else {
        printf("[***] At Generating Image\n[***] Error Code: %i\n[***] Scene: %s", result, scn->name);
    }
}
