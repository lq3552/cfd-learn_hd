/* template function to read the parameter from a line */

#ifndef SETPAR_H
#define SETPAR_H

template<typename T> 
bool GetParameter(std::stringstream& stream, std::string& temp, T& parameter,
		int &found, const int rank, const std::string& keyword, std::map<std::string, int>& checklist)
{
	double tempParameter; // in case of enum type

	stream >> temp;
	if (std::stringstream(temp) >> tempParameter)
		found++;
	if (found == rank)
	{
		parameter = static_cast<T>(tempParameter);
		checklist[keyword] += 1;
		return true;
	}

	return false;
}

template<>
bool GetParameter<std::string>(std::stringstream& stream, std::string& temp, std::string& parameter,
		int &found, const int rank, const std::string& keyword, std::map<std::string, int>& checklist)
{
	std::string tempParameter; // in case of enum type

	stream >> temp;
	if (std::stringstream(temp) >> tempParameter && tempParameter != "=")
		found++;
	if (found == rank)
	{
		parameter = tempParameter;
		checklist[keyword] += 1;
		return true;
	}

	return false;
}

template <typename T>
void ReadParameterFromLine(const std::string line, const std::string& keyword,
		T& parameter, std::map<std::string, int>& checklist, const int rank = 1)
{
	std::stringstream stream;
	stream << line;

	if (!stream.eof())
	{
		std::string firstWord;

		stream >> firstWord;
		if (firstWord == keyword)
		{ // first word must match keyword
			std::string temp;
			int found = 0;
			/* loop until the parameter is loaded */
			while(!stream.eof())
			{
				if(GetParameter<T>(stream, temp, parameter, found, rank, keyword, checklist))
					break;
			}
		}
	}
}

#endif
