/*
** extern.h for extern in rendu/UNIX/CONCURRENCE/PSU_2016_philo/include
**
** Made by anony
** Login   <yoann.wargnier@epitech.eu>
**
** Started on  Sun Mar 19 18:16:53 2017 anony
** Last update Sun Mar 19 18:17:21 2017 anony
*/

#ifndef __LIBRICEFEREE_EXTERN__
# define __LIBRICEFEREE_EXTERN__

# include <pthread.h>

int	RCFStartup(int ac, char **av);
void	RCFCleanup();
int	lphilo_eat();
int	lphilo_sleep();
int	lphilo_think();
int	lphilo_take_chopstick(const pthread_mutex_t *mutex_id);
int	lphilo_release_chopstick(const pthread_mutex_t *mutex_id);

#endif /* __LIBRICEFEREE_EXTERN__ */
