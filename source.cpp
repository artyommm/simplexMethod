#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<istream>
#include<vector>
using namespace std;

long long NOD(long long a, long long b);
//числитель numerator
//знаменатель denominator
class Common_fraction
{
protected:
	long long numerator;
	long long denominator;
public:
	Common_fraction operator + (Common_fraction drob2);
	Common_fraction operator - (Common_fraction drob2);
	Common_fraction operator * (Common_fraction drob2);
	Common_fraction operator * (long long value);
	Common_fraction operator / (Common_fraction drob2);
	Common_fraction operator + (int value);
	Common_fraction operator - (int value);
	Common_fraction operator * (int value);
	Common_fraction operator / (int value);
	friend std::ostream& operator<< (std::ostream &out, const Common_fraction &drob);
	friend std::istream& operator>> (std::istream &in, Common_fraction &drob);
	bool operator == (Common_fraction drob2);
	bool operator != (Common_fraction drob2);
	bool operator > (Common_fraction drob2);
	bool operator >= (Common_fraction drob2);
	bool operator < (Common_fraction drob2);
	bool operator <= (Common_fraction drob2);
	bool operator == (int number);
	bool operator != (int number);
	bool operator > (int number);
	bool operator >= (int number);
	bool operator < (int number);
	bool operator <= (int number);
	void operator = (int value);
	void operator = (const Common_fraction drob2);
	Common_fraction operator +=(int value);
	Common_fraction operator -=(int value);
	Common_fraction operator *=(int value);
	Common_fraction operator /=(int value);
	Common_fraction operator +=(Common_fraction drob2);
	Common_fraction operator -=(Common_fraction drob2);
	Common_fraction operator *=(Common_fraction drob2);
	Common_fraction operator /=(Common_fraction drob2);
	Common_fraction operator - ();//оператор смены знака
	friend Common_fraction fractional_part(Common_fraction number);
	void setValue(long long numerator, long long denominator);
	long long getDenominator()
	{
		return this->denominator;
	}
	long long getNumerator()
	{
		return this->numerator;
	}
};

void enter_data(vector<vector<Common_fraction>> &arr, int str, int vars, int limits, string *&znak, bool &maximizatsiya)
{
	cout << "----------ВВОД ДАННЫХ----------" << endl;
	//string *znak = new string[limits];//массив для определения знака неравенства
	maximizatsiya = false;
	for (int i = 0; i < limits; i++)
	{
		cout << "Свободный член " << i + 1 << "-го ограничения: ";
		cin >> arr[i][1];
		cout << "Введите коэффициенты для " << i + 1 << "-го ограничения" << endl;
		for (int j = 0; j < vars; j++)
		{
			cout << "При х" << j + 1 << ": ";
			cin >> arr[i][j + 2];//1 столбик для базовых пер-ых, второй св.чл, 3-й для коэф-та x1
		}
		cout << "Знак " << i + 1 << "-го ограничения: ";
		cin >> znak[i];
	}

	cout << "Свободный член функции равен ";
	cin >> arr[str - 1][1];
	cout << "Коэффициенты для функции" << endl;
	for (int j = 0; j < vars; j++)
	{
		cout << "При х" << j + 1 << ": ";
		cin >> arr[str - 1][j + 2];
	}

	cout << "Какую задачу будем решать? \n1 - min \n2 - max" << endl;
	int min_or_max = 0;
	cin >> min_or_max;
	if (min_or_max == 1)
	{
		for (int j = 0; j < vars; j++)
		{
			arr[str - 1][j + 2] = -(arr[str - 1][j + 2]);//если решаем задачу минимизации просто меняем знак
		}
		cout << "Решаем задачу минимизации!" << endl;
		maximizatsiya = false;
	}
	else if (min_or_max == 2)
	{
		cout << "Решаем задачу максимизации!" << endl;
		maximizatsiya = true;
	}
}

void print_tabl(vector<vector<Common_fraction>> &arr, int str, int cols)//В С-методе не будет выводиться буковка T
{
	cout << "----------ВЫВОД ТАБЛИЦЫ----------" << endl;
	for (int i = 0; i < str; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i == str - 1 && j == 0)
				cout << "f\t";
			else
				cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
}

void print_tabl_DStep_Method(vector<vector<Common_fraction>> &arr, int str, int cols)
{
	cout << "----------ВЫВОД ТАБЛИЦЫ----------" << endl;
	for (int i = 0; i < str; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i == str - 2 && j == 0)
				cout << "f\t";
			else if (i == str - 1 && j == 0)
				cout << "T\t";
			else
				cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
}

int find_main_col(vector<vector<Common_fraction>> &arr, int str, int cols)
{
	int mainCol = -1;
	Common_fraction maxValue;
	maxValue = 0;
	for (int i = 2; i < cols; i++)
	{
		if (arr[str - 1][i] > maxValue)//в двухэтапном методе смотрим на функцию T
		{
			maxValue = arr[str - 1][i];
			mainCol = i;
		}
	}
	return mainCol;
}

int find_main_str(vector<vector<Common_fraction>> &arr, int lims, int main_col)//ВОЗМОЖНО БУДЕТ ОШИБКА
{
	int mainStr = -1;
	Common_fraction minValue;
	minValue = 0;
	for (int i = 0; i < lims; i++)
	{
		if (arr[i][main_col] != 0 && (arr[i][1] / arr[i][main_col]) >= 0)//если (свободный член/член разрешающего столбца) >0
		{
			if (minValue == 0)//если минимально значение ещё не установлено - устанавливаем
			{
				minValue = arr[i][1] / arr[i][main_col];
				mainStr = i;
			}
			else if ((arr[i][1] / arr[i][main_col]) < minValue && (arr[i][1] / arr[i][main_col]) != 0)//если было установлено, то сравниваем
			{
				minValue = arr[i][1] / arr[i][main_col];
				mainStr = i;
			}
			else if (arr[i][1] == 0 && arr[i][main_col]>0 && minValue > 0)
			{
				minValue = 0;
				mainStr = i;
				break;
			}
		}
	}
	return mainStr;
}

