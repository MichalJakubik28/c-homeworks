#include "dijkstra.h"

#include "linked_list_utils.h"

#include <limits.h>

void relax(s_list_t *sites, site_t *site)
{
    sn_node_t *neighbor = site->neighbors->head;

    while (neighbor != NULL) {
        sn_node_t *next = neighbor->next;

        if (site->shortest_distance + neighbor->distance < neighbor->site->shortest_distance) {
            neighbor->site->shortest_distance = site->shortest_distance + neighbor->distance;
            neighbor->site->predecessor = site;
            s_node_t *site_node = s_get_by_site(sites, neighbor->site);
            remove_from_list(sites, site_node);
            s_list_insert_by_distance(sites, site_node);
        }

        neighbor = next;
    }
}

bool dijkstra(s_list_t *sites, unsigned int start_id, unsigned int target_id, site_t **target_site)
{
    s_node_t *starting_site = s_get_by_id(sites, start_id);
    s_node_t *ending_site = s_get_by_id(sites, target_id);
    if (starting_site == NULL || ending_site == NULL) {
        return false;
    }

    starting_site->site->shortest_distance = 0;

    // priority queue! (although time complexity is ruined anyway :/ )
    remove_from_list(sites, starting_site);
    s_list_insert_by_distance(sites, starting_site);

    s_node_t *curr_site = sites->head;

    while (curr_site != NULL) {
        if (curr_site == ending_site && curr_site->site->shortest_distance != UINT_MAX) {
            *target_site = curr_site->site;
            return true;
        }
        relax(sites, curr_site->site);

        curr_site = curr_site->next;
    }

    // no path
    return true;
}

unsigned int path_length(site_t *site)
{
    if (site == NULL) {
        return 0;
    }

    site_t *prev = site->predecessor;
    int counter = 1;
    while (prev != NULL) {
        prev = prev->predecessor;
        counter++;
    }
    return counter;
}
