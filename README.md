## US Cancer Incidence Analysis Project
This project is designed to analyze cancer incidence data across the United States by state and county. Utilizing C++ for data processing, it constructs graph representations from CSV files to facilitate efficient querying of cancer statistics. The system allows users to interactively search data by state, county, or year and provides visual representations of data connections through adjacency matrices and lists.

# Features 
- Data Import: Automatically reads and processes data from CSV files.
- Graphical Data Representation: Uses graphs, adjacency lists, and matrices for data analysis.
- Interactive Search: Allows users to query data based on state, county, and year.
- Performance Insights: Displays processing times for data queries, showcasing the efficiency of the data structures used.

# User Guide
To interact with the application, follow the prompts displayed in the console:

1) Choose Data Access Method:
- Input Graph to interact with the graph based queries.
- Input Directly to directly search and display data from the datasets.
- Input Exit to close the application.

2) Graph-based Interaction:
- Input 1 to search by state.
- Input 2 to search by county.
- Input 3 to search by year.
- Input 4 to display the adjacency matrix.
- Input 5 to display the list of edges.

3) Direct Data Interaction:
Follow on screen prompts to enter state, county, or year as required.

# Data Format
The data should be in CSV format with the following columns: County, State, Deaths, Population, Year. Ensure that files are placed in a data/ directory within the project folder.

# Contributors
- Juan Postiglione
- Jesus Gil
- David Hintz
