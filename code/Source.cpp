#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>

int runPythonScript(int arg1, int arg2, std::string python_script_path) {
	std::vector<std::string> args = { "python3", python_script_path, std::to_string(arg1), std::to_string(arg2) };
	
	int result = system((args[0] + " " + args[1] + " " + args[2] + " " + args[3]).c_str());

	return result; 
}

int main() {
	int method, dim, number;
	std::cout << "Enter method(sp-1,mxv-2,mxm-3),dim,number" << std::endl;
	std::cin >> method;
	std::cin >> dim;
	std::cin >> number;
	if (dim <= 0) {
		std::cout << "incorrect dim" << std::endl;
		return 0;
	}
	if (number <= 0) {
		std::cout << "incorrect number" << std::endl;
		return 0;
	}

	if (method == 1) {
		int result = runPythonScript(number, dim, "./sp_script.py");
		if (result == 0) {
			std::cout << "Python script executed successfully." << std::endl;
		}
		else {
			std::cout << "Error running Python script." << std::endl;
		}
	}
	else if (method == 2) {
		int result = runPythonScript(number, dim, "./mxv_script.py");
			if (result == 0) {
				std::cout << "Python script executed successfully." << std::endl;
			}
			else {
				std::cout << "Error running Python script." << std::endl;
			}
	}
	else if (method == 3) {
		int result = runPythonScript(number, dim, "./mxm_script.py");
		if (result == 0) {
			std::cout << "Python script executed successfully." << std::endl;
		}
		else {
			std::cout << "Error running Python script." << std::endl;
		}
	}
	else {
		std::cout << "incorrect method" << std::endl;
	}
}

