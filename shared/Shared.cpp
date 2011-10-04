#include "StdInc.h"
#include "Shared.h"

#ifdef WIN32
DWORD64 Shared::m_qwTickStart;
#endif

bool Shared::initialize()
{
#ifdef WIN32
	m_qwTickStart = GetTickCount64();
	return true;
#else
	// http://stackoverflow.com/questions/2958291/equivalent-to-gettickcount-on-linux
	return false;
#endif
}

void Shared::deinitialize()
{
}

float Shared::getCurrentTime()
{
#ifdef WIN32
	DWORD64 qwDelta = GetTickCount64() - m_qwTickStart;
	return (float)qwDelta / 1000.0f;
#else
	return 0.0f;
#endif
}

void Shared::sleep(unsigned int uiMs)
{
#ifdef WIN32
	Sleep(uiMs);
#else
	usleep(uiMs * 1000);
#endif
}
