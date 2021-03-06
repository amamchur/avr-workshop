#include "parser.hpp"

%%{
	machine fsm_name;

	quoted_param = '"' ((ascii - cntrl - space - '\\') | [ \t] | '\\'["tvfnr])+ '"';

	main := |*
	    'msg' => {
    	    handler_(this, parse_event::command_msg);
        };
        'on' => {
            handler_(this, parse_event::command_on);
        };
        'off' => {
            handler_(this, parse_event::command_off);
        };
        'delay' => {
            handler_(this, parse_event::command_delay);
        };
        'intensity' => {
            handler_(this, parse_event::command_intensity);
        };
        'animation' => {
            handler_(this, parse_event::command_animation);
        };
        [\+\-]? digit+ =>{
            handler_(this, parse_event::number_token);
        };
        quoted_param => {
            quoted_param_found_action();
        };
        32;
        '\n' => {
            handler_(this, parse_event::line_end);
        };

        any;
	*|;
}%%

namespace {
%% write data;
}

void base_parser::init() {
    %% write init;
}

const char* base_parser::do_parse(const char *p, const char *pe) {
    %% write exec;
    return p;
}
