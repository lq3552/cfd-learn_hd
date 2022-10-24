/* template function to read the parameter from a line */

template <typename T>
void ReadParameterFromLine(const std::string line, const std::string keyword,
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
			/* loop until the parameter is loaded */
			while(!stream.eof())
			{
				int found = 0;
				double tempParameter; // in case of enum type

				stream >> temp;
				if (std::stringstream(temp) >> tempParameter)
					found++;
				if (found == rank)
				{
					parameter = static_cast<T>(tempParameter);
					checklist[keyword] += 1;
					return;
				}
			}
		}
	}
}
