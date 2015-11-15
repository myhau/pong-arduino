#include <TVout.h>
#include "fontALL.h"
#include "schematic.h"
#include "TVOlogo.h"


class MyTv {
private:
    uint8_t w;
    uint8_t h;
public:
    MyTv(uint8_t w, uint8_t h) {
      this.w = w;
      this.h = h;
    }
    void draw_rect(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, char c1, char c2) {

    }
    void draw_circle(uint8_t x, uint8_t y, uint8_t r, char c1, char c2) {

    };
    void clear_screen() {
    };
};

MyTv TV2;

TVout TV;


int zOff = 150;
int xOff = 0;
int yOff = 0;
int cSize = 50;
int view_plane = 64;
float angle = PI/60;

float cube3d[8][3] = {
  {xOff - cSize,yOff + cSize,zOff - cSize},
  {xOff + cSize,yOff + cSize,zOff - cSize},
  {xOff - cSize,yOff - cSize,zOff - cSize},
  {xOff + cSize,yOff - cSize,zOff - cSize},
  {xOff - cSize,yOff + cSize,zOff + cSize},
  {xOff + cSize,yOff + cSize,zOff + cSize},
  {xOff - cSize,yOff - cSize,zOff + cSize},
  {xOff + cSize,yOff - cSize,zOff + cSize}
};
unsigned char cube2d[8][2];


int width = 120;
int height = 96;

void setup() {
  TV.begin(PAL,width,height);
  TV.select_font(font6x8);
  
  randomSeed(analogRead(0));
}



void loop() {
  int rsteps = random(10,60);
  printcube();
}

void intro() {
unsigned char w,l,wb;
  int index;
  w = pgm_read_byte(TVOlogo);
  l = pgm_read_byte(TVOlogo+1);
  if (w&7)
    wb = w/8 + 1;
  else
    wb = w/8;
  index = wb*(l-1) + 2;
  for ( unsigned char i = 1; i < l; i++ ) {
//    TV.bitmap((TV.hres() - w)/2,0,TVOlogo,index,w,i);
    index-= wb;
    TV.delay(50);
  }
  for (unsigned char i = 0; i < (TV.vres() - l)/2; i++) {
//    TV.bitmap((TV.hres() - w)/2,i,TVOlogo);
    TV.delay(50);
  }
  TV.delay(3000);
  TV.clear_screen();
}

void printcube() {
  //calculate 2d points
  for(byte i = 0; i < 8; i++) {
    cube2d[i][0] = (unsigned char)((cube3d[i][0] * view_plane / cube3d[i][2]) + (TV.hres()/2));
    cube2d[i][1] = (unsigned char)((cube3d[i][1] * view_plane / cube3d[i][2]) + (TV.vres()/2));
  }
  TV.delay_frame(1);
  TV.clear_screen();
  draw_cube();
}

void drawPaletka1(int y1) {
  TV.draw_rect(0, y1, 10, 30,WHITE, INVERT);
}

void drawPaletka2(int y1) {
  TV.draw_rect(width - 10, y1, 10, 30,WHITE, INVERT);
}

void drawPilka(int x1, int y1) {
  TV.draw_circle(x1, y1, 5, WHITE,INVERT);
}

void drawPlansza() {
  TV.draw_rect(0, 0, width - 1, height - 1, WHITE);
}

int velocityY1 = 1;
int y1 = 0;

int velocityY2 = 2;
int y2 = 0;

int velocityPx = 1;
int velocityPy = 1;

int pX = 20;

int pY = 30;


void draw_cube() {
  drawPlansza();
  y1 += velocityY1;
  y2 += velocityY2;

  pX += velocityPx;
  pY += velocityPy;

  if(y1 + 30 >= 96) velocityY1 = -1;
  if(y1 <= 0) velocityY1 = 1;

  if(y2 + 30 >= 96) velocityY2 = -1;
  if(y2 <= 0) velocityY2 = 1;


  if(pX + 5 >= 120) velocityPx = -1;
  if(pX <= 1) velocityPx = 1;

  if(pY + 5 >= 96) velocityPy = -1;
  if(pY <= 1) velocityPy = 1;
  
  drawPaletka1(y1);
  drawPaletka2(y2);
  drawPilka(pX, pY);

  delay(1);
}
