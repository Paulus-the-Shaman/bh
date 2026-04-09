#include <stdio.h>
#include "bh.h"
#include "maths.h"
#include "render.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void render(struct Scene* scn) {
    struct Vec3 bg = scn->bg;
    for (int y=0;y<scn->height;y++) {
        for (int x=0;x<scn->width;x++) {
            //making ray
            struct Vec3 ray = Vec3(
                (2.0f * x / (scn->height - 1)) - 1.0f,
                (2.0f * y / (scn->height - 1)) - 1.0f,
                scn->camera.focal_length
            );
            // looping through all objects with ray
            struct Collision collision;
            collision.bool = FALSE;
            for (int i=0; i < scn->obj_num; i++){
                struct Collision new_col = render_obj(scn->objects[i], ray, scn->camera.loc);
                if (new_col.length < collision.length)
                    collision = new_col;
            }
            //apply pixel color
            if (collision.bool)
                camera_write_pixel(scn, x, y, collision.color);
            else
             camera_write_pixel(scn, x, y, bg);

        }
    }
}

struct Collision render_obj(struct Object* obj, struct Vec3* ray, struct Vec3* cam_loc) {
    struct Collision col;
    struct Collision new_col;
    col.length = 9999999; // max length //TODO set to real max length
    for (int i=0; i<obj->capacity; i++) {
        new_col = tri_ray_collision(&obj->polygon[i], ray, cam_loc)
    }
}


void write_render(struct Scene* scn) {
    int result = stbi_write_png(scn->file, scn->width, scn->height, 3, scn->image, scn->width * 3);
    if (result == 1) {
        printf("[---] rendered result with code: %i\n", result);
    } else {
        printf("[***] At Generating Image\n[***] Error Code: %i\n[***] Scene: %s", result, scn->name);
    }
}
