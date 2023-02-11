#include "woody.h"

void parse_argc(int argc, char **argv, t_woody *woody)
{
	if (argc > 2)
	{
		if (ft_strcmp(argv[1], "-i") == 0 && argc == 3)
		{
			woody->i_flag = 1;
		}
		else if (ft_strcmp(argv[1], "-k") == 0 && argc == 3)
		{
			woody->k_flag = 1;
		}
		else if (ft_strcmp(argv[1], "-key" == 0) && argc == 4)
		{
			woody->key_flag = 1;
			woody->key_user = ft_atoi(argv[2]);
		}
		else
		{
			elf_error(E_USAGE);
		}
	}
	else if (argc != 2)
	{
		elf_error(E_USAGE);
	}
}

Elf64_Phdr *get_load_segment(t_woody *woody)
{
	if (!woody->ehdr->e_phoff || !woody->ehdr->e_phnum)
		return (NULL);

	for (int i = 0; i < woody->ehdr->e_phnum; i++)
	{
		if (woody->segments[i].p_type == PT_LOAD &&
			woody->segments[i].p_vaddr <= woody->ehdr->e_entry &&
			woody->segments[i].p_vaddr + woody->segments[i].p_memsz > woody->ehdr->e_entry)
		{
			return (&woody->segments[i]);
		}
	}
	return (NULL);
}

Elf64_Shdr *get_text_section(t_woody *woody)
{
	char *str_table;

	str_table = NULL;
	if (!woody->ehdr->e_shoff || !woody->ehdr->e_shnum ||
		woody->ehdr->e_shstrndx >= woody->ehdr->e_shnum)
	{
		return (NULL);
	}

	str_table = (char *)woody->addr + woody->sections[woody->ehdr->e_shstrndx].sh_offset;
	for (int i = 0; i < woody->ehdr->e_shnum; i++)
	{
		char *section_name = str_table + woody->sections[i].sh_name;

		if (ft_strncmp(".text", section_name, 6) == 0 &&
			(woody->sections[i].sh_type == SHT_PROGBITS) &&
			(woody->sections[i].sh_flags & SHF_EXECINSTR))
		{
			return (&woody->sections[i]);
		}
	}
	return (NULL);
}

void check_empty_space(t_woody *woody)
{
	void *start;
	void *pos;

	start = woody->addr + woody->code->p_offset + woody->code->p_filesz;
	pos = start;
	while (pos < (woody->addr + woody->filesize) && *(unsigned char *)pos == 0)
	{
		++pos;
	}

	if (pos - start < g_decryptor_len)
	{
		elf_error(E_NOSPACE);
	}
}

void parse_info(t_woody *woody)
{

	void *cryptopoint_start;

	woody->ehdr = (Elf64_Ehdr *)woody->addr;
	woody->segments = (Elf64_Phdr *)(woody->addr + woody->ehdr->e_phoff);
	woody->sections = (Elf64_Shdr *)(woody->addr + woody->ehdr->e_shoff);
	woody->code = get_load_segment(woody);
	woody->text = get_text_section(woody);

	check_empty_space(woody);
}
