//
// Created by andrii on 06.10.19.
//

#ifndef AVR_WORKSHOP_MENU_H
#define AVR_WORKSHOP_MENU_H

#include <stddef.h>
#include <zoal/io/button.hpp>

enum class lcd_display_mode {
    printer_info,
    rx_tx_info,

    count
};

void start_hartware_configuration();
void start_main_menu();

#endif
