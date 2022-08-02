#include "config.h"

#ifndef TEXT_OBJECTS_H
#define TEXT_OBJECTS_H

#define charTempX int_j // Yes, this is necessary
#define charTempY int_k // Yes, this is necessary

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
    SDL_Surface* surface;
    SDL_Rect dstrect;
};

#define SET_TEXT(text, textObj, charArr, pos_x, pos_y) \
    SET_TEXT_HELPER(text, textObj, pos_x, pos_y, charArr);

#define SET_TEXT_HELPER(text, textObj, pos_x, pos_y, charArr)                                              \
    textObj.str = text;                                                                                    \
    STRCPY(tempCharArray, textObj.str.c_str());                                                            \
    textObj.dstrect.w = 0;                                                                                 \
    textObj.dstrect.h = 0;                                                                                 \
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
    SDL_BlitSurface(textObj.surface, NULL, gameScreen, &textObj.dstrect);

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
    font = TTF_OpenFont((rootDir + fontFile).c_str(), size);                      \
    TTF_SetFontStyle(font, style);                                                \
    for (uint_i = minIndex; uint_i < (maxIndex + 1); uint_i++) {                  \
        ss.str(std::string());                                                    \
        ss << static_cast<char>(uint_i);                                          \
        SET_TEXT_CHAR(ss.str().c_str(), font, color, charArr[uint_i - 32]);       \
    }

#endif