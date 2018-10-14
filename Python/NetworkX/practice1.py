import networkx as nx

# Practice1: Read and write graphs

if __name__ == '__main__':
    # Create a graph
    G = nx.Graph() # Undirected Graph
    directedG = nx.DiGraph() # Directed Graph

    # Add nodes
    G.add_node(1)
    G.add_nodes_from([2, 3])

    # Add edges between nodes
    G.add_edge(1, 2)
    e = (2, 3)
    G.add_edge(*e) # Unpack tuple

    # Print properties of graph
    print(G.number_of_nodes())
    print(G.number_of_edges())

    nodes = list(G.nodes())
    print(nodes)
    edges = list(G.edges())
    print(edges)

