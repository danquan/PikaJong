#ifndef __DEFINITION_H
#define __DEFINITION_H

#include <random>
#include <chrono>
#include <ctime>

#ifdef __MAIN_H
    std::mt19937 Rand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    long long rand(long long l, long long r) {
        return Rand() % (r - l + 1) + l;
    }
    bool Inside(SDL_Rect mRect, SDL_Point mPoint) {
        return mRect.x <= mPoint.x && mPoint.x < mRect.x + mRect.w &&
               mRect.y <= mPoint.y && mPoint.y < mRect.y + mRect.h;
    }
#else
    extern std::mt19937 Rand;
    extern long long rand(long long l, long long r);
    extern bool Inside(SDL_Rect mRect, SDL_Point mPoint);
#endif

#endif