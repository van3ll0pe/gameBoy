#pragma once
#ifndef __PPU_HPP__
#define __PPU_HPP__

#define PIXEL_WIDTH 4
#define PIXEL_HEIGHT 4

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144

//######### COLOR PIXELS

#define DARKEST_GREEN 15,56,15
#define DARK_GREEN 48,98,48
#define LIGHT_GREEN 139,172,15
#define LIGHTEST_GREEN 155,188,15



#include "component.hpp"
#include <memory>
#include <SDL2/SDL.h>
#include <array>

namespace GB
{
    class Ppu : public Component
    {
        private:
            int window_width;
            int window_height;
            std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
            std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> render;

            std::array<uint8_t, SCREEN_WIDTH * SCREEN_HEIGHT * 3> frameBuffer;

            uint16_t tileDataArea;  //OBJECT address where stocked tiles
            uint16_t tileMapArea; //BACKGROUND address wherer stocked tiles
        
        public:
            Ppu();
            ~Ppu();

            //void draw();
            void clear_screen();
            void display();



    };
}

#endif //__PPU_HPP__