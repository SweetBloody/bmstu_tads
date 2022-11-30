#include <stdio.h>
#include "const.h"
#include "cdio.h"
#include "graph_matrix.h"
#include "analysis.h"

int main()
{
    graph_t graph;
    int choice = -1, ch;

    setbuf(stdout, NULL);

    while (choice != EXIT)
    {
        choice = print_menu();

        switch (choice)
        {
            case 1:
                graph_init(&graph);
                input_graph(&graph);
                print_graph(graph);
                break;

            case 2:
                ch = file_check("data.txt", "r");

                if (ch != OK)
                    return ch;

                graph_init(&graph);
                input_graph_from_file(&graph);
                print_graph(graph);
                break;

            case 3:
                print_graph(graph);
                export_to_dot(&graph, "graph.gv");
                break;

            case 4:
                input_nodes(&graph);
                break;

            case 5:
                process(graph, 0);
                break;

            case 6:
                analysis(graph);
                break;
        }
    }

    return OK;
}
