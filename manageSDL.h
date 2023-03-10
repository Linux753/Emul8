#ifndef MANAGESDL_H
#define MANAGESDL_H

int initScreen(struct Screen * screen);
void destroyScreen(struct Screen * screen);
void renderScreen(struct Screen * screen);
void updateEvent(struct Control * control);

#endif