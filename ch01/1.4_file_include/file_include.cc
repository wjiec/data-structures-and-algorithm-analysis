#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

// only using standard method
using namespace std;


// Class: IncludeParser
class IncludeParser {
public:
    IncludeParser(const string &input_file);

public:
    void parse(const string &output_file);

private:
    bool parse_include_syntax(const string &input_file);

private:
    string input_file;
    string output_buffer;
};


int main(int argc, char *argv[]) {
    // validator command parameters
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " [output.file] [input.file]" << endl;
        exit(1);
    }

    // create IncludeParser instance
    IncludeParser *parser = new IncludeParser(argv[2]);
    // save to file
    parser->parse(argv[1]);

    return 0;
}


IncludeParser::IncludeParser(const string &input_file) :
        input_file(input_file), output_buffer("") {
    // empty constructor
}


void IncludeParser::parse(const string &output_file) {
    // output file handler
    ofstream output(output_file, ios::out);
    if (!output.good()) {
        cerr << "Error: cannot open output file" << endl;
        exit(2);
    }
    // parse input file
    parse_include_syntax(input_file);
    // write to output file
    output << output_buffer;
    // close handler
    output.close();
}


bool IncludeParser::parse_include_syntax(const string &input_file) {
    // open input file
    ifstream input(input_file, ios::in);
    if (!input.good()) {
        cerr << "Error: cannot open input file" << endl;
        exit(4);
    }
    // foreach all lines
    for (string current_line; getline(input, current_line); ) {
        // find `include` on each line
        size_t position = current_line.find("include");
        // not found
        if (position == string::npos) {
            output_buffer += current_line + "\n";
        } else {
            // include file name
            string include_file;
            // output string stream
            istringstream os(current_line);
            // getting file name
            os >> include_file >> include_file;
            // check include file correct
            if (include_file == input_file) {
                cerr << "cannot include self" << endl;
            }
            // parse include file
            parse_include_syntax(include_file);
        }
    }
    return true;
}
