#pragma once
#include<iostream>
#include<Windows.h>
#include "Entities.h"
using namespace std;
void ShowIntro();

void Start() {
	while (true)
	{
		ShowIntro();
		system("cls");
	}
}
int w_count = 2;
Worker** workers = new Worker * [w_count] {
	new Worker{ new char[30] {"elvin123"},new char[30] {"Elvin"}
		,new char[30] {"Programmer"},new CV{9999,6,new char[30] {"C#,C++"},new char[30] {"great"}},NULL,NULL },
		new Worker{ new char[30] {"john26"},new char[30] {"John"}
			,new char[30] {"UI/UX Designer"},new CV{4335,6,new char[30] {"Adobe"},new char[30] {"great"}},NULL,NULL },
};


int e_count = 1;
Employer** employers = new Employer * [e_count] {
	new Employer{ new char[30] {"rafiq123"},new char[30] {"Rafiq Eliyev"},
	new char[30] {"Rafiq MMC"},new AD * [2] {
		new AD{1,new char[30] {".Net Developer"},5500,NULL,NULL},
		new AD{2,new char[30] {"Node.js Developer"},5499,NULL,NULL}
	},2
	}
};

Employer* getEmployerByUsername(const char* username) {
	for (size_t i = 0; i < e_count; i++)
	{
		if (strcmp(employers[i]->username, username) == 0) {
			return employers[i];
		}
	}
	return nullptr;
}

void ShowEmployerMenu() {
	cout << "Add advertisement 1 : " << endl;
	cout << "Show appliers     2 : " << endl;
}

int global_id = 2;

AD* GetNewAD() {
	cin.ignore();
	cin.clear();
	cout << "Enter advertisement title " << endl;
	char* title = new char[100] {};
	cin.getline(title, 100);
	cout << "Enter salary " << endl;
	double salary = 0;
	cin >> salary;
	++global_id;
	AD* ad = new AD{ global_id,title,salary };
	return ad;
}
void AddADToEmployer(Employer* employer, AD* ad) {
	auto temp = new AD * [employer->count + 1] {};
	for (size_t i = 0; i < employer->count; i++)
	{
		temp[i] = employer->ads[i];
	}temp[employer->count] = ad;
	employer->ads = temp;
	temp = nullptr;
	employer->count++;
}

Worker* GetWorkerByUsername(const char* username) {
	for (size_t i = 0; i < w_count; i++)
	{
		if (strcmp(workers[i]->username, username) == 0) {
			return workers[i];
		}
	}
	return nullptr;
}
void ShowWorkerMenu(const Worker* worker) {
	cout << "Advertisements 1 : " << endl;
	cout << "Create your own CV 2 : " << endl;//task
	cout << "Notifications(" << worker->count << ")   3 : " << endl;
	cout << "Observe your cv 4 : " << endl;//task
}
CV* CreateCV() {
	cout << "Enter salary : ";
	double salary = 0;
	cin >> salary;
	cout << "Enter Experience : ";
	int experience = 0;
	cin >> experience;
	cin.clear();
	cin.ignore();
	cout << "Enter languages : ";
	char* languages = new char[100];
	cin.getline(languages, 100);
	cout << "Enter about : ";
	char* about = new char[200];
	cin.getline(about, 200);
	CV* cv = new CV{ salary,experience,languages,about };
	return cv;
}


int GetCountByUsername(Worker**& workers, const int& count, const char* username) {
	int counter = 0;
	for (size_t i = 0; i < count; i++)
	{
		if (strcmp(workers[i]->username, username) == 0) {
			++counter;
		}
	}
	return counter;
}

int index_global = 0;
void ZipAppliers(Worker**& workers, int& count, Worker**& global, int& global_count) {
	int index = 0;
	auto temp = new Worker * [count] {};
	for (size_t i = 0; i < count; i++)
	{
		auto counter = GetCountByUsername(temp, index, workers[i]->username);
		auto counter2 = GetCountByUsername(global, index_global, workers[i]->username);
		if (counter2 == 0) {
			global[index_global++] = workers[i];
		}
		if (counter == 0) {
			temp[index++] = workers[i];
		}
	}
	workers = temp;
	count = index;
	temp = nullptr;
}

void OptimiseEmployerAppliers(Employer*& employer) {
	int global_count = 0;
	for (size_t i = 0; i < employer->count; i++)
	{
		auto appliers = employer->ads[i]->appliers;
		global_count += employer->ads[i]->app_count;
	}
	auto global = new Worker * [global_count] {};
	auto ads = employer->ads;
	for (size_t i = 0; i < employer->count; i++)
	{
		auto appliers = employer->ads[i]->appliers;
		ZipAppliers(appliers, employer->ads[i]->app_count, global, global_count);
		employer->ads[i]->appliers = appliers;
	}
	global_count = index_global;
	employer->appliers = global;
	employer->global_count = global_count;
	global = nullptr;
}

void AddCVToWorker(Worker* worker, CV* cv) {
	worker->cv = cv;
	cv = nullptr;
}
void ShowYourCv(const Worker* worker) {
	cout << "Name : " << worker->fullname << endl;
	cout << "Specialty : " << worker->speciality << endl;
	cout << "Salary : " << worker->cv->salary << endl;
	cout << "Experience : " << worker->cv->experience << endl;
	cout << "Languages : " << worker->cv->languages << endl;
	cout << "About : " << worker->cv->about << endl;
}
void ShowEmployerAD(Employer* employer) {
	for (size_t i = 0; i < employer->count; i++)
	{
		cout << "=========ADS=============" << endl;
		cout << "ID : " << employer->ads[i]->id << endl;
		cout << "TITLE : " << employer->ads[i]->title << endl;
		cout << "SALARY : " << employer->ads[i]->salary << "$" << endl;
	}
}

