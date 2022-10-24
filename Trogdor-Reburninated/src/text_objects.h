#include "include.h"

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
extern void renderTextChar_app(TextCharObject);
extern void renderText_app(TextObject, FontObject);
extern void renderTextChar_menu(TextCharObject);
extern void renderText_menu(TextObject, FontObject);
extern void setTextCharPosX(TextCharObject *, int);
extern void setTextCharPosY(TextCharObject *, int);
extern void destroyTextObjectTexture(TextCharObject);
extern void setFont(FontObject *, const char *, int, double, int, SDL_Color, bool);
extern void initializeFont_numbers(FontObject *);

// This should be a macro since pos_x and pos_y may (and likely will) change before they're needed
#define SET_TEXT(text, textObj, fontObj, pos_x, pos_y) \
    setText(text, &textObj, &fontObj);                 \
    setTextPos(&textObj, (Sint16)(pos_x), (Sint16)(pos_y));

/* Colors */
extern SDL_Color color_white;
extern SDL_Color color_black;
extern SDL_Color color_red;
extern SDL_Color color_gray;
extern SDL_Color color_orange;
extern SDL_Color color_brown;

/* Fonts */
extern FontObject font_serif_brown_6;
extern FontObject font_serif_brown_8;
extern FontObject font_serif_gray_6;
extern FontObject font_serif_gray_12;
extern FontObject font_serif_orange_6;
extern FontObject font_serif_red_6;
extern FontObject font_serif_red_6_mult;
extern FontObject font_serif_red_8;
extern FontObject font_serif_red_8_mult;
extern FontObject font_serif_red_12;
extern FontObject font_serif_white_6;
extern FontObject font_serif_white_6_mult;
extern FontObject font_serif_white_8;
extern FontObject font_serif_white_9;
extern FontObject font_serif_white_10;
extern FontObject font_serif_white_14;
extern FontObject font_nokia_12;
//extern FontObject font_serif_2_bold_black_23;
//extern FontObject font_serif_2_bold_red_23;
extern FontObject font_serif_2_red_6;
extern FontObject font_serif_2_red_13;
extern FontObject font_commodore_error_1;
extern FontObject font_commodore_error_2;

