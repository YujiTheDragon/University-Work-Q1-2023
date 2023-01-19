#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

class TV
{
private:
	string Manufacturer;
	int ScreenSize;
	bool isSmartTV;
public:
	TV()
	{
		Manufacturer = "";
		ScreenSize = 0;
		isSmartTV = false;
	}
	TV(string Manufacturer, int ScreenSize)
	{
		this->Manufacturer = Manufacturer;
		this->ScreenSize = ScreenSize;
	}
	TV(int ScreenSize)
	{
		this->ScreenSize = ScreenSize;
	}
	TV(const TV& sr)
	{
		this->Manufacturer = sr.Manufacturer;
		this->ScreenSize = sr.ScreenSize;
		this->isSmartTV = sr.isSmartTV;
	}

	string GetManufacturer()const
	{
		return Manufacturer;
	}
	int GetScreenSize()const
	{
		return ScreenSize;
	}
	bool GetisSmartTV()const
	{
		return isSmartTV;
	}

	friend ostream& operator<<(ostream& out, TV sr)
	{
		out << "TV: " << sr.Manufacturer << " " << sr.ScreenSize;
		return out;
	}
	friend istream& operator>>(istream& in, TV& sr)
	{
		in >> sr.Manufacturer >> sr.ScreenSize;
		return in;
	}
	TV& operator=(const TV& o)
	{
		this->Manufacturer = o.Manufacturer;
		this->ScreenSize = o.ScreenSize;
		this->isSmartTV = o.isSmartTV;
		return (*this);
	}

	bool operator==(const TV& sr)const
	{
		if (this->ScreenSize == sr.ScreenSize) return true;

		else return false;
	}
	bool operator<(const TV& tv)const
	{
		if (this->ScreenSize < tv.ScreenSize) return true;
		else return false;
	}
};

template<typename K, typename V>
ostream& operator<<(ostream& out, const map<K, V>& the_map) {

	for (const auto& kv : the_map) {
		out << "    " << kv.first << ": " << kv.second << "," << endl;
	}
	return out;
}

class TVStore
{
private:
	vector <TV> TVSetSales;
public:
	TVStore()
	{};
	TVStore(vector<TV>& tvset)
	{
		this->TVSetSales = tvset;
	}
	TVStore(const string& FileName)
	{
		ifstream File;
		File.open(FileName);
		if (!File)
		{
			cout << "Could not open file!";
		}
		else
		{
			TV kek;
			cout << "Opening the file!" << endl;
			while (!File.eof())
			{
				File >> kek;
				this->TVSetSales.push_back(kek);
			}
			File.close();
			TVSetSales.pop_back();

		}

	}

	void ReadIn(istream& istream)
	{
		TV kek;
		cout << "Opening the file!" << endl;
		while (!istream.eof())
		{
			istream >> kek;
			this->TVSetSales.push_back(kek);

		}

	}
	vector <TV> GetVector()
	{
		return TVSetSales;
	}

	map <string, int> CountSalesByManufacturer()
	{
		map<string, int> SalesByManufacturer;

		for (TV tv : TVSetSales)
		{
			SalesByManufacturer[tv.GetManufacturer()]++;
		}
		return SalesByManufacturer;
	}

	map <int, int> CountSalesBySize()
	{
		map<int, int> SalesBySize;

		for (TV tv : TVSetSales)
		{
			SalesBySize[tv.GetScreenSize()]++;
		}
		return SalesBySize;
	}

	friend ostream& operator<<(ostream& out, TVStore& sr)
	{
		for (TV tv : sr.TVSetSales)
		{
			out << tv << endl;
		}
		return out;
	}

	void MaxSalesByManufacturer()
	{
		int max = 0;
		string maxManufacturer;
		for (auto tv : CountSalesByManufacturer())
		{
			if (tv.second > max)
			{
				max = tv.second;
				maxManufacturer = tv.first;
			}
		}

		cout << "Max sales by producer: " << maxManufacturer << " " << max << endl;
	}

	void MaxSalesBySize()
	{
		int max = 0, maxSize = 0;

		for (auto tv : CountSalesBySize())
		{
			if (tv.second > max)
			{
				max = tv.second;
				maxSize = tv.first;
			}
		}

		cout << "Max sales by Screen Size: " << maxSize << " " << max << endl;
	}
};

int main()
{
	TVStore TVS = TVStore("C:\\Users\\YujiTheDragon\\Desktop\\TVs.txt");
	cout << TVS;
	cout << TVS.CountSalesByManufacturer();
	cout << endl << TVS.CountSalesBySize();
	TVS.MaxSalesByManufacturer();
	TVS.MaxSalesBySize();
}


