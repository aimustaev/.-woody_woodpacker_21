
#include "woody.h"

int main(int argc, char **argv)
{

    t_woody woody;

    ft_memset(&woody, 0, sizeof(woody));
    elf_error(E_OPEN);
    if (parse_argc(argc, argv, &woody))
    {
        return (1);
    }

    if (read_elf_file(&woody, argv[argc - 1]))
    {
        return (1);
    }

    if (parse_info(&woody))
    {
        free(woody.addr);
        return (1);
    }

    if (encrypt_func(&woody))
    {
        free(woody.addr);
        return (1);
    }
}