vector<vector<Common_fraction>> simple_Simplex_method(vector<vector<Common_fraction>> arr, int str, int cols, bool &inform)//просто для пересчёта когда уже есть ИОР
{
	Common_fraction zero;
	zero = 0;
	vector<vector<Common_fraction>> help_table(str, vector<Common_fraction>(cols, zero));

	inform = false;//по умолчанию false

	bool **checked = new bool*[str];//создаём вспомогательную табличку для проверки пересчитали ли мы этот элемент
	for (int i = 0; i < str; i++)
	{
		checked[i] = new bool[cols];
	}
	for (int i = 0; i < str; i++)//устанавливаем по дефолту false
	{
		for (int j = 0; j < cols; j++)
		{
			checked[i][j] = false;
		}
	}
	for (int i = 0; i < str; i++)//копируем все данные в табличку для помощи в пересчёте
	{
		for (int j = 0; j < cols; j++)
		{
			help_table[i][j] = arr[i][j];
		}
	}

	int mainCol = find_main_col(arr, str, cols);
	int mainStr = -1;
	if (mainCol != -1)
	{
		mainStr = find_main_str(arr, str - 1, mainCol);
		while (mainCol != -1 && mainStr != -1)
		{
			mainCol = find_main_col(help_table, str, cols);
			mainStr = find_main_str(help_table, str - 1, mainCol);//ищем главную строку но не трогаем две последние

			help_table[mainStr][0] = mainCol - 1;//выводим из базиса старую переменную и вводим новую

			for (int i = 1; i < cols; i++)//все элементы разрешающей строки делим на разрешающий элемент
			{
				help_table[mainStr][i] = help_table[mainStr][i] / arr[mainStr][mainCol];
				checked[mainStr][i] = true;
			}

			for (int i = 0; i < str; i++)
			{
				for (int j = 1; j < cols; j++)
				{
					if (help_table[i][0] == j - 1 && i != str - 1 && i != str - 2)//если строка и стобец базисной переменной пересекается и это не строка функции ставим 1 
					{
						help_table[i][j] = 1;
						checked[i][j] = true;
						for (int k = 0; k < str; k++)//ставим в столбике с базисом остальные все нули
						{
							if (checked[k][j] == false)//если эта не та единичка которую мы поставили
							{
								help_table[k][j] = 0;
								checked[k][j] = true;
							}
						}
					}
					else
					{
						if (checked[i][j] == false)
						{
							help_table[i][j] = ((arr[i][j] * arr[mainStr][mainCol]) - (arr[mainStr][j] * arr[i][mainCol])) / arr[mainStr][mainCol];
							checked[i][j] = true;
						}
					}
				}
			}

			for (int i = 0; i < str; i++)//устанавливаем по дефолту опять false
			{
				for (int j = 0; j < cols; j++)
				{
					checked[i][j] = false;
				}
			}

			/*print_tabl(help_table, str, cols);*/
			mainCol = find_main_col(help_table, str, cols);
			if (mainCol != -1)
			{
				mainStr = find_main_str(help_table, str - 1, mainCol);//ищем главную строку но не трогаем две последние
			}
			for (int q = 0; q < str; q++)
			{
				for (int p = 0; p < cols; p++)
				{
					arr[q][p] = help_table[q][p];
				}
			}
		}
	}
	print_tabl(help_table, str, cols);
	if (mainCol == -1 || mainStr == -1)
	{
		if (mainCol == -1)
		{
			cout << "Решение оптимально!" << endl;
			inform = true;//оптимальное решение найдено
		}
		else if (mainStr == -1)
		{
			cout << "Решения не существует!" << endl;
			inform = false;//не найдено оптимальное решение
		}
	}

	return help_table;
}

vector<vector<Common_fraction>> S_method_for_DStep(vector<vector<Common_fraction>> arr, int str, int cols, bool &inform)//ОТЛИЧАЕТСЯ ТЕМ ЧТО МЫ НЕ БЕРЁМ ДВЕ ПОСЛЕДНИХ СТРОКИ ПРИ ОПРЕДЕЛЕНИИ РАЗРЕШАЮЩЕЙ
{
	Common_fraction zero;
	zero = 0;
	vector<vector<Common_fraction>> help_table(str, vector<Common_fraction>(cols, zero));

	inform = false;

	bool **checked = new bool*[str];//создаём вспомогательную табличку для проверки пересчитали ли мы этот элемент
	for (int i = 0; i < str; i++)
	{
		checked[i] = new bool[cols];
	}
	for (int i = 0; i < str; i++)//устанавливаем по дефолту false
	{
		for (int j = 0; j < cols; j++)
		{
			checked[i][j] = false;
		}
	}
	for (int i = 0; i < str; i++)//копируем все данные в табличку для помощи в пересчёте
	{
		for (int j = 0; j < cols; j++)
		{
			help_table[i][j] = arr[i][j];
		}
	}

	int mainCol = find_main_col(arr, str, cols);
	int mainStr = -1;
	if (mainCol != -1)
	{
		mainStr = find_main_str(arr, str - 1, mainCol);
		while (mainCol != -1 && mainStr != -1)
		{
			mainCol = find_main_col(help_table, str, cols);
			mainStr = find_main_str(help_table, str - 2, mainCol);//ищем главную строку но не трогаем две последние

			help_table[mainStr][0] = mainCol - 1;//выводим из базиса старую переменную и вводим новую

			for (int i = 1; i < cols; i++)//все элементы разрешающей строки делим на разрешающий элемент
			{
				/*help_table[mainStr][i] /= arr[mainStr][mainCol];*/
				help_table[mainStr][i] = help_table[mainStr][i] / arr[mainStr][mainCol];
				checked[mainStr][i] = true;
			}

			for (int i = 0; i < str; i++)
			{
				for (int j = 1; j < cols; j++)
				{
					if (help_table[i][0] == j - 1 && i != str - 1 && i != str - 2)//если строка и стобец базисной переменной пересекается и это не строка функции ставим 1 
					{
						help_table[i][j] = 1;
						checked[i][j] = true;
						for (int k = 0; k < str; k++)//ставим в столбике с базисом остальные все нули
						{
							if (checked[k][j] == false)//если эта не та единичка которую мы поставили
							{
								help_table[k][j] = 0;
								checked[k][j] = true;
							}
						}
					}
					else
					{
						if (checked[i][j] == false)
						{
							help_table[i][j] = ((arr[i][j] * arr[mainStr][mainCol]) - (arr[mainStr][j] * arr[i][mainCol])) / arr[mainStr][mainCol];
							checked[i][j] = true;
						}
					}
				}
			}

			for (int i = 0; i < str; i++)//устанавливаем по дефолту опять false
			{
				for (int j = 0; j < cols; j++)
				{
					checked[i][j] = false;
				}
			}

			print_tabl_DStep_Method(help_table, str, cols);
			mainCol = find_main_col(help_table, str, cols);
			if (mainCol != -1)
			{
				mainStr = find_main_str(help_table, str - 1, mainCol);//ищем главную строку но не трогаем две последние
			}
			for (int q = 0; q < str; q++)
			{
				for (int p = 0; p < cols; p++)
				{
					arr[q][p] = help_table[q][p];
				}
			}
		}
	}
	print_tabl_DStep_Method(help_table, str, cols);
	if (mainCol == -1 || mainStr == -1)
	{
		if (mainCol == -1 && help_table[str - 1][1] == 0)
		{
			cout << "ИОР найдено!" << endl;
			inform = true;//ИОР найдено
		}
		else if (mainStr == -1 || help_table[str - 1][1] != 0)
		{
			cout << "ИОР не существует!" << endl;
			inform = false;//не существует ИОР
		}
	}

	return help_table;
}

