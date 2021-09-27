#include "../../includes/utils.h"

bool	is_whitespace(char c)
{
	if (c == 32 || (c > 8 && c < 14))
		return (true);
	return (false);
}