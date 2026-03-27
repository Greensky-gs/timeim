#include "display.h"
#include "main.h"
#include "args.h"
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_MAX_SIZE 12

static ColorType extract_color_type(char * a) {
	if (streq(a, "all")) return All;
	if (streq(a, "nuanced")) return AllNuanced;
	if (streq(a, "suffixes")) return Suffixes;
	if (streq(a, "numbers")) return Numbers;
	return None;
}
static int get_file(char car) {
	char path[64];

	snprintf(path, sizeof(path), "%s/%c.txt", DATADIR, car);

	return open(path, O_RDONLY, 0);
}
static int handle_str(char * str, int * files, int * index) {
	int i = 0;
	while (str[i] != 0) {
		files[*index] = get_file(str[i]);
		files[(*index) * -1 - 1] = 1;
		(*index)++;
		i++;
	}
	return i;
}
static int power10(int n) {
	int x = 1;
	while (n > 0) {
		x*=10;
		n--;
	}
	return x;
}
static int my_log10(int x) {
	if (x == 0) return 0;

	int l = 0;
	while (!(power10(l) <= x && power10(l + 1) > x)) {
		l++;
	}
	return l;
}
static int handle_int(int x, int * files, int * index) {
	if (x < 10) {
		files[*index] = get_file(48);
		(*index)++;
		files[*index] = get_file(48 + x);
		(*index)++;
		return 2;
	}
	int i = 0;
	while (i < 2) {
		int logx = my_log10(x);
		int maj = x / power10(logx);

		files[*index] = get_file(48 + maj);

		x = x % power10(logx);
		files[(*index) * -1 - 1] = 0;
		(*index)++;
		i++;
	}

	return 2;
}

struct help_entry {
	char * short_name;
	char * long_name;
	char * description;
};
void help_page() {
	printf("Usage : timeim [options]\n");

	struct help_entry entries[] = {
		{ "-h", "--help", "Displays this help page" },
		{ "-m", "--minutes", "Displays the minutes in the result" },
		{ "-s", "--seconds", "Displays the seconds in the result" },
		{ "-f", "--format \x1b[90mFORMAT\x1b[0m", "    Select the format, where \x1b[90mformat\x1b[0m is either 24 or 12, for hours" },
		{ NULL, "--hours", "Displays the hours in the result" },
		{ NULL, "--suffixes", "Displays the suffixes between each group of numbers" },
		{ NULL, "--color \x1b[90mCOLOR\x1b[0m", "     Select a coloration mode, where \x1b[90mCOLOR\x1b[0m is either one of : \x1b[33msuffixes\x1b[0m, \x1b[33mnumbers\x1b[0m, \x1b[33mall\x1b[0m or \x1b[33mnuanced\x1b[0m. Everything else will be ignored and not colored" }
	};

	int i = 0;
	while (i < 7) {
		struct help_entry entry = entries[i];
		printf("        ");
		if (entry.short_name == NULL) printf("    ");
		else printf("%s%c ", entry.short_name, entry.long_name == NULL ? ' ' : ',');

		printf("%-18s", entry.long_name);
		printf(entry.description);
		printf("\n");
		i++;
	}
}

int main(int argc, char * argv[]) {
	if (in_args(argc, argv, "-h", NULL) || in_args(argc, argv, "--help", NULL)) {
		help_page();
		return 0;
	}

	time_t raw;
	struct tm * timeinfo;

	time(&raw);
	timeinfo = localtime(&raw);

	int truearray[2 * FILE_MAX_SIZE] = {0};
	int * array = truearray + FILE_MAX_SIZE;

	int index = 0;

	int suffixes = in_args(argc, argv, "--suffixes", NULL);
	int seconds = in_args(argc, argv, "-s", NULL) || in_args(argc, argv, "--seconds", NULL);
	int minutes = in_args(argc, argv, "-m", NULL) || in_args(argc, argv, "--minutes", NULL);
	int hours = in_args(argc, argv, "--hours", NULL);

	if (!hours && !minutes && !seconds) {
		help_page();
		return 0;
	}

	char * colargs;
	ColorType coloration = None;
	if ((colargs = str_arg(argc, argv, "--color", NULL)) != NULL) {
		coloration = extract_color_type(colargs);
	}
	
	char * formatstr = NULL;
	if ((formatstr = str_arg(argc, argv, "-f", NULL)) == NULL) {
		formatstr = str_arg(argc, argv, "--format", NULL);
	}
	int is_12 = formatstr == NULL ? 0 : streq(formatstr, "12");

	if (is_12) {
		if (hours) {
			handle_int(timeinfo->tm_hour > 12 ? timeinfo->tm_hour - 12 : timeinfo->tm_hour, array, &index);
			if (suffixes && minutes) handle_str(":", array, &index);
		}
		if (minutes) {
			handle_int(timeinfo->tm_min, array, &index);
		}
		if (suffixes) {
			handle_str(timeinfo->tm_hour > 12 ? "pm" : "am", array, &index);
		}
	} else {
		if (hours) {
			handle_int(timeinfo->tm_hour, array, &index);
			if (suffixes) handle_str("h", array, &index);
		}
		if (minutes) {
			handle_int(timeinfo->tm_min, array, &index);
			if (suffixes) handle_str("m", array, &index);
		}
		if (seconds) {
			handle_int(timeinfo->tm_sec, array, &index);
			if (suffixes) handle_str("s", array, &index);
		}
	}

	if (index == 0) {
		help_page();
		return 0;
	};
	display(array, index, coloration);

	int i = 0;
	while (i < index) {
		close(array[i++]);
	}
	return 0;
}
