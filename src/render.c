#include <stdio.h>
#include "bh.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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


void write_render(struct Scene* scn) {
    int result = stbi_write_png(scn->file, scn->width, scn->height, 3, scn->image, scn->width * 3);
    if (result == 1) {
        printf("[---] rendered result with code: %i\n", result);
    } else {
        printf("[***] At Generating Image\n[***] Error Code: %i\n[***] Scene: %s", result, scn->name);
    }
}
