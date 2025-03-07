#include "minishell.h"

void del(void* ptr)
{
    free(ptr);
    return;
}

void clean_memory_or_save(void *ptr,e_status status)
{
    static t_list* save_add;

    if (status == save)
    {
        if (!ptr)
            return;
        ft_lstadd_back(ft_lstnew(&save_add,ptr));
        return;
    }
    if (status == clean)
    {
        ft_lstclear(&save_add,del);
        exit(0);
    }
}

//this function is allocation memory and save the address of the memory in linked list
void* allocation(size_t nbr_byte)
{
    void *ptr;

    ptr = malloc(nbr_byte);
    if (!ptr)
        clean_memory_or_save(ptr,clean);//this case is faild so send target to clean maning free
    clean_memory_or_save(ptr,save);//so is alcocation is success save the address of the memory
    return (ptr);
}