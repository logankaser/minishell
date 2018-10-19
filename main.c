#include <stdio.h>
#include "libft/includes/libft.h"

int	main()
{
	t_uvector str;

	ft_uvector_init(&str, 1);
	ft_string_append(&str, "Yesss!");
	ft_putstr(str.data);
	return 0;
}
