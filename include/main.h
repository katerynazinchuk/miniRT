/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:13:59 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/10/03 15:17:46 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_elemnts
{
	camera;
	*objects;
	*lights;
}	t_elements;

typedef struct s_objects
{
	type plane;
	type cylinder;
	type sphere;
}	t_objects;

typedef struct s_lights
{
	type ambient;
	type point_of_light

}	t_lights;