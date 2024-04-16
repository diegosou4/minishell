#include "../../includes/mini.h"

static int	ft_index(t_env *env, char *this)
{
	int		index;
	t_env	*ptr;

	index = 0;
	ptr = env;
	if (env == NULL)
		return (-1);
	if (ft_strlen(this) == 0)
		return (-1);
	while (ptr != NULL)
	{
		if ((ft_strncmp(ptr->key, this, ft_strlen(this)) == 0) 
			&& (ft_strlen(ptr->key) == ft_strlen(this) + 1))
		{
			return (index);
		}
		ptr = ptr->next;
		index++;
	}
	return (-1);
}

char	*ft_path_handler(t_env *env, char *variable)
{
	int		index;
	char	*holder;

	if (env == NULL)
		return (NULL);
	index = ft_index(env, variable);
	if (index == -1)
		return (NULL);
	while (index--)
	{
		env = env->next;
	}
	holder = env->value;
	return (holder);
}