#ifndef Pratima_ConsoleGraphics_H
#define Pratima_ConsoleGraphics_H
#include <windows.h>
#include <stdlib.h>


typedef struct CONSOLE_FONT_INFOEX
{
	ULONG cbSize;
	DWORD nFont;
	COORD dwFontSize;
	UINT FontFamily;
	UINT FontWeight;
	WCHAR FaceName[LF_FACESIZE];
} CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;
typedef CHAR_INFO PGRG;

BOOL WINAPI SetCurrentConsoleFontEx(HANDLE h, BOOL b, PCONSOLE_FONT_INFOEX lp);

enum COLOUR
{

	PGRG_BLACK		= 0x0000,
	PGRG_DBLUE	= 0x0010,
	PGRG_DGREEN	= 0x0020,
	PGRG_DCYAN	= 0x0030,
	PGRG_DRED		= 0x0040,
	PGRG_DMAGENTA = 0x0050,
	PGRG_DYELLOW	= 0x0060,
	PGRG_GREY			= 0x0070,
	PGRG_DGREY	= 0x0080,
	PGRG_BLUE			= 0x0090,
	PGRG_GREEN		= 0x00A0,
	PGRG_CYAN			= 0x00B0,
	PGRG_RED			= 0x00C0,
	PGRG_MAGENTA		= 0x00D0,
	PGRG_YELLOW		= 0x00E0,
	PGRG_WHITE		= 0x00F0,
};

enum PIXEL_TYPE
{
	PIXEL_SOLID = 0x2588,
	PIXEL_THREEQUARTERS = 0x2593,
	PIXEL_HALF = 0x2592,
	PIXEL_QUARTER = 0x2591,
};


int nScreenWidth = 0;
int nScreenHeight = 0;
COORD charBufSize = {0, 0};
COORD coordDest = {0, 0};
SMALL_RECT windowSize = {0, 0, 0, 0};
HANDLE hConsole;


void PGRG_WindowStart(int Screen_Width, int Screen_Height, int Font_Size)
{
	nScreenWidth = Screen_Width;
	nScreenHeight = Screen_Height;
	HANDLE wHnd;
	charBufSize.X = nScreenWidth-1;
	charBufSize.Y = nScreenHeight-1;
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = Font_Size;
	cfi.dwFontSize.Y = Font_Size;
	windowSize.Right = nScreenWidth-2;
	windowSize.Bottom= nScreenHeight-2;
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	SetConsoleScreenBufferSize(hConsole, charBufSize);
	SetConsoleActiveScreenBuffer(hConsole);
	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}
