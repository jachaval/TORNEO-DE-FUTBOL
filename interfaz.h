#ifndef INTERFAZ_H_INCLUDED
#define INTERFAZ_H_INCLUDED

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define APP_BACKCOLOR 0      //negro
#define APP_FORECOLOR 15     //blanco
#define APP_TITLEBACKCOLOR 1 //azul
#define APP_TITLEFORECOLOR 15//blanco
#define APP_ERRORCOLOR 4     //rojo
#define APP_OKCOLOR 2        //verdeoscuro
#define APP_DELAY 1000

enum Orientation {
    TEXT_LEFT,
    TEXT_RIGHT,
    TEXT_CENTER
};

void setColors(int foreColor = APP_FORECOLOR, int backColor = APP_BACKCOLOR);
void bar(int foreColor, int backColor, int y = SCREEN_HEIGHT, int width = SCREEN_WIDTH);
void title(const char* mensaje, int foreColor = APP_TITLEFORECOLOR, int backColor = APP_TITLEBACKCOLOR);
void msj(const char* mensaje, int foreColor = APP_FORECOLOR, int backColor = APP_BACKCOLOR, int y = SCREEN_HEIGHT, Orientation o = Orientation::TEXT_LEFT);
void delline(int line, int foreColor = APP_FORECOLOR, int backColor = APP_BACKCOLOR);
void initUI();





#endif // INTERFAZ_H_INCLUDED
