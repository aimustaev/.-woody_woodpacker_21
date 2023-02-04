#include "woody.h"

int parse_argc(int argc, char **argv, t_woody *woody){
    
    if (argc != 2 && argc != 3){
        write(STDERR_FILENO, E_USAGE, ft_strlen(E_USAGE));
        return (1);
    }

    if (argc > 2){
        if (ft_strcmp(argv[1], "-i") == 0){
            woody->i_flag = 'i';
        } else {
            write(STDERR_FILENO, E_FLAG, ft_strlen(E_FLAG));
            return(1);
        }  
    }
    return (0);
}

Elf64_Phdr	*get_load_segment(t_woody *woody)
{
	if (!woody->ehdr->e_phoff || !woody->ehdr->e_phnum)
		return (NULL);
	
	for (int i = 0; i < woody->ehdr->e_phnum; i++)
	{
		if (woody->segments[i].p_type == PT_LOAD && \
			woody->segments[i].p_vaddr <= woody->ehdr->e_entry && \
			woody->segments[i].p_vaddr + woody->segments[i].p_memsz > woody->ehdr->e_entry){
			return (&woody->segments[i]);
		}
	}
	return (NULL);
}

Elf64_Shdr	*get_text_section(t_woody *woody)
{
	char	*str_table;

	str_table = NULL;
	if (!woody->ehdr->e_shoff || !woody->ehdr->e_shnum || \
		woody->ehdr->e_shstrndx >= woody->ehdr->e_shnum) {
		return (NULL);
        }

	str_table = (char *)woody->addr + woody->sections[woody->ehdr->e_shstrndx].sh_offset;
	for (int i = 0; i < woody->ehdr->e_shnum; i++) {
		char *section_name = str_table + woody->sections[i].sh_name;

		if (ft_strncmp(".text", section_name, 6) == 0 && \
			(woody->sections[i].sh_type == SHT_PROGBITS) && \
			(woody->sections[i].sh_flags & SHF_EXECINSTR)){
			return (&woody->sections[i]);
		}
	}
	return (NULL);
}

int     check_empty_space(t_woody *woody)
{
	void	*start;
	void	*pos;

	start = woody->addr + woody->code->p_offset + woody->code->p_filesz;
	pos = start;
	while (pos < (woody->addr + woody->filesize) && *(unsigned char *)pos == 0){
		++pos;
	}
    if (pos - start < g_decryptor_len){
        write(STDERR_FILENO, E_NOSPACE, ft_strlen(E_NOSPACE));
        return (1);
    }
	return (0);
}

int parse_info(t_woody *woody){

    void    *cryptopoint_start;

    woody->ehdr = (Elf64_Ehdr *)woody->addr;
	woody->segments = (Elf64_Phdr *)(woody->addr + woody->ehdr->e_phoff);
	woody->sections = (Elf64_Shdr *)(woody->addr + woody->ehdr->e_shoff);
    woody->code = get_load_segment(woody);
	woody->text = get_text_section(woody);

    //ToDo проверяем не был ли файл закондирован ранее, зачем?
    cryptopoint_start = woody->addr + woody->code->p_offset + woody->code->p_filesz - g_decryptor_len;
    if (ft_memcmp(cryptopoint_start, g_decryptor, (size_t)(g_decryptor_len - sizeof(t_dset))) == 0){
        write(STDERR_FILENO, E_UNDER_ENCRYPTION, ft_strlen(E_UNDER_ENCRYPTION));
        return (1);
    }
    if (check_empty_space(woody)){
        return (1);
    }
    return (0);
}
