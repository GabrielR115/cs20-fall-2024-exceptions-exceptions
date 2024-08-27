#include "miltime.h"

#include <cstdlib>
#include <iostream>

using namespace std;

int main()
{
	try {
		Time time(0, 0, AM);
	} catch (const BadNamedParameterException<int>& e) {
		cerr << e.getDescription() << endl;
	}

	try {
		Time time(1, 60, AM);
	} catch (const BadNamedParameterException<int>& e) {
		cerr << e.getDescription() << endl;
	}

	return EXIT_SUCCESS;
}
