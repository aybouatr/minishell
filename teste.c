// #include <stdio.h>

// typedef enum
// {
//     e_close,
//     e_open
// } t_status_quote;

// typedef enum 
// {
//     e_nothing,
//     e_single_quote,
//     e_double_quote

// } t_type_quote;

// typedef struct
// {
//     t_status_quote status_quote;
//     t_type_quote type_quote;
// } t_quote;

// int is_spaces(char c) 
// {
//     return (c == ' ' || c == '\t');
// }

// void check_quote(t_quote *ifo_quote, char c) {

//     if (ifo_quote->status_quote == e_close)
//     {
//         if (c == '\'') {
//             ifo_quote->type_quote = e_single_quote;
//             ifo_quote->status_quote = e_open;
//         } else if (c == '"') {
//             ifo_quote->type_quote = e_double_quote;
//             ifo_quote->status_quote = e_open;
//         }
//     } 
//     else if (ifo_quote->status_quote == e_open)
//     {
//         if ((ifo_quote->type_quote == e_single_quote && c == '\'') || (ifo_quote->type_quote == e_double_quote && c == '"'))
//         {
//             ifo_quote->type_quote = e_nothing;
//             ifo_quote->status_quote = e_close;
//         }
//     }
// }

// short count_nbr_token(char *str) {
//     short counter = 0;
//     t_quote quote;

//     quote.status_quote = e_close;
//     quote.type_quote = e_nothing;

//     while (str && *str) {
//         // Skip spaces
//         while (str && *str && is_spaces(*str))
//         {
//             check_quote(&quote, *str);
//             str++;
//         }
//         if (!*str)
//             break;
//         counter++;
//         // Process the token
//         while (*str && (!is_spaces(*str) || quote.status_quote == e_open)) 
//         {
//             check_quote(&quote, *str);
//             str++;
//         }
//     }

//     return counter;
// }

// int main()
// {
//     char input_line[] = "ls -l | grep \"file hf fk ' '' \" && echo \"Found\" || echo \"Not Found\"";
//     short token_count = count_nbr_token(input_line);
//     printf("Number of tokens: %d\n", token_count);
//     return 0;
// }

#include <stdio.h>

int main() {
    int i = 1;

    while (i <= 10) {
        // If i is an even number, skip the rest of the loop and continue to the next iteration
        if (i % 2 == 0) 
        {
            i++;
            continue;
        }

        // This part of the code will only be executed for odd numbers
        printf("%d ", i);
        i++;
    }

    return 0;
}
