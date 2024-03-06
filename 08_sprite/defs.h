#ifndef _DEFS__H
#define _DEFS__H

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Hello World!";

const char* MAN_SPRITE_FILE = "img\\foo.png";
const int MAN_CLIPS[][4] = {
    {  0, 0, 64, 205},
    { 64, 0, 64, 205},
    {128, 0, 64, 205},
    {192, 0, 64, 205}};
const int MAN_FRAMES = sizeof(MAN_CLIPS)/sizeof(int)/4;

const char*  BIRD_SPRITE_FILE = "img\\83127-sprite-area-line-animated-bird-film.png";
const int BIRD_CLIPS[][4] = {
    {0, 0, 182, 168},
    {181, 0, 182, 168},
    {364, 0, 182, 168},
    {547, 0, 182, 168},
    {728, 0, 182, 168},

    {0, 170, 182, 168},
    {181, 170, 182, 168},
    {364, 170, 182, 168},
    {547, 170, 182, 168},
    {728, 170, 182, 168},

    {0, 340, 182, 168},
    {181, 340, 182, 168},
    {364, 340, 182, 168},
    {547, 340, 182, 168},
};
const int BIRD_FRAMES = sizeof(BIRD_CLIPS)/sizeof(int)/4;

#endif

