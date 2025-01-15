/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:00:08 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/11 14:09:07 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
    char *path = NULL;
    char *argt[] = {"slsllss", NULL};
    execve(path, argt, envp);
    return (0);
}
