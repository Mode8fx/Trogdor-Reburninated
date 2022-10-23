#ifndef ON_OPEN_AND_CLOSE_H
#define ON_OPEN_AND_CLOSE_H

#include "classes.h"

void InitializeDisplay();
void InitializeSound();
void InitializeController();
void renderBackground();
void renderTransparentForeground();
void closeController();
void destroyDisplay();
void DestroyAll();

#endif