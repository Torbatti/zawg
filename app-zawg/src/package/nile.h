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
#if !defined(NILE_IMPL_H)
# define NILE_IMPL_H

# include <assert.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

// ----------------------------------------------------------------------------
// Nile:
//
# if defined(__linux__) || defined(__gnu_linux__)
#  define NILE_PLATFORM_LINUX
# endif
# if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#  define NILE_PLATFORM_WINDOWS
# endif
//
// Nile:
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile:
//
# if defined(NILE_PLATFORM_LINUX)
#  define NILE_WINDOW_X11
#  define NILE_GRFX_BACKEND_OPENGL
# endif
# if defined(NILE_PLATFORM_WINDOWS)
#  define NILE_WINDOW_WIN32
#  define NILE_GRFX_BACKEND_OPENGL
# endif
//
// Nile:
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile:
//
# define NILE_FUNC(func)     NILE_##func
# define NILE_assert         assert
# define NILE_RESULT_SUCCESS 0
# define NILE_RESULT_FAIL    1

typedef struct NILE_Window NILE_Window;
typedef struct NILE_Event  NILE_Event;

// clang-format off
int NILE_windowCreate(NILE_Window **window_pointer, const char *window_title, int window_x,
                      int window_y, int window_width, int window_height, int window_flags);
int NILE_windowCreatePlatform(NILE_Window *window, const char *window_title, int window_x,
                      int window_y, int window_width, int window_height, int window_flags);
int NILE_windowCreateWin32Wgl(NILE_Window *window, const char *window_title, int window_x, int window_y, int window_width, int window_height, int window_flags);
int NILE_windowCreateX11Glx(NILE_Window *window, const char *window_title, int window_x, int window_y, int window_width, int window_height, int window_flags);

int NILE_windowClose(NILE_Window *window);
int NILE_windowClosePlatform(NILE_Window *window);
int NILE_windowCloseWin32Wgl(NILE_Window *window);
int NILE_windowCloseX11Glx(NILE_Window *window);

int NILE_windowSwapBuffers(NILE_Window *window);
int NILE_windowSwapBuffersPlatform(NILE_Window *window);
int NILE_windowSwapBuffersWin32Wgl(NILE_Window *window);
int NILE_windowSwapBuffersX11Glx(NILE_Window *window);
// clang-format on
//
// Nile:
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile:
//
// @brief: opengl includes
# if defined(NILE_GRFX_BACKEND_OPENGL)
#  define GLAD_GL_IMPLEMENTATION
#  include <glad/gl.h>
# endif

// @brief: opengles includes
# if defined(NILE_GRFX_BACKEND_OPENGLES)
#  define GLAD_GLES_IMPLEMENTATION
#  include <glad/gles.h>
# endif

// @brief: vulkan includes
# if defined(NILE_GRFX_BACKEND_VULKAN)
#  define GLAD_VULKAN_IMPLEMENTATION
#  include <glad/vulkan.h>
# endif

// @brief: linux includes
# if defined(NILE_PLATFORM_LINUX)
#  if defined(NILE_WINDOW_X11)
// @links: https://tronche.com/gui/x/xlib/introduction/header.html
#   include <X11/X.h>
#   include <X11/Xlib.h>
#   include <X11/Xutil.h>
#  endif
#  if defined(NILE_GRFX_BACKEND_OPENGL) && defined(NILE_WINDOW_X11)
#   define GLAD_GLX_IMPLEMENTATION
#   include <glad/glx.h>
#  endif
# endif

// @brief: windows includes
# if defined(NILE_PLATFORM_WINDOWS)
#  define WIN32_LEAN_AND_MEAN // @brief: will speed build process by excluding less used apis
#  include <tchar.h>
#  include <windows.h>
#  include <windowsx.h>
#  if defined(NILE_GRFX_BACKEND_OPENGL)
#   define GLAD_WGL_IMPLEMENTATION
#   include <glad/wgl.h>
#  endif
# endif
//
// Nile:
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile:
//

struct NILE_Window {

// @brief: linux specific
# if defined(NILE_PLATFORM_LINUX)
#  if defined(NILE_WINDOW_X11)
  Display *x11_display;
  Window   x11_window_parent;
  Window   x11_window;
  Colormap x11_colormap;
#   if defined(NILE_GRFX_BACKEND_OPENGL)
  GLXContext x11_gl_context;
#   endif
#  endif
#  if defined(NILE_WINDOW_WAYLAND)
#   if defined(NILE_GRFX_BACKEND_OPENGLES)
#   endif
#  endif
# endif

// @brief: windows specific
# if defined(PLATFORM_WINDOWS)
#  if defined(NILE_WINDOW_WIN32)
  HWND win32_window_handle;
  HDC  win32_context_handle;
#   if defined(NILE_GRFX_BACKEND_OPENGL)
  HGLRC win32_gl_context_handle;
#   endif
#  endif
# endif

  // @brief: platform nondependant
  void *user_ptr; /* ptr for usr data */

  int32_t pos_x, pos_y, width, height;
  int32_t old_pos_x, old_pos_y, old_width, old_height;

  int32_t last_mouse_pos_x, last_mouse_pos_y;

  int32_t exit_key;
  int32_t mod_key;

  int32_t   enabled_events;
  u_int32_t flags;
};
//
// Nile:
// ----------------------------------------------------------------------------

#endif // !defined(NILE_IMPL_H)
