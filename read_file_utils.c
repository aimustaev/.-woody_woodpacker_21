#include "woody.h"

ssize_t get_file_size(const char* file_name){
	ssize_t _file_size = 0;
	FILE* fd = fopen(file_name, "rb");
	if(fd == NULL){
		write(STDERR_FILENO, E_OPEN, ft_strlen(E_OPEN));
		_file_size = -1;
	}
	else{
		while(getc(fd) != EOF){
			_file_size++;
		}
		fclose(fd);
	}
	return _file_size;
}

int copy_file(t_woody *woody, char *filename){
	int fd = open(filename, O_RDONLY);
	if(fd < 0){
		write(STDERR_FILENO, E_OPEN, ft_strlen(E_OPEN));
		return (1);
	}

	if (read(fd, woody->addr, woody->filesize) != woody->filesize)
	{
		close(fd);
		free(woody->addr);
		write(STDERR_FILENO, E_COPY,  ft_strlen(E_COPY));
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
		(c[16] == ET_EXEC || c[16] == ET_DYN)) {
		return (0);
	} else {
		write(STDERR_FILENO, E_FILE_INVALID, ft_strlen(E_FILE_INVALID));
		return (1);
	}
}

int read_elf_file(t_woody *woody, char *filename){

    woody->filesize = get_file_size(filename);
    //ToDo откуда ноги растут?
	if (woody->filesize < (long)(sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) + sizeof(Elf64_Shdr))){
		write(STDERR_FILENO, E_FILE_INVALID, ft_strlen(E_FILE_INVALID));
		return (1);
    }

	woody->addr = malloc(woody->filesize);
	if (woody->addr == NULL){
		write(STDERR_FILENO, E_MALLOC, ft_strlen(E_MALLOC));
		return (1);
	}

	if (copy_file(woody, filename)){
		free(woody->addr);
		return (1);
	}

	if (check_fileformat(woody->addr)){
		free(woody->addr);
		return (1);
	}
    return (0);
}

    // printf("filesize = %ld\n", woody->filesize);