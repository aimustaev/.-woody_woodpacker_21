#include "woody.h"

ssize_t get_file_size(const char *file_name)
{
	struct stat stat;

	if (!(lstat(file_name, &stat) == 0))
	{
		elf_error(E_OPEN);
	}

	return stat.st_size;
}

void copy_file(t_woody *woody, char *filename)
{
	int fd = open(filename, O_RDONLY);

	if (fd < 0)
	{
		elf_error(E_OPEN);
	}

	if (read(fd, woody->addr, woody->filesize) != woody->filesize)
	{
		close(fd);
		free(woody->addr);
		elf_error(E_COPY);
	}

	close(fd);
}

void check_fileformat(unsigned char *c)
{
	if (c[0] == 0x7f &&
		c[1] == 'E' &&
		c[2] == 'L' &&
		c[3] == 'F' &&
		c[4] == ELFCLASS64 &&
		(c[16] == ET_EXEC || c[16] == ET_DYN))
	{
		return;
	}
	else
	{
		elf_error(E_FILE_INVALID);
	}
}

void read_elf_file(t_woody *woody, char *filename)
{

	woody->filesize = get_file_size(filename);

	woody->addr = malloc(woody->filesize);
	if (woody->addr == NULL)
	{
		elf_error(E_MALLOC);
	}

	copy_file(woody, filename);

	check_fileformat(woody->addr);
}
