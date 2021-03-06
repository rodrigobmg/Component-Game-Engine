/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
#pragma once

#define ENGINEASSETS "../EngineAssets/"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#define GLEW_STATIC
#include "glew.h"
#include "GL\glut.h"
#include "gl/freeglut_ext.h"
#include "glFunctions.h"
#include "soil/SOIL.h"
#include "bullet3/btBulletDynamicsCommon.h" // BULLET PHYSICS
#include <iostream>
#include <memory>
#include <unordered_map>
#define shared std::shared_ptr
#define mkShare std::make_shared
#define weak std::weak_ptr
static int windowOldWidth = 0;
static int windowOldHeight = 0;
static bool windowUpdated = false;

//----------------------------------------------------------------------------------------------------------------------
/// \brief  freeglut initialisation
/// \return bool true if glut initialisation was susscessful
//----------------------------------------------------------------------------------------------------------------------
bool initGlut(int& argc, char** argv);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  glew initialisation
/// \return GLenum true if glew initialisation was susscessful
//----------------------------------------------------------------------------------------------------------------------
GLenum initGlew();

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Delta Time 
//----------------------------------------------------------------------------------------------------------------------
void initTimerDT(); ///< initialisation
float updateTimerDT(); ///< update, return delta time

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Uses the current Delta Time to compute the current Frames Per Second (FPS)
/// prama	float delta time
/// \return	FPS
//----------------------------------------------------------------------------------------------------------------------
float currentFPS(float& dt);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  When a key is pressed down
/// prama  unsigned char key
/// prama  int
/// prama  int
//----------------------------------------------------------------------------------------------------------------------
void keyboardOnPress(unsigned char key, int, int);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  When a key is pressed released
/// prama  unsigned char key
/// prama  int
/// prama  int
//---------------------------------------------------------------------------------------------------------------------
void keyboardOnRelease(unsigned char key, int, int);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  When a special key is pressed
/// prama  int key
/// prama  int
/// prama  int
//---------------------------------------------------------------------------------------------------------------------
void keyboardSpecialKeys(int key, int, int);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Has the key been pressed
/// prama  short key
//----------------------------------------------------------------------------------------------------------------------
bool isKeyPressed(short key);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Toggle full screen mode
/// prama  bool
//----------------------------------------------------------------------------------------------------------------------
void toggleFullScreen(const bool& s);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Handles mouse input
/// prama  int (GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
/// prama  int (GLUT_DOWN, GLUT_UP)
/// prama  int mouse X position (from upper left)
/// prama  int mouse Y position (from upper left)
//----------------------------------------------------------------------------------------------------------------------
void mouseInput(int button, int state, int x, int y);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  is a mouse key pressed
/// prama  short (GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
/// \return bool
//----------------------------------------------------------------------------------------------------------------------
bool isMouseKeyPressed(short key);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  gets the mouse position
/// prama  int X
/// prama  int Y
//----------------------------------------------------------------------------------------------------------------------
void mousePosition(int& x, int& y);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  gets the mouse position when a mouse button was clicked and moving
/// prama  int X
/// prama  int Y
//----------------------------------------------------------------------------------------------------------------------
void mouseMotion(int x, int y);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  gets the mouse position when a mouse is just moving
/// prama  int X
/// prama  int Y
//----------------------------------------------------------------------------------------------------------------------
void mousePassiveMotion(int x, int y);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Is the window in full screen mode
/// \return bool true is in fullscreen
//----------------------------------------------------------------------------------------------------------------------
bool isFullScreen();

//----------------------------------------------------------------------------------------------------------------------
/// \brief  What to resize the screen to
/// prama  int width
/// prama  int height
//----------------------------------------------------------------------------------------------------------------------
void onResize(int width, int height);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  get the screen size
/// prama  int width
/// prama  int height
//----------------------------------------------------------------------------------------------------------------------
void getSize(int& newWidth, int& newHeight);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  rename the window once it has been created
/// prama  char* new title
//----------------------------------------------------------------------------------------------------------------------
inline void windowRename(const char* name) { glutSetWindowTitle(name); }

//----------------------------------------------------------------------------------------------------------------------
/// \brief  delete/free memory
//----------------------------------------------------------------------------------------------------------------------
void cleanup();

//----------------------------------------------------------------------------------------------------------------------
/// \brief  MAIN ENETRY POINT! called from main(), calls glut functions.
//----------------------------------------------------------------------------------------------------------------------
int run(int argc, char* argv[]);


