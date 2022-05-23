#include "../philo.h"

int check_args(int ac, char **args)
{
    int i;
    int j;

    if (ac != 5 && ac != 6)
        return 1;
    i = 0;
    while (args[i])
    {
        j = 0;
        while (args[i][j])
        {
            if (!ft_isdigit(args[i][j]))
                return 1;
            j++;
        }
        i++;
    }
    return 0;
}