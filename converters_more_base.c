#include "holberton.h"

/**
 * convert_o - Converts an unsigned int to octal and
 *                 copies the result to the output.
 * @output: A buffer_t struct containing a character array.
 * @arg_list: A va_list list containing the arguments.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_o(va_list arg_list, buffer_t *output)
{
	unsigned long int num;
	unsigned int ret = 0;
	char zero = '0';

	num = va_arg(arg_list, unsigned int);
	if (!(num == 0))
		ret += convert_ubase(output, num, "01234567");

	else
		ret += _copy(output, &zero, 1);
	return (ret);
}

/**
 * convert_S - Converts an argument to a string and
 *             copies it to the output.
 * Extra: Non-printable characteres (ASCII values < 32 or >= 127)
 *              are stored as \x followed by the ASCII code value in hex.
 * @args: A va_list list containing the arguments.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_S(va_list args, buffer_t *output)
{
	char *str, *null = "(null)", *hex = "\\x", zero = '0';
	int size, i;
	unsigned int ret = 0;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_copy(output, null, 6));

	for (size = 0; str[size];)
		size++;

	for (i = 0; *(str + i) != '\0'; i++)
	{
		if (*(str + i) < 32 || *(str + i) >= 127)
		{
			ret += _copy(output, hex, 2);
			if (*(str + i) < 16)
				ret += _copy(output, &zero, 1);
			ret += convert_ubase(output, *(str + i),
					     "0123456789ABCDEF");
			continue;
		}
		ret += _copy(output, (str + i), 1);
	}

	return (ret);
}

/**
 * convert_p - Converts the address of an argument to hex and
 *             copies the result to the output.
 * @args: A va_list list containing the arguments.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_p(va_list args, buffer_t *output)
{
	char *null = "(nil)", *index = "0x";
	unsigned long int address;
	unsigned int ret = 0;

	address = va_arg(args, unsigned long int);
	if (address == '\0')
		return (_copy(output, null, 5));

	ret += _copy(output, index, 2);
	ret += convert_ubase(output, address, "0123456789abcdef");
	return (ret);
}

/**
 * convert_R - Converts a string to ROT13 and copies
 *             it to the output.
 * @arg_list: A va_list list containing the arguments.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_R(va_list arg_list, buffer_t *output)
{
	char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *str, *null = "(null)";
	int i, j, size;
	unsigned int ret = 0;

	str = va_arg(arg_list, char *);
	if (str == NULL)
		return (_copy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	for (i = 0; *(str + i) != '\0'; i++)
	{
		for (j = 0; j < 52; j++)
		{
			if (*(str + i) == *(alpha + j))
			{
				ret += _copy(output, (rot13 + j), 1);
				break;
			}
		}
		if (j == 52)
			ret += _copy(output, (str + i), 1);
	}

	return (ret);
}
