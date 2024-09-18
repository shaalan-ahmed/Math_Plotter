#include "../Includes/raylib.h"
#include "../Includes/raymath.h"

#define RAYGUI_IMPLEMENTATION
#include "../Includes/raygui.h"

#define W 1920
#define H 1080

float origin_x = W / 2;
float origin_y = H / 2;

float SCAL = 1;

float range_x = 16 * SCAL;     
float range_y = 9 * SCAL;

float scale_x = W / (range_x * 2);
float scale_y = H / (range_y * 2);

Color background = {20, 20, 20, 255};
Color function = {49, 165, 206, 255};

float X_org(float p) {
    return (W / 2) + (p * scale_x);
}

float Y_org(float p) {
    return (H / 2) - (p * scale_y);
}

float pointX(float p) {
    return p * scale_x;
}

float pointY(float p) {
    return p * scale_y;
}

void drawP(float x, float y) {
    DrawPixel(X_org(x), Y_org(y), function);
}

void drawL(float x1, float y1, float x2, float y2, Color c) {
    DrawLine(X_org(x1), Y_org(y1), X_org(x2), Y_org(y2), c);
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

    SetTargetFPS(600);

    while (WindowShouldClose() == false) {
        BeginDrawing();

        ClearBackground(background);

        drawL(0, range_y, 0, -range_y, RAYWHITE);
            drawL(-range_x, 0, range_x, 0, RAYWHITE);

        for (int i = -range_x; i <= range_x; i++) {
            if (i == 0) continue;
            GuiLabel({X_org(i - 0.27), Y_org(0.10), pointX(1.9), pointY(1)}, TextFormat("%d", i));
            drawL(i, range_y, i, -range_y, {50, 50, 50, 255});
        }

        for (int i = -range_y; i <= range_y; i++) {
            if (i == 0) continue;
            GuiLabel({X_org(-1), Y_org(i + 0.2), pointX(1.9), pointY(1)}, TextFormat("%d", i));
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
        DrawCircle(X_org(0), Y_org(c), pointX(0.15), function);
        DrawCircle(X_org(0), Y_org(c), pointX(0.1), background);

        // x intersection
        float d = (b*b) - (4 * a * c);

        if (d > 0) {
            float x1 = (-b + sqrt(d)) / (2 * a);
            float x2 = (-b - sqrt(d)) / (2 * a);

            DrawCircle(X_org(x1), Y_org(0), pointX(0.15), function);
            DrawCircle(X_org(x1), Y_org(0), pointX(0.1), background);
            DrawCircle(X_org(x2), Y_org(0), pointX(0.15), function);
            DrawCircle(X_org(x2), Y_org(0), pointX(0.1), background);
        }

        if (d == 0) {
            float x3 = -b / (2 * a);

            DrawCircle(X_org(x3), Y_org(0), pointX(0.15), function);
            DrawCircle(X_org(x3), Y_org(0), pointX(0.1), background);
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
