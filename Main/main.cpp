#include "../Includes/raylib.h"
#include "../Includes/raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "../Includes/raygui.h"

#include <iostream>

using namespace std;

#define W 1920
#define H 1080

float SCAL = 1;

float range_x = 16 * SCAL;     
float range_y = 9 * SCAL;

float scale_x = W / (range_x * 2);
float scale_y = H / (range_y * 2);

Color background = {20, 20, 20, 255};
Color function = {49, 165, 206, 255};

float cX(float x) {
    return (W / 2) + (x * scale_x);
}

float cY(float y) {
    return (H / 2) - (y * scale_y);
}

float pointX(float p) {
    return p * scale_x;
}

float pointY(float p) {
    return p * scale_y;
}

void drawP(float x, float y) {
    DrawPixel(cX(x), cY(y), function);
}

void drawL(float x1, float y1, float x2, float y2, Color c) {
    DrawLine(cX(x1), cY(y1), cX(x2), cY(y2), c);
}

int main () {
    float a = 1;
    float b = 0;
    float c = 0;  

    InitWindow(W, H, nullptr);

    Font font = LoadFont("/usr/share/fonts/google-noto/NotoSerif-Regular.ttf");
    GuiSetFont(font);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    GuiSetStyle(DEFAULT, TEXT_PADDING, 20);
    GuiSetStyle(SLIDER, BASE_COLOR_NORMAL, 0);
    GuiSetStyle(SLIDER, SLIDER_WIDTH, 10);

    SetTargetFPS(60);

    while (WindowShouldClose() == false) {
        BeginDrawing();

        ClearBackground(background);

        drawL(0, range_y, 0, -range_y, RAYWHITE);
        drawL(-range_x, 0, range_x, 0, RAYWHITE);

        for (int i = -range_x; i <= range_x; i++) {
            if (i == 0) continue;
            GuiLabel({cX(i - 0.27), cY(0.10), pointX(1.9), pointY(1)}, TextFormat("%d", i));
            drawL(i, range_y, i, -range_y, {50, 50, 50, 255});
        }

        for (int i = -range_y; i <= range_y; i++) {
            if (i == 0) continue;
            GuiLabel({cX(-1), cY(i + 0.2), pointX(1.9), pointY(1)}, TextFormat("%d", i));
            drawL(-range_x, i, range_x, i, {50, 50, 50, 255});
        }

        SCAL -= GetMouseWheelMove() / 8;

        range_x = 16 * SCAL;     
        range_y = 9 * SCAL;

        scale_x = W / (range_x * 2);
        scale_y = H / (range_y * 2);

        for (float x = -range_x; x < range_x; x += 0.0001) {
            float y = a * (x * x) + (b * x) + (c);

            drawP(x, y);
        }

        // y intersection
        DrawCircle(cX(0), cY(c), pointX(0.15), function);
        DrawCircle(cX(0), cY(c), pointX(0.1), background);

        // x intersection
        float d = (b*b) - (4 * a * c);

        if (d > 0) {
            float x1 = (-b + sqrt(d)) / (2 * a);
            float x2 = (-b - sqrt(d)) / (2 * a);

            DrawCircle(cX(x1), cY(0), pointX(0.15), function);
            DrawCircle(cX(x1), cY(0), pointX(0.1), background);
            DrawCircle(cX(x2), cY(0), pointX(0.15), function);
            DrawCircle(cX(x2), cY(0), pointX(0.1), background);
        }

        if (d == 0) {
            float x3 = -b / (2 * a);

            DrawCircle(cX(x3), cY(0), pointX(0.15), function);
            DrawCircle(cX(x3), cY(0), pointX(0.1), background);
        }

        GuiSlider({1622.4, 1020 - 30, 210, 18}, "a", TextFormat("%.2f", a), &a, -5, 5);
        GuiSlider({1622.4, 1050 - 30, 210, 18}, "b", TextFormat("%.2f", b), &b, -range_x, range_x);
        GuiSlider({1622.4, 1080 - 30, 210, 18}, "c", TextFormat("%.2f", c), &c, -range_y, range_y);

        GuiSetStyle(DEFAULT, TEXT_SIZE, 30);

        GuiLabel({0, 0, 500, 50}, TextFormat("%.2f x^2 + (%.2f x) + (%.2f)", a, b, c));

        GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}
