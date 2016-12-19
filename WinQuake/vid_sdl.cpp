
#include <SDL.h>
#include <SDL_opengl.h>

#include "quakedef.h"

static int scr_width, scr_height;

SDL_Window* sdlWindow = NULL;
SDL_GLContext sdlContext = NULL;

/*
===================
VID_Init
===================
*/
void	VID_Init(unsigned char *palette)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		Sys_Error("SDL_Init error - %s", SDL_GetError());
	}

	int flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

	int width = 640;
	int height = 480;

	// set vid parameters
	if ((COM_CheckParm("-window")) == 0)
		flags |= SDL_WINDOW_FULLSCREEN;

	/*if ((i = COM_CheckParm("-width")) != 0)
		width = atoi(com_argv[i + 1]);

	if ((i = COM_CheckParm("-height")) != 0)
		height = atoi(com_argv[i + 1]);*/

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	sdlWindow = SDL_CreateWindow("SDLQuake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	if (!sdlWindow)
	{
		Sys_Error("SDL window could not be created! - %s", SDL_GetError());
	}

	sdlContext = SDL_GL_CreateContext(sdlWindow);
	if (!sdlContext)
	{
		Sys_Error("OpenGL context could not be created! - %s", SDL_GetError());
	}

	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		Con_DPrintf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}
}

void	VID_Shutdown()
{
	SDL_Quit();
}


/*void Sys_SendKeyEvents(void)
{
	SDL_Event event;
	int sym, state, but;
	int modstate;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			sym = event.key.keysym.sym;
			state = event.key.state;
			modstate = SDL_GetModState();
			switch (sym)
			{
			case SDLK_DELETE: sym = K_DEL; break;
			case SDLK_BACKSPACE: sym = K_BACKSPACE; break;
			case SDLK_F1: sym = K_F1; break;
			case SDLK_F2: sym = K_F2; break;
			case SDLK_F3: sym = K_F3; break;
			case SDLK_F4: sym = K_F4; break;
			case SDLK_F5: sym = K_F5; break;
			case SDLK_F6: sym = K_F6; break;
			case SDLK_F7: sym = K_F7; break;
			case SDLK_F8: sym = K_F8; break;
			case SDLK_F9: sym = K_F9; break;
			case SDLK_F10: sym = K_F10; break;
			case SDLK_F11: sym = K_F11; break;
			case SDLK_F12: sym = K_F12; break;
			case SDLK_BREAK:
			case SDLK_PAUSE: sym = K_PAUSE; break;
			case SDLK_UP: sym = K_UPARROW; break;
			case SDLK_DOWN: sym = K_DOWNARROW; break;
			case SDLK_RIGHT: sym = K_RIGHTARROW; break;
			case SDLK_LEFT: sym = K_LEFTARROW; break;
			case SDLK_INSERT: sym = K_INS; break;
			case SDLK_HOME: sym = K_HOME; break;
			case SDLK_END: sym = K_END; break;
			case SDLK_PAGEUP: sym = K_PGUP; break;
			case SDLK_PAGEDOWN: sym = K_PGDN; break;
			case SDLK_RSHIFT:
			case SDLK_LSHIFT: sym = K_SHIFT; break;
			case SDLK_RCTRL:
			case SDLK_LCTRL: sym = K_CTRL; break;
			case SDLK_RALT:
			case SDLK_LALT: sym = K_ALT; break;
			case SDLK_KP0:
				if (modstate & KMOD_NUM) sym = K_INS;
				else sym = SDLK_0;
				break;
			case SDLK_KP1:
				if (modstate & KMOD_NUM) sym = K_END;
				else sym = SDLK_1;
				break;
			case SDLK_KP2:
				if (modstate & KMOD_NUM) sym = K_DOWNARROW;
				else sym = SDLK_2;
				break;
			case SDLK_KP3:
				if (modstate & KMOD_NUM) sym = K_PGDN;
				else sym = SDLK_3;
				break;
			case SDLK_KP4:
				if (modstate & KMOD_NUM) sym = K_LEFTARROW;
				else sym = SDLK_4;
				break;
			case SDLK_KP5: sym = SDLK_5; break;
			case SDLK_KP6:
				if (modstate & KMOD_NUM) sym = K_RIGHTARROW;
				else sym = SDLK_6;
				break;
			case SDLK_KP7:
				if (modstate & KMOD_NUM) sym = K_HOME;
				else sym = SDLK_7;
				break;
			case SDLK_KP8:
				if (modstate & KMOD_NUM) sym = K_UPARROW;
				else sym = SDLK_8;
				break;
			case SDLK_KP9:
				if (modstate & KMOD_NUM) sym = K_PGUP;
				else sym = SDLK_9;
				break;
			case SDLK_KP_PERIOD:
				if (modstate & KMOD_NUM) sym = K_DEL;
				else sym = SDLK_PERIOD;
				break;
			case SDLK_KP_DIVIDE: sym = SDLK_SLASH; break;
			case SDLK_KP_MULTIPLY: sym = SDLK_ASTERISK; break;
			case SDLK_KP_MINUS: sym = SDLK_MINUS; break;
			case SDLK_KP_PLUS: sym = SDLK_PLUS; break;
			case SDLK_KP_ENTER: sym = SDLK_RETURN; break;
			case SDLK_KP_EQUALS: sym = SDLK_EQUALS; break;
			}
			// If we're not directly handled and still above 255
			// just force it to 0
			if (sym > 255)
				sym = 0;
			Key_Event(sym, state);
			break;

		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			but = event.button.button;
			if (but == 2)
				but = 3;
			else if (but == 3)
				but = 2;
			switch (but) {
			case 1:
			case 2:
			case 3:
				Key_Event(K_MOUSE1 + but - 1, event.type
					== SDL_MOUSEBUTTONDOWN);
				break;
			}
			break;

		case SDL_MOUSEMOTION:
			if (_windowed_mouse.value)
			{
				if ((event.motion.x != (vid.width / 2))
					|| (event.motion.y != (vid.height / 2))) {
					mouse_x = event.motion.xrel * 5;
					mouse_y = event.motion.yrel * 5;
					if ((event.motion.x < ((vid.width / 2) - (vid.width / 4)))
						|| (event.motion.x >
						((vid.width / 2) + (vid.width / 4)))
						|| (event.motion.y <
						((vid.height / 2) - (vid.height / 4)))
						|| (event.motion.y >
						((vid.height / 2) + (vid.height / 4))))
					{
						SDL_WarpMouse(vid.width / 2, vid.height / 2);
					}
				}
			}
			break;

		case SDL_QUIT:
			CL_Disconnect();
			Host_ShutdownServer(false);
			Sys_Quit();
			break;

		default:
			break;
		}
	}
}*/

/*void ToggleFullScreen()
{
	if (isFullScreen)
	{
		if (SDL_SetWindowFullscreen(_window, 0) != 0)
		{
			printf("Unable to switch window to fullscreen mode:%s\n", SDL_GetError());
		}
		isFullScreen = false;
	}
	else
	{
		if (SDL_SetWindowFullscreen(_window, 1) != 0)
		{
			printf("Unable to switch window to fullscreen mode:%s\n", SDL_GetError());
		}
		isFullScreen = true;
	}
}*/

/*
=================
GL_BeginRendering

=================
*/
void GL_BeginRendering(int *x, int *y, int *width, int *height)
{
	*x = *y = 0;
	*width = scr_width;
	*height = scr_height;
}


void GL_EndRendering(void)
{
	SDL_GL_SwapWindow(sdlWindow);
}