void PGRG_FillColor(CHAR_INFO buffer[],WORD color){
	for (int i = 0; i < nScreenWidth * nScreenHeight; ++i)
	{
		buffer[i].Char.AsciiChar = ' ';
		buffer[i].Attributes = color;
	}
}
void PGRG_Display(CHAR_INFO buffer[]){
 PGRG *screen = buffer;
WriteConsoleOutput(hConsole, screen, charBufSize, coordDest, &windowSize);
}

		
void PGRG_Line(int x1, int y1, int x2, int y2, CHAR_INFO buffer[], WORD color)
{

			int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = abs(dx);
	dy1 = abs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1;
			y = y1;
			xe = x2;
		}
		else
		{
			x = x2;
			y = y2;
			xe = x1;
		}
		if(x<(nScreenWidth-1) && y<nScreenHeight-1 && x>1 && y>1){
		buffer[y * (nScreenWidth - 1) + x].Attributes = color;
		}

		for (i = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0)
				px = px + 2 * dy1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
					y = y + 1;
				else
					y = y - 1;
				px = px + 2 * (dy1 - dx1);
			}

			if(x<(nScreenWidth-1) && y<nScreenHeight-1 && x>1 && y>1){
		buffer[y * (nScreenWidth - 1) + x].Attributes = color;
		}
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}

		if(x<(nScreenWidth-1) && y<nScreenHeight-1 && x>1 && y>1){
		buffer[y * (nScreenWidth - 1) + x].Attributes = color;
		}

		for (i = 0; y < ye; i++)
		{
			y = y + 1;
			if (py <= 0)
				py = py + 2 * dx1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
					x = x + 1;
				else
					x = x - 1;
				py = py + 2 * (dx1 - dy1);
			}

			if(x<(nScreenWidth-1) && y<nScreenHeight-1 && x>1 && y>1){
		buffer[y * (nScreenWidth - 1) + x].Attributes = color;
		}
		}
	}

}
void PGRG_Circle(int xc, int yc, int r,CHAR_INFO buffer[], WORD color)
	{
		
		int x = 0;
		int y = r;
		int p = 3 - 2 * r;
		if (!r) return;

		while (y >= x) // only formulate 1/8 of circle
		{if((xc-x)<(nScreenWidth-1) && (yc-y)<nScreenHeight-1 && (xc-x)>1 && (yc-y)>1){
			buffer[(yc-y) * (nScreenWidth - 1) + (xc-x)].Attributes = color;}//upper left left
			if((xc-y)<(nScreenWidth-1) && (yc-x)<nScreenHeight-1 && (xc-y)>1 && (yc-x)>1){
			buffer[(yc-x) * (nScreenWidth - 1) + (xc - y)].Attributes = color;}//upper upper left
			if((xc+y)<(nScreenWidth-1) && (yc-x)<nScreenHeight-1 && (xc+y)>1 && (yc-x)>1){
			buffer[(yc - x) * (nScreenWidth - 1) + (xc + y)].Attributes = color;}//upper upper right
			if((xc+x)<(nScreenWidth-1) && (yc-y)<nScreenHeight-1 && (xc+x)>1 && (yc-y)>1){
			buffer[(yc - y) * (nScreenWidth - 1) + (xc + x)].Attributes = color;}//upper right right
			if((xc-x)<(nScreenWidth-1) && (yc+y)<nScreenHeight-1 && (xc-x)>1 && (yc+y)>1){
			buffer[(yc + y) * (nScreenWidth - 1) + (xc - x)].Attributes = color;}//lower left left
			if((xc-y)<(nScreenWidth-1) && (yc+x)<nScreenHeight-1 && (xc-y)>1 && (yc+x)>1){
			buffer[(yc + x) * (nScreenWidth - 1) + (xc - y)].Attributes = color;}//lower lower left
			if((xc+y)<(nScreenWidth-1) && (yc+x)<nScreenHeight-1 && (xc+y)>1 && (yc+x)>1){
			buffer[(yc + x) * (nScreenWidth - 1) + (xc + y)].Attributes = color;}//lower lower right
			if((xc+x)<(nScreenWidth-1) && (yc+y)<nScreenHeight-1 && (xc+x)>1 && (yc+y)>1){
			buffer[(yc + y) * (nScreenWidth - 1) + (xc + x)].Attributes = color;}//lower right right
			if (p < 0) p += 4 * x++ + 6;
			else p += 4 * (x++ - y--) + 10;
		
		}
	}
	void PGRG_FillCircle(int center_x, int center_y, int radius,CHAR_INFO buffer[],WORD color) {
   		 int x, y;
    	 for (y = -radius; y <= radius; y++) {
      for (x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
							if((center_x + x)<(nScreenWidth-1) && (center_y + y)<nScreenHeight-1 && (center_x + x)>1 && (center_y + y)>1){
               	buffer[(center_y + y) * (nScreenWidth - 1) + (center_x + x)].Attributes = color;}
            }
        }
    }
		
}
void PGRG_Triangle(int x1, int y1, int x2, int y2, int x3, int y3,CHAR_INFO buffer[],WORD color)
	{
		
		PGRG_Line(x1, y1, x2, y2, buffer, color);
		PGRG_Line(x2, y2, x3, y3, buffer, color);
		PGRG_Line(x3, y3, x1, y1, buffer, color);
		
	}
void PGRG_Pixel(int x,int y,CHAR_INFO buffer[],WORD color){
	if(x<nScreenWidth-1 && y < nScreenHeight-1 && x>1 && y>1){
		buffer[ y* (nScreenWidth - 1) + x ].Attributes = color;
	}
}
void PGRG_Rectangle(int x , int y,int width,int height,CHAR_INFO buffer[],WORD color){
PGRG_Line(x, y, x+width, y, buffer, color);
PGRG_Line(x, y, x, y+height, buffer, color);
PGRG_Line(x, y+height, x+width, y+height, buffer, color);
PGRG_Line(x+width, y, x + width, y+height, buffer, color);
}


#endif
