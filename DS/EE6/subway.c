#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATIONS 1000
#define MAX_STATES 2000
#define MAX_EDGES_PER_STATE 50
#define MAX_NAME_LEN 128
#define INF 1000000000

typedef struct {
    int stations;
    int transfers;
} Dist;

// Lexicographical comparison: stations first, transfers second
int dist_less(Dist a, Dist b) {
    if (a.stations != b.stations) {
        return a.stations < b.stations;
    }
    return a.transfers < b.transfers;
}

typedef struct {
    int station_id;
    int line_id;
} State;

typedef struct {
    int to_state;
    int stations_cost;
    int transfers_cost;
} Edge;

typedef struct {
    Edge edges[MAX_EDGES_PER_STATE];
    int degree;
} Vertex;

char station_names[MAX_STATIONS][MAX_NAME_LEN];
int num_unique_stations = 0;

State states[MAX_STATES];
int num_states = 0;
int state_lookup[MAX_STATIONS][1000]; // lookup state index by station_id and line_id

Vertex state_graph[MAX_STATES];

int get_or_add_station(const char *name) {
    for (int i = 0; i < num_unique_stations; i++) {
        if (strcmp(station_names[i], name) == 0) {
            return i;
        }
    }
    strcpy(station_names[num_unique_stations], name);
    return num_unique_stations++;
}

int get_or_add_state(int station_id, int line_id) {
    if (line_id < 0 || line_id >= 1000) {
        // Fallback for extremely large line IDs
        for (int i = 0; i < num_states; i++) {
            if (states[i].station_id == station_id && states[i].line_id == line_id) {
                return i;
            }
        }
        states[num_states].station_id = station_id;
        states[num_states].line_id = line_id;
        return num_states++;
    }
    if (state_lookup[station_id][line_id] != -1) {
        return state_lookup[station_id][line_id];
    }
    states[num_states].station_id = station_id;
    states[num_states].line_id = line_id;
    state_lookup[station_id][line_id] = num_states;
    return num_states++;
}

void add_edge(int u, int v, int s_cost, int t_cost) {
    if (state_graph[u].degree >= MAX_EDGES_PER_STATE) {
        return;
    }
    // Avoid exact duplicate edges (same target and same costs)
    for (int i = 0; i < state_graph[u].degree; i++) {
        if (state_graph[u].edges[i].to_state == v &&
            state_graph[u].edges[i].stations_cost == s_cost &&
            state_graph[u].edges[i].transfers_cost == t_cost) {
            return;
        }
    }
    state_graph[u].edges[state_graph[u].degree].to_state = v;
    state_graph[u].edges[state_graph[u].degree].stations_cost = s_cost;
    state_graph[u].edges[state_graph[u].degree].transfers_cost = t_cost;
    state_graph[u].degree++;
}

Dist dist[MAX_STATES];
int visited[MAX_STATES];
int prev_state[MAX_STATES];

