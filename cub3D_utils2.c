/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:09:21 by fjallet           #+#    #+#             */
/*   Updated: 2023/03/18 19:10:40 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_strdup2(const char *s)
{
	size_t	len;
	size_t	i;
	char	*tab;

	i = 0;
	len = ft_strlen(s);
	tab = (char *) malloc (sizeof(char) * (len + 1));
	if (!tab)
		return (0);
	while (i < len)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}