/*
** main.c for main in rendu/UNIX/CONCURRENCE
**
** Made by anony
** Login   <yoann.wargnier@epitech.eu>
**
** Started on  Mon Mar 13 16:42:30 2017 anony
** Last update Sun Mar 19 21:34:45 2017 thomas desforges
*/

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "philo.h"

t_simulation	*get_sym(t_philo *philosophers, int eat_max, int nb_philo)
{
  t_spec	*spec;
  t_simulation	*sym;
  int		i;

  i = -1;
  if ((sym = malloc(nb_philo * sizeof(t_simulation))) == NULL
      || (spec = malloc(sizeof(t_spec))) == NULL)
    return (NULL);
  spec->eat_max = eat_max - 2;
  spec->nb_philo = nb_philo;
  spec->eat = 0;
  while (++i < nb_philo)
    {
      sym[i].id = i;
      sym[i].philosophers = philosophers;
      sym[i].spec = spec;
    }
  return (sym);
}

int		launch_thread(int eat_max, int nb_philosopher)
{
  t_simulation	*sym;
  t_philo	*philosophers;
  int		i;

  i = -1;
  if ((philosophers = malloc(nb_philosopher * sizeof(t_philo))) == NULL
      || (sym = get_sym(philosophers, eat_max, nb_philosopher)) == NULL)
    return (1);
  i = -1;
  while (++i < nb_philosopher)
    philosophers[i].chop_left = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
  i = -1;
  while (++i < nb_philosopher)
    pthread_create(&philosophers[i].thread, NULL, &main_loop, &sym[i]);
  i = -1;
  while (++i < nb_philosopher)
    pthread_join(philosophers[i].thread, NULL);
  free(philosophers);
  free(sym->spec);
  free(sym);
  return (0);
}

int		get_arg(int ac, char *av[], int *eat_max, int *philo)
{
  int		i;

  i = -1;
  *eat_max = -1;
  *philo =  0;
  while (++i < ac)
    {
      if (strncmp(av[i], "-p", 2) == 0 && av[i + 1])
	*philo = atoi(av[i + 1]);
      else if (strncmp(av[i], "-e", 2) == 0 && av[i + 1])
	*eat_max = atoi(av[i + 1]);
    }
  if (*eat_max < 1 || (*philo <= 1 || *philo > 10000))
    {
      dprintf(2, "usage: ./philo -e [1 - ] -p [2 - 10000]\n");
      return (1);
    }
  return (0);
}

int		main(int ac, char *av[])
{
  int		eat_max;
  int		philo;

  RCFStartup(ac, av);
  if (get_arg(ac, av, &eat_max, &philo) == 1)
    return (1);
  launch_thread(eat_max, philo);
  RCFCleanup();
  return (0);
}
