#ifndef PAINTER_H
#define PAINTER_H

#include <Windows.h>

#define COLOR0 RGB(255, 255, 255)

#define COLOR1 RGB(255, 0, 0)
#define COLOR2 RGB(0, 255, 0)
#define COLOR3 RGB(0, 0, 255)

#define COLOR4 RGB(255, 255, 0)
#define COLOR5 RGB(255, 0, 255)
#define COLOR6 RGB(0, 255, 255)

void drawMite(HDC &hdc, int x, int y, int size, int col_index) {

	int l_x = x - (size / 2);
	int r_x = x + (size / 2);

	int t_y = y - (size / 2);
	int b_y = y + (size / 2);

	COLORREF col;

	switch (col_index) {
	case 0: col = COLOR0; break;
	case 1: col = COLOR1; break;
	case 2: col = COLOR2; break;
	case 3: col = COLOR3; break;
	case 4: col = COLOR4; break;
	case 5: col = COLOR5; break;
	case 6: col = COLOR6; break;
	}

	for (int i = l_x; i <= r_x; i++) {
		for (int j = t_y; j <= b_y; j++) {
			SetPixel(hdc, i, j, col);

		}
	}
}

#endif
