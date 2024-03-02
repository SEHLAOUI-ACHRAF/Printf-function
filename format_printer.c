#include "main.h"

/**
 * printByFormat - Prints an argument based on its type
 * @Format_Spec: Formatted string
 * @list: List of arguments to be printed
 * @ind: indicator
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
*/

int printByFormat(const char *Format_Spec, int *ind, va_list list,
		char buffer[], int flags, int width,
		int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	Format_Spec_t Format_Spec_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; Format_Spec_types[i].Format_Spec != '\0'; i++)
		if (Format_Spec[*ind] == Format_Spec_types[i].Format_Spec)
			return (Format_Spec_types[i].prc_Fnc(list, buffer, flags,
						width, precision, size));

	if (Format_Spec_types[i].Format_Spec == '\0')
	{
		if (Format_Spec[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (Format_Spec[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (Format_Spec[*ind] != ' ' && Format_Spec[*ind] != '%')
				--(*ind);
			if (Format_Spec[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &Format_Spec[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
