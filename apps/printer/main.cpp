#include "localization.hpp"
#include "menu.hpp"
#include "pcb_cfg.hpp"

#include <avr/power.h>

void initialize_hardware() {
    clock_prescale_set(clock_div_1);

    mcu::power<usart, timer, adc>::on();

    mcu::mux::usart<usart, zoal::pcb::ard_d00, zoal::pcb::ard_d01, mcu::pd_05>::on();
    mcu::cfg::usart<usart, 115200>::apply();

    mcu::cfg::timer<timer, zoal::periph::timer_mode::up, 64, 1, 0xFF>::apply();
    mcu::irq::timer<timer>::enable_overflow_interrupt();

    mcu::mux::adc<adc, shield::analog_pin>::on();
    mcu::cfg::adc<adc>::apply();

    mcu::enable<usart, timer, adc>::on();

    zoal::utils::interrupts::on();

    shield::gpio_cfg();
    shield::init();
    shield::adc::enable_interrupt();

    create_custom_lcd_char<lcd>();
}

int main() {
    using namespace zoal::io;
    using namespace zoal::gpio;

    initialize_hardware();
    read_eeprom_data();

    uint16_t value = adc::read();
    if (value < 10) {
        start_hardware_configuration();
    } else {
        init_printer();
        start_main_menu();
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
        scheduler.handle();
    }
#pragma clang diagnostic pop
}

ISR(ADC_vect) {
    adc_value = shield::adc::value();
}

ISR(TIMER0_OVF_vect) {
    irq_handler::increment();
}

ISR(USART1_RX_vect) {
    usart::rx_handler<rx_buffer>();
}

ISR(USART1_UDRE_vect) {
    usart::tx_handler<tx_buffer>();
}
