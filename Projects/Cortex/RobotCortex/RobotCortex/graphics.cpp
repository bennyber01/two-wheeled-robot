#include "graphics.h"
#include <stdio.h>
#include <stdarg.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include "bitmap_image.hpp"

#include "DirectoryManager.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

void Graphics::Draw(const MotorsTicks & motorsTicks)
{
}

void Graphics::print(const char * format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void Graphics::println(const char * format, ...)
{
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	printf("\r\n");
}

bool Graphics::SaveAsBMP(const WheelsLocationsHolder & wheelsLocationsHolder, char * fileName)
{
	if (!CreateDirectoryFromFilePath(fileName))
	{
		ASSERT(FALSE);
		println("Graphics::SaveAsBMP : unable to create directory from file path : '%s'.", fileName);
		return false;
	}

	double minX = 0;
	double maxX = 0;
	double minY = 0;
	double maxY = 0;
	for (int i = 0; i < wheelsLocationsHolder.size(); ++i)
	{
		if (i == 0 || minX > wheelsLocationsHolder[i].leftWheelLoc.x) minX = wheelsLocationsHolder[i].leftWheelLoc.x;
		if (i == 0 || maxX < wheelsLocationsHolder[i].leftWheelLoc.x) maxX = wheelsLocationsHolder[i].leftWheelLoc.x;
		if (i == 0 || minY >-wheelsLocationsHolder[i].leftWheelLoc.y) minY = -wheelsLocationsHolder[i].leftWheelLoc.y;
		if (i == 0 || maxY <-wheelsLocationsHolder[i].leftWheelLoc.y) maxY = -wheelsLocationsHolder[i].leftWheelLoc.y;

		if (minX > wheelsLocationsHolder[i].rightWheelLoc.x) minX = wheelsLocationsHolder[i].rightWheelLoc.x;
		if (maxX < wheelsLocationsHolder[i].rightWheelLoc.x) maxX = wheelsLocationsHolder[i].rightWheelLoc.x;
		if (minY >-wheelsLocationsHolder[i].rightWheelLoc.y) minY = -wheelsLocationsHolder[i].rightWheelLoc.y;
		if (maxY <-wheelsLocationsHolder[i].rightWheelLoc.y) maxY = -wheelsLocationsHolder[i].rightWheelLoc.y;
	}

	minX -= 20;
	minY -= 20;
	maxX += 20;
	maxY += 20;

	bitmap_image image(maxX - minX, maxY - minY);
	image.clear(30);

	image_drawer draw(image);

	if (0)
	{
		for (int i = 0; i < wheelsLocationsHolder.size(); ++i)
		{
			const WheelsLocation & currLoc = wheelsLocationsHolder[i];

			int circleRadius = ((i == 0) ? 3 : 2);

			draw.pen_width(1);
			draw.pen_color(255,0,0);
			int x = currLoc.leftWheelLoc.x - minX;
			int y =-currLoc.leftWheelLoc.y - minY;
			draw.circle(x, y, circleRadius);

			draw.pen_width(1);
			draw.pen_color(0,255,0);
			x = currLoc.rightWheelLoc.x - minX;
			y =-currLoc.rightWheelLoc.y - minY;
			draw.circle(x, y, circleRadius);
		}
	}
	else
	{
		for (int i = 1; i < wheelsLocationsHolder.size(); ++i)
		{
			const WheelsLocation & currLoc0 = wheelsLocationsHolder[i-1];
			const WheelsLocation & currLoc1 = wheelsLocationsHolder[i];

			if (i == 1)
			{
				draw.pen_width(1);
				draw.pen_color(255,0,0);
				int x = currLoc0.leftWheelLoc.x - minX;
				int y =-currLoc0.leftWheelLoc.y - minY;
				draw.circle(x, y, 2);

				draw.pen_width(1);
				draw.pen_color(0,255,0);
				x = currLoc0.rightWheelLoc.x - minX;
				y =-currLoc0.rightWheelLoc.y - minY;
				draw.circle(x, y, 2);
			}

			draw.pen_width(1);
			draw.pen_color(255,0,0);
			int x0 = currLoc0.leftWheelLoc.x - minX;
			int y0 =-currLoc0.leftWheelLoc.y - minY;
			int x1 = currLoc1.leftWheelLoc.x - minX;
			int y1 =-currLoc1.leftWheelLoc.y - minY;
			draw.line_segment(x0, y0, x1, y1);

			draw.pen_width(1);
			draw.pen_color(0,255,0);
			x0 = currLoc0.rightWheelLoc.x - minX;
			y0 =-currLoc0.rightWheelLoc.y - minY;
			x1 = currLoc1.rightWheelLoc.x - minX;
			y1 =-currLoc1.rightWheelLoc.y - minY;
			draw.line_segment(x0, y0, x1, y1);
		}
	}

	image.save_image(fileName);

	return true;
}