vector<vector<Common_fraction>> reduction_to_equalities(vector<vector<Common_fraction>> arr, int str, int limits, int &vars, string *znak)//переход к равенствам
{
	Common_fraction zero;
	zero = 0;
	int count_new_vars = 0;//счётчик новых переменных (НЕ ИСКУССТВЕННЫХ)
	bool *add_new_var = new bool[limits];//чекнем добавляли ли мы в это уравнение переменную
	int *add_new_var_number = new int[limits];//если добавляли, то запомним её номер


	for (int i = 0; i < limits; i++)//изначально конечно же нет
	{
		add_new_var[i] = false;
		add_new_var_number[i] = NULL;//в номере будет нал
	}

	for (int i = 0; i < limits; i++)
	{
		if (znak[i] == ">")
		{
			count_new_vars++;//ДОБАВЛЯЕМ ПЕРЕМЕННУЮ
			add_new_var[i] = true;
			add_new_var_number[i] = vars + count_new_vars;
		}
		else if (znak[i] == ">=")
		{
			count_new_vars++;//ДОБАВЛЯЕМ ПЕРЕМЕННУЮ
			add_new_var[i] = true;
			add_new_var_number[i] = vars + count_new_vars;
		}
		else if (znak[i] == "<")
		{
			count_new_vars++;//ДОБАВЛЯЕМ ПЕРЕМЕННУЮ
			add_new_var[i] = true;
			add_new_var_number[i] = vars + count_new_vars;
		}
		else if (znak[i] == "<=")
		{
			count_new_vars++;//ДОБАВЛЯЕМ ПЕРЕМЕННУЮ
			add_new_var[i] = true;
			add_new_var_number[i] = vars + count_new_vars;
		}
	}

	vector<vector<Common_fraction>> table_for_method(str + 1, vector<Common_fraction>(vars + count_new_vars + 2, zero));

	//договоримся что последняя строка - ф-ция T, предпоследняя - f
	for (int i = 0; i < str + 1; i++)
	{
		if (i < str)//свободный член у функции по знаку оставляем таким же, а переменные переносим с противоположным знаком (для min)
		{
			table_for_method[i][1] = arr[i][1];
		}
		for (int j = 0; j < vars + count_new_vars + limits + 2; j++)
		{
			//скопировать старые данные в новую + данные о добавленных переменных + данные о искусственных элементах

			if (i < str && j < vars)//переписали данные о переменных которые уже были
			{
				if (i == str - 1)
				{
					if (arr[i][j + 2] == 0)
					{
						table_for_method[i][j + 2] = arr[i][j + 2];//чтобы в таблице не выводило -0
					}
					else
					{
						table_for_method[i][j + 2] = (arr[i][j + 2]);//переменные с противоположным знаком
					}
				}
				else
				{
					table_for_method[i][j + 2] = arr[i][j + 2];
				}
			}
			else if (i < str && (j >= vars && j < vars + count_new_vars))//если это добавленная переменная (естественная)
			{
				if (add_new_var[i] == true && add_new_var_number[i] == j + 1)//если в это уравнение добавлялась переменная и её номер совпадает с той которую мы проверяем
				{
					if (znak[i] == ">" || znak[i] == ">=")
					{
						table_for_method[i][j + 2] = -1;
					}
					else if (znak[i] == "<" || znak[i] == "<=")
					{
						table_for_method[i][j + 2] = 1;
					}
				}
				else if (add_new_var[i] == true && add_new_var_number[i] != j + 1 || add_new_var[i] == false)//если в это уравнение не добавлялась эта переменная ставим 0
				{
					table_for_method[i][j + 2] = 0;
				}
				else if (i == str - 1)//если это строка функции f 
				{
					table_for_method[i][j + 2] = 0;
				}
			}
		}
	}
	vars = vars + count_new_vars;
	return table_for_method;
	delete[] add_new_var_number;
	delete[] add_new_var;

}

