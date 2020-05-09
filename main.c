#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <alloca.h>
#include <sys/sendfile.h>

static char *tmp_file = "u-boot-padding.imx";
static char *padding_1k_in_head(char *file_name)
{
	uint32_t q;
	int to, from;
	int ret;
	int sz = getpagesize();

	from = open(file_name, O_RDONLY, S_IRUSR | S_IWUSR);
	to = open(tmp_file, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (from < 0 || to < 0) {
		fprintf(stderr, "unable to create a temporary file\n");
		exit(EXIT_FAILURE);
	}

	/* Padding 1k in the head. */
	lseek(to, 1024, SEEK_SET);

	do {
		/* copy a page each time. */
		ret = sendfile(to, from, NULL, sz);
	} while (ret > 0);

	close(to);
	close(from);

	/* change to the temporary file. */
	return tmp_file;
}

int main(int argc, char **argv)
{
	char *infile;

	if (argc != 2) {
		fprintf(stderr, "Usage: pading [file]\n");
		exit(EXIT_FAILURE);

	}
	infile = argv[1];
	padding_1k_in_head(infile);

	return 0;
}

