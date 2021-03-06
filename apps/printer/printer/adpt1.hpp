#ifndef AVR_WORKSHOP_ADPT1_HPP
#define AVR_WORKSHOP_ADPT1_HPP

#include "../parser/mpcl_parser.hpp"
#include "base.hpp"

namespace printer {
    class adpt1 : public base {
    public:
        using parser_type = mpcl_parser<128>;

        typedef struct {
            USB_Descriptor_Configuration_Header_t Config;
            USB_Descriptor_Interface_t Printer_Interface;
            USB_Descriptor_Endpoint_t Printer_DataOutEndpoint;
            USB_Descriptor_Endpoint_t Printer_DataInEndpoint;
        } usb_configuration;

        static constexpr uint16_t vendor_id = 0x12EE;
        static constexpr uint16_t product_id = 0x1043;

        void init() override;

        const char *name_pgmem() override;

        uint16_t get_descriptor(void *dst, uint16_t size) override;

        uint16_t get_configuration(void *dst, uint16_t size) override;

        uint16_t get_product_string(void *dst, uint16_t size) override;

        void process_data(const void *d, size_t size) override;
    private:
        static void command_callback(void *p, int e);

        parser_type parser;

        void process_command(parser_type *p, mpcl_parse_event event);
    };
}

#endif
