#include "profitview_socketio_cppConfig.h"
#include "SIOPocoTradeStream.h"
#include "WSCcTradeStream.h"
#include "TradeStreamMaker.h"
#include "profitview_poco.h"

#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
	const auto 
		name_arg{0},
		profitview_api_arg{1}, 
		symbol_args{2};

	if (argc < symbol_args) {
		// report version
		std::cout 
			<< argv[0] 
			<< " Version " 
			<< profitview_socketio_cpp_VERSION_MAJOR << "."
			<< profitview_socketio_cpp_VERSION_MINOR << std::endl;
		std::cout 
			<< "Usage: " << argv[name_arg] << " api_key_name data_type:market:symbol" << std::endl;
		return 1;
	}

    profitview::poco::Logger logger;

	std::string symbols{argv[symbol_args]};
	auto first_colon = symbols.find(':');
	auto second_colon = symbols.find(':', first_colon + 1);
	auto market{symbols.substr(first_colon + 1, second_colon - first_colon - 1)};
	auto symbol{symbols.substr(second_colon + 1)};

	std::vector<std::string> symbol_vector{symbol};
	TradeStreamMaker::register_stream<SIOPocoTradeStream>("SIOPocoStream", argv[profitview_api_arg]);
	TradeStreamMaker::register_stream<WSCcTradeStream>("WSCcStream");

	// TradeStreamMaker::make.at("SIOPocoStream")->subscribe(market, symbol_vector);
	TradeStreamMaker::get("WSCcStream").subscribe(market, symbol_vector);

	std::cout << "Press enter to quit" << std::endl;
	std::cin.get();
}