int main() {
    // Initialize lookup tables
    for (int i = 0; i < MAX_STATIONS; i++) {
        for (int j = 0; j < 1000; j++) {
            state_lookup[i][j] = -1;
        }
    }
    for (int i = 0; i < MAX_STATES; i++) {
        state_graph[i].degree = 0;
    }

    // Open file
    FILE *fp = fopen("bgstations.txt", "r");
    if (!fp) {
        fprintf(stderr, "Error opening bgstations.txt\n");
        return 1;
    }

    int num_lines;
    if (fscanf(fp, "%d", &num_lines) != 1) {
        fclose(fp);
        return 1;
    }

    for (int i = 0; i < num_lines; i++) {
        int line_id, num_line_stations;
        if (fscanf(fp, "%d %d", &line_id, &num_line_stations) != 2) {
            break;
        }

        int line_stations[MAX_STATIONS];
        for (int j = 0; j < num_line_stations; j++) {
            char name[MAX_NAME_LEN];
            int transfer_status;
            if (fscanf(fp, "%s %d", name, &transfer_status) != 2) {
                break;
            }
            int station_id = get_or_add_station(name);
            int state_idx = get_or_add_state(station_id, line_id);
            line_stations[j] = state_idx;
        }

        // Add line travel edges
        for (int j = 0; j < num_line_stations - 1; j++) {
            int u = line_stations[j];
            int v = line_stations[j+1];
            add_edge(u, v, 1, 0);
            add_edge(v, u, 1, 0);
        }
    }
    fclose(fp);

    // Add transfer edges between different lines at the same station
    for (int u = 0; u < num_unique_stations; u++) {
        int u_states[100];
        int u_states_count = 0;
        for (int i = 0; i < num_states; i++) {
            if (states[i].station_id == u) {
                u_states[u_states_count++] = i;
            }
        }
        for (int i = 0; i < u_states_count; i++) {
            for (int j = i + 1; j < u_states_count; j++) {
                add_edge(u_states[i], u_states[j], 0, 1);
                add_edge(u_states[j], u_states[i], 0, 1);
            }
        }
    }

    // Read start and end station names from stdin
    char start_name[MAX_NAME_LEN];
    char end_name[MAX_NAME_LEN];
    if (scanf("%s", start_name) != 1) return 0;
    if (scanf("%s", end_name) != 1) return 0;

    int start_station_id = -1;
    int end_station_id = -1;
    for (int i = 0; i < num_unique_stations; i++) {
        if (strcmp(station_names[i], start_name) == 0) {
            start_station_id = i;
        }
        if (strcmp(station_names[i], end_name) == 0) {
            end_station_id = i;
        }
    }

    if (start_station_id == -1 || end_station_id == -1) {
        // Just return if not found
        return 0;
    }

    if (start_station_id == end_station_id) {
        printf("%s\n", start_name);
        return 0;
    }

    // Initialize Dijkstra
    for (int i = 0; i < num_states; i++) {
        dist[i].stations = INF;
        dist[i].transfers = INF;
        visited[i] = 0;
        prev_state[i] = -1;
    }

    // Set all start states to 0 distance
    for (int i = 0; i < num_states; i++) {
        if (states[i].station_id == start_station_id) {
            dist[i].stations = 0;
            dist[i].transfers = 0;
        }
    }

    // Dijkstra main loop
    for (int step = 0; step < num_states; step++) {
        int u = -1;
        Dist min_d = {INF, INF};
        for (int i = 0; i < num_states; i++) {
            if (!visited[i] && dist_less(dist[i], min_d)) {
                min_d = dist[i];
                u = i;
            }
        }

        if (u == -1 || min_d.stations == INF) {
            break;
        }

        visited[u] = 1;

        for (int i = 0; i < state_graph[u].degree; i++) {
            int v = state_graph[u].edges[i].to_state;
            Dist cost = {state_graph[u].edges[i].stations_cost, state_graph[u].edges[i].transfers_cost};
            Dist new_d = {dist[u].stations + cost.stations, dist[u].transfers + cost.transfers};
            if (dist_less(new_d, dist[v])) {
                dist[v] = new_d;
                prev_state[v] = u;
            }
        }
    }

    // Find the best end state
    int best_end_state = -1;
    Dist min_end_dist = {INF, INF};
    for (int i = 0; i < num_states; i++) {
        if (states[i].station_id == end_station_id) {
            if (dist_less(dist[i], min_end_dist)) {
                min_end_dist = dist[i];
                best_end_state = i;
            }
        }
    }

    if (best_end_state == -1 || min_end_dist.stations == INF) {
        return 0;
    }

    // Reconstruct path
    int path[MAX_STATES];
    int path_len = 0;
    int curr = best_end_state;
    while (curr != -1) {
        path[path_len++] = curr;
        curr = prev_state[curr];
    }

    // Reverse path
    for (int i = 0; i < path_len / 2; i++) {
        int temp = path[i];
        path[i] = path[path_len - 1 - i];
        path[path_len - 1 - i] = temp;
    }

    // Print path in formatting style: SSN-n1(m1)-S1-n2(m2)-...-ESN
    int i = 0;
    printf("%s", station_names[states[path[0]].station_id]);
    while (i < path_len - 1) {
        int line = states[path[i]].line_id;
        int count = 0;
        // Go forward as long as we are on the same line and moving to adjacent stations
        while (i < path_len - 1 && states[path[i+1]].line_id == line) {
            if (states[path[i+1]].station_id != states[path[i]].station_id) {
                count++;
            }
            i++;
        }
        printf("-%d(%d)-%s", line, count, station_names[states[path[i]].station_id]);
        // If next step is a transfer (same station, different line), skip the transfer state
        if (i < path_len - 1 && states[path[i+1]].station_id == states[path[i]].station_id) {
            i++;
        }
    }
    printf("\n");

    return 0;
}
