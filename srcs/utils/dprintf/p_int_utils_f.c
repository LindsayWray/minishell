/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   p_int_utils_f.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: idonado <idonado@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 00:19:26 by idonado       #+#    #+#                 */
/*   Updated: 2020/07/07 01:07:19 by idonado       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

t_vars	int_mw_vars(const char *format, t_data *data, t_vars vars, va_list args)
{
	vars = vars_init(vars);
	vars.number = va_arg(args, int);
	vars = is_int_negative(vars);
	vars.str = ft_itoa(vars.number);
	vars.str = seek_last_number(vars);
	vars.min_width = ft_atoi(format + data->i_mwidth.i);
	vars.str_width = vars.is_negative == false \
	? ft_strlen(vars.str) : ft_strlen(vars.str) + 1;
	return (vars);
}

t_vars	int_nds_vars(t_vars vars, t_data *data, va_list args)
{
	vars.precision = va_arg(args, int);
	vars = check_precision(vars);
	vars.number = va_arg(args, int);
	vars = is_int_negative(vars);
	if (data->zeroes == true)
		vars.have_zero = true;
	vars = int_num_dot_num_a(vars);
	return (vars);
}
