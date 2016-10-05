#include <stdio.h>
#include <stdlib.h>

#include "program.hpp"

int main( void )
{
	Program program(1280, 720);

	if (program.Init())
	{
		program.Run();
	}

	return 0;
}
