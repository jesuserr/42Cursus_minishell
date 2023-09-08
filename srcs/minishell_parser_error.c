/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:24:01 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/08 16:09:14 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	p_common_errors4(char *line)
{
	char	*cmd;
	char	*tmp;

	cmd = p_t_s_cmd_trim_redi(line);
	tmp = quotes_analysis(cmd);
	free(cmd);
	cmd = ft_strtrim(tmp, " ");
	free(tmp);
	if (!*cmd && ft_strnstr(line, "|", ft_strlen(line)))
	{
		free(cmd);
		ft_error_shell("syntax error near unexpected ");
		g_info->last_status = 2;
		return (1);
	}
	free(cmd);
	return (0);
}

int	p_common_errors3(char *line)
{
	char	t_e[2];
	char	tmp[500];

	t_e[0] = error_redi_pattern(line, '>');
	t_e[1] = 0;
	if (t_e[0] > -1)
	{
		g_info->last_status = 2;
		if (!t_e[0])
		{
			ft_strlcpy(tmp, "syntax error near unexpected token", 500);
			ft_strlcat(tmp, " 'newline'", 500);
		}
		else
		{
			ft_strlcpy(tmp, "syntax error near unexpected token1 ", 500);
			ft_strlcat(tmp, t_e, 500);
		}
		ft_error_shell(tmp);
		return (1);
	}
	return (p_common_errors4(line));
}

int	p_common_errors2(char *line)
{
	char	t_e[2];
	char	tmp[500];

	t_e[0] = error_redi_pattern(line, '<');
	t_e[1] = 0;
	if (t_e[0] > -1)
	{
		g_info->last_status = 2;
		if (!t_e[0])
			ft_strlcpy(tmp, "syntax error near unexpected token EOF", 500);
		else
		{
			ft_strlcpy(tmp, "syntax error near unexpected token ", 500);
			ft_strlcat(tmp, t_e, 500);
		}
		ft_error_shell(tmp);
		return (1);
	}
	return (p_common_errors3(line));
}

int	p_common_errors1(char *line)
{
	if (ft_strnstr(line, "<<<<<", ft_strlen(line)))
	{
		ft_error_shell("syntax error near unexpected token '<<'");
		return (1);
	}
	else if (ft_strnstr(line, "<<<<", ft_strlen(line)))
	{
		ft_error_shell("syntax error near unexpected token '<'");
		return (1);
	}
	else if (ft_strnstr(line, ">>>>", ft_strlen(line)))
	{
		ft_error_shell("syntax error near unexpected token '>>'");
		return (1);
	}
	else if (ft_strnstr(line, ">>>", ft_strlen(line)))
	{
		ft_error_shell("syntax error near unexpected token '>'");
		return (1);
	}
	else if (!verify_syntax_quotes(line))
		return (1);
	return (0);
}

int	p_common_errors(char *line)
{
	if (ft_strnstr(line, "|||", ft_strlen(line)))
	{
		ft_error_shell("syntax error near unexpected token '||'");
		return (1);
	}
	else if (ft_strnstr(line, ";;", ft_strlen(line)))
	{
		ft_error_shell("syntax error near unexpected token ';;'");
		return (1);
	}
	else if (ft_strnstr(line, "&&&", ft_strlen(line)))
	{
		ft_error_shell("syntax error near unexpected token '&'");
		return (1);
	}
	else if (p_t_s_type(line))
	{
		ft_error_shell("syntax error near unexpected token at EOL");
		return (1);
	}
	if (p_common_errors1(line))
		return (1);
	else
		return (p_common_errors2(line));
}