/* Text Objects */
extern TextObject text_0_loading;
extern SDL_Rect text_0_loading_censor_rect;
extern TextObject text_1_presents;
extern TextObject text_3_click_anywhere_to_start;
extern TextObject text_3_quit;
//extern TextObject text_3_programmed;
//extern TextObject text_3_designed;
extern TextObject text_3_page;
extern TextObject text_3_instructions_1;
extern TextObject text_3_instructions_2;
extern TextObject text_3_instructions_3;
extern TextObject text_3_instructions_4;
extern TextObject text_3_instructions_5;
extern TextObject text_3_hints_1;
extern TextObject text_3_hints_2;
extern TextObject text_3_hints_3;
extern TextObject text_3_hints_4;
extern TextObject text_3_hints_5;
extern TextObject text_3_hints_6;
extern TextObject text_3_hints_7;
extern TextObject text_3_credits_1;
extern TextObject text_3_credits_2;
extern TextObject text_3_credits_3;
extern TextObject text_3_credits_4;
extern TextObject text_3_credits_5;
extern TextObject text_3_credits_6;
extern TextObject text_3_credits_7;
extern TextObject text_3_credits_8;
extern TextObject text_3_coming_soon_1;
extern TextObject text_3_coming_soon_2;
extern TextObject text_3_coming_soon_3;
extern TextObject text_3_coming_soon_4;
extern TextObject text_3_coming_soon_5;
extern TextObject text_3_coming_soon_6;
extern TextObject text_3_instructions_2a;
extern TextObject text_3_hints_2a;
extern TextObject text_3_hints_3a;
extern TextObject text_3_hints_4a;
extern TextObject text_3_hints_5a;
extern TextObject text_3_coming_soon_4a;
extern TextObject text_4_score_val;
extern TextObject text_4_mans_val;
extern TextObject text_4_level_val;
extern TextObject text_4_score;
extern TextObject text_4_mans;
extern TextObject text_4_level;
extern TextObject text_4_burninate_black;
extern TextObject text_4_burninate_red;
extern TextObject text_4_paused_1;
extern TextObject text_4_paused_2;
extern TextObject text_4_paused_3;
extern TextObject text_9_level_gray;
extern TextObject text_9_beaten_gray;
extern TextObject text_9_level_red;
extern TextObject text_9_beaten_red;
extern TextObject text_9_nice_work;
extern TextObject text_10_again_gray;
extern TextObject text_10_challenge_gray;
extern TextObject text_10_again_white;
extern TextObject text_10_challenge_white;
extern TextObject text_10_again_red;
extern TextObject text_10_challenge_red;
extern TextObject text_10_again_orange;
extern TextObject text_10_challenge_orange;
extern TextObject text_10_its_over_gray;
extern TextObject text_10_its_over_red;
extern TextObject text_10_username_val;
extern TextObject text_10_enter_initials;
extern TextObject text_10_send_em;
extern TextObject text_10_hi_scores_gray;
extern TextObject text_10_view_gray;
extern TextObject text_10_hi_scores_white;
extern TextObject text_10_view_white;
extern TextObject text_10_hi_scores_red;
extern TextObject text_10_view_red;
extern TextObject text_10_hi_scores_orange;
extern TextObject text_10_view_orange;
extern TextObject text_11_cutscene;
extern TextObject text_12_cutscene;
extern TextObject text_13_cutscene;
extern TextObject text_14_cutscene;
extern TextObject text_15_cutscene;
extern TextObject text_16_cutscene;
extern TextObject text_17_cutscene;
extern TextObject text_18_cutscene;
extern TextObject text_19_cutscene;
extern TextObject text_20_cutscene;
extern TextObject text_21_cutscene;
extern TextObject text_22_cutscene;
extern TextObject text_23_cutscene_1;
extern TextObject text_23_cutscene_2;
extern TextObject text_23_cutscene_3;
extern TextObject text_23_cutscene_4;
extern TextObject text_23_cutscene_5;
extern TextObject text_23_cutscene_6;
extern TextObject text_23_cutscene_7;
extern TextObject text_23_cutscene_8;
extern TextObject text_23_cutscene_9;
extern TextObject text_23_cutscene_10;
extern TextObject text_23_cutscene_11;
extern TextObject text_23_cutscene_12;
extern TextObject text_23_cutscene_13;
extern TextObject text_23_cutscene_14;
extern TextObject text_25_ye_olde_high_scores;
extern TextObject text_25_name;
extern TextObject text_25_level;
extern TextObject text_25_score;
extern TextObject text_25_name_1_val;
extern TextObject text_25_level_1_val;
extern TextObject text_25_score_1_val;
extern TextObject text_25_1;
extern TextObject text_25_name_2_val;
extern TextObject text_25_level_2_val;
extern TextObject text_25_score_2_val;
extern TextObject text_25_2;
extern TextObject text_25_name_3_val;
extern TextObject text_25_level_3_val;
extern TextObject text_25_score_3_val;
extern TextObject text_25_3;
extern TextObject text_25_name_4_val;
extern TextObject text_25_level_4_val;
extern TextObject text_25_score_4_val;
extern TextObject text_25_4;
extern TextObject text_25_name_5_val;
extern TextObject text_25_level_5_val;
extern TextObject text_25_score_5_val;
extern TextObject text_25_5;
extern TextObject text_25_name_6_val;
extern TextObject text_25_level_6_val;
extern TextObject text_25_score_6_val;
extern TextObject text_25_6;
extern TextObject text_25_name_7_val;
extern TextObject text_25_level_7_val;
extern TextObject text_25_score_7_val;
extern TextObject text_25_7;
extern TextObject text_25_name_8_val;
extern TextObject text_25_level_8_val;
extern TextObject text_25_score_8_val;
extern TextObject text_25_8;
extern TextObject text_25_name_9_val;
extern TextObject text_25_level_9_val;
extern TextObject text_25_score_9_val;
extern TextObject text_25_9;
extern TextObject text_25_name_10_val;
extern TextObject text_25_level_10_val;
extern TextObject text_25_score_10_val;
extern TextObject text_25_10;
extern TextObject text_error_1;
extern TextObject text_error_2;

#endif