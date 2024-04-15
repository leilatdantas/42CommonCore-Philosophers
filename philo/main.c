/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:19:52 by lebarbos          #+#    #+#             */
/*   Updated: 2024/04/15 14:08:49 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message(LIGHTBLUE FORK COLOR_RESET, philo);
	ft_usleep(data->time_to_die);
	print_message(RED DIE COLOR_RESET, philo);
	pthread_mutex_unlock(philo->r_fork);
}

int	check_args(char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || !is_number(argv[1]))
		return (write(1, "Wrong number_of_philosophers\n", 30), 1);
	if (ft_atoi(argv[2]) < 0 || !is_number(argv[2]))
		return (write(1, "Wrong time_to_die.\n", 20), 1);
	if (ft_atoi(argv[3]) < 0 || !is_number(argv[3]))
		return (write(1, "Wrong time_to_eat.\n", 20), 1);
	if (ft_atoi(argv[4]) < 0 || !is_number(argv[4]))
		return (write(1, "Wrong time_to_sleep.\n", 22), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || !is_number(argv[5])))
		return (write(1, "Wrong number_of_times_must_eat.\n", 32), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong number os arguments.\n");
		return (EXIT_FAILURE);
	}
	if (check_args(argv) != 0)
		return (EXIT_FAILURE);
	philos = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philos)
		return (EXIT_FAILURE);
	init_data(&data, philos, argv, argc);
	init_philos(&data, philos);
	if (data.philo_nbr == 1)
		one_philo(&data, &philos[0]);
	else
		create_threads(&data, philos);
	ft_destroy(&data);
	ft_free(&data);
	return (0);
}
