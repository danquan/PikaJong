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
    bool Inside(const SDL_Rect &mRect, const SDL_Point &mPoint) {
        return mRect.x <= mPoint.x && mPoint.x < mRect.x + mRect.w &&
               mRect.y <= mPoint.y && mPoint.y < mRect.y + mRect.h;
    }
    SDL_Point Center(const SDL_Rect &mRect) {
        return {(mRect.x + (mRect.x + mRect.w - 1)) / 2, (mRect.y + (mRect.y + mRect.h)) / 2};
    }
    int min(int x, int y) {
        return x < y ? x : y;
    }
#else
    extern std::mt19937 Rand;
    extern long long rand(long long l, long long r);
    extern bool Inside(const SDL_Rect &mRect, const SDL_Point &mPoint);
    extern SDL_Point Center(const SDL_Rect &mRect);
    extern min(int x, int y);
#endif

#endif