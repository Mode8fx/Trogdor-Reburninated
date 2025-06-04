#include "text_objects.h"
#include "general.h"
#include "window.h"
#include "config.h"

char tempCharArray[64];
Uint8 charCounter;
Sint16 charWidthCounter;

char tempChar[2] = { '\0', '\0' };
#if !defined(SDL1)
SDL_Surface *temp_text;
#endif

void setText(std::string text, TextObject *textObj, FontObject *fontObj) {
	textObj->str = text;
	STRCPY(tempCharArray, textObj->str.c_str());
	textObj->dstrect.w = 0;
	textObj->dstrect.h = 0;
	for (uint_i = 0; uint_i < textObj->str.length(); uint_i++) {
		i = tempCharArray[uint_i] - 32;
#if !defined(SDL1)
		if (fontObj->textChars[i].texture == NULL) {
#else
		if (fontObj->textChars[i].surface == NULL) {
#endif
			tempChar[0] = i + 32;
			setTextChar(tempChar, fontObj->font, fontObj->color, &fontObj->textChars[i]);
		}
		textObj->dstrect.w += fontObj->textChars[i].dstrect.w;
		textObj->dstrect.h = max(textObj->dstrect.h, (Sint16)fontObj->textChars[i].dstrect.h);
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
#if !defined(SDL1)
#if !defined(PSP)
	temp_text = TTF_RenderText_Solid(font, text, text_color);
#else
	if (int(text[0]) != 32) {
		temp_text = TTF_RenderUTF8_Blended(font, text, text_color);
	} else {
		temp_text = TTF_RenderUTF8_Blended(font, "", text_color);
	}
#endif
	textCharObj->texture = SDL_CreateTextureFromSurface(renderer, temp_text);
    SDL_FreeSurface(temp_text);
#else
    textCharObj->surface = TTF_RenderText_Solid(font, text, text_color);
#endif
    TTF_SizeText(font, text, &charTempX, &charTempY);
    textCharObj->dstrect.w = charTempX;
    textCharObj->dstrect.h = charTempY;
}

void renderTextChar(TextCharObject textCharObj) {
    outputRect = textCharObj.dstrect;
    outputRect.x += gameToWindowDstRect.x;
    outputRect.y += gameToWindowDstRect.y;
#if !defined(SDL1)
    SDL_RenderCopy(renderer, textCharObj.texture, NULL, &outputRect);
#else
    SDL_BlitSurface(textCharObj.surface, NULL, windowScreen, &outputRect);
#endif
}

void renderText(TextObject textObj, FontObject fontObj) {
	STRCPY(tempCharArray, textObj.str.c_str());
	charWidthCounter = 0;
	for (charCounter = 0; charCounter < textObj.str.length(); charCounter++) {
		setTextCharPosX(&CHAR_AT_INDEX(charCounter, fontObj.textChars), (textObj.dstrect.x + charWidthCounter));
		setTextCharPosY(&CHAR_AT_INDEX(charCounter, fontObj.textChars), textObj.dstrect.y);
		renderTextChar(CHAR_AT_INDEX(charCounter, fontObj.textChars));
		charWidthCounter += CHAR_AT_INDEX(charCounter, fontObj.textChars).dstrect.w;
	}
}

void renderTextChar_app(TextCharObject textCharObj) {
	outputRect = textCharObj.dstrect;
	outputRect.x += appToWindowDstRect.x;
	outputRect.y += appToWindowDstRect.y;
#if !defined(SDL1)
	SDL_RenderCopy(renderer, textCharObj.texture, NULL, &outputRect);
#else
	SDL_BlitSurface(textCharObj.surface, NULL, windowScreen, &outputRect);
#endif
}

void renderText_app(TextObject textObj, FontObject fontObj) {
	STRCPY(tempCharArray, textObj.str.c_str());
	charWidthCounter = 0;
	for (charCounter = 0; charCounter < textObj.str.length(); charCounter++) {
		setTextCharPosX(&CHAR_AT_INDEX(charCounter, fontObj.textChars), (textObj.dstrect.x + charWidthCounter));
		setTextCharPosY(&CHAR_AT_INDEX(charCounter, fontObj.textChars), textObj.dstrect.y);
		renderTextChar_app(CHAR_AT_INDEX(charCounter, fontObj.textChars));
		charWidthCounter += CHAR_AT_INDEX(charCounter, fontObj.textChars).dstrect.w;
	}
}

void renderTextChar_menu(TextCharObject textCharObj) {
	outputRect = textCharObj.dstrect;
	outputRect.x += menuToWindowDstRect.x;
	outputRect.y += menuToWindowDstRect.y;
#if !defined(SDL1)
	SDL_RenderCopy(renderer, textCharObj.texture, NULL, &outputRect);
#else
	SDL_BlitSurface(textCharObj.surface, NULL, windowScreen, &outputRect);
#endif
}

void renderText_menu(TextObject textObj, FontObject fontObj) {
	STRCPY(tempCharArray, textObj.str.c_str());
	charWidthCounter = 0;
	for (charCounter = 0; charCounter < textObj.str.length(); charCounter++) {
		setTextCharPosX(&CHAR_AT_INDEX(charCounter, fontObj.textChars), (textObj.dstrect.x + charWidthCounter));
		setTextCharPosY(&CHAR_AT_INDEX(charCounter, fontObj.textChars), textObj.dstrect.y);
		renderTextChar_menu(CHAR_AT_INDEX(charCounter, fontObj.textChars));
		charWidthCounter += CHAR_AT_INDEX(charCounter, fontObj.textChars).dstrect.w;
	}
}

void setTextCharPosX(TextCharObject *textCharObj, int pos_x) {
    textCharObj->dstrect.x = pos_x;
}

void setTextCharPosY(TextCharObject *textCharObj, int pos_y) {
    textCharObj->dstrect.y = pos_y;
}

void destroyTextObjectTexture(TextCharObject textCharObj) {
#if !defined(SDL1)
    SDL_DestroyTexture(textCharObj.texture);
#else
    SDL_FreeSurface(textCharObj.surface);
#endif
}

int getDesiredFontSize(FontObject *fontObj) {
	if (fontObj->scaleToWindow) {
		return max((int)fontObj->originalSize, (int)(fontObj->multSize * screenScale_menu));
	} else {
		return max((int)fontObj->originalSize, (int)(fontObj->multSize * gameHiResMult));
	}
}

void setFont(FontObject *fontObj, unsigned char font_data[], unsigned int font_len, int originalSize, double multSize, int style, SDL_Color color, bool scaleToWindow) {
	fontObj->originalSize = originalSize;
	fontObj->multSize = multSize;
	fontObj->scaleToWindow = scaleToWindow;
	fontObj->size = getDesiredFontSize(fontObj);
	fontObj->style = style;
	fontObj->color = color;
	fontObj->font = TTF_OpenFontRW(SDL_RWFromConstMem(font_data, font_len), 1, fontObj->size);
	TTF_SetFontStyle(fontObj->font, fontObj->style);
}

void initializeFont_numbers(FontObject *fontObj) {
	STRCPY(tempCharArray, "0123456789");
	for (uint_i = 0; uint_i < 10; uint_i++) {
		i = tempCharArray[uint_i] - 32;
#if !defined(SDL1)
		if (fontObj->textChars[i].texture == NULL) {
#else
		if (fontObj->textChars[i].surface == NULL) {
#endif
			tempChar[0] = i + 32;
			setTextChar(tempChar, fontObj->font, fontObj->color, &fontObj->textChars[i]);
		}
	}
}

Uint64 fps_lastTime = 0;
double fps_freq;
Uint8 fps_frameCount = 0;
Uint8 fps_frameCountLastSecond = 0;

void printFPS(FontObject *fontObj) {
	fps_frameCount++;
#if !defined(SDL1)
	Uint64 currentTime = SDL_GetPerformanceCounter();
	if (fps_lastTime == 0) {
		fps_lastTime = currentTime;
		fps_freq = (double)SDL_GetPerformanceFrequency();
	}

	double elapsed = (double)(currentTime - fps_lastTime) / fps_freq;
	if (elapsed >= 1.0) {
		fps_frameCountLastSecond = fps_frameCount;
		fps_frameCount = 0;
		fps_lastTime = currentTime;
	}
#else
	Uint64 currentTime = SDL_GetTicks();

	if (currentTime > fps_lastTime + 1000) {
		fps_frameCountLastSecond = fps_frameCount;
		fps_frameCount = 0;
		fps_lastTime = currentTime;
	}
#endif
	Sint16 fps_counterX = windowWidth / 2;
	Sint16 fps_counterY = windowHeight * 15 / 16;

	int hundreds = int(fps_frameCountLastSecond) / 100 + 16;
	fontObj->textChars[hundreds].dstrect.x = fps_counterX - 20;
	fontObj->textChars[hundreds].dstrect.y = fps_counterY;
	renderTextChar_app(fontObj->textChars[hundreds]);

	int tens = (int(fps_frameCountLastSecond) / 10) % 10 + 16;
	fontObj->textChars[tens].dstrect.x = fps_counterX;
	fontObj->textChars[tens].dstrect.y = fps_counterY;
	renderTextChar_app(fontObj->textChars[tens]);

	int ones = int(fps_frameCountLastSecond) % 10 + 16;
	fontObj->textChars[ones].dstrect.x = fps_counterX + 20;
	fontObj->textChars[ones].dstrect.y = fps_counterY;
	renderTextChar_app(fontObj->textChars[ones]);
}