#pragma once

#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#endif

double mapf(double val, double in_min, double in_max, double out_min, double out_max);
bool pointOffScreen(int x, int y);