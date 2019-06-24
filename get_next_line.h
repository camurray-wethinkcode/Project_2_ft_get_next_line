/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurray <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 19:56:10 by camurray          #+#    #+#             */
/*   Updated: 2019/06/24 20:44:28 by camurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1000

typedef struct			s_listgnl
{
	char				*text;
	char				*lnew;
	struct s_listgnl	*next;
	int					fd;
}						t_listgnl;

int						get_next_line(int const fd, char **line);

#endif
