/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:02:43 by hadia             #+#    #+#             */
/*   Updated: 2025/03/28 16:20:58 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point project(t_point p, t_fdf *fdf)
{
	(void)fdf;
	t_point projected;

	projected.x = p.x - p.y;
	projected.y = (p.x + p.y) / 2 - p.z;
	projected.z = p.z;
	return (projected);
}