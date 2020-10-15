#include "graphics.h"
#include <iostream>
#include "stb_image.h"

void graphics::shape::reload(type shapeType)
{
	switch (shapeType)
	{
	case quad:
	{
		vertexData = {};
		indexData = {};
		vertexData.insert(vertexData.end(), { width * -1.0f, height * 1.0f, 0.0f, 0.0f, 1.0f });
		vertexData.insert(vertexData.end(), { width * 1.0f, height * 1.0f, 0.0f, 1.0f, 1.0f });
		vertexData.insert(vertexData.end(), { width * 1.0f, height * -1.0f, 0.0f, 1.0f, 0.0f });
		vertexData.insert(vertexData.end(), { width * -1.0f, height * -1.0f, 0.0f, 0.0f, 0.0f });
		indexData.insert(indexData.end(), { 0, 1, 2 });
		indexData.insert(indexData.end(), { 2, 3, 0 });
		break;
	}
	case circle:
	{
		vertexData = {};
		indexData = {};
		// detail(int)
		float angle = 0.0f;
		vertexData.insert(vertexData.end(), { 0.0f, 0.0f, 0.0f, 0.5f, 0.5f });
		for (int stage = 1; stage <= detail; stage++)
		{
			vertexData.insert(vertexData.end(), { cos((float)glm::radians(angle)), sin((float)glm::radians(angle)), 0.0f, (cos((float)glm::radians(angle))+1.0f)/2.0f , (sin((float)glm::radians(angle))+1.0f)/2.0f });
			if (stage >= 2)
			{
				indexData.insert(indexData.end(), { 0, stage - 1, stage });
			}
			angle += 360.0f / detail;
		}
		indexData.insert(indexData.end(), { 0, detail, 1 });
		break;
	}
	case sphere:
	{
		vertexData = {};
		indexData = {};
		// detail(int) - dictates number of longitudes on equator and latitudes
		int longitudes = detail + 2; //vertical - dictate points on circle
		int latitudes = detail; //horizontal - how many circles we have
		vertexData.insert(vertexData.end(), { 0.0f, 0.0f, 0.5f, 0.0f, 0.0f }); //tip
		for (int i = 1; i < longitudes; i++)
		{
			indexData.insert(indexData.end(), { 0, i, i+1 });
		}
		indexData.insert(indexData.end(), { 0, longitudes, 1 });
		float radius = 0.0f;
		float distance = 0.0f;
		int currentPoint = 0;
		for (int i = 1; i <= (int)(latitudes*capHeight); i++)
		{
			float angle = 0.0f;
			radius = sin(3.1415*(float)i/(latitudes+1));
			distance = cos(3.1415 * (float)i / (latitudes + 1));
			for (int j = 1; j <= longitudes; j++)
			{
				float cosine = cos((float)glm::radians(angle));
				float sine = sin((float)glm::radians(angle));
				vertexData.insert(vertexData.end(), { 0.5f*radius*cosine, 0.5f*radius*sine, 0.5f*distance, (radius*cosine+1)/2 ,(radius*sine+1)/2 });
				currentPoint++;
				if (latitudes>1 && i!=latitudes && j!=longitudes)
				{
					indexData.insert(indexData.end(), { currentPoint, currentPoint + 1, currentPoint + longitudes});
					indexData.insert(indexData.end(), { currentPoint + 1, currentPoint + longitudes, currentPoint + longitudes +1});
				}
				if (latitudes > 1 && i != latitudes && j == longitudes)
				{
					indexData.insert(indexData.end(), { currentPoint, currentPoint + 1 - longitudes, currentPoint + 1 });
					indexData.insert(indexData.end(), { currentPoint + 1, currentPoint + longitudes, currentPoint });
				}
				angle += 360.0f / longitudes;
			}
		}
		if (capHeight == 1.0f)
		{
			vertexData.insert(vertexData.end(), { 0.0f, 0.0f, -0.5f, 0.0f, 0.0f }); //tip
			currentPoint++;
			for (int i = 1; i < longitudes; i++)
			{
				indexData.insert(indexData.end(), { currentPoint, currentPoint - i, currentPoint - i - 1 });
			}
			indexData.insert(indexData.end(), { currentPoint, currentPoint - longitudes, currentPoint - 1 });
		}
		break;
	}
	case geoSphere:
	{
		vertexData = {};
		indexData = {};
		int width, height, nrChannels;
		const char* mapLoc = geoSphereImageLoc.c_str();
		unsigned char* mapData = stbi_load(mapLoc, &width, &height, &nrChannels, 3);
		//starts with bottom-left towards bottom-right
		int verticesNum = width * height;
		//x = psinAcosB y = psinAsinB z = pcosB A=yaw (0-2pi), B=pitch (0-pi)
		float radius;
		float yaw;
		float pitch;
		float x, y, z;
		for (int j = 1; j < height; j++)
		{
			//pitch
			for (int i = 0; i <= width; i++)
			{
				//yaw
				radius = (((int)mapData[((height-j)*(width)+i)*3])/255.0f)*0.1f+0.9f;
				yaw = (float)i*360/width;
				pitch = (float)j*180/height;
				z = radius * (float)sin(glm::radians(pitch)) * (float)cos(glm::radians(yaw));
				x = radius * (float)sin(glm::radians(pitch)) * (float)sin(glm::radians(yaw));
				y =	radius * (float)cos(glm::radians(pitch));
				vertexData.insert(vertexData.end(), {x ,y ,z , (float)i/width, (float)(height-j)/height });
				int pointA, pointB, pointC, pointD;
				pointA = (j - 1) * (width + 1) + i;							//top-left
				pointB = (j - 1) * (width + 1) + ((i + 1) % (width + 1));	//top-right
				pointC = j * (width + 1) + i;								//bottom-left
				pointD = j * (width + 1) + ((i + 1) % (width + 1));			//bottom-right
				if (j != height - 1)
				{
					indexData.insert(indexData.end(), { pointA ,pointB ,pointC });
					indexData.insert(indexData.end(), { pointB ,pointD ,pointC });
				}
			}
		}
	}
	}
}

graphics::shape::shape()
{
}
