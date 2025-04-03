//Data of a cuboid

#include <stdio.h>
#include <stdbool.h>


//Cuboid structure
typedef struct {

    double length;
    double width;
    double height;

} Cuboid;

//Check the values of the sides
void set_size(Cuboid *c, double l, double w, double h) {
    if (l > 0 && w > 0 && h > 0) {
        c->length = l;
        c->width = w;
        c->height = h;
    }
    else {
        printf("Invalid dimensions. Please provide positive values.\n");
    }
}

//Calculate volume
double calc_volume(Cuboid c) {
    return c.length * c.width * c.height;
}

//Calculate surface
double calc_surface(Cuboid c) {
    return 2 * (c.length * c.width + c.length * c.height + c.width * c.height);
}

//Check if the cuboid has a square face
bool has_square_face(Cuboid c) {
    return (c.length == c.width || c.length == c.height || c.width == c.height);
}
int main() {

    Cuboid myCuboid;

    set_size(&myCuboid, 3.0, 6.0, 6.0);
    printf("The volume of the cuboid is: %.2f\n", calc_volume(myCuboid));
    printf("The surface area of the cuboid is: %.2f\n", calc_surface(myCuboid));

    if (has_square_face(myCuboid)) {
        printf("The cuboid has a square face.\n");
    }
    else {
        printf("The cuboid does not have a square face.\n");
    }

    return 0;
}