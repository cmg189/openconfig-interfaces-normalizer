



#ifndef SWITCH_GENERATE_H
#define SWITCH_GENERATE_H




void openconfig_interfaces_interface_ethernet_config(const json_object *config_obj, const char *if_name, switch_cfg_t *switch_cfg);

void openconfig_interfaces_interface(const json_object *interface_obj, switch_cfg_t *switch_cfg);

void openconfig_interfaces(const json_object *interfaces_obj, switch_cfg_t *switch_cfg);




#endif  /* SWITCH_GENERATE_H */




