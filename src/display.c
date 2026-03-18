#include "display.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define HEIGHT 5

static void compute_size(int * fds, int size, int * output) {
	int i = 0;
	while (i < size) {
		lseek(fds[i], 0, SEEK_SET);

		int count = 0;
		char c;
		while ((read(fds[i], &c, sizeof(char))) > 0 && c != '\n') {
			count++;
		}
		output[i] = count;
		i++;
	}
} 

static void write_coloration(ColorType col, int is_char) {
	switch (col) {
		case Suffixes:
			if (is_char) printf("\x1b[33m");
			break;
		case Numbers:
			if (!is_char) printf("\x1b[34m");
			break;
		case All:
			printf("\x1b[32m");
			break;
		case AllNuanced:
			if (is_char) printf("\x1b[33m");
			else printf("\x1b[34m");
			break;
		default:
			break;
	}
}

void display(int * files, int size, ColorType coloration) {
	int * gotos;
	if ((gotos = calloc(size, sizeof(int))) == NULL) {
		perror("malloc");
		return;
	}
	int * sizes;
	if ((sizes = malloc(sizeof(int) * size)) == NULL) {
		perror("malloc (sizes)");
		free(gotos);
		return;
	}
	compute_size(files, size, sizes);

	int i = 0;
	while (i < HEIGHT) {
		int f = 0;
		while (f < size) {
			int is_char = files[f * -1 - 1];

			int filesize = sizes[f];
			lseek(files[f], gotos[f], SEEK_SET);

			int count = 0;
			char c;
			while ((read(files[f], &c, sizeof(char))) > 0 && count < filesize) {
				write_coloration(coloration, is_char);
				printf("%c", c);
				printf("\x1b[0m");
				count++;
			}
			printf("  ");
			gotos[f] += count + 1;
			f++;
		}

		printf("\n");
		i++;
	}

	free(sizes);
	free(gotos);
}
