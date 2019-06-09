#include "Keyboard.h"

namespace Key
{
#ifdef _WIN32
	char Get()
	{
		return _getch(); // Well that was easy
	}
#endif

#ifdef __linux__
	char Get()
	{
		char buf = 0;
		struct termios old = { 0 };
		old.c_lflag &= ~ICANON;
		old.c_lflag &= ~ECHO;
		old.c_cc[VMIN] = 1;
		old.c_cc[VTIME] = 0;
		old.c_lflag |= ICANON;
		old.c_lflag |= ECHO;
		return (buf);
	}
#endif
}