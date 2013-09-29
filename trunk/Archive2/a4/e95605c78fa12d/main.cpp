#include    <unistd.h>
#include	<stdlib.h>

typedef struct	s_meta
{
	int	y;
	int	x;
	int	is_ok;
}				t_meta;

int		ft_strcmp(char *input, char *our_str)
{
	int		i;

	i = 0;
	while (input[i] && our_str[i])
	{
		if (input[i] != our_str[i])
			return (0);
		i++;
	}
	if (input[i] != our_str[i])
		return (0);
	return (1);
}

char	*ft_strcpy(char *dest, char *src, int tot)
{
	char		*save;

	save = dest;
	while(tot && (*dest++ = *src++))
		tot--;
	return (save);
}

t_meta	ft_count(char *tab)
{
	t_meta	meta;
	int		size_x;
	int		i;

	meta.x = 0;
	meta.y = 0;
	meta.is_ok = 1;
	i = 0;
	size_x = 0;
	while (tab[i])
	{
		if (tab[i] == '\n')
		{
			if (meta.y > 0 && meta.x != size_x)
				meta.is_ok = 0;
			meta.y++;
			meta.x = size_x;
			size_x = 0;
		}
		size_x++;
		i++;
	}
	return (meta);
}

char	*cpy_input()
{
	int		len;
	int		count;
	int		tot;
	char	*temp;
	char	*ret;

	len = 100;
	tot = 0;
	ret = (char*)malloc(sizeof(char) * (len + 1));
	ret[len] = '\0';
	while (count = read(0, ret + tot, len - tot))
	{
		tot += count;
		if (count == len - tot)
		{
			len *= 2;
			temp = ret;
			ret = (char*)malloc(sizeof(char) * (len));
			ft_strcpy(ret, temp, tot);
			free(temp);
		}		
	}
	ret[tot] = '\0';
	return (ret);
}

char	print00(int x, int y, int i, int j)
{
	if ((i == 1 && j == 1) || (i == x && j == 1))
		return ('o');
	else if ((1 < i && i < x) && ((j == 1) || ( j == y)))
		return ('-');
	else if (((i == 1) && (1 < j && j < y)) || ((i == x) && (1 < j && j < y)))
		return ('|');
	else if ((i == 1 && j == y) || (i == x && j == y))
		return ('o');
	else
		return (' ');
}

char	print01(int x, int y, int i, int j)
{
	if (i == 1 && j == 1)
		return ('/');
	else if ((i == x && j == 1) || (j == y && i == 1))
		return ('\\');
	else if (i == x && j == y)
		return ('/');
	else if (i == 1 || j == 1 || i == x || j == y)
		return ('*');
	else
		return (' ');
}

char	print02(int x, int y, int i, int j)
{
	if (i == 1 && j == 1)
		return ('A');
	else if (i == x && j == 1)
		return ('A');
	else if ((i == 1 && j == y) || (j == y && i == x))
		return ('C');
	else if (i == 1 || j == 1 || i == x || j == y)
		return ('B');
	else
		return (' ');
}

char	print03(int x, int y, int i, int j)
{
	if (i == 1 && j == 1)
		return ('A');
	else if (i == 1 && j == y)
		return ('A');
	else if ((i == x && j == 1) || (j == y && i == x))
		return ('C');
	else if (i == 1 || j == 1 || i == x || j == y)
		return ('B');
	else
		return (' ');
}

char	print04(int x, int y, int i, int j)
{
	if (i == 1 && j == 1)
		return ('A');
	else if ((i == x && j == 1) || (j == y && i == 1))
		return ('C');
	else if (i == x && j == y)
		return ('A');
	else if (i == 1 || j == 1 || i == x || j == y)
		return ('B');
	else
		return (' ');
}

char	*colle(int x, int y, char (*print)(int, int, int, int))
{
	int		j;
	int		i;
	int		k;
	char	*str;

	str = (char*)malloc(sizeof(char) * (j * i) + 1);
	j = 1;
	k = 0;
	while (j <= y)
	{
		i = 1;
		while (i <= x)
		{
			str[k] = (*print)(x, y, i, j);
			i++;
			k++;
		}
		str[y] = ('\n');
		j++;
		k++;
	}
	str[k] = '\0';
	return (str);
}

void    ft_putchar(char c)
{
	write(1, &c, 1);
}

void    ft_putnbr(int n)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(48 + n);
}

void	display(int	ok, char which, int x, int y)
{
	if (ok > 1)
		write(1, " || ", 4);
	write(1, "[colle-0", 8);
	write(1, &which, 1);
	write(1, "] [", 3);
	ft_putnbr(x);
	write(1, "] [", 3);
	ft_putnbr(y);
	write(1, "]", 1);
}

void	display_error(void)
{
	write(1, "aucune", 6);
}

int		main(void)
{
	t_meta	meta;
	char	*input;
	char	*our_str;
	int		ok;

	input = cpy_input();
	meta = ft_count(input);
	if (meta.is_ok && (!(ok = 0)))
	{
		if (ft_strcmp(input, colle(meta.x, meta.y, &print00)) && (ok += 1))
			display(1, '0', meta.x, meta.y);
		if (ft_strcmp(input, colle(meta.x, meta.y, &print01)) && (ok += 1))
			display(ok, '1', meta.x, meta.y);
		if (ft_strcmp(input, colle(meta.x, meta.y, &print02)) && (ok += 1))
			display(ok, '2', meta.x, meta.y);
		if (ft_strcmp(input,ar x, meta.y, &print03)) && (ok += 1))
			display(ok, '3', meta.x, meta.y);
		if (ft_strcmp(input, colle(meta.x, meta.y, &print04)) && (ok += 1))
			display(ok, '4', meta.x, meta.y);
	}
	if (ok == 0)
		display_error();
	write(1, "\n", 1);
	return (0);
}