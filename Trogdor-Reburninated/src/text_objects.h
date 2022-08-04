#include "config.h"
#include "general.h"
#include "system_specific_macros.h"
#include "window.h"

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
    SDL_Surface *surface;
    SDL_Rect dstrect;
};

//extern void SET_TEXT(const char[], TextObject *, TextCharObject[], Sint16, Sint16);
extern void updateText(TextObject *, string);
extern void setTextChar(const char *, TTF_Font *, SDL_Color, TextCharObject *);
extern void renderTextChar(TextCharObject);
extern void renderText(TextObject, TextCharObject[]);
extern void setTextCharPosX(TextCharObject *, int);
extern void setTextCharPosY(TextCharObject *, int);
extern void destroyTextObjectTexture(TextCharObject);
extern void setFont(TTF_Font *, string, int, int, TextCharObject[], SDL_Color, Uint32, Uint32);

#define SET_TEXT(text, textObj, charArr, pos_x, pos_y)                                                     \
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

/* Text Objects */
extern char tempCharArray[64];
extern Uint8 charCounter;
extern Sint16 charWidthCounter;
extern std::stringstream ss;

#endif