/*
** philo.c for hehe in /home/thomas/rendu/PSU_2016_philo
** 
** Made by thomas desforges
** Login   <thomas@epitech.net>
** 
** Started on  Thu Mar 16 20:12:05 2017 thomas desforges
** Last update Sun Mar 19 21:34:28 2017 thomas desforges
*/

#include <unistd.h>
#include "philo.h"

static void		think(t_simulation *sym)
{
  lphilo_take_chopstick(&sym->philosophers[sym->id].chop_left);
  pthread_mutex_lock(&sym->philosophers[sym->id].chop_left);
  lphilo_think();
  pthread_mutex_unlock(&sym->philosophers[sym->id].chop_left);
  lphilo_release_chopstick(&sym->philosophers[sym->id].chop_left);
}

static void			p_sleep()
{
  lphilo_sleep();
}

static void		eat(t_simulation *sym, int *i)
{
  int		next_id;

  next_id = (sym->id + 1 < sym->spec->nb_philo) ? sym->id + 1 : 0;
  lphilo_take_chopstick(&sym->philosophers[sym->id].chop_left);
  pthread_mutex_lock(&sym->philosophers[sym->id].chop_left);
  lphilo_take_chopstick(&sym->philosophers[next_id].chop_left);
  if (pthread_mutex_trylock(&sym->philosophers[next_id].chop_left) != 0)
    {
      pthread_mutex_unlock(&sym->philosophers[sym->id].chop_left);
      lphilo_release_chopstick(&sym->philosophers[sym->id].chop_left);
      usleep(1);
      return (eat(sym, i));
    }
  lphilo_eat();
  lphilo_release_chopstick(&sym->philosophers[sym->id].chop_left);
  pthread_mutex_unlock(&sym->philosophers[sym->id].chop_left);
  lphilo_release_chopstick(&sym->philosophers[next_id].chop_left);
  pthread_mutex_unlock(&sym->philosophers[next_id].chop_left);
  *i += 1;
}

void		*main_loop(void *args)
{
  int		i;
  t_simulation	*sym;
  int		eat_max;

  i = 0;
  sym = (t_simulation *)args;
  eat_max = (sym->id == 0) ? sym->spec->eat_max + 1 : sym->spec->eat_max;
  while (i <= eat_max)
    {
      p_sleep();
      sym->spec->eat = (i > sym->spec->eat) ? i : sym->spec->eat;
      think(sym);
      eat(sym, &i);
    }
  return (NULL);
}
