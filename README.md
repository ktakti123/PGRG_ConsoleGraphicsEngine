# PGRG_ConsoleGraphicsEngine
Light weight header file for writing graphics in your console with C language. Learning programming has never been this fun before .

Here's a simple example code to get hang of things. 


#include <stdio.h>
#include <windows.h>
#include "PGRG_ConsoleGraphics.h"
int main()
{ int x = 1;
	int y = 1;
  int ax = 1;  //This is just to move geometric shapes in the buffer screen.
  int ay = 1;
	PGRG_WindowStart(150, 200, 2); // create window with its size. This takes With , Height and Font Size(size of each pixel) as arguments. just put fontsize to 2 
	PGRG buffer[150 * 200]; //This line of code simply sets of size of the drawing buffer where we print graphics. Make this same size a window size. 
	
	while (1) // Ahh dont be furious now. It's my way of being lazy. Set up a boolean if you like . In C remember to add <stdbool.h> for booleans. 
	{
		PGRG_FillColor(buffer); //This clears whole screen with the colors you choose
		PGRG_Line(x, 5, 60, 20, buffer,PGRG_BLACK);//Draws line with two points (x1,y1),(x2,y2). arguments sorted as (x1,y1,x2,y2,buffer,color)
		PGRG_Circle(x,y,5,buffer,PGRG_WHITE);//Draws circle arguments is (circle centeroint x, centerpoint y , radius,color)
		PGRG_FillCircle(100,30,5,buffer,PGRG_BLUE); //Same as above . In this case circle is filled with color.
		PGRG_Triangle(10,40,100,200,70,100,buffer,PGRG_GREEN); // Draws triangles with 3 points (x1,y1,x2,y2,x3,y3,buffer,color)
		PGRG_Pixel(10,50,buffer,PGRG_DBLUE);//Draws single pixel at (x,y)
		PGRG_Rectangle(20,30 ,10,10,buffer,PGRG_GREEN);// (topleft x1,topleft y1, width, height, buffer , color) Prints Square or Rectangle.
		PGRG_Display(buffer);// Displays Everything to Screen
	// Just some Code for bouncing balls around.
		x=x+ax; 
		y=y+ay;
		if(x > nScreenWidth-5  || x < 0)
		ax = -ax;
		if(y> nScreenHeight-5  || y< 0)
		ay = -ay;
	}
	return 0;
}

