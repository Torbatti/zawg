/*
 * Zawg 0.1.0
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

#include <assert.h>
#include <stdio.h>

#include "package/nile.h"
#include "package/nile.c"

#include <unistd.h>

int
main()
{
  NILE_Window *window;
  NILE_Event  *event;

  // @brief: create window
  int windowCreate_result = NILE_windowCreate(
      &window, "Zawg | Pre-Alpha", 0, 0, 1080, 720, 0
  );
  if(windowCreate_result == NILE_RESULT_FAIL)
  {
    puts("NILE_windowCreate failed");
    return -1;
  }
  assert(window != NULL);

  int quit = 1;
  // @brief: main loop: get events -> render -> swap
  while(quit)
  {
    //
    glClearColor(0.8, 0.6, 0.7, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    NILE_windowSwapBuffers(window);

    usleep(1000 * 10);
  }

  // @brief: close window
  int windowClose_result = NILE_windowClose(window);
  if(windowClose_result == NILE_RESULT_FAIL)
  {
    puts("NILE_windowClose failed");
    return -1;
  }

  return 0;
}
