#ifndef _STDINC_H
#define _STDINC_H

#include <stdio.h>
#include <string>

#ifdef WIN32
  #define WIN32_LEAN_AND_MEAN
  #include <winsock2.h>
  #include <windows.h>
#endif

#include "../shared/Shared.h"

#include "Server.h"
extern Server *g_pServer;

#endif
