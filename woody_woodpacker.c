
#include "woody.h"

int main(int argc, char **argv)
{

    t_woody woody;

    ft_memset(&woody, 0, sizeof(woody));
    parse_argc(argc, argv, &woody);

    read_elf_file(&woody, argv[argc - 1]);

    parse_info(&woody);

    encrypt_func(&woody);

    free(woody.addr);
    return (0);
}