void ShowAllAds() {
	for (size_t i = 0; i < e_count; i++)
	{
		ShowEmployerAD(employers[i]);
	}
}

AD* getADById(int id) {
	for (size_t i = 0; i < e_count; i++)
	{
		for (size_t k = 0; k < employers[i]->count; k++)
		{
			if (employers[i]->ads[k]->id == id) {
				return employers[i]->ads[k];
			}
		}
	}
	return nullptr;
}

void addApplierToAD(AD* ad, Worker* worker) {
	auto temp = new Worker * [ad->app_count + 1] {};
	for (size_t i = 0; i < ad->app_count; i++)
	{
		temp[i] = ad->appliers[i];
	}temp[ad->app_count] = worker;
	ad->appliers = temp;
	temp = nullptr;
	ad->app_count++;
}

void AddBIDIDToWorker(Worker* worker, int id) {
	auto temp = new int[worker->id_count + 1] {};
	for (size_t i = 0; i < worker->id_count; i++)
	{
		temp[i] = worker->ids[i];
	}
	temp[worker->id_count] = id;
	worker->ids = temp;
	temp = nullptr;
	worker->id_count++;
}

void BidToAds(Worker* worker, int id) {
	auto ad = getADById(id);
	if (ad != nullptr) {
		addApplierToAD(ad, worker);
		AddBIDIDToWorker(worker, id);
		cout << "Your BID Added successfully" << endl;
	}
	else {
		cout << "Not Found" << endl;
	}
}

void ShowWorker(const Worker* worker) {
	cout << "\n===========================\n";
	cout << "Username : " << worker->username << endl;
	cout << "Fullname : " << worker->fullname << endl;
	cout << "Speciality : " << worker->speciality << endl;
	cout << "CV INFO" << endl;
	ShowYourCv(worker);
	cout << "ADS " << endl;
	for (size_t i = 0; i < worker->id_count; i++)
	{
		auto ad = getADById(worker->ids[i]);
		cout << "ID : " << worker->ids[i] << " AD : " << ad->title << endl;
	}
	cout << "\n===========================\n";
}

void ShowAppliers(Employer* employer) {
	for (size_t i = 0; i < employer->global_count; i++)
	{
		ShowWorker(employer->appliers[i]);
	}
}

void NotifyWorker(Worker* worker, Notification* notification) {
	auto temp = new Notification * [worker->count + 1] {};
	for (size_t i = 0; i < worker->count; i++)
	{
		temp[i] = worker->notifications[i];
	}temp[worker->count] = notification;
	worker->notifications = temp;
	temp = nullptr;
	worker->count++;
}

void ShowNotification(Worker* worker) {
	for (size_t i = 0; i < worker->count; i++)
	{
		cout << "NOTIFICATION" << endl;
		cout << "Message : " << worker->notifications[i]->message << endl;
		cout << "DATE : " << worker->notifications[i]->date << endl;
	}
}

void ShowIntro() {
	cout << "==============" << endl;
	cout << "Worker(w) or Employer(e)" << endl;
	char select = ' ';
	cin >> select;
	if (select == 'w') {
		cin.ignore();
		cin.clear();
		cout << "Enter username : " << endl;
		char* username = new char[100] {};
		cin.getline(username, 100);

		auto worker = GetWorkerByUsername(username);
		if (worker != nullptr) {
			ShowWorkerMenu(worker);
			int select = 0;
			cin >> select;
			if (select == 1) {
				ShowAllAds();
				cout << "Select ADs ID for BID : " << endl;
				int id = 0;
				cin >> id;
				BidToAds(worker, id);
				system("pause");

			}
			else if (select == 3) {
				ShowNotification(worker);
				system("pause");
			}
			else if (select == 2) {
				auto cv = CreateCV();
				AddCVToWorker(worker, cv);
			}
			else if (select == 4) {
				ShowYourCv(worker);
				system("pause");
			}
		}
	}
	else if (select == 'e') {
		cin.ignore();
		cin.clear();
		cout << "Enter username : " << endl;
		char* username = new char[50] {};
		cin.getline(username, 50);

		auto employer = getEmployerByUsername(username);
		if (employer != nullptr) {
			OptimiseEmployerAppliers(employer);
			ShowEmployerMenu();
			int select = 0;
			cin >> select;
			if (select == 1) {
				auto ads = GetNewAD();
				AddADToEmployer(employer, ads);
			}
			else if (select == 2) {
				ShowAppliers(employer);
				cin.ignore();
				cin.clear();
				cout << "Enter Applier username : " << endl;
				char* username = new char[100] {};
				cin.getline(username, 100);
				auto worker = GetWorkerByUsername(username);
				if (worker == nullptr) {
					cout << "Not Found" << endl;
				}
				else {
					cout << "Enter Message : " << endl;
					char* message = new char[300] {};
					cin.getline(message, 300);
					Notification* notification = new Notification{ message,__DATE__ };
					NotifyWorker(worker, notification);
					cout << "Your response sent successfully" << endl;
				}
			}
		}
		else {
			cout << "Not found" << endl;
			system("color 4");
			system("pause");
			system("color 7");
		}
	}
	else {
		cout << "Invalid selection" << endl;
	}

}

#pragma once
#pragma once
