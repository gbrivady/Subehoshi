#include <stdio.h>
#include "main.h"

int main() {
    vector2d* v1 = v2d_null();
    vector2d* v2 = v2d_null();

    vector2d* u1 = v2d_null();
    vector2d* u2 = v2d_null();
    u1->x = 10.;
    u2->x = -10.;
    printf("Object one : v1 = (%f, %f) u1 = (%f, %f) \n", v1->x, v1->y, u1->x, u1->y);
    printf("Object two : v2 = (%f, %f) u2 = (%f, %f) \n", v2->x, v2->y, u2->x, u2->y);

    void update_gravity(vector2d* v1, vector2d* v2, vector2d* u1, vector2d* u2){
        vector2d* a1 = v2d_sub_f(u2, u1);
        double norm2 = v2d_norm2(a1);
        norm2 = norm2*sqrt(norm2);
        v2d_scale(0.005/norm2,a1);
        v2d_add(v1, a1);
        v2d_add(u1, v1);

        v2d_scale(-1, a1);
        v2d_add(v2, a1);
        v2d_add(u2, v2);
        free(a1);
    };
    for (int i = 0; i < 1000; i++)
    {
        update_gravity(v1, v2, u1, u2);
        printf("Object one : v1 = (%f, %f) u1 = (%f, %f) \n", v1->x, v1->y, u1->x, u1->y);
        printf("Object two : v2 = (%f, %f) u2 = (%f, %f) \n", v2->x, v2->y, u2->x, u2->y);

    }
    
    free(v1);
    free(v2);
    free(u1);
    free(u2);
}
