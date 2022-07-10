/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:01:25 by vaghazar          #+#    #+#             */
/*   Updated: 2022/07/03 15:26:38 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// C program to show thread functions

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* func(void* arg)
{
	// detach the current thread
	// from the calling thread
	pthread_detach(pthread_self());

	printf("Inside the thread\n");
    printf("pthread_self() = %d\n", pthread_self());

	// exit the current thread
	pthread_exit(NULL);
}

void fun()
{
    // t_philo philo;
	pthread_t ptid;

	// Creating a new thread
	pthread_create(&ptid, NULL, &func, NULL);
    // printf("ptid = %d\n", philo.ptid);
	// pthread_create(&(philo.ptid), NULL, &func, NULL);
    printf("ptid = %d\n pthread_self() =%d\n ", ptid, pthread_self());
	printf("This line may be printed"
		" before thread terminates\n");

	// The following line terminates
	// the thread manually
	// pthread_cancel(ptid);

	// Compare the two threads created
	// if(pthread_equal(philo.ptid, pthread_self()))
	if(pthread_equal(ptid, pthread_self()))
		printf("Threads are equal\n");
	else
		printf("Threads are not equal\n");

	// Waiting for the created thread to terminate
	pthread_join(ptid, NULL);

	printf("This line will be printed"
		" after thread ends\n");

	pthread_exit(NULL);
}

// Driver code
int main()
{
	fun();
	return 0;
}
