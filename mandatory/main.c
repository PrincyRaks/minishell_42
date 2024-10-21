/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:31:19 by rrakotos          #+#    #+#             */
/*   Updated: 2024/10/21 15:55:07 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
    printf("%s\n", getenv("MAIL"));
    return (0);
    // char **ls = malloc(sizeof)
    execve("/bin/ls", "", NULL);
}
