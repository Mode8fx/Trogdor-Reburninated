#include "text_objects.h"

void setText(const char text[], TextObject *textObj, TextCharObject charArr[]) {
    textObj->str = text;
    STRCPY(tempCharArray, textObj->str.c_str());
    textObj->dstrect.w = 0;
    textObj->dstrect.h = 0;
    for (uint_i = 0; uint_i < textObj->str.length(); uint_i++) {
        textObj->dstrect.w += charArr[tempCharArray[uint_i] - 32].dstrect.w;
        textObj->dstrect.h = max(textObj->dstrect.h, (Sint16)charArr[tempCharArray[uint_i] - 32].dstrect.h);
    }
}

void setTextPos(TextObject *textObj, Sint16 pos_x, Sint16 pos_y) {
    textObj->dstrect.x = pos_x;
    textObj->dstrect.y = pos_y;
}

void updateText(TextObject *textObj, string text) {
    textObj->str = text;
}

void setTextChar(const char *text, TTF_Font *font, SDL_Color text_color, TextCharObject *textCharObj) {
    textCharObj->surface = TTF_RenderText_Solid(font, text, text_color);
    TTF_SizeText(font, text, &charTempX, &charTempY);
    textCharObj->dstrect.w = charTempX;
    textCharObj->dstrect.h = charTempY;
}

void renderTextChar(TextCharObject textCharObj) {
    SDL_BlitSurface(textCharObj.surface, NULL, gameScreen, &textCharObj.dstrect);
}

void renderText(TextObject textObj, TextCharObject charArr[]) {
    STRCPY(tempCharArray, textObj.str.c_str());
    charWidthCounter = 0;
    for (charCounter = 0; charCounter < textObj.str.length(); charCounter++) {
        setTextCharPosX(&CHAR_AT_INDEX(charCounter, charArr), (textObj.dstrect.x + charWidthCounter));
        setTextCharPosY(&CHAR_AT_INDEX(charCounter, charArr), textObj.dstrect.y);
        renderTextChar(CHAR_AT_INDEX(charCounter, charArr));
        charWidthCounter += CHAR_AT_INDEX(charCounter, charArr).dstrect.w;
    }
}

void setTextCharPosX(TextCharObject *textCharObj, int pos_x) {
    textCharObj->dstrect.x = pos_x;
}

void setTextCharPosY(TextCharObject *textCharObj, int pos_y) {
    textCharObj->dstrect.y = pos_y;
}

void destroyTextObjectTexture(TextCharObject textCharObj) {
    SDL_FreeSurface(textCharObj.surface);
}

void setFont(TTF_Font *font, string fontFile, int size, int style, TextCharObject charArr[], SDL_Color color, Uint32 minIndex, Uint32 maxIndex) {
    font = TTF_OpenFont((rootDir + fontFile).c_str(), size);
    TTF_SetFontStyle(font, style);
    for (uint_i = minIndex; uint_i < (maxIndex + 1); uint_i++) {
        ss.str(std::string());
        ss << static_cast<char>(uint_i);
        setTextChar(ss.str().c_str(), font, color, &charArr[uint_i - 32]);
    }
}