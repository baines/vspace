#include "engine.h"

int main(int argc, char **argv)
{
	Engine::init();

	while(Engine::running)
		Engine::run();
	exit(0);
}
