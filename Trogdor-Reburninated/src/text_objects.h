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

/* Single Characters */
struct TextCharObject {
#if !defined(SDL1)
    SDL_Texture *texture;
#else
    SDL_Surface *surface;
#endif
    SDL_Rect dstrect;
};

struct FontObject {
    TTF_Font *font;
	int size;
	int style;
	SDL_Color color;
	TextCharObject textChars[126 + 1 - 32];
};

extern void setText(const char [], TextObject *, FontObject *);
extern void setTextPos(TextObject *, Sint16, Sint16);
extern void updateText(TextObject *, string);
extern void setTextChar(const char *, TTF_Font *, SDL_Color, TextCharObject *);
extern void renderTextChar(TextCharObject);
extern void renderText(TextObject, FontObject);
extern void setTextCharPosX(TextCharObject *, int);
extern void setTextCharPosY(TextCharObject *, int);
extern void destroyTextObjectTexture(TextCharObject);
extern void setFont(FontObject *, const char *, int, double, int, SDL_Color);
extern void initializeFont_numbers(FontObject *);

// This should be a macro since pos_x and pos_y may (and likely will) change before they're needed
#define SET_TEXT(text, textObj, fontObj, pos_x, pos_y) \
    setText(text, &textObj, &fontObj);                 \
    setTextPos(&textObj, (Sint16)(pos_x), (Sint16)(pos_y));

/* Text Objects */
extern char tempCharArray[64];
extern Uint8 charCounter;
extern Sint16 charWidthCounter;

#endif