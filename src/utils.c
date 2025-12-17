/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:47:36 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/03 15:47:39 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_error(const char *msg)
{
	ft_putendl_fd("Error", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	free_arrays(t_objects *obj, t_light *arr)
{
	free(obj->sps);
	free(obj->pls);
	free(obj->cys);
	free(arr);
}

void	handle_esc(mlx_key_data_t key_info, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (key_info.key == MLX_KEY_ESCAPE && key_info.action == MLX_PRESS)
		mlx_close_window(mlx);
}
