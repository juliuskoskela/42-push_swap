# include "array/inc/array.h"
# include "libft/inc/libft.h"

typedef struct		s_graph_node
{
	char			*name;
	t_arr			edges;
	int				flag;
}					t_graph_node;

typedef	struct		s_graph_edge
{
	int				weight;
	t_graph_node	*in;
	t_graph_node	*out;
}					t_graph_edge;

typedef struct		s_graph
{
	t_arr			nodes;
	t_arr			edges;
	size_t			size;
}					t_graph;



void				print_node(void **node, size_t i)
{
	t_graph_node	*ptr;
	t_graph_node	*ptr2;

	ptr = *node;
	printf("%zu. %s\n", i, ptr->name);
	printf("flag = %d\n", ptr->flag);
	i = 0;
	while (i < ptr->edges.count)
	{
		ptr2 = a_get(&ptr->edges, i);
		printf("edge[%zu] = %s\n", i, ptr2->name); 
		i++;
	}
}

void				recurse_edges(t_arr *edges)
{
	t_graph_node	*current;
	size_t			i;

	i = 0;
	while (i < edges->count)
	{
		current = a_get(edges, i);
		if (current->flag == 0)
		{
			if (current->flag == 0)
				printf("%s\n", current->name);
			current->flag = 1;
			recurse_edges(&current->edges);
		}
		i++;
	}
}

void				print_root(t_graph_node *root)
{
	
	if (root->flag == 1)
		return ;
	printf("root: %s\n", root->name);
	recurse_edges(&root->edges);
}

t_graph_node		new_graph_node(char *name, int edge_count, ...)
{

	va_list			ap;
	t_graph_node	out;

	out.edges = a_alloc(edge_count);
	va_start(ap, edge_count);
	while (edge_count--)
	{
		a_add(&out.edges, va_arg(ap, t_graph_node *));
	}
	va_end(ap);
	out.name = name;
	out.flag = 0;
	return (out);
}

int				main(void)
{
	t_graph_node	nodes[3];
	/*t_arr			graph;*/

	nodes[0] = new_graph_node("0", 0);
	nodes[1] = new_graph_node("1", 1, &nodes[0]);
	nodes[2] = new_graph_node("2", 2, &nodes[0], &nodes[1]);
	print_root(&nodes[2]);
	/*graph = a_alloc(3);*/
	/*a_addn(&graph, 3, &nodes[0], &nodes[1], &nodes[2]);*/
	/*a_iter(&graph, print_node);*/
}
