/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_assign_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 14/06/2024 11:14:35 by smuravye          #+#    #+#             */
/*   Updated: 11/06/2024 14:26:26 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir_type(t_llex *tmp, t_type type, t_type type_next)
{
	tmp->type = type;
	if (tmp->next)
	{
		tmp = tmp->next;
		tmp->type = type_next;
		while (tmp->next && tmp->next->conn_with_prev)
		{
			tmp = tmp->next;
			tmp->type = type_next;
		}
	}
}

void	handle_redirs(t_llex *tmp)
{
	if (!ft_strcmp("<", tmp->value))
		handle_redir_type(tmp, REDIR_IN, INFILE);
	else if (!ft_strcmp(">", tmp->value))
		handle_redir_type(tmp, REDIR_OUT, OUTFILE);
	else if (!ft_strcmp("<<", tmp->value))
		handle_redir_type(tmp, HEREDOC, HEREDOC_END);
	else if (!ft_strcmp(">>", tmp->value))
		handle_redir_type(tmp, APPEND, OUTFILE_APP);
}
