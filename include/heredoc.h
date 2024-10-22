/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:03:37 by alvmoral          #+#    #+#             */
/*   Updated: 2024/10/22 12:02:03 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "pipex_bonus.h"
# include "heredoc.h"
# include "system_calls_bonus.h"

int		here_doc(char *delimiter, char **path);
void	call_pipe(t_pipe *pipex, int argc);
void	call_here_doc(t_pipe *pipex, int argc);

#endif
