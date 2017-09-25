#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>

namespace caveofprogramming {

    class Screen {
    private:
        int screenWidth;
        int screenHeight;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        Uint32* buffer1;
        Uint32* buffer2;
        SDL_Event event;
    public:
        const static int SCREEN_WIDTH = 800;
        const static int SCREEN_HEIGHT = 600;
        const static Uint8 ALPHA = 0xFF;
        const int size = screenWidth * screenHeight;

        Screen(int screenWidth = SCREEN_WIDTH, int screenHeight = SCREEN_HEIGHT) :
        screenWidth(screenWidth), screenHeight(screenHeight),
        window(NULL), renderer(NULL),
        texture(NULL), buffer1(NULL), buffer2(NULL) {
            
        }
        
        int getScreenWidth();
        int getScreenHeight();
        bool init();
        bool processEvent();
        void update();
        void blurBox();
        void clear();
        void close();
        void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
        ~Screen();
    };
}

#endif /* SCREEN_H_ */