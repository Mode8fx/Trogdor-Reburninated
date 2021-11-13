#if defined(SDL1)

#include "config.h"

#ifndef TEXT_OBJECTS_H
#define TEXT_OBJECTS_H

#define charTempX int_j
#define charTempY int_k

struct TextRect {
    Sint16 x = 0;
    Sint16 y = 0;
    Sint16 w = 0;
    Sint16 h = 0;
};

/* Full Words/Phrases */
struct TextObject {
    string str;
    TextRect dstrect;
};

#define CHAR_AT_INDEX(index, charArr) charArr[tempCharArray[index] - 32]

/* ################# */
/* # Standard Text # */
/* ################# */

/* Single Characters */
struct TextCharObject {
    SDL_Surface *surface;
    SDL_Rect dstrect;
};

#define SET_TEXT(text, textObj, charArr, pos_x, pos_y) \
    TextObject textObj;                                \
    SET_TEXT_HELPER(text, textObj, pos_x, pos_y, charArr);

#define SET_TEXT_HELPER(text, textObj, pos_x, pos_y, charArr)                                              \
    textObj.str = text;                                                                                    \
    STRCPY(tempCharArray, textObj.str.c_str());                                                            \
    for (uint_i = 0; uint_i < textObj.str.length(); uint_i++) {                                            \
        textObj.dstrect.w += charArr[tempCharArray[uint_i] - 32].dstrect.w;                                \
        textObj.dstrect.h = max(textObj.dstrect.h, (Sint16)charArr[tempCharArray[uint_i] - 32].dstrect.h); \
    }                                                                                                      \
    textObj.dstrect.x = (Sint16)pos_x;                                                                     \
    textObj.dstrect.y = (Sint16)pos_y;

#define UPDATE_TEXT(textObj, text) \
    textObj.str = text;

#define SET_TEXT_CHAR(text, font, text_color, textObj)              \
    textObj.surface = TTF_RenderText_Solid(font, text, text_color); \
    TTF_SizeText(font, text, &charTempX, &charTempY);               \
    textObj.dstrect.w = charTempX;                                  \
    textObj.dstrect.h = charTempY;

#define RENDER_TEXT_CHAR(textObj) \
    SDL_BlitSurface(textObj.surface, NULL, screen, &textObj.dstrect);

#define RENDER_TEXT(textObj, charArr)                                                                \
    STRCPY(tempCharArray, textObj.str.c_str());                                                      \
    charWidthCounter = 0;                                                                            \
    for (charCounter = 0; charCounter < textObj.str.length(); charCounter++) {                       \
        SET_TEXT_POS_X(CHAR_AT_INDEX(charCounter, charArr), (textObj.dstrect.x + charWidthCounter)); \
        SET_TEXT_POS_Y(CHAR_AT_INDEX(charCounter, charArr), textObj.dstrect.y);                      \
        RENDER_TEXT_CHAR(CHAR_AT_INDEX(charCounter, charArr));                                       \
        charWidthCounter += CHAR_AT_INDEX(charCounter, charArr).dstrect.w;                           \
    }

#define SET_TEXT_POS_X(textObj, pos_x) \
    textObj.dstrect.x = (pos_x);

#define SET_TEXT_POS_Y(textObj, pos_y) \
    textObj.dstrect.y = (pos_y);

#define DESTROY_TEXT_OBJECT_TEXTURE(textObj) \
    SDL_FreeSurface(textObj.surface);

#define SET_FONT(font, fontFile, size, style, charArr, color, minIndex, maxIndex) \
	TTF_Font *font;                                                               \
    font = TTF_OpenFont((rootDir + fontFile).c_str(), size);                      \
    TTF_SetFontStyle(font, style);                                                \
    TextCharObject charArr[maxIndex + 1 - 32];                                    \
    for (uint_i = minIndex; uint_i < (maxIndex + 1); uint_i++) {                  \
        ss.str(std::string());                                                    \
        ss << static_cast<char>(uint_i);                                          \
        SET_TEXT_CHAR(ss.str().c_str(), font, color, charArr[uint_i - 32]);       \
    }

/* ##################### */
/* # Text With Outline # */
/* ##################### */

#if !defined (WII) && !defined(GAMECUBE) // unfortunately, SDL_Wii doesn't support outlines

/* Single Characters */
struct TextCharObjectWithOutline {
    SDL_Surface *surface, *outline_surface;
    SDL_Rect dstrect, outline_rect;
    Sint8 outlineOffset_x, outlineOffset_y;
};

#define ADJUST_CHAR_OUTLINE_OFFSET(arr, c, x, y, size)                                            \
    if (x > 0) {                                                                                  \
        arr[c].outlineOffset_x += max((int)(x * GAME_HEIGHT_MULT * arr[c].dstrect.h / size), 1);  \
    } else if (x < 0) {                                                                           \
        arr[c].outlineOffset_x += min((int)(x * GAME_HEIGHT_MULT * arr[c].dstrect.h / size), -1); \
    }                                                                                             \
    if (y > 0) {                                                                                  \
        arr[c].outlineOffset_y += max((int)(y * GAME_HEIGHT_MULT * arr[c].dstrect.h / size), 1);  \
    } else if (y < 0) {                                                                           \
        arr[c].outlineOffset_y += min((int)(y * GAME_HEIGHT_MULT * arr[c].dstrect.h / size), -1); \
    }

