



#ifndef SWITCH_UTILS_H
#define SWITCH_UTILS_H




void switch_cfg_output_config(switch_cfg_t *cfg);

void switch_cfg_cleanup_ports(switch_cfg_t *cfg);

switch_status_e switch_cfg_add_port(const char *if_name, switch_cfg_t *cfg);

switch_status_e switch_cfg_set_port_type(const char *if_name, const char *type, switch_cfg_t *cfg);

switch_status_e switch_cfg_set_port_description(const char *if_name, const char *desc, switch_cfg_t *cfg);

switch_status_e switch_cfg_set_port_enabled(const char *if_name, const bool enabled, switch_cfg_t *cfg);

switch_status_e switch_cfg_set_port_mtu(const char *if_name, const int mtu, switch_cfg_t *cfg);

switch_status_e switch_cfg_set_port_speed(const char *if_name, const char *speed, switch_cfg_t *cfg);

switch_status_e switch_cfg_set_port_advertised_speed(const char *if_name, const char *speed, switch_cfg_t *cfg);

switch_status_e switch_cfg_set_port_auto_negotiate(const char *if_name, const bool autoneg, switch_cfg_t *cfg);




#endif  /* SWITCH_UTILS_H */




