class Shared;

#ifndef _SHARED_H
#define _SHARED_H

class Shared
{
private:
	Shared();

public:
	static bool initialize();
	static void deinitialize();

	static float getCurrentTime();
	static void sleep(unsigned int uiMs);

private:
#ifdef WIN32
	static DWORD64 m_qwTickStart;
#endif
};

#endif
