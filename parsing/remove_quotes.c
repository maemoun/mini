#include "main.h"

char *remove_quotes(const char *str)
{
	int i = 0, j = 0;
	int len = ft_strlen(str);
	char quote = 0;
	char *res = malloc(len + 1);
	if (!res)
		return NULL;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return res;
}
