#include "bh.h"
#include "maths.h"
#include "render.h"


int main() {
    // Scene and Camera
    struct Scene scene = mk_scene("main", 500, 500, "image.png", 2, Vec3(50, 50, 50));
    scene.camera.loc = Vec3(0.0, 0.0, 0.0);

    // Mesh
    struct Triangle tri = Triangle(Vec3(0, 1, 5), Vec3(1, 0, 5), Vec3(-1, 0, 5));
    scene_add_tri(&scene, tri, Vec3(255, 0, 0));
    scene_add_tri(&scene, Triangle(Vec3(-1, .5, 3), Vec3(-1, 0, 3), Vec3(2, 0, 3)), Vec3(0, 255, 0));

    // Render
    render(&scene);
    write_render(&scene);
    return 0;
}


