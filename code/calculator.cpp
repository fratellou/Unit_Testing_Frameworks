#include "calculator.h"  
using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 2) {
        executeCommandsFromFile(argv[1]);  // Execute commands from a file if a filename is provided as a command line argument
    } else if (argc == 1) {
        executeCommandsFromStdin();  // Execute commands from standard input if no command line argument is provided
    }
    else {
        cerr << "Invalid input.";  
    }
    return 0;  
}

// Function to execute commands from a file
void executeCommandsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        processCommand(line);  // Process each line as a command
    }

    file.close();
}

// Function to execute commands from standard input
void executeCommandsFromStdin() {
    cout << "Enter a commands (or 'exit' to quit):\n";
    string line;
    while (true) {
        getline(cin, line);
        if (line == "exit") {
            break;
        }

        processCommand(line);  // Process each line as a command
    }
}

// Function to process a command string
void processCommand(const string& command) {
    istringstream iss(command);
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};

    if (!tokens.empty()) {
        try {
            unique_ptr<Command> cmd = CommandFactory::createCommand(tokens[0], vector<string>(tokens.begin() + 1, tokens.end()));
            cmd->execute(executionContext);  // Execute the command with the global ExecutionContext
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << std::endl;  // Print error message if an exception occurs
        }
    }
}