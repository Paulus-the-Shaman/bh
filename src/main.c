#include "bh.h"
#include "maths.h"


int main() {
    struct Scene scene = mk_scene("main", 256, 256, "image.png", 1, Vec3(255, 0, 0));
    scene.camera.loc = Vec3(-3.0, 0.0, 15.0);
    scene_add_tri(&scene, mk_triangle(Vec3(0, 5, 20), Vec3(1, 0, 20), Vec3(-1, 0, 20)));
    render(&scene);
    write_render(&scene);
    return 0;
}


