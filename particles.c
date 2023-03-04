#include "particles.h"
#include <stdlib.h>
#include <stdio.h>

struct particle {
    double x;
    double y;
    double vx;
    double vy;
    double r;
    double m;
};

struct particle *particles;

int generateParticles(int count) {
    printf("Generating %d particles...\n", count);
    int size = sizeof(struct particle) * count;
    printf("Allocating %d bytes of memory...\n", size);
    particles = malloc(size);
    if(particles == NULL){
        printf("Failed to allocate memory for particles!\n");
        return 0;
    }

    for(int i = 0; i < count; i++){
        addParticle(0, 0, 0, 0, 0, 0);
    }

    return 1;
}

int addParticle(int x, int y, int vx, int vy, int r, int m) {
    int success = 1;

    struct particle p = {x, y, vx, vy, r, m};
    particles[sizeof(particles) / sizeof(struct particle)] = p;

    return success;
}

void update(double dt) {
    for(int i = 0; i < sizeof(particles) / sizeof(struct particle); i++){
        particles[i].x += particles[i].vx * dt;
        particles[i].y += particles[i].vy * dt;
    }
}

int randomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void freeParticles() {
    free(particles);
}