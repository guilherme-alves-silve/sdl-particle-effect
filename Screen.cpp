#include "Screen.h"

#include <iostream>

using namespace std;

namespace caveofprogramming {

    bool Screen::init() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            cout << "Failed to init SDL: " << SDL_GetError() << endl;
            return false;
        }

        window = SDL_CreateWindow(
                "Particle Fire explosion",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                screenWidth,
                screenHeight,
                SDL_WINDOW_SHOWN
                );

        if (NULL == window) {
            cout << "Failed to create the window: " << SDL_GetError() << endl;
            SDL_Quit();
            return false;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
        texture = SDL_CreateTexture(
                renderer,
                SDL_PIXELFORMAT_RGBA8888,
                SDL_TEXTUREACCESS_STATIC,
                screenWidth,
                screenHeight
                );

        if (NULL == renderer) {
            cout << "Cannot create renderer: " << SDL_GetError() << endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }

        if (NULL == texture) {
            cout << "Cannot create texture: " << SDL_GetError() << endl;
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }

        buffer1 = new Uint32[size];
        buffer2 = new Uint32[size];

        clear();

        return true;
    }

    int Screen::getScreenWidth() {
        return screenWidth;
    }

    int Screen::getScreenHeight() {
        return screenHeight;
    }

    void Screen::update() {
        SDL_UpdateTexture(texture, NULL, buffer1, screenWidth * sizeof (Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    void Screen::clear() {
        memset(buffer1, 0, size * sizeof (Uint32));
        memset(buffer2, 0, size * sizeof (Uint32));
    }

    void Screen::blurBox() {

        Uint32* temp = buffer1;
        buffer1 = buffer2;
        buffer2 = temp;

        for (int y = 0; y < screenHeight; y++) {
            for (int x = 0; x < screenWidth; x++) {

                int redTotal = 0;
                int greenTotal = 0;
                int blueTotal = 0;

                Uint8 red;
                Uint8 green;
                Uint8 blue;

                for (int row = -1; row <= 1; row++) {
                    for (int col = -1; col <= 1; col++) {
                        int currentY = row + y;
                        int currentX = col + x;
                        
                        if ((currentY >= 0 && currentY < screenHeight) &&
                                (currentX >= 0 && currentX < screenWidth)) {
                            Uint32 color = buffer2[currentY * screenWidth + currentX];
                            red = color >> 24;
                            green = color >> 16;
                            blue = color >> 8;

                            redTotal += red;
                            greenTotal += green;
                            blueTotal += blue;
                        }
                    }
                }

                red = redTotal / 9;
                green = greenTotal / 9;
                blue = blueTotal / 9;

                setPixel(x, y, red, green, blue);
            }
        }
    }

    void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

        if ((x < 0 || x >= screenWidth) ||
                (y < 0 || y >= screenHeight)) {
            return;
        }

        Uint32 color = 0;
        color += red;
        color <<= 8;
        color += green;
        color <<= 8;
        color += blue;
        color <<= 8;
        color += ALPHA;
        
        buffer1[(y * screenWidth) + x] = color;
    }

    bool Screen::processEvent() {
        while (SDL_PollEvent(&event)) {
            if (SDL_QUIT == event.type) {
                return false;
            }
        }

        return true;
    }

    void Screen::close() {
        delete [] buffer1;
        delete [] buffer2;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(texture);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    Screen::~Screen() {
        close();
    }
}