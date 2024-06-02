#define MATRIX 0
#if (MATRIX == 1)
#include <GyverMAX7219.h>

#define WIDTH 8
#define HEIGH 1
#define CS_PIN D4

#define AM_W WIDTH * 8 // 4 матрицы (32 точки)
#define AM_H HEIGH * 8 // 2 матрицы (16 точек)
MAX7219<WIDTH, HEIGH, CS_PIN> mtrx;

void MatrixBegin(void)
{
  mtrx.begin();
}
void MatrixPrint(String time, String date)
{
  mtrx.setCursor(0, 0);
  mtrx.printf("%s", time.c_str());
  mtrx.setCursor(34, 0);
  mtrx.printf("%s", date.c_str());
  mtrx.update();
}

void MatrixBrightness(uint8_t brightness)
{
  mtrx.setBright(&brightness);
}
#else

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, D7,
                                               NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE + NEO_MATRIX_ZIGZAG,
                                               NEO_GRB + NEO_KHZ800);

void MatrixBegin()
{
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(2);
  matrix.setTextColor(matrix.Color(255, 255, 255));
}

int x = matrix.width();
int pass = 0;

void MatrixPrint(String time, String date)
{
  matrix.fillScreen(0);
  matrix.setCursor(1, 0);
  matrix.print(time);
  matrix.show();
}
#endif