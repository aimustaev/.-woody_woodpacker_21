
#include "woody.h"

int main(int argc, char **argv)
{

    if (argc != 1){
        return (ERROR_CODE);
    }

    DIR *dir;
    struct dirent *ent;

    t_woody woody;
    ft_memset(&woody, 0, sizeof(woody));

    if ((dir = opendir("/tmp/test")) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL)
        {
            // printf("%s\n", ft_strjoin("/tmp/test/", ent->d_name));
            if (ft_strcmp(ent->d_name, ".") != 0 && ft_strcmp(ent->d_name, "..") != 0)
            {
                if (read_elf_file(&woody, ft_strjoin("/tmp/test/", ent->d_name)) == ERROR_CODE)
                {
                    free(woody.addr);
                    continue;
                }
                if (parse_info(&woody) == ERROR_CODE)
                {
                    free(woody.addr);
                    continue;
                }
                if (encrypt_func(&woody) == ERROR_CODE)
                {
                    free(woody.addr);
                    continue;
                }
                free(woody.addr);
            }
        }
        closedir(dir);
    }
    return (0);
}
