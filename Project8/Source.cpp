#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Fio {
	char last_name[20];
	char first_name[20];
	char patronimyc[20];
};

struct Date {
	char day[3];
	char mon[3];
	char year[5];
};

struct Adres {
	char city[20];
	char street[20];
	int house;
	int flat;
};

struct Base {
	Fio fio;
	Date date;
	char educ;
	char familystatus;
	int count_child;
	char job;
	Adres adres;
	int phone;
};

struct Base_2
{
	Fio fio;
	int age;
	Adres adres;
	char job;
	char sex;
	int count_child;
	char familystatus;
};

void text_to_bin(ifstream& in, ofstream& out) {
	Base base;
	while (!in.eof()) {
		in >> base.fio.last_name;
		in >> base.fio.first_name;
		in >> base.fio.patronimyc;
		in.get();
		for (int i = 0; i < 2; i++)
			base.date.day[i] = in.get();
		for (int i = 0; i < 2; i++)
			base.date.mon[i] = in.get();
		for (int i = 0; i < 4; i++)
			base.date.year[i] = in.get();
		in >> base.educ;
		in >> base.familystatus;
		in >> base.count_child;
		in >> base.job;
		in >> base.adres.city;
		in >> base.adres.street;
		in >> base.adres.house;
		in >> base.adres.flat;
		in >> base.phone;
		out.write((char*)&base, sizeof(base));
	}
}
void print_base(Base base) {
	cout << base.fio.last_name << " ";
	cout << base.fio.first_name << " ";
	cout << base.fio.patronimyc << " ";
	cout << base.date.day[0];
	cout << base.date.day[1];
	cout << base.date.mon[0];
	cout << base.date.mon[1];
	cout << base.date.year[0];
	cout << base.date.year[1];
	cout << base.date.year[2];
	cout << base.date.year[3] << " ";
	cout << base.educ << " ";
	cout << base.familystatus << " ";
	cout << base.count_child << " ";
	cout << base.job << " ";
	cout << base.adres.city << " ";
	cout << base.adres.street << " ";
	cout << base.adres.house << " ";
	cout << base.adres.flat << " ";
	cout << base.phone << endl;
}
void bin_to_text(ifstream& in) {
	Base base;
	while (!in.eof()) {
		in.read((char*)&base, sizeof(base));
		print_base(base);
	}
}

int average_number_of_children(ifstream& in) {
	Base base;
	int count_people = 0;
	int count_children = 0;
	while (!in.eof())
	{
		in.read((char*)&base, sizeof(base));
		count_people++;
		count_children += base.count_child;
	}
	int aver_num_of_child = count_children / count_people;
	return aver_num_of_child;
}

int age_people(Base base, Date date, int mon, int day) {
	int age;

	if ((base.date.mon[0] - '0') * 10 + (base.date.mon[1] - '0') == mon && (base.date.day[0] - '0') * 10 + (base.date.day[1] - '0') <= day || ((base.date.mon[0] - '0') * 10 + (base.date.mon[1] - '0') < mon))
		age = 2023 - ((base.date.year[0] - '0') * 1000 + (base.date.year[1] - '0') * 100 + (base.date.year[2] - '0') * 10 + (base.date.year[3] - '0'));
	if ((base.date.mon[0] - '0') * 10 + (base.date.mon[1] - '0') >= mon)
		age = 2023 - ((base.date.year[0] - '0') * 1000 + (base.date.year[1] - '0') * 100 + (base.date.year[2] - '0') * 10 + (base.date.year[3] - '0')) - 1;
	return age;
}

void chosen_people(ifstream& in, ofstream& out, int aver_num_of_child, int mon, int day) {
	Base base;
	Base_2 base_new;
	int age;
	while (!in.eof())
	{
		in.read((char*)&base, sizeof(base));
		age = age_people(base, base.date, mon, day);
		if (age > 35 && base.count_child < aver_num_of_child)
		{
			base_new.fio = base.fio;
			base_new.age = age;
			base_new.adres = base.adres;
			base_new.job = base.job;
			base_new.sex = 'ћ';
			base_new.count_child = base.count_child;
			base_new.familystatus = base.familystatus;
			out.write((char*)&base_new, sizeof(base_new));
		}
	}
}

char* fio_to_arr(Fio fio) {
	char* arr = new char[25];
	int i = 0;
	while (fio.last_name[i] != '\0') {
		arr[i] = fio.last_name[i++];
	}
	arr[i++] = ' ';
	arr[i++] = fio.first_name[0];
	arr[i++] = '.';
	arr[i++] = ' ';
	arr[i++] = fio.patronimyc[0];
	arr[i++] = '.';
	arr[i] = '\0';
	return arr;
}

void base_people(ifstream& in, ofstream& out) {
	Base_2 base;
	int mid_age = 0, count = 0, max_age = 0;
	out << " | " << setfill('-') << setw(111) << " | " << endl << setfill(' ');
	out << " | " << setw(22) << left << "Last Name" << " | " << setw(32) << left << "City" << " | " << setw(3) << left << "Age" << " | " << setw(3) << left << "Job" << " | " << setw(3) << left << "Sex" << " | " << setw(14) << left << "Count children" << " | " << setw(13) << left << "Family status" " |" << endl;
	out << setfill('-') << setw(111) << " | " << " | " << endl << setfill(' ');
	while (!in.eof()) {
		in.read((char*)&base, sizeof(base));
		out << " | " << setw(22) << left << fio_to_arr(base.fio);
		out << " | " << setw(32) << base.adres.city;
		out << " | " << setw(3) << base.age;
		out << " | " << setw(3) << base.job;
		out << " | " << setw(3) << base.sex;
		out << " | " << setw(14) << base.count_child;
		out << " | " << setw(13) << base.familystatus << " |";
		out << endl;
		out << setfill('-') << setw(111) << " | " << " | " << endl << setfill(' ');
	}
}

int main() {
	setlocale(LC_ALL, "ru");

	ifstream in("base.txt");
	ofstream out("base.bin", ios::binary);

	text_to_bin(in, out);

	in.close();
	out.close();



	ifstream in_check("base.bin", ios::binary);
	bin_to_text(in_check);
	in_check.close();

	ifstream in2("base.bin", ios::binary);
	ofstream out2("chosen_people.bin", ios::binary);

	int aver_num_of_child = average_number_of_children(in2);
	in2.close();
	ifstream in22("base.bin", ios::binary);

	int mon, day;
	cout << "¬ведите число относительно которого считать возраст людей(мес€ц и день): ";
	cin >> mon >> day;
	chosen_people(in22, out2, aver_num_of_child, mon, day);

	in22.close();
	out2.close();



	ifstream in3("chosen_people.bin", ios::binary);
	ofstream out3("base_people.txt");

	base_people(in3, out3);

	in3.close();
	out3.close();
}