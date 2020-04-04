#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<memory.h>

const int WIDTH = 800;
const int HEIGHT = 600;

typedef struct
{
    uint8_t r,g,b,a;
}Pixel;

Pixel get_pixel(char* text,int index){
    Pixel* pixel = malloc(sizeof(Pixel));
    memset(pixel,0,sizeof(Pixel));
    if(text[index] == '1'){
        pixel->r = 255;
        pixel->g = 255;
        pixel->b = 255; 
    }
    pixel->a = 255;
    return *pixel;
}


int fget_size(FILE* file){
    int ch = 0;
    int count = 0;
    while(ch != EOF){
        ch = fgetc(file);
        count++;
    }
    return count;
}

int main(int argc,char *argv[]){

    FILE* fd = fopen("message.txt","r");
    Pixel pixels[2550];
    char text[2550];
    memset(&text,0,2550);
    fread(text,1,2550,fd);
    for(int i = 0;i < 2550;i++){
        Pixel pixel = get_pixel(text,i);
        printf("R: %d G: %d B: %d\n",pixel.r,pixel.g,pixel.b);
        pixels[i] = pixel;
    }

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("binaryImage",50,50,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_Event event;

    SDL_Surface *bits = SDL_CreateRGBSurfaceFrom(pixels,51,51,32,51*4,
                                                        0xff000000,
                                                        0x00ff0000,
                                                        0x0000ff00,
                                                        0x000000ff);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,bits);

    bool running = true;
    while(running){
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_QUIT:{
                return -1;
            }
        }
        SDL_Rect src_rect = {0,0,51,51};
        SDL_Rect dest_rect = {10,10,300,300};
        SDL_RenderCopy(renderer,texture,&src_rect,&dest_rect);

        SDL_RenderPresent(renderer);
    }

    fclose(fd);
    return 0;
}