#include <cmath>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <random>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include "Camera.h"
#include "Ray.h"
#include "Trace.h"
#include "Sphere.h"
#include "LightSource.h"
#include "MCG_GFX_Lib.h"

std::mutex mutex;

void thread1(int id, Traceray traceray, Camera camera, LightSource lightpoint, float startingPoint, float range, int x)
{


	for (int k = startingPoint; k <= startingPoint + range; k++)
	{

		for (int j = 0; j <= x; j++)
		{
			glm::vec3 pixelColour;

			// Draw the pixel to the screen
			glm::ivec2 pixelPosition = glm::ivec2(j, k); //Gets the position of the pixel

			Ray raycreated = camera.Returnray(pixelPosition);//stores the returnray inside raycreated
			intersectResult tmpResult;

			//Change 0 to 1-5, sets number of time ray is reflected.
			pixelColour = traceray.Raytracer(raycreated, lightpoint, camera, 10);

			pixelColour = glm::clamp(pixelColour, glm::vec3(0.0f), glm::vec3(1.0f)) * 255.0f;


			mutex.lock();
			MCG::DrawPixel(pixelPosition, pixelColour);
			mutex.unlock();
			

		}

		if (id == 0)
		{
			mutex.lock();
			MCG::ProcessFrame();
			mutex.unlock();
		}

	}


}

int main(int argc, char *argv[])
{


	// Variable for storing window dimensions
	int x = 640;
	int y = 480;

	glm::ivec2 windowSize(x, y);

	// Call MCG::Init to initialise and create your window
	// Tell it what size you want the window to be
	if (!MCG::Init(windowSize))
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return -1;
	}

	// Sets every pixel to the same colour
	// parameters are RGBA, numbers are from 0 to 255
	MCG::SetBackground(glm::ivec3(0, 0, 0));

	// Preparing a position to draw a pixel
	glm::ivec2 pixelPosition = windowSize / 2;

	// Preparing a colour to draw
	// Colours are RGB, each value ranges between 0 and 255
	glm::vec3 pixelColour(0, 255, 0);






	
	float timer = 0.0f;
	bool run = true;

	// This is our game loop
	// It will run until the user presses 'escape' or closes the window
	while (MCG::ProcessFrame())
	{
	


		Camera camera;
		Traceray traceray;
		Sphere sphere[2];
		LightSource lightpoint;
		
		//Change the number to whatever amount of threads you want to have
    #define NUM_THREADS 5
		std::thread threads[NUM_THREADS];

		lightpoint.setLightpos(glm::vec3(0.0f, -10.0f, 5.0f));
		lightpoint.setLightColour(glm::vec3(1.0f, 1.0f, 1.0f));
		lightpoint.setAmbientLight(glm::vec3(0.1f));
		lightpoint.setObjectShininess(10.0f);

		std::random_device rseed;
		std::mt19937 rng(rseed());
		
		std::uniform_real_distribution<float> colourX(0.1, 1);
		std::uniform_real_distribution<float> colourY(0.1, 1);
		std::uniform_real_distribution<float> colourZ(0.1, 1);

		glm::vec3 randColour;
		randColour.x = colourX(rng);
		randColour.y = colourY(rng);
		randColour.z = colourZ(rng);

		glm::vec3 randColour1;
		randColour1.x = colourX(rng);
		randColour1.y = colourY(rng);
		randColour1.z = colourZ(rng);

		sphere[0].SetRadius(1.5f);
		sphere[0].SetSphereori(glm::vec3(1.2f, 1.0f, -10.0f));
		sphere[0].setSphereColour(glm::vec3(randColour.x, randColour.y, randColour.z));
		
		sphere[1].SetRadius(1.5f);
		sphere[1].SetSphereori(glm::vec3(-2.0f, 0.0f, -10.0f));
		sphere[1].setSphereColour(glm::vec3(randColour1.x, randColour1.y, randColour1.z));
		
		
		for (int i = 0; i < (sizeof(sphere) / sizeof(*sphere)); i++)
		{
			traceray.SetSpheres(sphere[i]);
		}
		
		
	

		//for (int i = 0; i < (sizeof(sphere) / sizeof(*sphere)); i++)
		//{
		//	
		//	//This sets the positions of sphere randomly
		//	std::uniform_real_distribution<float> distX(0.0f, 20.0f);
		//	std::uniform_real_distribution<float> distY(0.0f, 20.0f);
		//	std::uniform_real_distribution<float> distZ(-5.0f,-50.0f); 

		//	// This randomly chooses colour of spheres
		//	std::uniform_real_distribution<float> colourX(0.1, 1); 
		//	std::uniform_real_distribution<float> colourY(0.1, 1);
		//	std::uniform_real_distribution<float> colourZ(0.1, 1);

		//	//random radius size
		//	std::uniform_real_distribution<float> radius(1.5f, 2.0f);

		//glm::vec3 randColour;
		//randColour.x = colourX(rng);
		//randColour.y = colourY(rng);
		//randColour.z = colourZ(rng);

		//	glm::vec3 randPos;
		//	randPos.x = distX(rng);
		//	randPos.y = distY(rng);
		//	randPos.z = distZ(rng);

		//	glm::vec3 color;
		//	sphere[i].SetRadius(radius(rng));
		//	sphere[i].SetSphereori(randPos);
		//	sphere[i].setSphereColour(randColour);
		//	

		//	traceray.SetSpheres(sphere[i]);
		//}
		
	  //Setting Camera
		camera.setWindowsize(glm::ivec2(x, y));
		camera.setCampos(glm::vec3(0.0f, 0.0f, 0.0f));
		//camera.setCampos(glm::vec3(-15.0f, -10.0f, -3.0f));

		float numOfthreads = NUM_THREADS;
		float startingPoint = 0;
		float range = y / numOfthreads;
		int id = 0;
		int count = 0;

	
		auto start = std::chrono::high_resolution_clock::now();
		// for loop that goes through each thread
		while (run)
		{
			for (int k = 0; k < numOfthreads; k++)
			{

				threads[k] = std::thread(&thread1, id, traceray, camera, lightpoint, startingPoint, range, x);


				startingPoint = startingPoint + range;
				count++;
				//std::cout << " startingPoint = " << startingPoint << std::endl;   
			}

			for (int l = 0; l < numOfthreads; l++)
			{
				if (threads[l].joinable())
				{
					threads[l].join();
				}

			}

			run = false;
		}


		
		
		int key;
		auto stop = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double>elapsed = stop - start;
		std::cout << "Time taken: " << elapsed.count() << "s\n";
		std::cout << "drew spheres" << std::endl;
		//Pausing prgram so that  time can be shown.
		system("pause");
		
		

	}


	return 0;


}






