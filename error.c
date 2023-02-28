/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 01:55:16 by aimustaev         #+#    #+#             */
/*   Updated: 2023/02/09 22:14:00 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

int elf_error(char *err)
{
    write(STDERR_FILENO, E_TITLE, ft_strlen(E_TITLE));
    write(STDERR_FILENO, err, ft_strlen(err));
    return ERROR_CODE;
    // exit(1);
}