#include "../../includes/minishell.h"

static void	unlink_token(t_token *token)
{
	t_token	*prev;
	t_token	*next;

	prev = token->prev;
	next = token->next;
	prev->next = next;
	if (next)
		next->prev = prev;
}

static void add_to_last_cmd(t_shell *shell, t_token *current, char *str)
{
	while (current)
	{
		if (current->type == COMMAND || current->type == ARGUMENT)
		{
			current->content = ft_strjoin(shell, current->content, " ");
			current->content = ft_strjoin(shell, current->content, str);
			return ;
		}
		current = current->prev;
	}
}

static void	merge_cmds(t_shell *shell, t_token **current)
{
	char	*str;
	t_token	*tmp;
	t_token	*before;

	str = NULL;
	before = (*current)->prev;
	while (*current && (*current)->type == UNKNOWN)
	{
		if (str)
		{
			str = ft_strjoin(shell, str, " ");
			str = ft_strjoin(shell, str, (*current)->content);
		}
		else
			str = ft_strdup(shell, (*current)->content);
		tmp = (*current)->next;
		unlink_token(*current);
		*current = tmp;
	}
	if (str)
		add_to_last_cmd(shell, before, str);
}

void	ft_merge_tokens(t_shell *shell, t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == UNKNOWN)
			merge_cmds(shell, &tmp);
		else
			tmp = tmp->next;
	}
}

void	ft_merge_args_with_cmd(t_shell *shell, t_token *token)
{
	char	*args;
	t_token	*tmp;

	while (token)
	{
		if (token->type == ARGUMENT)
		{
			args = token->content;
			tmp = token->prev;
			unlink_token(token);
			add_to_last_cmd(shell, tmp, args);
		}
		token = token->next;
	}
}
