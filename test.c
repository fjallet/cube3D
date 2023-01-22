#include <stdio.h>
#include <stdlib.h>

char	ft_put_unsigned_nbr_base(unsigned long int nb, char *base)
{
	if (nb >= 16)
	{
		ft_put_unsigned_nbr_base(nb / 16, base);
		ft_put_unsigned_nbr_base(nb % 16, base);
	}
	else
    {
		return(base[nb]);
    }
}

int	ft_count_ubase(unsigned long int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		count++;
	while (nb != 0)
	{
		count++;
		nb = nb / 16;
	}
	return (count);
}

unsigned int xtou64(const char *str)
{
    unsigned int res = 0;
    char c;

    while ((c = *str++)) 
    {
        char v = (c & 0xF) + (c >> 6) | ((c >> 3) & 0x8);
        res = (res << 4) | (unsigned int) v;
    }

    return (res);
} 

int	ft_print_unsignbr_base(unsigned long int nb)
{
	int		count;
	char	*base;
    int     i = 0;
	base = "0123456789abcdef";
	count = ft_count_ubase(nb);
    char *color;
    color = malloc(sizeof(char) * count);
    while (i < count)
    {
	    color[i] = ft_put_unsigned_nbr_base(nb, base);
        i++;
        nb = nb / 16;
    }
    char *color2;
    color2 = malloc(sizeof(char) * count);
    i = 0;
    count--;
    while(i < count)
    {
        color2[i] = color[count];
        color2[count] = color[i];
        count--;
        i++;
        printf("color2[i] == %c\n", color2[i]);
        printf("color2[count] == %c\n", color2[count]);
    }
    color2[i] = color[count];
    printf("color == %s\n", color);
    printf("color2 == %s\n", color2);
    unsigned int test = xtou64(color2);
    printf("test == %d\n", test);
    return(0);
}

int	ft_atoi(const char	*nptr)
{
	int			i;
	int			neg;
	long int	nbr;

	if (!nptr)
		return (0);
	i = 0;
	neg = 1;
	nbr = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
		neg = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = (nptr[i] - '0') + (nbr * 10);
		i++;
	}
	return (nbr * neg);
}

int	main(int ac, char **av)
{
	(void)ac;
    ft_print_unsignbr_base(ft_atoi(av[1]));
    return (0);
}




 /** Take a hex string and convert it to a 64bit number (max 16 hex digits).
 * The string must only contain digits and valid hex characters.
 


 * hex2int
 * take a hex string and convert it to a 32bit number (max 8 hex digits)
 
uint32_t hex2int(char *hex) {
    uint32_t val = 0;
    while (*hex) {
        // get current character then increment
        uint8_t byte = *hex++; 
        // transform hex character to the 4bit equivalent number, using the ascii table indexes
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;    
        // shift 4 to make space for new digit, and add the 4 bits of the new digit 
        val = (val << 4) | (byte & 0xF);
    }
    return val;
}*/