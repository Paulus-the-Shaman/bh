#include <stdlib.h>

#include "bh.h"



int main() {
    struct Scene scene = mk_scene("main", 256, 256, "image.png", 1);
    render(&scene);
    write_render(&scene);
    return 0;
}


