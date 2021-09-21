#include "../../includes/utils.h"

static int	count_words(char const *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != c)
			if (str[i + 1] == '\0' || str[i + 1] == c)
				count++;
		i++;
	}
	return (count);
}

static char	*next_word(char const *str, int i, char c)
{
	int		len;
	char	*new_word;
	int		k;
	int		start;

	len = 0;
	start = i;
	while ((str[i] != c) && (str[i] != '\0'))
	{
		len++;
		i++;
	}
	new_word = (char *)malloc((len + 1) * sizeof(char));
	if (new_word == NULL)
		return (0);
	k = 0;
	while (k < len && str[start] != '\0')
	{
		new_word[k] = str[start];
		start++;
		k++;
	}
	new_word[len] = '\0';
	return (new_word);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		word_count;
	int		i;
	int		j;

	word_count = count_words(s, c);
	strs = (char **)malloc((word_count + 1) * sizeof (char *));
	if (!strs || !s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c) && (i == 0 || (s[i - 1] == c)))
		{
			strs[j] = next_word(s, i, c);
			if (strs[j] == NULL)
				return (ft_free_array(strs));
			j++;
		}
		i++;
	}
	strs[word_count] = NULL;
	return (strs);
}