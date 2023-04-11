#ifndef PRINTERS_H
#define PRINTERS_H

#include "linked_list_utils.h"

/**
 * @brief Prints info about a container.
 *
 * @param container1 container whose information is to be printed
 */
void print_container(container_t *container1);

/**
 * @brief Converts waste type initial to waste type string.
 *
 * @param letter waste type initial
 * @retval waste type string
 */
char *waste_to_long_form(char letter);

/**
 * @brief Prints info about all containers.
 *
 * @param containers containers whose info is to be printed
 */
void print_all_containers(c_list_t *containers);

/**
 * @brief Prints info about containers that pass given filters.
 *
 * @param containers containers whose info is to be filtered and printed
 * @param waste_types waste types character array
 * @param capacity array of capacity min and max
 * @param public accessibility of containers
 * @param filters array of flags indicating which filters are to be used
 */
void print_filtered_containers(c_list_t *containers, char waste_types[7], unsigned int capacity[2], bool public, bool filters[3]);

/**
 * @brief Prints info about all sites.
 *
 * @param sites sites whose info is to be printed
 */
void print_sites(s_list_t *sites);

/**
 * @brief Prints waste types in sorted form.
 *
 * @param waste_types waste types to be sorted and printed
 */
void print_waste_types(char *waste_types);

/**
 * @brief Prints IDs of site neighbors.
 *
 * @param site site whose neighbors' IDs are to be printed
 */
void print_site_neighbors(site_t *site);

/**
 * @brief Prints the shortest path between two sites.
 *
 * @param site target site
 * @param path_length length of path between the two sites
 */
bool print_dijkstra(site_t *site, unsigned int path_length);

#endif //PRINTERS_H
