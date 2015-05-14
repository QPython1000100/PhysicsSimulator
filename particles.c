/* Contains the particle struct and the interactions between particles.  All interactions go in Calculate.
Currently just has the capability to bounce off each other based on velocity and mass.  Specific units are not implemented yet. */
#include <math.h>

struct Particle    // Generic particle struct containing all the values for a particle: its position, velocity, mass, energy. Will add force charges, spin, etc.
{
    double xc; // x, y, z coordinates in meters
    double yc;
    double zc;
    double xv; // x, y, z velocities in meters per second
    double yv;
    double zv;
    double mass; // kilograms
    double energy; // Joules
};

typedef struct Particle particle; // For ease of use

double *unitVector(double vec[3])   // Calculate unit tangent vector
{
    double sum = 0;
    int i;
    for (i=0; i<3; i++)
    {
        sum += pow(vec[i], 2);
    }
    double div = sqrt(sum);
    static double result[3];
    for (i=0; i<3; i++)
    {
        result[i]=vec[i]/div;
    }
    return result;
}

int Calculate(int len, particle *particles[])   // Performs the point-in-time calculations and then applies the calculated velocity to the calculated positions
{
    double GRAV = 6.673E-11;
    int i; // i and x are for the for loops
    int x;
    for (i=0; i<len; i++)
    {
        for (x=0; x<len; x++)
        {
            if (x <= i)   // Avoids having a particle interact with itself
            {
                continue;
            }
            if (particles[x]->xc == particles[i]->xc && particles[x]->yc == particles[i]->yc && particles[x]->zc == particles[i]->zc)   // If two particles are in the same place: collision
            {
                double mx = particles[x]->mass; // Ease of use
                double mi = particles[i]->mass;
                double xmult = mx/mi; // Multiplier for the impact of x on i
                double imult = 1/xmult; // Multiplier for the impact of i on x
                double vals[] = {particles[x]->xv - particles[i]->xv, particles[x]->yv - particles[i]->yv, particles[x]->zv - particles[i]->zv}; // Particle x's impact, so it doesn't change before we can compute for particle i
                particles[x]->xv += (particles[i]->xv - particles[x]->xv)*imult; // Velocity changes for collision
                particles[x]->yv += (particles[i]->yv - particles[x]->yv)*imult;
                particles[x]->zv += (particles[i]->zv - particles[x]->zv)*imult;
                particles[i]->xv += (vals[0])*xmult;
                particles[i]->yv += (vals[1])*xmult;
                particles[i]->zv += (vals[2])*xmult;
            }
            double vec[3] = {particles[x]->xc - particles[i]->xc, particles[x]->yc - particles[i]->yc, particles[x]->zc - particles[i]->zc}; // Gravity (classical physics for now)
            double *v = unitVector(vec);
            double dVec[3];
            dVec[0] = v[0];
            dVec[1] = v[1];
            dVec[2] = v[2];
            double magnitude = vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2];
            double gravForce = GRAV * (particles[x]->mass * particles[i]->mass)/magnitude;
            dVec[0] *= gravForce;
            dVec[1] *= gravForce;
            dVec[2] *= gravForce;
            particles[i]->xv += dVec[0]/particles[i]->mass;
            particles[i]->yv += dVec[1]/particles[i]->mass;
            particles[i]->zv += dVec[2]/particles[i]->mass;
            particles[x]->xv -= dVec[0]/particles[x]->mass;
            particles[x]->yv -= dVec[1]/particles[x]->mass;
            particles[x]->zv -= dVec[2]/particles[x]->mass; // End gravity
        }
    }
    for (i=0; i<len; i++)   // Apply velocity
    {
        particle *p = particles[i]; // Ease of use
        p->xc += p->xv;
        p->yc += p->yv;
        p->zc += p->zv;
    }
    return 0;
}
