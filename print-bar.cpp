/* Prints a simple bar to stdout, e.g.
 * $ ./print-bar -w 10 -f ▣ -e ▢ 50
 * Outputs: ▣▣▣▣▣▢▢▢▢▢
 *
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#include <iostream>
#include "boost/program_options.hpp"

using namespace std;

const string DEFAULT_TICK_FULL = "▣";
const string DEFAULT_TICK_EMPTY = "▢";
const int BAR_WIDTH = 10;


void print_bar(int usage, int width, string tick_full, string tick_empty) {
    string bar;

    int scaledusage = rint(usage * width / 100);

    int i;
    for (i = 0; i < scaledusage; i++)
        bar.append(tick_full);

    for (; i < width; i++)
        bar.append(tick_empty);

    cout << bar;
}

bool flag_equal(char* flag, char* that) {
    return strcmp(flag, that) == 0;
}

int main(int argc, char *argv[])
{
    int width, usage;
    string tick_full, tick_empty;

    namespace po = boost::program_options;
    po::options_description desc(" [options] <usage>");
    desc.add_options()
      ("help,h", "Print help message")
      ("width,w", po::value<int>(&width)->default_value(BAR_WIDTH),
                "The width of the bar, i.e. number of chars")
      ("tick-full,f", po::value<string>(&tick_full)->default_value(DEFAULT_TICK_FULL),
                    "The character that indicates usage")
      ("tick-empty,e", po::value<string>(&tick_empty)->default_value(DEFAULT_TICK_EMPTY),
                    "The character that indicates emptiness")
      ("usage", po::value<int>(&usage)->required(),
                "A usage integer between 0-100");

    po::positional_options_description positionalOptions;
    positionalOptions.add("usage", 1);

    po::variables_map vm;

    try {
        po::store(po::command_line_parser(argc, argv).options(desc)
                  .positional(positionalOptions).run(), vm);

        if(vm.count("help")) {
            cerr << argv[0] << desc << endl;
            return 0;
        }
        po::notify(vm);
    }
    catch(boost::program_options::required_option& e)
    {
        std::cerr << "ERROR: " << e.what() << endl;
        return 1;
    }
    catch(boost::program_options::error& e)
    {
        std::cerr << "ERROR: " << e.what() << endl;
        return 1;
    }


    if(usage < 0) {
        usage = 0;
    }
    else if(usage > 100) {
        usage = 100;
    }
    print_bar(usage, width, tick_full, tick_empty);
    return 0;
}
