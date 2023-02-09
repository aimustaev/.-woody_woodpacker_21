/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 01:55:16 by aimustaev         #+#    #+#             */
/*   Updated: 2023/02/09 22:12:09 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void elf_error(char *err)
{
    write(STDERR_FILENO, "\033[31mHELO\033[0m", ft_strlen("\033[31mHELO\033[0m"));
    write(STDERR_FILENO, err, ft_strlen(err));
    exit(1);
}