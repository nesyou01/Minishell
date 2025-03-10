#include "../../includes/minishell.h"

int	ft_echo(t_shell *shell, t_command *cmd)
{
	int	n_flag;
	int	i;

	n_flag = cmd->argv && cmd->argv[1] && ft_strcmp(cmd->argv[1], "-n") == 0;
	if (n_flag)
		i = 2;
	else
		i = 1;
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
