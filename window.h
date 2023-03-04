//
// Created by Moritz H on 04.03.2023.
//

#ifndef P001_SIMULATION_WINDOW_H
#define P001_SIMULATION_WINDOW_H

int generateWindow(int width, int height);
int generateRenderer();
void render();
void setDrawColor(int r, int g, int b, int a);
void drawCircle(int x, int y, int r);
void drawLine(int x1, int y1, int x2, int y2);
void drawRect(int x, int y, int w, int h);
void closeWindow();

#endif //P001_SIMULATION_WINDOW_H