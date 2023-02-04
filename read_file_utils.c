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

int copy_file(t_woody *woody, char *filename)
{
	int fd = open(filename, O_RDONLY);

	if (fd < 0)
	{
		elf_error(E_OPEN);
		return (1);
	}

	if (read(fd, woody->addr, woody->filesize) != woody->filesize)
	{
		close(fd);
		free(woody->addr);
		elf_error(E_COPY);
		return (1);
	}

	close(fd);
	return (0);
}

int check_fileformat(unsigned char *c)
{
	if (c[0] == 0x7f &&
		c[1] == 'E' &&
		c[2] == 'L' &&
		c[3] == 'F' &&
		c[4] == ELFCLASS64 &&
		(c[16] == ET_EXEC || c[16] == ET_DYN))
	{
		return (0);
	}
	else
	{
		elf_error(E_FILE_INVALID);
	}
}

int read_elf_file(t_woody *woody, char *filename)
{

	woody->filesize = get_file_size(filename);

	woody->addr = malloc(woody->filesize);
	if (woody->addr == NULL)
	{
		elf_error(E_MALLOC);
	}

	if (copy_file(woody, filename))
	{
		free(woody->addr);
		return (1);
	}

	if (check_fileformat(woody->addr))
	{
		free(woody->addr);
		return (1);
	}
	return (0);
}
