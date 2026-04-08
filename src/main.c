#include "bh.h"
#include "maths.h"


int main() {
    // Scene and Camera
    struct Scene scene = mk_scene("main", 500, 500, "image1.png", 2, Vec3(255, 255, 255));
    scene.camera.loc = Vec3(0.0, 0.0, 0.0);

    // Mesh
    struct Triangle tri = mk_triangle(Vec3(0, 1, 5), Vec3(1, 0, 5), Vec3(-1, 0, 5), Vec3(255, 255, 0));
    scene_add_tri(&scene, tri);
    scene_add_tri(&scene, mk_triangle(Vec3(0, 5, 20), Vec3(1, 0, 20), Vec3(-1, 0, 20), Vec3(0, 255, 255)));

    // Render
    render(&scene);
    write_render(&scene);
    return 0;
}


