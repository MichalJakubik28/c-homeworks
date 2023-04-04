#ifndef PRINTERS_H
#define PRINTERS_H

#include "linked_list_utils.h"

void print_container(container_t *container1);
char *waste_to_long_form(char letter);
void print_all_containers(c_list_t *containers);
void print_filtered_containers(c_list_t *containers, char waste_types[7], unsigned int capacity[2], bool public, bool filters[3]);
void print_sites(s_list_t *sites);
void print_waste_types(char *waste_types);
void print_site_neighbors(site_t *site);

#endif //PRINTERS_H
