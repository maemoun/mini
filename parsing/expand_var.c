#include "main.h"

char *get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (!strcmp(env->key, key))
			return env->value;
		env = env->next;
	}
	return "";
}

int is_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') ||
			c == '_');
}

char *append_char(char *str, char c)
{
	size_t len = ft_strlen(str);
	char *tmp = ft_realloc(str, len + 2);
	if (!tmp)
	{
		free(str);
		return NULL;
	}
	tmp[len] = c;
	tmp[len + 1] = '\0';
	return tmp;
}

char *append_str(char *dest, const char *src)
{
	size_t len_dest = ft_strlen(dest);
	size_t len_src = ft_strlen(src);
	char *tmp = ft_realloc(dest, len_dest + len_src + 1);
	if (!tmp)
	{
		free(dest);
		return NULL;
	}
	strcat(tmp, src);
	return tmp;
}

static char *expand_exit_status(char *result, t_data *dt)
{
	char *status = ft_itoa(dt->exit_status);
	if (!status)
	{
		free(result);
		return NULL;
	}
	char *tmp = append_str(result, status);
	free(status);
	return tmp;
}

char *expand_variable(const char *src, int *i, char *result, t_env *env)
{
	int start = *i;
	while (is_var_char(src[*i]))
		(*i)++;
	int key_len = *i - start;
	char *key = malloc(key_len + 1);
	if (!key)
	{
		free(result);
		return NULL;
	}
	int j = 0;
	while (j < key_len)
	{
		key[j] = src[start + j];
		j++;
	}
	key[key_len] = '\0';

	char *val = get_env_value(env, key);
	char *tmp = append_str(result, val);
	free(key);
	return tmp;
}

char *expand_var(const char *src, t_data *dt, t_env *env)
{
	char *result = malloc(1);
	if (!result)
		return NULL;
	result[0] = '\0';

	int i = 0;
	while (src[i])
	{
		if (src[i] == '$')
		{
			i++;
			if (src[i] == '\0')
			{
				result = append_char(result, '$');
				break;
			}
			else if (src[i] == '?')
			{
				result = expand_exit_status(result, dt);
				if (!result)
					return NULL;
				i++;
			}
			else if (!is_var_char(src[i]))
			{
				result = append_char(result, '$');
				if (!result)
					return NULL;
			}
			else
			{
				result = expand_variable(src, &i, result, env);
				if (!result)
					return NULL;
			}
		}
		else
		{
			result = append_char(result, src[i]);
			if (!result)
				return NULL;
			i++;
		}
	}
	return result;
}
