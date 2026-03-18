#include "args.h"
#include <stdlib.h>

int streq(char * a, char * b) {
	int i = 0;
	while (a[i] != 0 && b[i] != 0) {
		if (a[i] != b[i]) return 0;
		i++;
	}

	return a[i] == b[i];
}
int in_args(int c, char * a[], char * t, int * index) {
	if (index != NULL) *index = -1;
	int i = 1;
	while (i < c) {
		if (streq(a[i], t)) {
			if (index != NULL) *index = i;
			return 1;
		};
		i++;
	}

	return 0;
}

char * str_arg(int c, char * a[], char * t, int * index) {
	if (index != NULL) *index = -1;

	int i = 1;
	while (i < c - 1) {
		if (streq(a[i], t)) {
			if (index != NULL) *index = i + 1;
			return a[i + 1];
		}
		i++;
	}

	return NULL;
}
