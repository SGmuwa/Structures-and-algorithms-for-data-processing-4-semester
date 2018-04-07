#include "Source.h"
#include "..\z8.4_overloadFunctions\Array.cpp"
#include "..\z8.4_overloadFunctions\matrix.h"

using namespace TestModule;
using namespace z8_4;

int main(int argc, char * argv[]) { return Source().main(argc, argv); }

Source::Source()
{
}


Source::~Source()
{
}

int Source::main(int argc, char * argv[])
{
	{
		z8_4::Array<int> a;// = Array<int>(0, 0, true);
		a = Array<int>();
		a = Array<int>();
	}
	return 0;
}

bool Source::Tester()
{
	return true;
}
