#pragma once
#include "bh.h"
#include "maths.h"


enum BOOL {
    FALSE,
    TRUE
};



void render(struct Scene* scn);
struct Collision render_obj(struct Object* obj, struct Vec3 ray, struct Vec3 cam_loc);

void write_render(struct Scene* scn);
