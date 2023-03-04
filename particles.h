//
// Created by Moritz H on 04.03.2023.
//

#ifndef P001_SIMULATION_PARTICLES_H
#define P001_SIMULATION_PARTICLES_H

int generateParticles(int count);
int addParticle(int x, int y, int vx, int vy, int r, int m);
void update(double dt);
int randomInt(int min, int max);
void freeParticles();


#endif //P001_SIMULATION_PARTICLES_H