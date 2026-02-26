/*
 * Nile 0.1.0
 *
 * Copyright (c) 2026 Arya Bakhtiari
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#if !defined(NILE_IMPL_C)
# define NILE_IMPL_C

# include "nile.h"

// ----------------------------------------------------------------------------
// Nile:
//
int
NILE_FUNC(windowCreate)(
    NILE_Window **window_pointer, const char *window_title,
    int window_x, int window_y, int window_width, int window_height,
    int window_flags
)
{
  // @todo: need an arena allocator to replace mallocing twice

  // @brief: alloc window
  *window_pointer = (NILE_Window *)malloc(sizeof(NILE_Window));
  NILE_assert((*window_pointer) != NULL);

  // @brief: create window
  int windowCreate_result;
  windowCreate_result = NILE_windowCreatePlatform(
      *window_pointer, window_title, window_x, window_y, window_width,
      window_height, window_flags
  );
  NILE_assert(windowCreate_result == NILE_RESULT_SUCCESS);

  NILE_assert((*window_pointer) != NULL);

  return NILE_RESULT_SUCCESS;
}

int
NILE_FUNC(windowClose)(NILE_Window *window)
{
  NILE_assert(window != NULL);

  int windowClose_result;
  windowClose_result = NILE_windowClosePlatform(window);
  NILE_assert(windowClose_result == NILE_RESULT_SUCCESS);

  // @brief: free allocated memory
  free(window);

  return 0;
}

int
NILE_FUNC(windowSwapBuffers)(NILE_Window *window)
{
  NILE_assert(window != NULL);

  // @brief: internal windowSwapBuffers
  int windowSwapBuffers_result;
  windowSwapBuffers_result = NILE_windowSwapBuffersPlatform(window);
  NILE_assert(windowSwapBuffers_result == NILE_RESULT_SUCCESS);

  return 0;
}
//
// Nile:
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile:
//
int
NILE_FUNC(windowCreatePlatform)(
    NILE_Window *window, const char *window_title, int window_x,
    int window_y, int window_width, int window_height, int window_flags
)
{
  NILE_assert(window != NULL);

  int windowCreate_result;

# if defined(NILE_PLATFORM_LINUX)
#  if defined(NILE_WINDOW_X11)
#   if defined(NILE_GRFX_BACKEND_OPENGL)
  windowCreate_result = NILE_windowCreateX11Glx(
      window, window_title, window_x, window_y, window_width,
      window_height, window_flags
  );
#   endif
#  endif
#  if defined(NILE_WINDOW_WAYLAND)
#   if defined(NILE_GRFX_BACKEND_OPENGLES)
  windowCreate_result = NILE_windowCreateWaylandEgl(
      window, window_title, window_x, window_y, window_width,
      window_height, window_flags
  );
#   endif
#  endif
# endif // defined(NILE_PLATFORM_LINUX)

# if defined(NILE_WINDOW_WINDOWS)
#  if defined(NILE_GRFX_BACKEND_OPENGL)
  windowCreate_result = NILE_windowCreateWin32Wgl(
      window, window_title, window_x, window_y, window_width,
      window_height, window_flags
  );
#  endif
# endif // defined(NILE_WINDOW_WINDOWS)

  NILE_assert(windowCreate_result == NILE_RESULT_SUCCESS);

  return NILE_RESULT_SUCCESS;
}

int
NILE_FUNC(windowClosePlatform)(NILE_Window *window)
{
  NILE_assert(window != NULL);

  int windowClose_result;

# if defined(NILE_PLATFORM_LINUX)
#  if defined(NILE_WINDOW_X11)
#   if defined(NILE_GRFX_BACKEND_OPENGL)
  windowClose_result = NILE_windowCloseX11Glx(window);
#   endif
#  endif
#  if defined(NILE_WINDOW_WAYLAND)
#   if defined(NILE_GRFX_BACKEND_OPENGLES)
  windowClose_result = NILE_windowCloseWaylandEgl(window);
#   endif
#  endif
# endif // defined(NILE_PLATFORM_LINUX)

# if defined(NILE_WINDOW_WINDOWS)
#  if defined(NILE_GRFX_BACKEND_OPENGL)
  windowClose_result = NILE_windowCloseWin32Wgl(window);
#  endif
# endif // defined(NILE_WINDOW_WINDOWS)

  NILE_assert(windowClose_result == NILE_RESULT_SUCCESS);

  // @brief: free allocated memory
  free(window);

  return 0;
}

int
NILE_FUNC(windowSwapBuffersPlatform)(NILE_Window *window)
{
  NILE_assert(window != NULL);

  // @brief: internal windowSwapBuffers
  int windowSwapBuffers_result;

# if defined(NILE_PLATFORM_LINUX)
#  if defined(NILE_WINDOW_X11)
#   if defined(NILE_GRFX_BACKEND_OPENGL)
  windowSwapBuffers_result = NILE_windowSwapBuffersX11Glx(window);
#   endif
#  endif
#  if defined(NILE_WINDOW_WAYLAND)
#   if defined(NILE_GRFX_BACKEND_OPENGLES)
  windowSwapBuffers_result = NILE_windowSwapBuffersWaylandEgl(window);
#   endif
#  endif
# endif // defined(NILE_PLATFORM_LINUX)

# if defined(NILE_WINDOW_WINDOWS)
#  if defined(NILE_GRFX_BACKEND_OPENGL)
  windowSwapBuffers_result = NILE_windowSwapBuffersWin32Wgl(window);
#  endif
# endif // defined(NILE_WINDOW_WINDOWS)

  NILE_assert(windowSwapBuffers_result == NILE_RESULT_SUCCESS);

  return 0;
}
//
// Nile:
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile:
//
//
// @todo: better error handling
// @todo: better logging
// @todo: better profiling
//
// @todo: software rendering
// @todo: glx legact and base
// @todo: add more info about glx modern with extension
//
// @todo: better naming for NILE_WindowX11 struct fields and struct name?
//
// @section(x11-):
// @section(x11-sm6sguct): x11-glx-modern create window overview
// - @section(x11-sm6sguct-ms896bep): idk?
// - @section(x11-sm6sguct-dbzvdgqa): create glx context
// - @section(x11-sm6sguct-rkrwvtxe): load gl from gladloader
// - @section(x11-sm6sguct-kfnzz886): get window attributes + set glviewport if gl/glx is enabled
// @section(x11-x49awnqj): x11-glx close window overview
// @section(x11-yzed2mnd): x11-glx swap window buffer overview

//
// @note(aabib): X11 overview
//
// @links:
// - https://hereket.com/posts/linux_creating_x11_windows/
// - https://tronche.com/gui/x/xlib/introduction/overview.html
// - https://tronche.com/gui/x/xlib/glossary/
// - https://docs.rs/winit/latest/winit/platform/x11/index.html
//
// - The X Window System supports one or more screens containing overlapping windows or subwindows.
// - A screen is a physical monitor and hardware, which can be either color, grayscale, or monochrome.
//
// - Each window and pixmap has its own coordinate system. [0, 0] at the upper-left corner
// - Coordinates are integral, in terms of pixels, and coincide with pixel centers.
// - For a window, the origin is inside the border at the inside, upper-left corner.
//
// - X does not guarantee to preserve the contents of windows. When part or all of a window \
// is hidden and then brought back onto the screen, its contents may be lost.
// - The server then sends the client program an `Expose` event to notify it that part or all \
// of the window needs to be repainted.
//
// - X also provides off-screen storage of graphics objects, called pixmaps.
// - Single plane (depth 1) pixmaps are sometimes referred to as bitmaps.
// - Pixmaps can be used in most graphics functions interchangeably with windows and are used in \
// various graphics operations to define patterns or tiles.
// - Windows and pixmaps together are referred to as drawables.
//
// @note(aabib): Naming and Argument Conventions within Xlib
// @links:
// - https://tronche.com/gui/x/xlib/introduction/naming.html
//
// @note(aabib):
// - Coordinates and sizes in X are actually 16-bit quantities.
// - This decision was made to minimize the bandwidth required for a given level of performance.
// - Coordinates usually are declared as an int in the interface.
// - Values larger than 16 bits are truncated silently.
// - Sizes (width and height) are declared as unsigned quantities.
//

//
// @section(x11-sm6sguct-ms896bep): info
//
// @syntax:
// - Display *XOpenDisplay(display_name);
// @argument: display_name
// - char *display_name;
// - Specifies the hardware display name, which determines the display \
// and communications domain to be used.
//  - On a POSIX-conformant system, if the display_name is NULL,
//  it defaults to the value of the DISPLAY environment variable.
// @return:
// - If succeed , returns pointer to a Display (defined in X11/Xlib.h)
// - If failed , returns NULL
// @links:
// - https://tronche.com/gui/x/xlib/display/opening.html
//
//
// XCreateWindow , XCreateSimpleWindow
// @links:
// - https://tronche.com/gui/x/xlib/window/XCreateWindow.html
//
// Window XCreateWindow(display, parent, x, y, width, height, border_width, depth,
//                        class, visual, valuemask, attributes)
// Display *display;
// Window parent;
// int x, y;
// unsigned int width, height;
// unsigned int border_width;
// int depth;
// unsigned int class;
// Visual *visual
// unsigned long valuemask;
// XSetWindowAttributes *attributes;
//

# if defined(NILE_PLATFORM_LINUX)
#  if defined(NILE_WINDOW_X11) && defined(NILE_GRFX_BACKEND_OPENGL)

// @todo: better naming `windowCreate` ?
int
NILE_FUNC(windowCreateX11Glx)(
    NILE_Window *windowX11Glx, const char *window_title, int window_x,
    int window_y, int window_width, int window_height, int window_flags
)
{
  if(windowX11Glx == NULL)
  {
    // @todo: better error handling with logging
    puts("NILE_Window *window is NULL");

    // @note: no cleanup needed

    return NILE_RESULT_FAIL;
  }

  // @brief:
  // @onFail:
  // @onCleanup:
  Display *main_display = (Display *)XOpenDisplay(0);
  if(main_display == NULL)
  {
    // @todo: better error handling with logging
    puts("cannot connect to X server\n");

    // @note: no cleanup needed

    return NILE_RESULT_FAIL;
  }

  // @brief:
  // @todo: error handling? no documentation found if function can fail or not
  int default_screen = XDefaultScreen(main_display);

  // @brief:
  // @todo: error handling? no documentation found if function can fail or not
  Window root_window = XDefaultRootWindow(main_display);

  // @brief: modern glx context initialization
  // @todo: rework and rename this!
  int gladloaderloadglx_result
      = gladLoaderLoadGLX(main_display, default_screen);
  if(!gladloaderloadglx_result)
  {
    puts("Unable to load GLX.\n");

    // @todo: cleanup

    return NILE_RESULT_FAIL;
  }
  printf(
      "Loaded GLX %d.%d\n",
      GLAD_VERSION_MAJOR(gladloaderloadglx_result),
      GLAD_VERSION_MINOR(gladloaderloadglx_result)
  );

  // @brief:
  Visual *default_visual = DefaultVisual(main_display, default_screen);
  if(default_visual == NULL)
  {
    printf("cannot connect to X server\n");

    // @todo: cleanup

    return NILE_RESULT_FAIL;
  }

  // @brief:
  Colormap colormap = XCreateColormap(
      main_display, root_window, default_visual, AllocNone
  );

  // @brief:
  // int                  window_x            = 0;
  // int                  window_y            = 0;
  // int                  window_width        = 1024;
  // int                  window_height       = 512;
  int                  window_border_width = 0;
  int                  window_depth        = CopyFromParent;
  int                  window_class        = CopyFromParent;
  Visual              *window_visual       = CopyFromParent;
  XSetWindowAttributes attributes;
  attributes.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask;
  attributes.colormap   = colormap;

  // @brief:
  Window window = XCreateWindow(
      main_display, root_window, window_x, window_y, window_width,
      window_height, window_border_width,
      DefaultDepth(main_display, default_screen), InputOutput,
      default_visual, CWColormap | CWEventMask, &attributes
  );
  if(!window)
  {
    printf("Unable to create window.\n");

    // @todo: cleanup

    return NILE_RESULT_FAIL;
  }

  // @brief:
  XMapWindow(main_display, window);
  XStoreName(
      main_display, window,
      "[glad] Modern/Base GLX with X11 - this is intentional"
  );

  GLint visual_attributes[]
      = {GLX_RENDER_TYPE, GLX_RGBA_BIT, GLX_DOUBLEBUFFER, 1, None};

  int          num_fbc = 0;
  GLXFBConfig *fbc     = glXChooseFBConfig(
      main_display, default_screen, visual_attributes, &num_fbc
  );

  GLint context_attributes[]
      = {GLX_CONTEXT_MAJOR_VERSION_ARB,
         3,
         GLX_CONTEXT_MINOR_VERSION_ARB,
         3,
         GLX_CONTEXT_PROFILE_MASK_ARB,
         GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
         None};

  GLXContext context = glXCreateContextAttribsARB(
      main_display, fbc[0], NULL, 1, context_attributes
  );
  if(!context)
  {
    printf("Unable to create OpenGL context.\n");

    // @todo: cleanup

    return NILE_RESULT_FAIL;
  }

  glXMakeCurrent(main_display, window, context);

  // @brief: load gl from gladloader
  int gl_version = gladLoaderLoadGL();
  if(!gl_version)
  {
    printf("Unable to load GL.\n");

    // @todo: cleanup

    return NILE_RESULT_FAIL;
  }
  printf(
      "Loaded GL %d.%d\n", GLAD_VERSION_MAJOR(gl_version),
      GLAD_VERSION_MINOR(gl_version)
  );

  XWindowAttributes gwa;
  XGetWindowAttributes(main_display, window, &gwa);
  glViewport(0, 0, gwa.width, gwa.height);

  NILE_assert(main_display != NULL);
  windowX11Glx->x11_window        = window;
  windowX11Glx->x11_window_parent = 0;
  windowX11Glx->x11_display       = main_display;
  windowX11Glx->x11_colormap      = colormap;

  windowX11Glx->x11_gl_context = context;
  printf("%li ", colormap);

  return NILE_RESULT_SUCCESS;
}

// @todo: better naming `windowClose`?
int
NILE_FUNC(windowCloseX11Glx)(NILE_Window *windowX11Glx)
{
  // @brief: winX11Glx pointer should be an empty initilized winX11Glx struct pointer
  if(windowX11Glx == NULL)
  {
    // @todo: better error handling with logging
    puts("NILE_WindowX11Glx *win32 is NULL");

    // @note: no cleanup needed

    return NILE_RESULT_FAIL;
  }

  NILE_assert(windowX11Glx != NULL);
  NILE_assert(windowX11Glx->x11_display != NULL);

  glXMakeCurrent(windowX11Glx->x11_display, 0, 0);
  glXDestroyContext(
      windowX11Glx->x11_display, windowX11Glx->x11_gl_context
  );

  XDestroyWindow(windowX11Glx->x11_display, windowX11Glx->x11_window);
  XFreeColormap(windowX11Glx->x11_display, windowX11Glx->x11_colormap);
  XCloseDisplay(windowX11Glx->x11_display);

  gladLoaderUnloadGLX();

  // @todo: which functions can fail?
  // @todo: error handling?

  return NILE_RESULT_SUCCESS;
}

// @todo: better naming `swapWindowBuffers` , `windowSwapBuffers` ?
int
NILE_FUNC(windowSwapBuffersX11Glx)(NILE_Window *windowX11Glx)
{
  // @brief: winX11Glx pointer should be an empty initilized winX11Glx struct pointer
  if(windowX11Glx == NULL)
  {
    // @todo: better error handling with logging
    puts("NILE_WindowX11Glx *win32 is NULL");

    // @note: no cleanup needed

    return NILE_RESULT_FAIL;
  }

  glXSwapBuffers(windowX11Glx->x11_display, windowX11Glx->x11_window);
  // @todo: which functions can fail?
  // @todo: error handling?

  return NILE_RESULT_SUCCESS;
}
#  endif // defined(NILE_WINDOW_X11) && defined(NILE_GRFX_BACKEND_OPENGL)

#  if defined(NILE_WINDOW_WAYLAND)           \
      && defined(NILE_GRFX_BACKEND_OPENGLES)
#  endif // defined(NILE_WINDOW_WAYLAND) && defined(NILE_GRFX_BACKEND_OPENGLES)

# endif // defined (NILE_PLATFORM_LINUX)
//
// Nile:
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile:
//
# if defined(NILE_PLATFORM_WINDOWS)

// NOTE(AABIB):
//   A callback function, that processes messages sent to a window
//   https://learn.microsoft.com/en-us/windows/win32/api/winuser/nc-winuser-wndproc
//   https://learn.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure
//   https://learn.microsoft.com/en-us/windows/win32/winmsg/window-notifications
//   https://learn.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues#system-defined-messages
//
LRESULT CALLBACK
NILE_win32_defaultCallback(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
)
{
  LRESULT resault = NILE_RESULT_SUCCESS;

  switch(uMsg)
  {
    // Keyboard
    case WM_ACTIVATE : //
      break;
    case WM_APPCOMMAND : //
      break;
    case WM_DEADCHAR : //
      break;
    case WM_HOTKEY : //
      break;
    case WM_KILLFOCUS : //
      break;
    case WM_SETFOCUS : //
      break;
    case WM_SYSDEADCHAR : //
      break;
    case WM_UNICHAR : //
      break;

    case WM_SYSKEYDOWN : //
      break;
    case WM_SYSCHAR : //
      break;
    case WM_SYSKEYUP : //
      break;
    case WM_KEYDOWN : //
      break;
    case WM_KEYUP : //
      break;
    case WM_CHAR : //
      break;

    // Mouse
    case WM_LBUTTONDOWN : //
      break;
    case WM_LBUTTONUP : //
      break;
    case WM_MBUTTONDOWN : //
      break;
    case WM_MBUTTONUP : //
      break;
    case WM_RBUTTONDOWN : //
      break;
    case WM_RBUTTONUP : //
      break;
    case WM_XBUTTONDOWN : //
      break;
    case WM_XBUTTONUP : //
      break;

    // Clipboard
    case WM_CLEAR : //
      break;
    case WM_COPY : //
      break;
    case WM_CUT : //
      break;
    case WM_PASTE : //
      break;

    //
    // Window
    //
    case WM_SHOWWINDOW : // @brief: window is hidden or shown
      break;
    case WM_SIZE : // @brief: window is resized
      break;
    case WM_SIZING : // @brief: window is being resized
      break;
    case WM_MOVE : // @brief: window is moved
      break;
    case WM_MOVING : // @brief: window is being moved
      break;

    case WM_QUIT :
    case WM_CLOSE   : DestroyWindow(hWnd); break;
    case WM_DESTROY : PostQuitMessage(0); break;
    default         : return DefWindowProc(hWnd, uMsg, wParam, lParam);
  }

  return (resault);
}

int
win32_checkMouseFlags(UINT uMsg)
{
  switch(uMsg)
  {
    case MK_CONTROL  : break;
    case MK_LBUTTON  : break;
    case MK_MBUTTON  : break;
    case MK_RBUTTON  : break;
    case MK_SHIFT    : break;
    case MK_XBUTTON1 : break;
    case MK_XBUTTON2 : break;
  }

  return NILE_RESULT_SUCCESS;
}
int
win32_checkMousePosition(LPARAM lParam)
{
  int xPos = GET_X_LPARAM(lParam);
  int yPos = GET_Y_LPARAM(lParam);

  return NILE_RESULT_SUCCESS;
}

// GetStartupInfoW  doesnt work correctly
// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
//
// Window Class
//
// NOTE(AABI):
//   WNDCLASSEX (A/W) -> RegisterClassEx and GetClassInfoEx
//   maximum length of lpszClassName is 256
//   https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassa
//   https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexa
//
// NOTE(AABI):
//   When you create your HWND, you need to make sure that it has the CS_OWNDC set for its style.
//   https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL)
//   https://learn.microsoft.com/en-us/windows/win32/api/_opengl/
//
//
// NOTE(AABIB):
//   https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program
//   https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-winmain
//
// TODO(AABIB):
//   When can we get a hdc and where do we get it?
//
// @notes:
// - An excerpt from the book Windows Via C/C++ [1]
// - Note As it turns out, HMODULEs and HINSTANCEs are exactly the same thing. If the \
// documentation for a function indicates that an HMODULE is required, you can pass an \
// HINSTANCE and vice versa. There are two data types because in 16-bit Windows HMODULEs \
// and HINSTANCEs identified different things/
// - [1] Richter, Jeffery and Nasarre, Christophe, Windows Via C/C++, 5th ed, Redmond: Microsoft Press 2008, pp. 74
//
// @links:
// - https://stackoverflow.com/questions/2126657/how-can-i-get-hinstance-from-a-dll
// - https://devblogs.microsoft.com/oldnewthing/20040614-00/?p=38903
// - https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulehandlea
//
// @notes: wgl extensions
// - https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_create_context.txt
//
// TODO: read what <THIS> does
// MessageBox MSDN
// GetSystemMetrics MSDN :
// // // Determine the resolution of the clients desktop screen.
// // screenWidth  = GetSystemMetrics(SM_CXSCREEN);
// // screenHeight = GetSystemMetrics(SM_CYSCREEN);
//
// NOTE(AABIB):
//   https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmessage
//
// NOTE(AABI): Funny enough peekmessage used to return -1 on err xD
// If a message is available, the return value is nonzero.
// If no messages are available, the return value is zero.
//
//
// @note:
// on wgl modern version we need to make a temp wgl gl context and
// replace it with our new context from modern wgl extension
//
//
// @todo: icon create/load/get abstractions
// @todo: input [mouse,keyboard,controller] abstractions
//
#  if defined(NILE_GLUE_WGL)
int
NILE_createWindow_WIN32_WGL(NILE_Window_Win32 *win32)
{
  int result = NILE_RESULT_SUCCESS;

  // @brief: win32 pointer should be an empty initilized win32 struct pointer
  if(win32 == NULL)
  {
    // @todo: better error handling with logging
    puts("NILE_Window_Win32 *win32 is NULL");

    result = NILE_RESULT_FAIL;
    return result;
  }

  // @brief: if main is used instead of WinMain as the main entry point
  //         have to get hInstance from GetModuleHandle()
  HMODULE HInstance = GetModuleHandleA(NULL);
  if(HInstance == NULL)
  {
    // @todo: better error handling with logging
    DWORD GetModuleHandleA_err = GetLastError();
    puts("GetModuleHandleA failed");

    result = NILE_RESULT_FAIL;
    return result;
  }

  // @brief:
  LPCSTR      win32_mainWindowName = "Main Window";
  WNDCLASSEXA window_classexa      = {0};
  window_classexa.cbSize           = sizeof(WNDCLASSEXA);
  window_classexa.style
      = CS_HREDRAW // @brief: redraw entire window if client width changes on movment or resize
      | CS_VREDRAW // @brief: redraw entire window if client height changes on movment or resize
      | CS_DBLCLKS // @brief: enable sending double-click messages to the window procedure.
      | CS_OWNDC; // @brief: unique device context for each window in the class.
  window_classexa.lpfnWndProc   = NILE_win32_defaultCallback;
  window_classexa.cbClsExtra    = 0;
  window_classexa.cbWndExtra    = 0;
  window_classexa.hInstance     = HInstance;
  window_classexa.hIcon         = NULL;
  window_classexa.hCursor       = NULL;
  window_classexa.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  window_classexa.lpszMenuName  = NULL;
  window_classexa.lpszClassName = "MainWindowClass";
  window_classexa.hIconSm       = 0;

  // @brief:
  ATOM registerclass = RegisterClassExA(&window_classexa);
  if(registerclass == 0)
  {
    // @todo: better error handling with logging
    DWORD RegisterClassExA_err = GetLastError();
    puts("RegisterClassExA failed");

    result = NILE_RESULT_FAIL;
    return result;
  }

  // @brief:
  int  window_x      = CW_USEDEFAULT;
  int  window_y      = CW_USEDEFAULT;
  int  window_width  = CW_USEDEFAULT;
  int  window_height = CW_USEDEFAULT;
  HWND HWindow       = CreateWindowExA(
      0, window_classexa.lpszClassName, win32_mainWindowName,
      WS_OVERLAPPEDWINDOW | WS_VISIBLE, window_x, window_y,
      window_width, window_height, 0, 0, HInstance, 0
  );
  if(HWindow == NULL)
  {
    // @todo: better error handling with logging
    DWORD CreateWindowExA_err = GetLastError();
    puts("CreateWindowExA failed");

    // @brief: no cleanup needed

    result = NILE_RESULT_FAIL;
    return result;
  }

  // @brief:
  HDC HDeviceContext = GetDC(HWindow);
  if(HDeviceContext == NULL)
  {
    // @todo: better error handling with logging
    DWORD GetDC_err = GetLastError();
    puts("GetDC failed");

    // @brief: cleanup
    DestroyWindow(HWindow);

    result = NILE_RESULT_FAIL;
    return result;
  }

  // @brief:
  PIXELFORMATDESCRIPTOR pixelformatd = {};
  pixelformatd.nSize                 = sizeof(pixelformatd);
  pixelformatd.nSize                 = sizeof(PIXELFORMATDESCRIPTOR);
  pixelformatd.dwFlags
      = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
  pixelformatd.iPixelType = PFD_TYPE_RGBA;
  pixelformatd.cColorBits = 32;
  pixelformatd.cDepthBits = 32;
  pixelformatd.iLayerType = PFD_MAIN_PLANE;

  int format = ChoosePixelFormat(HDeviceContext, &pixelformatd);
  if(format == 0)
  {
    // @todo: better error handling with logging
    DWORD ChoosePixelFormat_err = GetLastError();
    puts("ChoosePixelFormat failed");

    // @brief: cleanup
    ReleaseDC(HWindow, HDeviceContext);
    DestroyWindow(HWindow);

    result = NILE_RESULT_FAIL;
    return result;
  }

  int setpixelformat_result
      = SetPixelFormat(HDeviceContext, format, &pixelformatd);
  if(setpixelformat_result == FALSE)
  {
    // @todo: better error handling with logging
    DWORD SetPixelFormat_err = GetLastError();
    puts("SetPixelFormat failed");

    // @brief: cleanup
    ReleaseDC(HWindow, HDeviceContext);
    DestroyWindow(HWindow);

    result = NILE_RESULT_FAIL;
    return result;
  }

#   if defined(NILE_GLUE_WGL_BASE)
  // @brief: create wgl context
  HGLRC wgl_gl_context = wglCreateContext(HDeviceContext);
  if(wgl_gl_context == NULL)
  {
    // @todo: better error handling with logging
    DWORD wglCreateContext_err = GetLastError();
    puts("wglCreateContext failed");

    // @brief: cleanup
    ReleaseDC(HWindow, HDeviceContext);
    DestroyWindow(HWindow);

    result = NILE_RESULT_FAIL;
    return result;
  }
  // @todo: should i check if `wglMakeCurrent` failed or not?
  wglMakeCurrent(HDeviceContext, wgl_gl_context);

  // @breif: load wgl
  int gladloaderloadwgl_result = gladLoaderLoadWGL(HDeviceContext);
  if(gladloaderloadwgl_result == FALSE)
  {
    // @todo: better error handling with logging
    DWORD gladLoaderLoadWGL_err = GetLastError();
    puts("gladLoaderLoadWGL failed");

    // @brief: cleanup
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(wgl_gl_context);
    ReleaseDC(HWindow, HDeviceContext);
    DestroyWindow(HWindow);

    result = NILE_RESULT_FAIL;
    return result;
  }
#   endif
#   if defined(NILE_GLUE_WGL_MODERN)
  // @brief: create temp wgl context
  HGLRC wgl_gl_temp_context = wglCreateContext(HDeviceContext);
  if(wgl_gl_temp_context == NULL)
  {
    // @todo: better error handling with logging
    DWORD wglCreateContext_err = GetLastError();
    puts("wglCreateContext failed");

    // @brief: cleanup
    ReleaseDC(HWindow, HDeviceContext);
    DestroyWindow(HWindow);

    result = NILE_RESULT_FAIL;
    return result;
  }
  // @todo: should i check if `wglMakeCurrent` failed or not?
  wglMakeCurrent(HDeviceContext, wgl_gl_temp_context);

  // @breif: load wgl
  int gladloaderloadwgl_result = gladLoaderLoadWGL(HDeviceContext);
  if(gladloaderloadwgl_result == FALSE)
  {
    // @todo: better error handling with logging
    DWORD gladLoaderLoadWGL_err = GetLastError();
    puts("gladLoaderLoadWGL failed");

    // @brief: cleanup
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(wgl_gl_temp_context);
    ReleaseDC(HWindow, HDeviceContext);
    DestroyWindow(HWindow);

    result = NILE_RESULT_FAIL;
    return result;
  }

  // @brief: create modern wgl context and replace temp context
  int wgl_context_attributes[]
      = {WGL_CONTEXT_MAJOR_VERSION_ARB,
         3,
         WGL_CONTEXT_MINOR_VERSION_ARB,
         3,
         WGL_CONTEXT_FLAGS_ARB,
         WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
         0};
  HGLRC wgl_gl_context = wglCreateContextAttribsARB(
      HDeviceContext, NULL, wgl_context_attributes
  );
  if(wgl_gl_context == NULL)
  {
    // @todo: better error handling with logging
    DWORD wglCreateContextAttribsARB_err = GetLastError();
    puts("wglCreateContextAttribsARB failed");

    // @brief: cleanup
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(wgl_gl_temp_context);
    ReleaseDC(HWindow, HDeviceContext);
    DestroyWindow(HWindow);

    result = NILE_RESULT_FAIL;
    return result;
  }

  // @todo: should i check if `wglMakeCurrent`,`wglDeleteContext`and `wglMakeCurrent` failed or not?
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(wgl_gl_temp_context);
  wglMakeCurrent(HDeviceContext, wgl_gl_context);
#   endif
  // @breif: load gl
  int gladloaderloadgl_result = gladLoaderLoadGL();
  if(gladloaderloadgl_result == FALSE)
  {
    // @todo: better error handling with logging
    DWORD wglMakeCurrent_err = GetLastError();
    puts("wglMakeCurrent failed");

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(wgl_gl_context);
    ReleaseDC(HWindow, HDeviceContext);
    DestroyWindow(HWindow);

    result = NILE_RESULT_FAIL;
    return result;
  }

  // @todo: should i check if `ShowWindow`and`UpdateWindow` failed or not?
  ShowWindow(HWindow, SW_SHOWDEFAULT);
  UpdateWindow(HWindow);

  // @brief: passing handles to internal win32 pointer
  NILE_assert(HDeviceContext != NULL);
  NILE_assert(HWindow != NULL);
  NILE_assert(wgl_gl_context != NULL);
  win32->hcontext    = HDeviceContext;
  win32->hwindow     = HWindow;
  win32->hgl_context = wgl_gl_context;

  return 0;
}

int
NILE_closeWindow_WIN32_WGL(NILE_Window_Win32 *win32)
{
  NILE_assert(win32 != NULL);
  NILE_assert(win32->hgl_context != NULL);
  NILE_assert(win32->hcontext != NULL);
  NILE_assert(win32->hwindow != NULL);

  // Clean-up:
  if(win32->hgl_context)
    wglDeleteContext(win32->hgl_context);
  if(win32->hcontext)
    ReleaseDC(win32->hwindow, win32->hcontext);
  if(win32->hwindow)
    DestroyWindow(win32->hwindow);

  return 0;
}

int
NILE_windowSwapBuffers_WIN32_WGL(NILE_Window_Win32 *win32)
{
  NILE_assert(win32 != NULL);
  NILE_assert(win32->hgl_context != NULL);
  NILE_assert(win32->hcontext != NULL);
  NILE_assert(win32->hwindow != NULL);

  SwapBuffers(win32->hcontext);
  return 0;
}
#  endif // NILE_GLUE_WGL
# endif  // NILE_PLATFORM_WINDOWS
//
// Nile:
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile:
//

//
// Nile:
// ----------------------------------------------------------------------------

#endif
