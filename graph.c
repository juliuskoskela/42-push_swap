# include "array/inc/array.h"
# include "libft/inc/libft.h"
# define NO_ID -1

typedef struct		s_graph_node
{
	char			*name;
	int				flag;
}					t_graph_node;

typedef	struct		s_graph_edge
{
	double			weight;
	t_graph_node	*left;
	t_graph_node	*right;
}					t_graph_edge;

typedef struct		s_graph
{
	t_arr			nodes;
	t_arr			edges;
	size_t			size;
}					t_graph;

t_graph_node		*graph_new_node(char *name)
{
	t_graph_node	*new;

	new = (t_graph_node *)malloc(sizeof(t_graph_node));
	new->name = name;
	new->flag = 0;
	return (new);
}

t_graph				graph_new()
{
	t_graph			out;

	out.nodes = a_alloc(1);
	out.edges = a_alloc(1);
	out.size = 0;
	return (out);
}

void				graph_add_node(t_graph *g, char *name)
{
	t_graph_node	*node;

	node = graph_new_node(name);
	a_add(&g->nodes, node);
	g->size++;
}

void				graph_add_edge(t_graph *g, double weight,
					size_t in, size_t out)
{
	t_graph_edge	*new;

	new = (t_graph_edge *)malloc(sizeof(t_graph_edge));
	new->weight = weight;
	new->left = a_get(&g->nodes, in);
	new->right = a_get(&g->nodes, out);
	if (!new->left || !new->right || in == out)
	{
		printf("Edge failed!\n");
		return ;
	}
	a_add(&g->edges, new);
}

void				print_string(void **str, size_t i)
{
	char			*ptr;

	ptr = *str;
	printf("%s\n", ptr);
}

size_t				parse_words(t_arr *src, t_arr *dst, size_t i, size_t max)
{
	char	*line;
	char	**tab;
	size_t	tabsize;

	line = a_get(src, i);
	tab = s_split(line, ' ');
	tabsize = 0;
	while (tab[tabsize])
		tabsize++;
	if (i == 0)
		max = tabsize;
	a_assign(dst, (void **)tab, max);
	free(tab);
	return (max);
}

void				a_parse(t_arr *src, t_arr *dst,
					size_t (*parse)(t_arr *, t_arr *, size_t, size_t))
{
	size_t			i;
	size_t			max;

	i = 0;
	max = 0;
	while (i < dst->count)
	{
		max = parse(dst, src, i, max);	
		i++;
	}
}

void				graph_print_nodes(t_graph *g)
{
	size_t			i;
	size_t			j;
	t_graph_node	*node;
	t_graph_edge	*edge;

	i = 0;
	while (i < g->nodes.count)
	{
		node = a_get(&g->nodes, i);
		j = 0;
		printf("\n%s\n\n", node->name);
		while (j < g->edges.count)
		{
			edge = a_get(&g->edges, j);
			if (s_cmp(edge->left->name, node->name) == 0)
				printf(" [%0.1f]> %s\n", edge->weight, edge->right->name);
			j++;
		}
		j = 0;
		while (j < g->edges.count)
		{
			edge = a_get(&g->edges, j);
			if (s_cmp(edge->right->name, node->name) == 0)
				printf("<[%0.1f]  %s\n", edge->weight, edge->left->name);
			j++;
		}
		i++;
	}
}

int				main(void)
{
	t_graph			graph;

	graph = graph_new();
	graph_add_node(&graph, "NODE 1");
	graph_add_node(&graph, "NODE 2");
	graph_add_node(&graph, "NODE 3");
	graph_add_edge(&graph, 0.2, 0, 1);
	graph_add_edge(&graph, 0.5, 1, 2);
	graph_add_edge(&graph, 0.7, 0, 2);
	graph_add_edge(&graph, 0.1, 2, 1);
	graph_print_nodes(&graph);

	/*t_arr 	lines = a_alloc(1);*/
	/*a_add(&lines, "word1 word2     word3   ");*/
	/*a_add(&lines, "   word4  word5   word6 w123890  ");*/
	/*t_arr	words = a_alloc(1);*/

	/*a_parse(&words, &lines, parse_words);*/
	/*a_iter(&lines, print_string);*/
	/*a_iter(&words, print_string);*/
}
