#include "../../includes/minishell.h"

int	ft_echo(t_shell *shell, t_command *cmd)
{
	int	n_flag;
	int	i;
	int	j;

	n_flag = 0;
	i = 1;
	while (cmd->argv[i] && ft_strncmp(cmd->argv[i], "-n", 2) == 0)
	{
		j = 2;
		while (cmd->argv[i][j] == 'n')
			j++;
		if (cmd->argv[i][j] != '\0')
			break;
		n_flag = 1;
		i++;
	}
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i++]);
		if (cmd->argv[i])
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
