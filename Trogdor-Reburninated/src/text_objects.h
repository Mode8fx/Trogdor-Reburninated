#include "general.h"
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

extern void setText(const char[], TextObject *, TextCharObject[]);
extern void setTextPos(TextObject *, Sint16, Sint16);
extern void updateText(TextObject *, string);
extern void setTextChar(const char *, TTF_Font *, SDL_Color, TextCharObject *);
extern void renderTextChar(TextCharObject);
extern void renderText(TextObject, TextCharObject[]);
extern void setTextCharPosX(TextCharObject *, int);
extern void setTextCharPosY(TextCharObject *, int);
extern void destroyTextObjectTexture(TextCharObject);
extern void setFont(TTF_Font *, string, int, double, int, TextCharObject[], SDL_Color, Uint32, Uint32);

// This should be a macro since pos_x and pos_y may (and likely will) change before they're needed
#define SET_TEXT(text, textObj, charArr, pos_x, pos_y) \
    setText(text, &textObj, charArr);                  \
    setTextPos(&textObj, (Sint16)(pos_x), (Sint16)(pos_y));

/* Text Objects */
extern char tempCharArray[64];
extern Uint8 charCounter;
extern Sint16 charWidthCounter;
extern std::stringstream ss;

#endif