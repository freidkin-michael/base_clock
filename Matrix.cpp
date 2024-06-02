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