#define RENDER_TEXT_CHAR_WITH_OUTLINE(textObj)                                     \
    SDL_BlitSurface(textObj.outline_surface, NULL, screen, &textObj.outline_rect); \
    SDL_BlitSurface(textObj.surface, NULL, screen, &textObj.dstrect);

#define RENDER_TEXT_WITH_OUTLINE(textObj, charArr)                                                                                                                     \
    STRCPY(tempCharArray, textObj.str.c_str());                                                                                                                        \
    charWidthCounter = 0;                                                                                                                                              \
    for (charCounter = 0; charCounter < textObj.str.length(); charCounter++) {                                                                                         \
        SET_TEXT_WITH_OUTLINE_POS_X(CHAR_AT_INDEX(charCounter, charArr), (textObj.dstrect.x + charWidthCounter), CHAR_AT_INDEX(charCounter, charArr).outlineOffset_x); \
        SET_TEXT_WITH_OUTLINE_POS_Y(CHAR_AT_INDEX(charCounter, charArr), textObj.dstrect.y, CHAR_AT_INDEX(charCounter, charArr).outlineOffset_y);                      \
        RENDER_TEXT_CHAR_WITH_OUTLINE(CHAR_AT_INDEX(charCounter, charArr));                                                                                            \
        charWidthCounter += CHAR_AT_INDEX(charCounter, charArr).dstrect.w;                                                                                             \
    }

#define SET_TEXT_CHAR_WITH_OUTLINE(text, font, text_color, outline_color, textObj)        \
    textObj.surface = TTF_RenderText_Solid(font, text, text_color);                       \
    TTF_SizeText(font, text, &charTempX, &charTempY);                                     \
    textObj.dstrect.w = charTempX;                                                        \
    textObj.dstrect.h = charTempY;                                                        \
    TTF_SetFontOutline(font, max((textObj.dstrect.h / 10), int(ceil(GAME_HEIGHT_MULT)))); \
    textObj.outline_surface = TTF_RenderText_Solid(font, text, outline_color);            \
    TTF_SizeText(font, text, &charTempX, &charTempY);                                     \
    textObj.outline_rect.w = charTempX;                                                   \
    textObj.outline_rect.h = charTempY;                                                   \
    TTF_SetFontOutline(font, 0);

#define SET_TEXT_WITH_OUTLINE(text, textObj, pos_x, pos_y, charArr) \
    TextObject textObj;                                             \
    SET_TEXT_WITH_OUTLINE_HELPER(text, textObj, pos_x, pos_y, charArr);

#define SET_TEXT_WITH_OUTLINE_HELPER(text, textObj, pos_x, pos_y, charArr)                            \
    textObj.str = text;                                                                               \
    STRCPY(tempCharArray, textObj.str.c_str());                                                       \
    for (uint_i = 0; uint_i < textObj.str.length(); uint_i++) {                                       \
        textObj.dstrect.w += charArr[tempCharArray[uint_i]].dstrect.w;                                \
        textObj.dstrect.h = max(textObj.dstrect.h, (Sint16)charArr[tempCharArray[uint_i]].dstrect.h); \
    }                                                                                                 \
    textObj.dstrect.x = pos_x;                                                                        \
    textObj.dstrect.y = pos_y;

#define SET_TEXT_WITH_OUTLINE_POS_X(textObj, pos_x, offset) \
    textObj.dstrect.x = (pos_x);                            \
    textObj.outline_rect.x = (pos_x) + (offset);

#define SET_TEXT_WITH_OUTLINE_POS_Y(textObj, pos_y, offset) \
    textObj.dstrect.y = (pos_y);                            \
    textObj.outline_rect.y = (pos_y) + (offset);

#define DESTROY_TEXT_WITH_OUTLINE_OBJECT_TEXTURE(textObj) \
    SDL_FreeSurface(textObj.surface);                     \
    SDL_FreeSurface(textObj.outline_surface);

#else

struct TextCharObjectWithOutline {
    SDL_Surface *surface;
    SDL_Rect dstrect;
};

#define ADJUST_CHAR_OUTLINE_OFFSET(arr, c, x, y, size)

#define RENDER_TEXT_CHAR_WITH_OUTLINE(textObj) \
    RENDER_TEXT_CHAR(textObj)

#define RENDER_TEXT_WITH_OUTLINE(textObj, charArr) \
    RENDER_TEXT(textObj, charArr)

#define SET_TEXT_CHAR_WITH_OUTLINE(text, font, text_color, outline_color, textObj) \
    SET_TEXT_CHAR(text, font, text_color, textObj)

#define SET_TEXT_WITH_OUTLINE(text, textObj, pos_x, pos_y, charArr) \
    SET_TEXT(text, textObj, pos_x, pos_y, charArr)

#define SET_TEXT_WITH_OUTLINE_HELPER(text, textObj, pos_x, pos_y, charArr) \
    SET_TEXT_HELPER(text, textObj, pos_x, pos_y, charArr)

#define SET_TEXT_WITH_OUTLINE_POS_X(textObj, pos_x, offset) \
    SET_TEXT_POS_X(textObj, pos_x)

#define SET_TEXT_WITH_OUTLINE_POS_Y(textObj, pos_y, offset) \
    SET_TEXT_POS_Y(textObj, pos_y)

#define DESTROY_TEXT_WITH_OUTLINE_OBJECT_TEXTURE(textObj) \
    DESTROY_TEXT_OBJECT_TEXTURE(textObj)

#endif

#endif

#endif