vector<vector<Common_fraction>> Double_step_method(vector<vector<Common_fraction>> arr, int str, int limits, int vars, bool &inform)
{
	Common_fraction zero;
	zero = 0;

	int *add_synthetic_var_number = new int[limits];//номер искусственной переменной


	for (int i = 0; i < limits; i++)
	{
		add_synthetic_var_number[i] = vars + (i + 1);//номера искусственных переменных пойдут после всех естественных
	}
	//потом добавим искусственные переменные просто ко ВСЕМ ограничениям чтобы не парица, т.е.
	//прибавится стока переменных скока ограничений )0
	//и того у нас столбцов
	//потому что идёт под базис и под свободный член

	vector<vector<Common_fraction>> table_for_method(str + 1, vector<Common_fraction>(vars + limits + 2, zero));

	//договоримся что последняя строка - ф-ция T, предпоследняя - f
	for (int i = 0; i < str + 1; i++)
	{
		if (i < str)//свободный член у функции по знаку оставляем таким же, а переменные переносим с противоположным знаком (для min)
		{
			table_for_method[i][1] = arr[i][1];
		}
		for (int j = 0; j < vars +  limits + 2; j++)
		{
			//скопировать старые данные в новую + данные о добавленных переменных + данные о искусственных элементах

			if (i < str && j < vars)//переписали данные о переменных которые уже были
			{
				if (i == str - 1)
				{
					if (arr[i][j + 2] == 0)
					{
						table_for_method[i][j + 2] = arr[i][j + 2];//чтобы в таблице не выводило -0
					}
					else
					{
						table_for_method[i][j + 2] = (arr[i][j + 2]);//переменные с противоположным знаком
					}
				}
				else
				{
					table_for_method[i][j + 2] = arr[i][j + 2];
				}
			}
			else if (i < str + 1 && (j >= vars && j <vars + limits))//если это искусственная переменная
			{
				if (add_synthetic_var_number[i] == j + 1)
				{
					table_for_method[i][j + 2] = 1;
					table_for_method[i][0] = add_synthetic_var_number[i];//заносим её в базис

				}
				else
				{
					table_for_method[i][j + 2] = 0;
				}
			}
		}
	}

	for (size_t j = 1; j < vars + 2; j++)
	{
		for (size_t i = 0; i < str - 1; i++)
		{
			table_for_method[str][j] = table_for_method[str][j] + table_for_method[i][j];
		}
	}

	/*print_tabl_DStep_Method(table_for_method, str + 1, vars + limits + 2);*/

	table_for_method = S_method_for_DStep(table_for_method, str + 1, vars + limits + 2, inform);

	vector<vector<Common_fraction>> table_for_return(str, vector<Common_fraction>(vars + 2, zero));
	//теперь скопируем все данные туда
	for (int i = 0; i < str; i++)
	{
		for (int j = 0; j < vars + 2; j++)
		{
			if (!(i == str - 1 && j == 0))//если это не ячейка где должна быть буковка f (функция)
				table_for_return[i][j] = table_for_method[i][j];
		}
	}

	return table_for_return;

	delete[] add_synthetic_var_number;

}

vector<vector<Common_fraction>> GomoriMethod(vector<vector<Common_fraction>> input_arr, int &num_of_str, int &lims, int &num_of_vars, string *&znak, bool &inform)
{
	Common_fraction zero;
	zero = 0;
	//vector<vector<Common_fraction>> help_table(str, vector<Common_fraction>(cols, zero));
	Common_fraction max_fract_part;
	max_fract_part = 0;
	inform = false;
	int number_of_lim_with_max_fract_part = -1;//номер ограничения с максимальной дробной частью
	for (int i = 0; i < lims; i++)
	{
		if (fractional_part(input_arr[i][1]) > max_fract_part)
		{
			max_fract_part = fractional_part(input_arr[i][1]);
			number_of_lim_with_max_fract_part = i;
		}
	}
	if (number_of_lim_with_max_fract_part != -1)
	{
		lims++;
		string *new_znak = new string[lims];//массив для определение знака неравенства + НОВОЕ НЕРАВЕНСТВО
		for (int i = 0; i < lims; i++)
		{
			if (i == lims - 1)//если это строка с новым неравенством
			{
				new_znak[i] = ">=";//пусть неравенство в виде a1x1+a2x2+...>=C
			}
			else
			{
				new_znak[i] = "=";
			}
		}
		delete[] znak;
		znak = new_znak;

		num_of_str++;
		vector<vector<Common_fraction>> Gomori_table(num_of_str, vector<Common_fraction>(num_of_vars + 2, zero));
		////терь перенесём всё в новую таблицу

		for (int i = 0; i < num_of_str; i++)
		{
			for (int j = 0; j < num_of_vars + 2; j++)//последнюю строку ячейку где буква f и последнее ограничение не трогаем ( в базис тож нич не заносим )
			{
				if ((i == num_of_str && j == 0))//если это ячейка где должен быть символ f 
					continue;
				else if (i == num_of_str - 2)//строка нового ограничения
				{
					Gomori_table[i][j] = fractional_part(input_arr[number_of_lim_with_max_fract_part][j]);
					if (Gomori_table[i][j] != 0)
					{
						inform = true;
					}
				}
				else if (i == num_of_str - 1)//если это строка функции f
				{
					if (j == 1)
						Gomori_table[i][j] = input_arr[i - 1][j];
					else
						Gomori_table[i][j] = (input_arr[i - 1][j]);
				}
				else
					Gomori_table[i][j] = input_arr[i][j];
			}
		}
		//print_tabl(Gomori_table, num_of_str, num_of_vars + 2);
		//теперь нужно сделать в строке num_of_str - 1 все коэффициенты целыми
		if (inform == true)
		{
			long long max_denominator = -1;
			while (max_denominator != 1)
			{
				for (int i = 1; i < num_of_vars + 2; i++)
				{
					if (Gomori_table[num_of_str - 2][i].getNumerator() != 0 && Gomori_table[num_of_str - 2][i].getDenominator() > max_denominator)
					{
						max_denominator = Gomori_table[num_of_str - 2][i].getDenominator();//num_of_str-1 - строка функции, num_of_str-2 - строка нового ограничения
					}
				}

				for (int i = 1; i < num_of_vars + 2; i++)
				{
					if (Gomori_table[num_of_str - 2][i].getNumerator() != 0)
					{
						Gomori_table[num_of_str - 2][i] = Gomori_table[num_of_str - 2][i] * max_denominator;
					}
				}
				print_tabl(Gomori_table, num_of_str, num_of_vars + 2);

				max_denominator = -1;
				for (int i = 1; i < num_of_vars + 2; i++)
				{
					if (Gomori_table[num_of_str - 2][i].getNumerator() != 0 && Gomori_table[num_of_str - 2][i].getDenominator() > max_denominator)
					{
						max_denominator = Gomori_table[num_of_str - 2][i].getDenominator();//num_of_str-1 - строка функции, num_of_str-2 - строка нового ограничения
					}
				}

			}

			//print_tabl(Gomori_table, num_of_str, num_of_vars + 2);
			vector<vector<Common_fraction>> table_for_answer;
			table_for_answer = reduction_to_equalities(Gomori_table, num_of_str, lims, num_of_vars, znak);
			//print_tabl(table_for_answer, num_of_str, num_of_vars + 2);
			table_for_answer = Double_step_method(table_for_answer, num_of_str, lims, num_of_vars, inform);
			print_tabl(table_for_answer, num_of_str, num_of_vars + 2);
			table_for_answer = simple_Simplex_method(table_for_answer, num_of_str, num_of_vars + 2, inform);
			print_tabl(table_for_answer, num_of_str, num_of_vars + 2);//отсюда размер str X cols

			return table_for_answer;
		}
		else
		{
			cout << "Целочисленного решения не существует!" << endl;
			return Gomori_table;
		}
	}
	else
	{
		cout << "Решение уже целочисленное!" << endl;
		return input_arr;
	}

}

