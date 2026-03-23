/*
This file is a part of the microstructure intelligent design software project.

Created:     Qi Huang 2023.04

Modified:    Qi Huang 2023.04;

Copyright (c) 2019-2023 Science center for phase diagram, phase transition, material intelligent design and manufacture, Central South University, China

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free
	Software Foundation, either version 3 of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "modules/modules.h"
int main(int argc, char* argv[]) {
	// get solver
	pf::Solvers* solver = pf::Solvers::get_instance();
	string infile_path, fname = "path.in";
	bool is_init_by_last = false;
	if (argc == 2) {
		is_init_by_last = true;
		infile_path = argv[1];
	}
	else if (argc == 1) {
#ifdef _WIN32
		std::fstream fin(fname, std::ios::in);
		if (!fin) {
			is_init_by_last = false;
			fin.close();
			pf::printf_color_on_control("> Some information/funtions of MInDes (I/i), or normal initialization (N/n)?\n");
			char c = getchar(); char enter = getchar(); //get enter
			if (c == 'i' || c == 'I') {
				solver->mid_info();
				return 0;
			}
		}
		else {
			is_init_by_last = false;
			getline(fin, infile_path);
			fin.close();
			pf::printf_color_on_control("> Last mid input file is " + infile_path + "\n");
			pf::printf_color_on_control("> Init this input file again (Y/y), or some information/funtions of MInDes (I/i), or normal initialization (N/n)?\n");
			char c = getchar(); char enter = getchar(); //get enter
			if (c == 'y' || c == 'Y')
				is_init_by_last = true;
			else if (c == 'i' || c == 'I') {
				solver->mid_info();
				return 0;
			}
		}
#else
		solver->mid_info();
		return 0;
#endif
	}
	if (argc >= 3) {
		string _path = argv[0];
		pf::printf_color_on_control("> Please dont input more than one string after " + _path + "!\n");
		SYS_PROGRAM_STOP;
	}
	if (is_init_by_last == false) {
		if (!pf::SelectFilePath(infile_path)) {
			pf::printf_color_on_control("> MInDes EXIT !!!\n");
			SYS_PROGRAM_STOP;
		}
	}
	std::fstream fout(fname, std::ios::out);
	if (!fout) {
		pf::printf_color_on_control("Failed to add the string to path.in!");
		cout << endl;
	}
	fout << infile_path;
	fout.close();

	solver->init(infile_path);

	pf::init_modules(infile_path);

	solver->run();

	return 0;
}
