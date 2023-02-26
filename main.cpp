#include <iostream>
#include <fstream>
#include <optional>
#include <vector>
#include <string>

using namespace std;

namespace mySpace {
	class FullName {
	public:	
		FullName() {
			Name = "";
			Patronic = "";
			Surname = "";
		}
		~FullName() {}
		string Name, Surname;
		optional<string> Patronic;
	};
	class Student {
	public:
		mySpace::FullName StudName;
		string GroupNumber;
		vector<size_t> Scores;
		float avgScore;
		void AddScore(size_t _sc) {
			Scores.push_back(_sc);
			float sum = 0;
			for (auto it : Scores) {
				sum += it;
			}
			avgScore = sum / Scores.size();
		}
	};
	class StudentsGroup {
	public:
		vector<Student> StudGroup;
		void AddStudent(Student _S) {
			StudGroup.push_back(_S);
		}
		void DelStudent (size_t _n) {
			auto it = StudGroup.begin();
			StudGroup.erase(it + _n);
		}
		void print() {
			for (auto it : StudGroup) {
				cout << it.GroupNumber << ": " << it.StudName.Name << " ";
				if (it.StudName.Patronic.value() != "") cout << it.StudName.Patronic.value() << " ";
				cout << it.StudName.Surname << ". Average score: " << it.avgScore << "\nList of scores: ";
				for (auto its : it.Scores) {
					cout << its << " ";
				}
				cout << endl;
			}
		}
		void print_(vector<Student>& stg) {
			size_t sz = stg.size();
			auto it = stg.begin();
			for (size_t i = 0; i < sz; i++) {
				cout << it->GroupNumber << ": " << it->StudName.Name << " ";
				if (it->StudName.Patronic.value() != "") cout << it->StudName.Patronic.value() << " ";
				cout << it->StudName.Surname << ". Average score: " << it->avgScore << "\nList of scores: ";
				for (auto its : it->Scores) {
					cout << its << " ";
				}
				cout << endl;
			}
		}
		class IRepository {
		public:
			void Save(string _path, StudentsGroup &sg) {
				ofstream out(_path, ios::binary);
				size_t sz = sg.StudGroup.size();
				auto it = sg.StudGroup.begin();
				out << "{\n";
				for (size_t i = 0; i < sz; i++) {
					out << "\"GroupNumber\": \"" << it->GroupNumber << "\",\n";
					out << "\"StudName\": \"" << it->StudName.Name << "\",\n";
					if (it->StudName.Patronic.value() != "") out << "\"Patronic\": \"" << it->StudName.Patronic.value() << "\",\n";
					out << "\"Surname\": \"" << it->StudName.Surname << "\",\n\"avgScore\": " << it->avgScore << ",\n";
					out << "\"Scores\": [ ";
					size_t cnt = 0;
					for (auto its : it->Scores) {
						out << its;
						cnt++;
						if (cnt < it->Scores.size()) out << ", ";
					}
					out << " ]\n";
					++it;
				}
				out << "}\n";
				out.close();
			}
			void Open(string _path, StudentsGroup& newGroup) {
				Student newStudent;
				ifstream in(_path, ios::binary);
				string str;
				while (!in.eof())
				{
					in >> str;
					if (str == "\"GroupNumber\":") {
						in >> str;
						str.erase(0, 1);
						str.erase(str.size() - 2, 2);
						newStudent.GroupNumber = str;
					}
					if (str == "\"StudName\":") {
						in >> str;
						str.erase(0, 1);
						str.erase(str.size() - 2, 2);
						newStudent.StudName.Name = str;
					}
					if (str == "\"Surname\":") {
						in >> str;
						str.erase(0, 1);
						str.erase(str.size() - 2, 2);
						newStudent.StudName.Surname = str;
					}
					if (str == "\"Patronic\":") {
						in >> str;
						str.erase(0, 1);
						str.erase(str.size() - 2, 2);
						newStudent.StudName.Patronic = str;
					}
					if (str == "\"avgScore\":") {
						in >> str;
						str.erase(str.size() - 1, 1);
						newStudent.avgScore = stof(str);
					}
					if (str == "\"Scores\":") {
						in >> str;
						newStudent.Scores.clear();
					m0:	in >> str;
						if (str != "]") {
							if (str[str.size()-1] == ',') str.erase(str.size() - 1, 1);
							newStudent.AddScore(stoi(str));
							goto m0;
						} else newGroup.AddStudent(newStudent);
					}
				}
				return;
			}
		};
	};
}

int main()
{
	mySpace::StudentsGroup grp1234;
	mySpace::Student st1, st2, st3, st4;
	st1.StudName.Name = "Vasya";
	st1.StudName.Surname = "Pupkin";
	st1.GroupNumber = "1234";
	st1.AddScore(4);
	st1.AddScore(3);
	st1.AddScore(5);
	st1.AddScore(5);
	st2.StudName.Name = "Petr";
	st2.StudName.Surname = "Ivanov";
	st2.GroupNumber = "1234";
	st2.AddScore(5);
	st2.AddScore(5);
	st3 = st1;
	st3.StudName.Name = "John";
	st3.StudName.Surname = "Smith";
	st3.AddScore(5);
	st4 = st2;
	st4.StudName.Patronic = "Ivanovich";
	st4.AddScore(2);
	grp1234.AddStudent(st1);
	grp1234.AddStudent(st2);
	grp1234.AddStudent(st3);
	grp1234.AddStudent(st4);
	grp1234.print();
	mySpace::StudentsGroup::IRepository sv;
	sv.Save("d:/l7.json", grp1234);
	grp1234.DelStudent(2);
	cout << "\nFile reading:\n";
	mySpace::StudentsGroup gr;
	sv.Open("d:/l7.json", gr);
	gr.print();
}

