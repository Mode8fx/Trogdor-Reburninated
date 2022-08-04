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
extern string tempStr;
extern TextObject text_0_loading;
extern SDL_Rect text_0_loading_censor_rect;
extern TextObject text_1_presents;
extern TextObject text_3_click_anywhere_to_start;
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
extern TextObject text_4_score_val;
extern TextObject text_4_mans_val;
extern TextObject text_4_level_val;
extern TextObject text_4_score;
extern TextObject text_4_mans;
extern TextObject text_4_level;
extern TextObject text_4_burninate_black;
extern TextObject text_4_burninate_red;
extern TextObject text_6_paused_1;
extern TextObject text_6_paused_2;
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
extern TextObject text_23_congratulations;
extern TextObject text_23_you_got;
extern TextObject text_23_good_score;
extern TextObject text_23_cast;
extern TextObject text_23_trogdor;
extern TextObject text_23_perez;
extern TextObject text_23_hackworth;
extern TextObject text_23_the_steve;
extern TextObject text_23_the_blue_knight;
extern TextObject text_23_the_red_knight;
extern TextObject text_23_the_siamese;
extern TextObject text_23_archers;
extern TextObject text_23_and_wordly_wise;
extern TextObject text_23_as_the_kerrek;
extern TextObject text_23_keep_playing;
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

#endif