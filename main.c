#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#define count 20
#define tps 100

SDL_Window *window;
SDL_Renderer *renderer;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct particle {
    double x;
    double y;
    double vx;
    double vy;
    double r;
    double m;
};

struct particle particles[count];

int init();
void generateParticles();
void loop();
int collision(struct particle *p1, struct particle *p2);
void collisionResponse(struct particle *p1, struct particle *p2);
void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius);
void update(double dt);
void render();
void close();

int main(int argc, char* args[] ) {

    if(init() != 1){
        printf("Failed to initialize!\n");
    } else {
        generateParticles();

        loop();

        close();
    }
    return 0;
}

int init(){
    int success = 1;

    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL){
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        success = 0;
    } else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer == NULL){
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            success = 0;
        } else {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags)){
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = 0;
            }
        }
    }

    return success;
}

void generateParticles(){
    for(int i = 0; i < count; i++){
        particles[i].x = rand() % SCREEN_WIDTH;
        particles[i].y = rand() % SCREEN_HEIGHT;
        particles[i].vx = rand() % 50;
        particles[i].vy = rand() % 50;
        particles[i].r = 20;
        particles[i].m = 1;
    }
}

void loop(){
    int quit = 0;
    SDL_Event e;
    clock_t start = clock(), end;
    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = 1;
            }
        }

        end = clock();
        if((end - start) >= 1 / tps){
            double dt = (end - start) / (double) tps;
            update(dt);
            render();
            start = end;
        }
    }
}

void update(double dt){
    for(int i = 0; i < count; i++){
        particles[i].x += particles[i].vx * dt;
        particles[i].y += particles[i].vy * dt;

        if(particles[i].x < particles[i].r || particles[i].x > SCREEN_WIDTH - particles[i].r){
            particles[i].vx *= -1;
        }

        if(particles[i].y < particles[i].r || particles[i].y > SCREEN_HEIGHT - particles[i].r){
            particles[i].vy *= -1;
        }
    }

    for(int i = 0; i < count; i++){
        for(int j = i + 1; j < count; j++){
            if(collision(&particles[i], &particles[j]) == 1){
                collisionResponse(&particles[i], &particles[j]);
            }
        }
    }
}

void render(){
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    for(int i = 0; i < count; i++){
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        DrawCircle(renderer, particles[i].x, particles[i].y, particles[i].r);
        for(int j = i + 1; j < count; j++){
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderDrawLine(renderer, particles[i].x, particles[i].y, particles[j].x, particles[j].y);
        }
    }

    SDL_RenderPresent(renderer);
}

int collision(struct particle *p1, struct particle *p2) {
    double dx = p1->x - p2->x;
    double dy = p1->y - p2->y;
    double dr = p1->r + p2->r;

    if (dx * dx + dy * dy < dr * dr) {
        return 1;
    }

    return 0;
}

void collisionResponse(struct particle *p1, struct particle *p2) {
    double dx = p1->x - p2->x;
    double dy = p1->y - p2->y;
    double dvx = p1->vx - p2->vx;
    double dvy = p1->vy - p2->vy;

    double dvdr = dx * dvx + dy * dvy;
    double dist = p1->r + p2->r;

    double J = 2 * p1->m * p2->m * dvdr / ((p1->m + p2->m) * dist);

    double Jx = J * dx / dist;
    double Jy = J * dy / dist;

    p1->vx -= Jx / p1->m;
    p1->vy -= Jy / p1->m;

    p2->vx += Jx / p2->m;
    p2->vy += Jy / p2->m;
}

void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y){
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void close(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}