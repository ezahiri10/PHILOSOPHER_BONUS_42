/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_leaks.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:48:05 by ezahiri           #+#    #+#             */
/*   Updated: 2024/06/08 15:33:08 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACK_LEAKS_H
# define TRACK_LEAKS_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

static	inline	void*	__malloc(size_t size, const char* file, int line, const char* func, int pid)
{
	int		fd;
	FILE	*log;
	void	*ptr;
	char	*str;


	fd = open("adrress_logs.py", O_CREAT | O_RDWR, 0644);
	log = fopen("adrress_logs.py", "a");
    ptr = malloc(size);
    if (ptr != NULL)
        fprintf(log, "Memory allocated at address: %p, file: %s, line: %d in function: %s with pid: %d\n", ptr, file, line, func, pid);
    else
        fprintf(log, "Failed to allocate memory at file: %s, line: %d in function: %s with pid: %d\n", file, line, func, pid);
	fclose(log);
	close(fd);
    return(ptr);
}

static	inline	void	__free(void *ptr, const char* file, int line, const char* func, int pid)
{
	FILE	*log;
	int		fd;

	free(ptr);
	fd = open("adrress_logs.py", O_CREAT | O_RDWR, 0644);
	log = fopen("adrress_logs.py", "a");
	fprintf(log, "Memory freed from address: %p, file: %s, line: %d in function: %s, pid: %d\n", ptr, file, line, func, pid);
	fclose(log);
	close(fd);
}

# ifndef malloc
#  define malloc(size) __malloc(size, __FILE__, __LINE__, __func__, getpid())
# endif

# ifndef free
#define free(ptr) __free(ptr, __FILE__, __LINE__, __func__, getpid())
# endif

#endif