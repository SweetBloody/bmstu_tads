#include <stdio.h>
#include "cdio.h"
#include "const.h"
#include "process.h"
#include "structs.h"
#include "analysis.h"

int main()
{
    int ch, number, choice = -1, array_stack_flag = STACK_EMPTY, list_stack_flag = STACK_EMPTY, len = 0;
    array_stack_t array_stack;
    struct list_stack_t *list_stack = NULL;
    struct list_stack_t *pointer;
    struct mem_array_t mem_array;
    mem_array.index = 0;

    init_array_stack(&array_stack);

    while (choice != EXIT)
    {
        choice = print_menu();

        switch (choice)
        {
            case 1:
                input_number(&number);

                ch = add_to_array_stack(&array_stack, number);

                array_stack_flag = OK;

                if (ch != OK)
                    printf("Stack is overflowed!\n");

                break;

            case 2:
                input_number(&number);

                if (list_stack_flag == STACK_EMPTY)
                {
                    list_stack = init_list_stack(number);
                    pointer = list_stack;
                    len = 1;
                }
                else
                    ch = add_to_list_stack(&pointer, &len, number);

                list_stack_flag = OK;

                if (ch != OK)
                    printf("Stack is overflowed!\n");
                break;

            case 3:
                if (array_stack_flag == STACK_EMPTY)
                    printf("Stack is empty!\n");
                else
                    array_stack_flag = delete_from_array_stack(&array_stack);

                break;

            case 4:
                if (list_stack_flag == STACK_EMPTY)
                    printf("Stack is empty!\n");
                else
                {
                    list_stack_flag = delete_from_list_stack(&pointer, &mem_array);
                    len -= 1;
                }
                break;

            case 5:
                if (array_stack_flag == STACK_EMPTY)
                    printf("Stack is empty!\n");
                else
                    print_array_stack(array_stack);
                break;

            case 6:
                if (list_stack_flag == STACK_EMPTY)
                    printf("Stack is empty!\n");
                else
                    print_list_stack(pointer, len);
                break;

            case 7:
                if (list_stack_flag == STACK_EMPTY)
                    printf("Stack is empty!\n");
                else
                    print_list_stack_address(pointer, mem_array, len);
                break;

            case 8:
                if (array_stack_flag == STACK_EMPTY)
                    printf("Stack is empty!\n");
                else
                {
                    process_array_stack(&array_stack);
                    array_stack_flag = STACK_EMPTY;
                }
                break;

            case 9:
                if (list_stack_flag == STACK_EMPTY)
                    printf("Stack is empty!\n");
                else
                {
                    process_list_stack(&pointer, &mem_array);
                    list_stack_flag = STACK_EMPTY;
                }
                break;

            case 10:
                analysis();
                break;

            case 11:
                time_push_pop();
                break;
        }
    }

    return OK;
}
