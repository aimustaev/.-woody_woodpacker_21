/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:22:33 by Jraye             #+#    #+#             */
/*   Updated: 2023/02/05 01:19:09 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
#define WOODY_H
#include <elf.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include "libft.h"

#define E_FLAG "Error: wrong flag! Wrong flag is ignored\n"
#define E_FILE_INVALID "Error: invalid file, must be valid linux elf64\n"
#define E_NOSPACE "Error: could not find space for decryptor\n"
#define E_COPY "Error: failed to copy info from input file\n"
#define E_LSEEK "Error: failed to lseek the size of input file\n"
#define E_MALLOC "Error: failed to do malloc()\n"
#define E_OPEN "Error: failed to open input file\n"
#define E_READ "Error: failed to read input file\n"
#define E_UNDER_ENCRYPTION "Error: wrong binary file! Binary file is already under our encryption\n"
#define E_USAGE "Wrong syntax. Correct way is to type: ./woody_woodpacker ./path/binary or ./woody_woodpacker -i ./path/binary\n"
#define E_WRITE_WOODY "Error: could not write to 'woody' file\n"
#define E_KEY_GENERATOR "Error: key generator exception, try again\n"

#define KEY_FORMAT "key_value: %#.16llx\n"
#define CHUNK 4096

extern unsigned char g_decryptor[];
extern unsigned int g_decryptor_len;

typedef struct s_decryption_set
{
	uint64_t original_entry;
	uint64_t encrypted_code;
	uint64_t encrypted_size;
	uint64_t key;
	uint64_t encrypted_entry;
} t_dset;

typedef struct s_woody
{
	ssize_t filesize;
	void *addr;
	Elf64_Ehdr *ehdr;
	Elf64_Phdr *code;
	Elf64_Phdr *segments;
	Elf64_Shdr *text;
	Elf64_Shdr *sections;
	int logs_fd;
	char i_flag;
	int res;
	uint64_t key;
} t_woody;

int parse_argc(int argc, char **argv, t_woody *woody);
int read_elf_file(t_woody *woody, char *filename);
int parse_info(t_woody *woody);
int encrypt_func(t_woody *woody);

#endif
