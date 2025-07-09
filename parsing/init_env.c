#include "main.h"

t_env *init_env(char **envp)
{
    t_env *head = NULL;
    while (*envp)
    {
        char *entry = *envp;
        char *equal = ft_strchr(entry, '=');
        if (equal)
        {
            t_env *new = malloc(sizeof(t_env));
            new->key = ft_substr(entry, 0, equal - entry);
            new->value = ft_strdup(equal + 1);
            new->next = head;
            head = new;
        }
        envp++;
    }
    return head;
}