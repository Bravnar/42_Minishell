/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:53:13 by smuravyev         #+#    #+#             */
/*   Updated: 2024/03/27 14:32:21 by smuravyev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "EHL_Bangers ---> $ "

/*----------------------------------------------------------------------------*/
/*                                  LIBRARIES                                 */
/*----------------------------------------------------------------------------*/

# include "../lib/includes/my_lib.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <limits.h>
# include <unistd.h>
# include "colors.h"


/*----------------------------------------------------------------------------*/
/*                                 STRUCTURES                                 */
/*----------------------------------------------------------------------------*/

typedef struct s_main
{
	char	*input;
	bool	is_cmd;
	bool	is_arg;
	t_list	*l_list;
}	t_main;

/*----------------------------------------------------------------------------*/
/*                                  FUNCTIONS                                 */
/*----------------------------------------------------------------------------*/


#endif