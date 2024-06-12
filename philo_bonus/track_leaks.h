/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_leaks.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:05 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/12 23:13:55 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACK_LEAKS_H
# define TRACK_LEAKS_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_log_info
{
	const char	*file;
	const char	*func;
	int			line;
	int			pid;
}				t_log_info;

static	inline	void	*__malloc(size_t size, t_log_info info)
{
	int		fd;
	FILE	*log;
	void	*ptr;

	fd = open("adrress_logs.py", O_CREAT | O_RDWR, 0644);
	log = fopen("adrress_logs.py", "a");
	ptr = malloc(size);
	if (ptr != NULL)
		fprintf(log, "Memory allocated at address: %p, file: %s, line: %d " \
				"in function: %s with pid: %d\n", \
				ptr, info.file, info.line, info.func, info.pid);
	else
		fprintf(log, "Failed to allocate memory at file: %s, line: %d " \
				"in function: %s with pid: %d\n", \
				info.file, info.line, info.func, info.pid);
	fclose(log);
	close(fd);
	return (ptr);
}

static	inline	void	__free(void *ptr, t_log_info info)
{
	FILE	*log;
	int		fd;

	free(ptr);
	fd = open("adrress_logs.py", O_CREAT | O_RDWR, 0644);
	log = fopen("adrress_logs.py", "a");
	fprintf(log, "Memory freed from address: %p, file: %s, line: %d " \
			"in function: %s, pid: %d\n", \
			ptr, info.file, info.line, info.func, info.pid);
	fclose(log);
	close(fd);
}

# ifndef MALLOC
#  define MALLOC(size) __malloc(size, (t_log_info){__FILE__, __func__, __LINE__, getpid()})
# endif

# ifndef FREE
#  define FREE(ptr) __free(ptr, (t_log_info){__FILE__, __func__, __LINE__, getpid()})
# endif

#endif
