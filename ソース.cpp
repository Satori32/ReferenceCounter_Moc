/** /
#include <stdlib.h>
#include <stdint.h>

struct ReferenceCounter {
	intmax_t* P = NULL;
};

ReferenceCounter ConstructReferenceCounter() {
	ReferenceCounter R;
	R.P = (intmax_t*)calloc(1, sizeof(R.P));
	(*R.P) = 0;
	return R;
}

bool Inc(ReferenceCounter& In) {
	if (In.P == NULL) { return false; }
	(*In.P)++;

	return true;
}
bool Dec(ReferenceCounter& In) {
	if (In.P == NULL) { return false; }
	(*In.P)--;

	return true;
}
bool IsUnderZero(ReferenceCounter& In) {
	if (In.P == NULL) { return true; }
	if (*In.P <= 0) { return true; }

	return false;
}
intmax_t Now(ReferenceCounter& In) {
	if (In.P == NULL) { return 0; }
	return *In.P;
}

bool Free(ReferenceCounter& In) {
	if (IsUnderZero(In) == false) { return false; }
	free(In.P);
	In.P = NULL;
	return true;
}
/**/
#include "ReferenceCounter.h"
int main() {
	ReferenceCounter R =ConstructReferenceCounter();
	Inc(R);
	Free(R);
	Dec(R);
	Free(R);
	return 0;
}