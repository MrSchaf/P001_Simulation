#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include "window.h"
#include "particles.h"
#define count 20
#define tps 100

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;


int init();
void loop();
void close();

int main(int argc, char* args[] ) {

    if(init() != 1){
        printf("Failed to initialize!\n");
    } else {

        loop();

        close();
    }
    return 0;
}

int init(){
    int success = 1;

    if(generateWindow(SCREEN_WIDTH, SCREEN_HEIGHT) != 1){
        printf("Failed to initialize window!\n");
        success = 0;
    } else if(generateParticles(count) != 1){
        printf("Failed to initialize particles!\n");
        success = 0;
    }

    return success;
}

void loop(){
    int quit = 0;
    SDL_Event e;
    clock_t start, end;
    start = clock();
    double dt;

    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = 1;
            }
        }
        while(!quit){
            while(SDL_PollEvent(&e) != 0){
                if(e.type == SDL_QUIT){
                    quit = 1;
                }
            }
            end = clock();
            dt = (double)(end - start) / CLOCKS_PER_SEC;
            if(dt >= 1.0 / tps){
                start = end;
                update(dt);
                render();
            }
        }
    }
}


void close(){
    closeWindow();
    freeParticles();
}