#include "main.h"

static int is_empty_quote(const char *s)
{
    return (s[0] == '\'' && s[1] == '\'' && s[2] == '\0')
        || (s[0] == '"'  && s[1] == '"' && s[2] == '\0');
}

void join_tokens_with_no_space(t_token **tokens)
{
    t_token *curr = *tokens;
    while (curr && curr->next)
    {
        if (curr->has_space_after == 0)
        {
            if (is_empty_quote(curr->next->value))
            {
                t_token *tmp = curr->next;
                curr->has_space_after = tmp->has_space_after;
                curr->next = tmp->next;
                free(tmp->value);
                free(tmp);
                continue;
            }
            char *v1 = curr->value;
            char *v2 = curr->next->value;
            size_t l1 = ft_strlen(v1);
            size_t l2 = ft_strlen(v2);
            char *joined = malloc(l1 + l2 + 1);
            if (!joined)
                return;
            my_strcpy(joined, v1);
            my_strcat(joined, v2);
            free(curr->value);
            curr->value = joined;
            t_token *tmp = curr->next;
            curr->has_space_after = tmp->has_space_after;
            curr->next = tmp->next;
            free(tmp->value);
            free(tmp);
            continue;
        }
        curr = curr->next;
    }
    curr = *tokens;
    while (curr)
    {
        char *clean = remove_quotes(curr->value);
        free(curr->value);
        curr->value = clean;
        curr = curr->next;
    }
}