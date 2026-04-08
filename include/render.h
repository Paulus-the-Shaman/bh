#pragma once
#include "bh.h"
#include "maths.h"


struct Collision {
    float angle;
    float length;
    struct Vec3 loc;
};


void render(struct Scene* scn);
void render_obj();

void write_render(struct Scene* scn);
