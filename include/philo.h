/*
** philo.h for philo.h in rendu/UNIX/CONCURRENCE/include
** 
** Made by anony
** Login   <yoann.wargnier@epitech.eu>
** 
** Started on  Mon Mar 13 16:41:31 2017 anony
// Last update Thu Mar 16 20:37:00 2017 thomas desforges
*/

#ifndef PHILO_H_
# define PHILO_H_

# include "extern.h"

typedef struct		s_philo
{
  pthread_t		thread;
  pthread_mutex_t	chop_left;
}			t_philo;

typedef struct		s_spec
{
  int			eat;
  int			eat_max;
  int			nb_philo;
}			t_spec;

typedef struct		s_simulation
{
  int			id;
  t_philo		*philosophers;
  t_spec		*spec;
}			t_simulation;

void			*main_loop(void *args);

#endif /* !PHILO_H_ */
