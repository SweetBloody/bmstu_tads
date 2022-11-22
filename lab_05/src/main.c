#include <stdio.h>
#include "const.h"
#include "process.h"
#include "cdio.h"
#include "analysis.h"

int main()
{
    int choice = -1, ch;
    double time_set[8] = {1, 5, 0, 3, 0, 4, 0, 1};
    model_t model;

    srand(time(NULL));

    while (choice != EXIT)
    {
        choice = print_menu();

        switch (choice)
        {
            case 1:
                init_model(&model);
                ch = modelling_array_queue(&model, time_set, 1);
                if (ch == QUEUE_OVERFLOW + 1)
                {
                    printf("\nQueue of 1 type is overflowed!\n");
                    return ch;
                }
                if (ch == QUEUE_OVERFLOW + 2)
                {
                    printf("\nQueue of 2 type is overflowed!\n");
                    return ch;
                }
                print_modelling_info(model);
                print_analysis(model, time_set);
                break;

            case 2:
                init_model(&model);
                modelling_list_queue(&model, time_set, 1);
                print_modelling_info(model);
                print_analysis(model, time_set);
                break;

            case 3:
                time_settings(time_set);
                break;

            case 4:
                analysis(time_set);
                break;

        }
    }

    return OK;
}
