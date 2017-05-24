#include "Turmite.h"


int main() {
	Turmite mite = Turmite::read("rules.txt");

	mite.simulate();
}
