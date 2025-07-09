#include "main.h"

int get_token_end(char *s, int i)
{
    if (s[i] == '$' && (s[i + 1] == '\'' || s[i + 1] == '"'))
    {
        char quote = s[i + 1];
        i += 2;
        while (s[i] && s[i] != quote)
            i++;
        if (s[i] == quote)
            i++;
        return i;
    }
    if (s[i] == '<' || s[i] == '>')
    {
        if (s[i + 1] == s[i])
            return i + 2;
        return i + 1;
    }
    if(s[i] == '|')
        return i + 1;
    if (s[i] == '"' || s[i] == '\'')
    {
        char quote = s[i++];
        while (s[i] && s[i] != quote)
            i++;
        if (s[i] == quote)
            i++;
        return i;
    }
    while (s[i] && !ft_isspace(s[i]) && s[i] != '"' && s[i] != '\'' &&
        s[i] != '<' && s[i] != '>' && s[i] != '|')
        i++;
    return i;
}
