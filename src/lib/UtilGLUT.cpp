/*/////////////////////////////////////////////////////////////////////////////////////////////////
module:  implementation of GLUT utility class
purpose: implements general utilities for OpenGL/GLUT/OS support

written: U.Kuenzler
version: 2.00
history: 2.00 - version for OpenGL 4.x applications
history: 1.00 - initial version for OpenGL drawing application
/////////////////////////////////////////////////////////////////////////////////////////////////*/




// system includes ////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#ifdef WIN32
#include <windows.h>
#endif // WIN32


// OpenGL helper includes /////////////////////////////////////////////////////////////////////////
#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


// application helper includes ////////////////////////////////////////////////////////////////////
#include "lib/UtilGLUT.hpp"
using namespace std;



bool UtilGLUT::getFilePath(string& filepath, const string& filter, const string& initial, bool open)
///////////////////////////////////////////////////////////////////////////////////////////////////
{
	bool result = false;

#ifdef WIN32
#ifdef _UNICODE
	// WIN32 requires wchar_t type strings, so you need to convert all std::strings
	// (see VS2005 project settings for character set --> can be _UNICODE or _MBCS)
	// std::cout << "DEBUG: UtilGLUT::getFilePath() (_UNICODE Version)" << std::endl;
	wstring wstr_initial = wstring(initial.begin(), initial.end());
	wstring wstr_filter = wstring(filter.begin(), filter.end());

	// replace custom filter string separator L'\n' with L'\0' required by the OFN structure
	for (unsigned int i=0; i<wstr_filter.size(); i++)
	{
		if (wstr_filter[i] == L'\n') wstr_filter[i] = L'\0';
	}

	// initialize Win32 OPENFILENAME structure file open common dialog box
	OPENFILENAME ofn;					// windows common dialog struct
	wchar_t pathbuffer[260];			// buffer for file path (needs to be of wide char type)
	ZeroMemory(&ofn, sizeof(ofn));		// clear memory
	ofn.lStructSize = sizeof(ofn);		// determine size of common dialog struct
	ofn.hwndOwner = NULL;				// handle of parent window
	ofn.lpstrFile = pathbuffer;			// buffer for file path
	ofn.nMaxFile = sizeof(pathbuffer);	// determine size of file path buffer
	ofn.lpstrFile[0] = L'\0';			// init with '\0' (wchar_t) so it is not used for initialization
	ofn.nFilterIndex = 1;				// index of the currently selected file filter control
	ofn.lpstrFileTitle = NULL;			// buffer that receives the file name and extension (without path)
	ofn.nMaxFileTitle = 0;				// size of the buffer pointed to by lpstrFileTitle
	ofn.lpstrDefExt = L"DAT";			// buffer containing default extension if non is user supplied

	// a set of bit flags, which can be used to initialize the dialog box
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	// buffer containing pairs of null-terminated filter strings (terminated by two NULL characters)
	ofn.lpstrFilter = wstr_filter.c_str();

	// NULL terminated string that can specify the initial directory
	ofn.lpstrInitialDir = wstr_initial.c_str();

	// display the Open dialog box and get file path or return false otherwise
	if (open)
	{
		if ( GetOpenFileName(&ofn) )
		{
			// get open file path system call successful, set result
			result = true;

			// convert from wchar_t to wstring and string type (may not work for arbitrary UNICODE)
			wstring wstr_path(pathbuffer);
			filepath = string(wstr_path.begin(), wstr_path.end());

			// std::wcout << L"DEBUG: file path = '" << pathbuffer << L"' (wchar_t)" << std::endl;
			// std::cout << "DEBUG: file path = '" << filepath << "' (char)" << std::endl;
		}
	}
	else // save
	{
		if ( GetSaveFileName(&ofn) )
		{
			// get save file path system call successful, set result
			result = true;

			// convert from wchar_t to wstring and string type (may not work for arbitrary UNICODE)
			wstring wstr_path(pathbuffer);
			filepath = string(wstr_path.begin(), wstr_path.end());

			// std::wcout << L"DEBUG: file path = '" << pathbuffer << L"' (wchar_t)" << std::endl;
			// std::cout << "DEBUG: file path = '" << filepath << "' (char)" << std::endl;
		}
	}

#else // NOT _UNICODE
	// VS2005 can be configured for non _UNICODE version (i.e. _MBCS characters)
	// std::cout << "DEBUG: UtilGLUT::getFilePath() (_MBCS Version)" << std::endl;

	// replace custom filter string separator '\n' with '\0' required by the OFN structure
	string str_filter = filter;
	for (unsigned int i=0; i<filter.size(); i++)
	{
		if (str_filter[i] == '\n') str_filter[i] = '\0';
	}

	// initialize Win32 OPENFILENAME structure file open common dialog box
	OPENFILENAME ofn;					// windows common dialog struct
	char pathbuffer[260];				// buffer for file path (needs to be of wide char type)
	ZeroMemory(&ofn, sizeof(ofn));		// clear memory
	ofn.lStructSize = sizeof(ofn);		// determine size of common dialog struct
	ofn.hwndOwner = NULL;				// handle of parent window
	ofn.lpstrFile = pathbuffer;			// buffer for file path
	ofn.nMaxFile = sizeof(pathbuffer);	// determine size of file path buffer
	ofn.lpstrFile[0] = '\0';			// init with '\0' (wchar_t) so it is not used for initialization
	ofn.nFilterIndex = 1;				// index of the currently selected file filter control
	ofn.lpstrFileTitle = NULL;			// buffer that receives the file name and extension (without path)
	ofn.nMaxFileTitle = 0;				// size of the buffer pointed to by lpstrFileTitle
	ofn.lpstrDefExt = "DAT";			// buffer containing default extension if non is user supplied

	// a set of bit flags, which can be used to initialize the dialog box
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	// buffer containing pairs of null-terminated filter strings (terminated by two NULL characters)
	ofn.lpstrFilter = str_filter.c_str();

	// NULL terminated string that can specify the initial directory
	ofn.lpstrInitialDir = initial.c_str();

	// display the Open dialog box and get file path or return false otherwise
	if (open)
	{
		if ( GetOpenFileName(&ofn) )
		{
			// get open file path system call successful, set result
			result = true;

			// convert from wchar_t to wstring and string type (may not work for arbitrary unicode)
			filepath = string(pathbuffer);

			// std::cout << "DEBUG: file path = '" << filepath << "' (char)" << std::endl;
		}
	}
	else // save
	{
		if ( GetSaveFileName(&ofn) )
		{
			// get save file path system call successful, set result
			result = true;

			// convert from wchar_t to wstring and string type (may not work for arbitrary unicode)
			filepath = string(pathbuffer);

			// std::cout << "DEBUG: file path = '" << filepath << "' (char)" << std::endl;
		}
	}
#endif // NOT _UNICODE
#endif // WIN32

	return result;
}
// UtilGLUT::getFilePath() ////////////////////////////////////////////////////////////////////////





