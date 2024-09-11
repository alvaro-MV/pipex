/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:03:37 by alvmoral          #+#    #+#             */
/*   Updated: 2024/09/01 16:42:10 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "pipex.h"

int		here_doc(char *delimiter, char **path);
void	execute_pipe_hd(char **path, char **argv, int infd);
void	execute_child_hd(char **argv, char **path, int pipefd[2]);

#endif