/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurray <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 19:07:04 by camurray          #+#    #+#             */
/*   Updated: 2019/06/24 21:14:43 by camurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "./libft/libft.h"

/*
** I'm using lists.
** My list structure is defined in my GNL.h file.
** I had to name it t_listgnl because t_list was
** already in use in my libft.h file and double declaration.
** BUFF_SIZE is a macro defined in GNL.h.
** BUFF_SIZE has +1 for the '\0'.
** NULL is used with lists so that you don't point to garbage values.
** I check that my input is not a negative fd, or an empty string
** and that BUFF_SIZE is bigger than 0, if not return -1.
** If I pass these checks I create a new list by calling
** my static function createnewlist - static so only this .c file sees it.
** This appies to all extra functions in my file.
** I run my inputchecks function on my newly created list
** to add nodes to it and save a pointer called storage to this filled in list.
** I add an end to my execution loop that says until strchr finds a '\n'
** so the loop will execute until I reach my end of line & then stop executing.
** In my loop I use the read function to get the line of text,
** and I add checks so that if this read function does soemthing wrong
** my GNL function returns the correct value and doesn't bomb out.
** I call my returnchecks function here to add a '\0' to the end
** of the text line and to make sure I don't overwrite any value but use strdup
** to create a copy & strncpy & strlen to add the '\0' in the right place.
** The +1 is again because the '\0' must be at the end of the string
** so the length plus 1 gives me an attachment right at the end.
** Then I move to the end of my text string.
** I free my storage node and use strjoin to make sure I haven't lost any text.
** I again call my returnchecks function to reruna ll the same text on the
** newly joined string and add the '\0' etc etc, and return my line.
** I hope my project works :)
** I worked hard on this.
*/

static t_listgnl	*createnewlist(int fd)
{
	t_listgnl *list;

	if (!(list = (t_listgnl*)malloc(sizeof(*list))))
		return (NULL);
	list->text = NULL;
	list->next = NULL;
	list->fd = fd;
	list->lnew = ft_strnew(0);
	return (list);
}

static void			addnode(t_listgnl **input, t_listgnl *node)
{
	t_listgnl *list;

	list = *input;
	while (list->next != NULL)
		list = list->next;
	list->next = node;
}

static t_listgnl	*inputchecks(t_listgnl *input, int fd)
{
	t_listgnl *storage;
	t_listgnl *list;

	storage = NULL;
	list = input;
	while (list)
	{
		if (list->fd == fd)
			return (list);
		if (!(list->next))
		{
			storage = createnewlist(fd);
			addnode(&list, storage);
			return (storage);
		}
		list = list->next;
	}
	return (NULL);
}

static int			returnchecks(char *input, char **line)
{
	char	*str;

	if (input == NULL)
		return (0);
	str = ft_strchr(input, '\n');
	if (str != NULL)
	{
		*str = '\0';
		*line = ft_strdup(input);
		ft_strncpy(input, &str[1], ft_strlen(&str[1]) + 1);
		return (1);
	}
	else if (!(ft_strlen(input) <= 0))
	{
		*line = ft_strdup(input);
		*input = '\0';
		return (1);
	}
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	char				str[BUFF_SIZE + 1];
	static t_listgnl	*input = NULL;
	t_listgnl			*storage;
	int					returnvalue;

	if (input == NULL)
		input = createnewlist(fd);
	if ((fd == -1) || (line == NULL) || (BUFF_SIZE <= 0))
		return (-1);
	storage = inputchecks(input, fd);
	while (!(ft_strchr(storage->lnew, '\n')))
	{
		returnvalue = read(fd, str, BUFF_SIZE);
		if (returnvalue == -1)
			return (-1);
		if (returnvalue == 0)
			return (returnchecks(storage->text, line));
		str[returnvalue] = '\0';
		storage->text = ft_strjoin(storage->lnew, str);
		free(storage->lnew);
		storage->lnew = storage->text;
	}
	return (returnchecks(storage->text, line));
}

/*
** run: gcc -Wall -Wextra -Werror get_next_line.c libft/ft_putendl.c
** libft/ft_strchr.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlen.c
** libft/ft_strnew.c libft/ft_strncpy.c libft/ft_putstr.c
**
** ./a.out test.txt
**
** for leaks add while (1)
** then run leaks
**
** int		main(int argc, char **argv)
** {
** int		fd;
** char	*line;
**
** if (argc == 1)
** fd = 0;
** else if (argc == 2)
** fd = open(argv[1], O_RDONLY);
** else
** return (2);
** get_next_line(fd, &line);
** ft_putendl(line);
** while (get_next_line(fd, &line) == 1)
** {
** ft_putendl(line);
** free(line);
** }
** if (argc == 2)
** close(fd);
** }
** credit for this main goes to ctaljaar who helped me understand lists
*/
