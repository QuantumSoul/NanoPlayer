/*
 * Copyright (C) 2016 shiro
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef NANOPLAYER_H
# define NANOPLAYER_H
# define TRUE 1
# define FALSE 0
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <pthread.h>

# include "fmod.h"

typedef enum		e_action
{
	PLAY, PAUSE, NEXT, PREV, STOP, OPEN, VOL
}					t_action;

typedef	struct		s_stopcond
{
	pthread_cond_t	cond_stop;
	pthread_mutex_t	mut_stop;
}					t_stopcond;

typedef	struct		s_timemutex
{
	unsigned int	val;
	pthread_mutex_t	mut_time;
}					t_timemutex;

typedef struct		s_chanmutex
{
	FMOD_CHANNEL	*val;
	pthread_mutex_t	mut;
}					t_chanmutex;

typedef	struct		s_operation
{
	t_action		action;
	void			(*function)(void);
}					t_operation;

typedef struct		sigaction t_sigaction;

t_stopcond	stop;
t_timemutex time_count;
t_chanmutex	channel;

void		exit_FMOD_error(FMOD_RESULT res);
void		exit_proc_error();
void		exit_file_error(char *fct);
void		exit_memory_error();
void		exit_thread_error();

void		*count(void *arg);
void		wait_time(unsigned int lenght);
void		write_pid(void);
void		init_handler(void);
pid_t		get_pid();
void		send_operation(pid_t pid, char op, char *arg2);

int			seek_char(char c, FILE *stream);
char		*get_line(FILE *stream);

void		music_pause();
void		music_unpause();
void		music_next();
void		music_prev();
void		music_stop();
void		music_open();
void		music_volume();

FMOD_SYSTEM	*create_system();
FMOD_SOUND	*create_sound(char* path, FMOD_SYSTEM *sys);
void		play_sound(FMOD_SOUND *snd, FMOD_SYSTEM *sys);
t_operation	**init_tab_operations();

#endif /* NANOPLAYER_H */

