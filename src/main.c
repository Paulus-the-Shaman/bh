#include <stdlib.h>

#include "maths.h"
#include "render.h"
#include "bh.h"


int main() {
    // Scene and Camera
    struct Scene scene = mk_scene("main", 500, 500, "image.png", 2, Vec3(50, 50, 50));
    scene.camera.loc = Vec3(0.0, 0.0, 0.0);

    // Mesh
    struct Triangle* tris = malloc(sizeof(struct Triangle)*6);
    struct Vec3 A = Vec3(-1, 0, 5);
    struct Vec3 B = Vec3(1, 0, 5);
    struct Vec3 C = Vec3(1, 0, 6);
    struct Vec3 D = Vec3(-1, 0, 6);
    struct Vec3 E = Vec3(0, 1, 5.5);
    tris[0] = Triangle(A,E,B);
    tris[1] = Triangle(B,E,C);
    tris[2] = Triangle(C,E,D);
    tris[3] = Triangle(D,E,A);
    tris[4] = Triangle(A,B,D);
    tris[5] = Triangle(D,C,B);
    struct Object obj = Object(6, Vec3(200, 79, 30), tris);
    Obj_rotate(&obj, Z, rad(30));
    Obj_rotate(&obj, Y, rad(30));
    scene_add_obj(&scene, obj);

    //scene_add_tri(&scene, Triangle(Vec3(1, 0, 5), Vec3(-1, 0, 5), Vec3(0, 1, 5)) , Vec3(255, 0, 0));
    //scene_add_tri(&scene, Triangle(Vec3(1, 0, 4), Vec3(-.5, 0, 4), Vec3(1.5, .5, 6)) , Vec3(0, 255, 0));
    

    // Render
    render(&scene);
    write_render(&scene);
    return 0;
}


