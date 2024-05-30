#pragma once

class DataManager {
public:
	virutal void saveData(const std::string& address);
	virutal void loadData(const std::string& address);
};

class DataWorekres : public DataManager {
	//TODO
};

class DataTransactions : public DataManager {
	//TODO
};

class DataItems : public DataManager {
	//TODO
};