#include <stdio.h>

int is_spaces(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

int is_valid_token(char c, int quote, int doubl_quote)
{
    // Treat tokens as valid when not inside quotes or if inside quotes
    if (!is_spaces(c) && ((quote % 2 == 0) || (doubl_quote % 2 == 0)))
        return (1);
    return (0);
}

void count_quotes(char c, int *quote, int *double_quote)
{
    if (c == '\'')
        *quote += 1;  // Toggle single quote state
    if (c == '"')
        *double_quote += 1;  // Toggle double quote state
}

short count_nbr_token(char* str)
{
    int		(i), (quote) ,(double_quote);
	short	counter;

	i = 0;
	counter = 0;
    quote = 0;
    double_quote = 0;
    while (str && str[i])
    {
        // Skip spaces outside of quotes
        while (str[i] && is_spaces(str[i]) && (quote % 2 == 0) && (double_quote % 2 == 0))
        {
            count_quotes(str[i], &quote, &double_quote);
            i++;
        }

        // If we're outside of quotes and we encounter a valid token, increment the counter
        if (str[i] && is_valid_token(str[i], quote, double_quote))
        {
            counter++;
            // Skip until we hit a space or quote to continue the next token
        }

        // If inside a quote, keep going until we find the closing quote
        while (str[i] && !is_spaces(str[i]) && (quote % 2 == 0) && (double_quote % 2 == 0))
        {
            count_quotes(str[i], &quote, &double_quote);
            i++;
        }

        // Skip over the content inside the quotes as a single token
        while (str[i] && ((quote % 2 == 1) || (double_quote % 2 == 1)))
        {
            count_quotes(str[i], &quote, &double_quote);
            i++;
        }
    }

    return counter;
}

int main()
{
    // Test cases
    char *test_str1 = "Hello 'World' \"This\" is a test";
    char *test_str2 = "  Single   word ";
    char *test_str3 = "Test with \"double quotes\" and 'single quotes' inside";
    char *test_str4 = " \"Unclosed quotes";
    char *test_str5 = "No quotes here";

    printf("Test 1: %s\n", test_str1);
    printf("Token count: %d\n", count_nbr_token(test_str1));

    printf("\nTest 2: %s\n", test_str2);
    printf("Token count: %d\n", count_nbr_token(test_str2));

    printf("\nTest 3: %s\n", test_str3);
    printf("Token count: %d\n", count_nbr_token(test_str3));

    printf("\nTest 4: %s\n", test_str4);
    printf("Token count: %d\n", count_nbr_token(test_str4));

    printf("\nTest 5: %s\n", test_str5);
    printf("Token count: %d\n", count_nbr_token(test_str5));

    return 0;
}
