#include <ze_engine.h>

int main(void)
{
	ZeroEngine engine;

	engine.Initialize();
	//engine.Run();
	engine.Shutdown();
	return 0;
}