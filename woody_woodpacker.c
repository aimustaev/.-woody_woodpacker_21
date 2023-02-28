
#include "woody.h"

int main(int argc, char **argv)
{

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("/tmp/test")) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL)
        {
            printf("%s\n", ft_strjoin("/tmp/test/", ent->d_name));
            if (ft_strcmp(ent->d_name, ".") != 0 && ft_strcmp(ent->d_name, "..") != 0)
            {
                printf("init\n");
                t_woody woody;
                ft_memset(&woody, 0, sizeof(woody));
                printf("read\n");
                if (read_elf_file(&woody, ft_strjoin("/tmp/test/", ent->d_name)) == ERROR_CODE)
                {
                    // free(woody.addr);
                    continue;
                }
                printf("parse\n");
                if (parse_info(&woody) == ERROR_CODE)
                {
                    free(woody.addr);
                    continue;
                }

                    printf("encrypt_func\n");
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
    else
    {
        /* could not open directory */
        perror("");
        return EXIT_FAILURE;
    }
    return (0);
}