void main()
{
	setlocale(LC_ALL, "Rus");
	cout << setprecision(4);
	int count_of_new_vars = 0;
	int num_of_str, num_of_colomns, num_of_vars, num_of_lims; //количество строк, столбцов симплекс таблицы
															  //переменных и ограничений
	bool information = false;//переменная, отвечающая за информацию было найдено ИОР/оптимальное решение или нет
	bool task_of_max = false;
	////////////////////////////НАЧАЛО ВВОДА ДАННЫХ///////////////////////////////////////
	cout << "Введите количество естественных переменных: ";
	cin >> num_of_vars;
	num_of_colomns = num_of_vars + 2;//количество столбцов на 2 больше чем переменных 
									 //для указания базовых переменных и свободных членов
									 //будем считать что [i][0] - столбец базовых переменных
									 //[i][1] - столбец свободных членов
	cout << "Введите количество ограничений: ";
	cin >> num_of_lims;
	num_of_str = num_of_lims + 1;//количество строк на 1 больше чем ограничений для отслеживания функции f
	string *znak = new string[num_of_lims];//массив для определение знака неравенства
	Common_fraction zero;
	zero = 0;
	vector<vector<Common_fraction>> enter_table(num_of_str, vector<Common_fraction>(num_of_colomns, zero));
	enter_data(enter_table, num_of_str, num_of_vars, num_of_lims, znak, task_of_max);
	////////////////////////////КОНЕЦ ВВОДА ДАННЫХ///////////////////////////////////////

	vector<vector<Common_fraction>> answer_table;
	//answer_table = Double_step_method(enter_table, num_of_str, num_of_lims, num_of_vars, znak, count_of_new_vars, information);
	answer_table = reduction_to_equalities(enter_table, num_of_str, num_of_lims, num_of_vars, znak);
	cout << "Исходная таблица:" << endl;
	print_tabl(answer_table, num_of_str, num_of_vars + 2);
	answer_table = Double_step_method(answer_table, num_of_str, num_of_lims, num_of_vars, information);
	//num_of_vars = num_of_vars + count_of_new_vars;
	count_of_new_vars = 0;
	//print_tabl(answer_table, num_of_str, num_of_vars + 2);
	if (information == true)//если ИОР найдено, улучшаем его
	{
		answer_table = simple_Simplex_method(answer_table, num_of_str, num_of_vars + 2, information);

		if (information == true)//если найдено оптимальное решение - ищем целочисленное
		{
			bool uluchshenie = false;
			cout << "Нужно находить целочисленное решение? \n0 - нет\n1 - да" << endl;
			cin >> uluchshenie;
			if (uluchshenie == 1)
			{
				vector<vector<Common_fraction>> answer;
				answer = GomoriMethod(answer_table, num_of_str, num_of_lims, num_of_vars, znak, information);
				Common_fraction max_fract_part;
				max_fract_part = 0;
				int number_of_lim_with_max_fract_part = -1;//номер ограничения с максимальной дробной частью
				for (int i = 0; i < num_of_lims; i++)
				{
					if (fractional_part(answer[i][1]) > max_fract_part)
					{
						max_fract_part = fractional_part(answer[i][1]);
						number_of_lim_with_max_fract_part = i;
					}
				}
				if (number_of_lim_with_max_fract_part != -1)
				{
					while (number_of_lim_with_max_fract_part != -1)
					{
						max_fract_part = 0;
						number_of_lim_with_max_fract_part = -1;
						answer = GomoriMethod(answer, num_of_str, num_of_lims, num_of_vars, znak, information);
						print_tabl(answer, num_of_str, num_of_vars + 2);
						for (int i = 0; i < num_of_lims; i++)
						{
							if (fractional_part(answer[i][1]) > max_fract_part)
							{
								max_fract_part = fractional_part(answer[i][1]);
								number_of_lim_with_max_fract_part = i;
							}
						}
					}
					if (task_of_max == true)
					{
						cout << "fmax = " << "-"<<answer[num_of_str - 1][1] << endl;
					}
					else
					{
						cout << "fmin = " << answer[num_of_str - 1][1] << endl;
					}
					print_tabl(answer, num_of_str, num_of_vars + 2);
				}
				else
				{
					cout << "Решение целочисленное!" << endl;
				}
			}
		}
	}
	
	system("pause");
}

