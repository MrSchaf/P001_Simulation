#include "window.h"
#include <stdio.h>
#include <SDL.h>

SDL_Window *window;
SDL_Renderer *renderer;

int generateWindow(int width, int height){
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if(window == NULL){
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return 0;
    } else {
        generateRenderer();
    }
    return 1;
}

int generateRenderer(){
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return 0;
    }
    return 1;
}

void render(){
    SDL_RenderPresent(renderer);
}

void setDrawColor(int r, int g, int b, int a){
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void drawCircle(int x, int y, int r){
    for(int w = 0; w < r * 2; w++){
        for(int h = 0; h < r * 2; h++){
            int dx = r - w;
            int dy = r - h;
            if((dx*dx + dy*dy) <= (r * r)){
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void drawLine(int x1, int y1, int x2, int y2){
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void drawRect(int x, int y, int w, int h){
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderDrawRect(renderer, &rect);
}

void closeWindow(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;

    SDL_Quit();
}