///////////////////////////////////////////////////////////////////////////////////////////////////
//
// NOTE:  The glutGetModifiers() function can only be used during certain GLUT callbacks, because
//        we need it during glutMotionFunc() callback, we use WIN32 access to the modifier keys.
//        (GLUT reference: "glutGetModifiers returns the modifier key state at the time the input
//        event for a keyboard, special, or mouse callback is generated. THIS ROUTINE MAY ONLY BE
//        CALLED WHILE A KEYBOARD, SPECIAL, OR MOUSE CALLBACK IS BEING HANDLED.")
//
///////////////////////////////////////////////////////////////////////////////////////////////////
int UtilGLUT::getKeyboardModifier(int& state)
///////////////////////////////////////////////////////////////////////////////////////////////////
{
#ifdef WIN32

	BYTE keyState[256];
	GetKeyboardState((LPBYTE)&keyState);

	//int wkey = keyState[VK_SHIFT];
	//int wkey = GetKeyState(VK_SHIFT);
	//int ctrl = (GetKeyState(VK_CONTROL) & 0x80000000) ? 1 : 0;

	// get control keys through WIN32 functions (init with WIN32 inactive state)
	static int shift_key = 1;
	static int ctrl_key  = 1;
	static int alt_key   = 1;
	// static int capslock_key = 0;


	if (shift_key != keyState[VK_SHIFT])
	{
		shift_key = keyState[VK_SHIFT];
		// std::cout << "DEBUG: Win32 SHIFT key: " << shift_key << std::endl;

		if (shift_key > 1)
		{
			// SHIFT key pressed
			state = GLUT_DOWN;
			return GLUT_ACTIVE_SHIFT;
		}
		else
		{
			// SHIFT key released
			state = GLUT_UP;
			return GLUT_ACTIVE_SHIFT;
		}
	}

	if (ctrl_key != keyState[VK_CONTROL])
	{
		ctrl_key = keyState[VK_CONTROL];
		// std::cout << "DEBUG: Win32 CTRL key: " << ctrl_key << std::endl;

		if (ctrl_key > 1)
		{
			// CTRL key pressed
			state = GLUT_DOWN;
			return GLUT_ACTIVE_CTRL;
		}
		else
		{
			// CTRL key released
			state = GLUT_UP;
			return GLUT_ACTIVE_CTRL;
		}
	}

	if (alt_key != keyState[VK_MENU])
	{
		alt_key = keyState[VK_MENU];
		// std::cout << "DEBUG: Win32 ALT key: " << alt_key << std::endl;

		if (alt_key > 1)
		{
			// ALT key pressed
			state = GLUT_DOWN;
			return GLUT_ACTIVE_ALT;
		}
		else
		{
			// ALT key released
			state = GLUT_UP;
			return GLUT_ACTIVE_ALT;
		}
	}

	/* CAPSLOCK currently not supported by GLUT
	if (capslock_key != keyState[VK_CAPITAL])
	{
		capslock_key = keyState[VK_CAPITAL];
		// std::cout << "DEBUG: Win32 CAPS-LOCK key: " << capslock_key << std::endl;

		if (capslock_key == 129)
		{
			std::cout << "DEBUG: Win32 CapsLock Mode: On" << std::endl;
		}
		else if (capslock_key == 128)
		{
			std::cout << "DEBUG: Win32 CapsLock Mode: Off" << std::endl;
		}
	}
	// CAPSLOCK currently not supported by GLUT */

#else // not WIN32, try to use GLUT (works with cursor keys, but usually not with mouse --> see note)

	// get control keys through GLUT functions (init with GLUT inactive state)
	static int modifier_key = 0;

	int keyState = glutGetModifiers();

	if (modifier_key != keyState)
	{
		//
		std::cout << "DEBUG: Glut modifier key: " << keyState << std::endl;

		if (keyState > 0)
		{
			// new modifier key pressed, return it
			modifier_key = keyState;;
			state = GLUT_DOWN;
			return keyState;
		}
		else
		{
			// modifier key released, return previous modifier
			state = GLUT_UP;
			std::swap(modifier_key, keyState);
			return keyState;
		}
	}
#endif // WIN32

	return 0;
}
// UtilGLUT::checkKeyboardModifier() //////////////////////////////////////////////////////////////


void UtilGLUT::showFPS(const string& title)
///////////////////////////////////////////////////////////////////////////////////////////////////
{
	// replace current GLUT window title with FPS string ("append" can not be implemented,
	// because there is no GLUT function to get the current window title.)

	// calculate frames per second (FPS)
	static int frame = 0;
	static int time = 0;
	static int timebase = 0;
	stringstream title_fps; 

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000)
	{
		title_fps.setf(std::ios::fixed, std::ios::floatfield);
		title_fps.precision(2);
		title_fps << title << " ( FPS: " << frame*1000.0 / (time - timebase) << " )";
		glutSetWindowTitle((title_fps.str()).c_str());
		timebase = time;
		frame = 0;
	}
}
// UtilGLUT::showFPS() ////////////////////////////////////////////////////////////////////////////


void UtilGLUT::showMessageBox( const string& msg, const string& title)
///////////////////////////////////////////////////////////////////////////////////////////////////
{
#ifdef WIN32
	MessageBox(0, msg.c_str(), title.c_str(), MB_OK);
#endif // WIN32
}
// UtilGLUT::showMessageBox() /////////////////////////////////////////////////////////////////////
