/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:03:37 by alvmoral          #+#    #+#             */
/*   Updated: 2024/09/12 17:27:52 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "pipex.h"

int		here_doc(char *delimiter, char **path);
void	call_pipe(char **path, char **argv, int argc);
void	call_here_doc(char **path, char **argv, int argc);
void	execute_pipe_hd(char **path, char **argv, int infd);
void	execute_child_hd(char **argv, char **path, int pipefd[2]);

#endif
