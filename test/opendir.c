#include "minishell.h"

int main(void)
{
    DIR *dir_ptr;

    struct dirent *read_dir;

    dir_ptr = opendir("/");

    if (!dir_ptr)
    {
        perror("Error");
        return (-1);
    }

    while ((read_dir = readdir(dir_ptr)) != NULL)
    {
        if (read_dir->d_type == DT_REG)
            printf("FILE: %s \n", read_dir->d_name);
        else if (read_dir->d_type == DT_DIR)
            printf("DIR: %s \n", read_dir->d_name);
    }
    
    if (closedir(dir_ptr) == -1)
    {
        perror("Error for closing \n");
        return (-1);
    }
    return (0);
}