Common_fraction Common_fraction::operator+(Common_fraction drob2)
{
	Common_fraction temp;
	if (this->denominator == drob2.denominator)
	{
		long long nod = 0;
		temp.numerator = this->numerator + drob2.numerator;
		temp.denominator = this->denominator;
		nod = NOD(temp.numerator, temp.denominator);//находим НОД числителя и знаменателя
		if (nod != 0)//если он не 0 то делим на него
		{
			temp.numerator /= nod;
			temp.denominator /= nod;
		}
		if (temp.numerator == 0)
		{
			temp.denominator = 1;
		}
		return temp;
	}
	else if (this->denominator != drob2.denominator)//знаменатели не равны либо равны 0 то обработать ошибку
	{
		long long nod = 0;
		temp.numerator = ((this->numerator)*drob2.denominator) + (drob2.numerator*(this->denominator));
		temp.denominator = (this->denominator)*drob2.denominator;
		nod = NOD(temp.numerator, temp.denominator);//находим НОД числителя и знаменателя
		if (nod != 0)//если он не 0 то делим на него
		{
			temp.numerator /= nod;
			temp.denominator /= nod;
		}
		if (temp.numerator == 0)
		{
			temp.denominator = 1;
		}
		return temp;
	}
}
Common_fraction Common_fraction::operator-(Common_fraction drob2)
{
	Common_fraction temp;
	if (this->denominator == drob2.denominator)
	{
		long long nod = 0;
		temp.numerator = this->numerator - drob2.numerator;
		temp.denominator = this->denominator;
		nod = NOD(temp.numerator, temp.denominator);//находим НОД числителя и знаменателя
		if (nod != 0)//если он не 0 то делим на него
		{
			temp.numerator /= nod;
			temp.denominator /= nod;
		}
		if (temp.numerator == 0)
		{
			temp.denominator = 1;
		}
		return temp;
	}
	else if (this->denominator != drob2.denominator)//знаменатели не равны либо равны 0 то обработать ошибку
	{
		if (drob2.numerator == 0)
		{
			temp.numerator = this->numerator;
			temp.denominator = this->denominator;
			return temp;
		}
		else
		{
			long long nod = 0;
			temp.numerator = ((this->numerator)*drob2.denominator) - (drob2.numerator*(this->denominator));
			temp.denominator = (this->denominator)*drob2.denominator;
			nod = NOD(temp.numerator, temp.denominator);//находим НОД числителя и знаменателя
			if (nod != 0)//если он не 0 то делим на него
			{
				temp.numerator /= nod;
				temp.denominator /= nod;
			}
			if (temp.numerator == 0)
			{
				temp.denominator = 1;
			}
			return temp;
		}
	}
}
Common_fraction Common_fraction::operator*(Common_fraction drob2)
{
	long long nod = 0;
	Common_fraction temp;
	temp.numerator = (this->numerator)*drob2.numerator;
	temp.denominator = (this->denominator)*drob2.denominator;
	nod = NOD(temp.numerator, temp.denominator);//находим НОД числителя и знаменателя
	if (nod != 0)//если он не 0 то делим на него
	{
		temp.numerator /= nod;
		temp.denominator /= nod;
	}

	if (temp.denominator == 0)
	{
		cout << "Ошибка! Делить на нуль нельзя!" << endl;
		temp.numerator = 0;
		temp.denominator = 1;
		return temp;
	}
	else
	{
		if (temp.numerator == 0)
		{
			temp.denominator = 1;
		}

		if (temp.denominator < 0)
		{
			temp.denominator = temp.denominator*(-1);
			temp.numerator = temp.numerator*(-1);
		}
		return temp;
	}
}
Common_fraction Common_fraction::operator/(Common_fraction drob2)
{
	long long nod = 0;
	Common_fraction temp;
	temp.numerator = (this->numerator)*drob2.denominator;
	temp.denominator = (this->denominator)*drob2.numerator;
	nod = NOD(temp.numerator, temp.denominator);//находим НОД числителя и знаменателя
	if (nod != 0)//если он не 0 то делим на него
	{
		temp.numerator /= nod;
		temp.denominator /= nod;
	}

	if (temp.denominator == 0)
	{
		cout << "Ошибка! Делить на нуль нельзя!" << endl;
		temp.numerator = 0;
		temp.denominator = 1;
		return temp;
	}
	else
	{
		if (temp.numerator == 0)
		{
			temp.denominator = 1;
		}

		if (temp.denominator < 0)
		{
			temp.denominator = temp.denominator*(-1);
			temp.numerator = temp.numerator*(-1);
		}
		return temp;
	}
}
Common_fraction Common_fraction::operator+(int value)
{
	Common_fraction temp;
	temp.denominator = this->denominator;
	temp.numerator = this->numerator + value * (this->denominator);
	if (temp.numerator == 0)
	{
		temp.denominator = 1;
	}
	return temp;
}
Common_fraction Common_fraction::operator-(int value)
{
	Common_fraction temp;
	temp.denominator = this->denominator;
	temp.numerator = this->numerator - value * (this->denominator);
	if (temp.numerator == 0)
	{
		temp.denominator = 1;
	}
	return temp;
}
Common_fraction Common_fraction::operator*(int value)
{
	long long nod = 0;
	Common_fraction temp;
	temp.denominator = this->denominator;
	temp.numerator = this->numerator * value;
	nod = NOD(temp.numerator, temp.denominator);//находим НОД числителя и знаменателя
	if (nod != 0)//если он не 0 то делим на него
	{
		temp.numerator /= nod;
		temp.denominator /= nod;
	}

	if (temp.denominator == 0)
	{
		cout << "Ошибка! Делить на нуль нельзя!" << endl;
		temp.numerator == 0;
		temp.denominator == 1;
		return temp;
	}
	else
	{
		if (temp.numerator == 0)
		{
			temp.denominator = 1;
		}
		if (temp.denominator < 0)
		{
			temp.denominator = temp.denominator*(-1);
			temp.numerator = temp.numerator*(-1);
		}
		return temp;
	}
}
Common_fraction Common_fraction::operator*(long long value)
{
	long long nod = 0;
	Common_fraction temp;
	temp.denominator = this->denominator;
	temp.numerator = this->numerator * value;
	nod = NOD(temp.numerator, temp.denominator);//находим НОД числителя и знаменателя
	if (nod != 0)//если он не 0 то делим на него
	{
		temp.numerator /= nod;
		temp.denominator /= nod;
	}

	if (temp.denominator == 0)
	{
		cout << "Ошибка! Делить на нуль нельзя!" << endl;
		temp.numerator == 0;
		temp.denominator == 1;
		return temp;
	}
	else
	{
		if (temp.numerator == 0)
		{
			temp.denominator = 1;
		}
		if (temp.denominator < 0)
		{
			temp.denominator = temp.denominator*(-1);
			temp.numerator = temp.numerator*(-1);
		}
		return temp;
	}
}
Common_fraction Common_fraction::operator/(int value)
{
	Common_fraction temp;
	temp.denominator = this->denominator*value;
	temp.numerator = this->numerator;
	if (temp.numerator == 0)
	{
		temp.denominator = 1;
	}
	if (temp.denominator < 0)
	{
		temp.denominator = temp.denominator*(-1);
		temp.numerator = temp.numerator*(-1);
	}
	return temp;
}
bool Common_fraction::operator==(Common_fraction drob2)
{
	long long nod = 0;
	nod = NOD(this->numerator, this->denominator);//находим НОД числителя и знаменателя
	if (nod != 0)//если он не 0 то делим на него
	{
		this->numerator /= nod;
		this->denominator /= nod;
	}
	nod = 0;
	nod = NOD(drob2.numerator, drob2.denominator);//находим НОД числителя и знаменателя
	if (nod != 0)//если он не 0 то делим на него
	{
		drob2.numerator /= nod;
		drob2.denominator /= nod;
	}

	if ((this->numerator == drob2.numerator) && (this->denominator == drob2.denominator))
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool Common_fraction::operator!=(Common_fraction drob2)
{
	long long nod = 0;
	nod = NOD(this->numerator, this->denominator);//находим НОД числителя и знаменателя
	if (nod != 0)//если он не 0 то делим на него
	{
		this->numerator /= nod;
		this->denominator /= nod;
	}
	nod = 0;
	nod = NOD(drob2.numerator, drob2.denominator);//находим НОД числителя и знаменателя
	if (nod != 0)//если он не 0 то делим на него
	{
		drob2.numerator /= nod;
		drob2.denominator /= nod;
	}

	if ((this->numerator == drob2.numerator) && (this->denominator == drob2.denominator))
	{
		return false;
	}
	else
	{
		return true;
	}

}
bool Common_fraction::operator>(Common_fraction drob2)
{
	Common_fraction temp1 = *this;
	Common_fraction temp2 = drob2;

	long long temp = temp1.denominator;
	temp1.numerator *= temp2.denominator;
	//this->denominator *= drob2.denominator; //зачем домножать числитель если можно сравнить
	temp2.numerator *= temp1.denominator;    //только знаменатели
											 //drob2.denominator *= temp;
	if (temp1.numerator > temp2.numerator)
		return true;
	else
		return false;
}
bool Common_fraction::operator>=(Common_fraction drob2)
{
	Common_fraction temp1 = *this;
	Common_fraction temp2 = drob2;

	long long temp = temp1.denominator;
	temp1.numerator *= temp2.denominator;
	//this->denominator *= drob2.denominator; //зачем домножать числитель если можно сравнить
	temp2.numerator *= temp1.denominator;    //только знаменатели
											 //drob2.denominator *= temp;
	if (temp1.numerator >= temp2.numerator)
		return true;
	else
		return false;
}
bool Common_fraction::operator<(Common_fraction drob2)
{
	Common_fraction temp1 = *this;
	Common_fraction temp2 = drob2;

	long long temp = temp1.denominator;
	temp1.numerator *= temp2.denominator;
	//this->denominator *= drob2.denominator; //зачем домножать числитель если можно сравнить
	temp2.numerator *= temp1.denominator;    //только знаменатели
											 //drob2.denominator *= temp;
	if (temp1.numerator < temp2.numerator)
		return true;
	else
		return false;
}
bool Common_fraction::operator<=(Common_fraction drob2)
{
	Common_fraction temp1 = *this;
	Common_fraction temp2 = drob2;

	long long temp = temp1.denominator;
	temp1.numerator *= temp2.denominator;
	//this->denominator *= drob2.denominator; //зачем домножать числитель если можно сравнить
	temp2.numerator *= temp1.denominator;    //только знаменатели
											 //drob2.denominator *= temp;
	if (temp1.numerator <= temp2.numerator)
		return true;
	else
		return false;
}
void Common_fraction::operator=(int value)
{
	this->numerator = value;
	this->denominator = 1;
}
void Common_fraction::operator=(const Common_fraction drob2)
{
	this->numerator = drob2.numerator;
	this->denominator = drob2.denominator;
}
void Common_fraction::setValue(long long numerator, long long denominator)
{
	this->numerator = numerator;
	this->denominator = denominator;
}
bool Common_fraction::operator==(int number)
{
	Common_fraction temp1 = *this;
	Common_fraction temp2;
	temp2.denominator = temp1.denominator;
	temp2.numerator = number * temp1.denominator;
	if (temp1.numerator == temp2.numerator)
	{
		return true;
	}
	else
		return false;

}
bool Common_fraction::operator!=(int number)
{
	Common_fraction temp1 = *this;
	Common_fraction temp2;
	temp2.denominator = temp1.denominator;
	temp2.numerator = number * temp1.denominator;
	if (temp1.numerator == temp2.numerator)
	{
		return false;
	}
	else
		return true;
}
bool Common_fraction::operator>(int number)
{
	Common_fraction temp1 = *this;
	Common_fraction temp2;
	temp2.denominator = temp1.denominator;
	temp2.numerator = number * temp1.denominator;
	if (temp1.numerator > temp2.numerator)
	{
		return true;
	}
	else
		return false;
}
bool Common_fraction::operator>=(int number)
{
	Common_fraction temp1 = *this;
	Common_fraction temp2;
	temp2.denominator = temp1.denominator;
	temp2.numerator = number * temp1.denominator;
	if (temp1.numerator >= temp2.numerator)
	{
		return true;
	}
	else
		return false;
}
bool Common_fraction::operator<(int number)
{
	Common_fraction temp1 = *this;
	Common_fraction temp2;
	temp2.denominator = temp1.denominator;
	temp2.numerator = number * temp1.denominator;
	if (temp1.numerator < temp2.numerator)
	{
		return true;
	}
	else
		return false;
}
bool Common_fraction::operator<=(int number)
{
	Common_fraction temp1 = *this;
	Common_fraction temp2;
	temp2.denominator = temp1.denominator;
	temp2.numerator = number * temp1.denominator;
	if (temp1.numerator <= temp2.numerator)
	{
		return true;
	}
	else
		return false;
}
Common_fraction Common_fraction::operator+=(int value)
{
	Common_fraction temp;
	temp = *this + value;
	return temp;
}
Common_fraction Common_fraction::operator-=(int value)
{
	Common_fraction temp;
	temp = *this - value;
	return temp;
}
Common_fraction Common_fraction::operator*=(int value)
{
	Common_fraction temp;
	temp = *this * value;
	if (temp.denominator < 0)
	{
		temp.denominator = temp.denominator*(-1);
		temp.numerator = temp.numerator*(-1);
	}
	return temp;
}
Common_fraction Common_fraction::operator/=(int value)
{
	Common_fraction temp;
	temp = *this / value;
	if (temp.denominator < 0)
	{
		temp.denominator = temp.denominator*(-1);
		temp.numerator = temp.numerator*(-1);
	}
	return temp;
}
Common_fraction Common_fraction::operator+=(Common_fraction drob2)
{
	return *this + drob2;
}
Common_fraction Common_fraction::operator-=(Common_fraction drob2)
{
	return *this - drob2;
}
Common_fraction Common_fraction::operator*=(Common_fraction drob2)
{
	Common_fraction temp;
	temp = *this * drob2;
	if (temp.denominator < 0)
	{
		temp.denominator = temp.denominator*(-1);
		temp.numerator = temp.numerator*(-1);
	}

	return temp;
}
Common_fraction Common_fraction::operator/=(Common_fraction drob2)
{
	Common_fraction temp;
	temp = *this / drob2;
	if (temp.denominator < 0)
	{
		temp.denominator = temp.denominator*(-1);
		temp.numerator = temp.numerator*(-1);
	}

	return temp;
}
Common_fraction Common_fraction::operator-()
{
	this->numerator = this->numerator*(-1);
	return *this;
}
long long NOD(long long a, long long b)
{
	a = abs(a);
	b = abs(b);
	if (a != 0 && b != 0)
	{
		if (a == 1 || b == 1)
			return 1;
		else
		{
			while (a != b)
			{
				if (a > b)
				{
					a = a - b;
				}
				else
				{
					b = b - a;
				}
				if (a == 1 || b == 1)
					return 1;
			}
			return a;
		}
	}
	else
	{
		return 0;
	}
}
std::ostream & operator<<(std::ostream & out, const Common_fraction & drob)
{
	if (drob.numerator != 0)//если не равна 0, то пишем всю дробь и числитель и знаменатель
	{
		if (drob.numerator == drob.denominator)
		{
			out << 1;

			return out;
		}
		else if (drob.denominator == 1)
		{
			out << drob.numerator;

			return out;
		}
		else
		{
			out << drob.numerator << "/" << drob.denominator;

			return out;
		}
	}
	else//если числитель равен 0 то выводим просто 0
	{
		out << drob.numerator;

		return out;
	}
}

std::istream & operator>>(std::istream & in, Common_fraction & drob)
{
link://переходим по этой ссылке и заново вводим числитель и знаменатель
	cout << "Числитель: ";
	in >> drob.numerator;
	cout << "Знаменатель: ";
	in >> drob.denominator;//при возможности нужно сократить

	if (drob.denominator == 0)
	{
		cout << "Знаменатель не может равняться нулю! Введите данные заново: " << endl;
		goto link;
	}

	long long nod = 0;
	nod = NOD(drob.numerator, drob.denominator);//находим НОД числителя и знаменателя
	if (nod != 0)//если он не 0 то делим на него
	{
		drob.numerator /= nod;
		drob.denominator /= nod;
	}

	return in;
}
Common_fraction fractional_part(Common_fraction number)
{
	if (number.denominator < 0)
	{
		number.denominator = number.denominator*(-1);
		number.numerator = number.numerator*(-1);
	}

	Common_fraction P;
	if (number > 0)
	{
		P = number - (int)(number.numerator / number.denominator);
		return P;
	}
	else if (number < 0)
	{
		P = number + (int)(-number.numerator / number.denominator);
		P = P + 1;
		return P;
	}
	else if (number == 0)
	{
		P.numerator = 0;
		P.denominator = 1;
		return P;
	}
}
