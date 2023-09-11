#include "ppu.hpp"
#include <iostream>
#include <iterator>

#include "bus.hpp"

namespace GB
{
    Ppu::Ppu() : Component(), window(nullptr, SDL_DestroyWindow), render(nullptr, SDL_DestroyRenderer)
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            exit(EXIT_FAILURE);

        this->window_height = SCREEN_HEIGHT * PIXEL_HEIGHT;
        this->window_width = SCREEN_WIDTH * PIXEL_WIDTH;

        this->window.reset(SDL_CreateWindow("GameBoy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN));
        this->render.reset(SDL_CreateRenderer(this->window.get(), -1, SDL_RENDERER_ACCELERATED));
        
        
        this->frameBuffer.fill(0);
    }

    Ppu::~Ppu()
    {
        this->render.~unique_ptr();
        this->window.~unique_ptr();
        SDL_Quit();
    }

    void
    Ppu::display()
    {
        SDL_RenderPresent(render.get());
    }

    void
    Ppu::clear_screen()
    {
        SDL_SetRenderDrawColor(render.get(), 0, 0, 0, 255);
        SDL_RenderClear(render.get());
    }

    
/*
    void
    Ppu::draw()
    {
        std::size_t i = 0;
        while (i < this->frameBuffer.size)
        {
            uint8_t r = this->frameBuffer[i++];
            uint8_t g = this->frameBuffer[i++];
            uint8_t b = this->frameBuffer[i++];

            SDL_Rect pixel = {.h = PIXEL_HEIGHT, .w = PIXEL_WIDTH, .x = }


        }
    }*/
}

