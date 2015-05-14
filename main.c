/* This is just a demo used to test the program.
Currently trying to simulate the Earth orbiting the Sun. */

#include <stdio.h>
#include "particles.c"

int main()
{
    particle Earth, Sun;
    Earth.xc = 1496E8; // All 3 coordinates are this makes appropriate distance from the sun
    Earth.yc = 0;
    Earth.zc = 0;
    Sun.xc = 0;
    Sun.yc = 0;
    Sun.zc = 0;
    Sun.xv, Sun.yv, Sun.zv = 0;
    Earth.xv, Earth.zv = 0;
    Earth.yv = 3E4;
    Earth.mass = 5.924E24;
    Sun.mass = 1.989E30;
    int i = 0;
    particle *particles[2] = {&Earth, &Sun};
    while (1==1)
    {
        Calculate(2, particles);
        ++i;
        if (i % 604800 == 0)
        {
            printf("%f, %f, %f\n", Earth.xc, Earth.yc, Earth.zc);
            sleep(1);
        }
    }
}
