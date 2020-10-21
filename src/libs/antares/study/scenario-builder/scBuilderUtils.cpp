/*
** Copyright 2007-2018 RTE
** Authors: Antares_Simulator Team
**
** This file is part of Antares_Simulator.
**
** Antares_Simulator is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** There are special exceptions to the terms and conditions of the
** license as they are applied to this software. View the full text of
** the exceptions in file COPYING.txt in the directory of this software
** distribution
**
** Antares_Simulator is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Antares_Simulator. If not, see <http://www.gnu.org/licenses/>.
**
** SPDX-License-Identifier: licenceRef-GPL3_WITH_RTE-Exceptions
*/

#include <sstream>
#include <iomanip>
#include <string>
#include <yuni/core/string/string.h>
#include "scBuilderUtils.h"

namespace Antares
{
namespace Data
{
namespace ScenarioBuilder
{

	string fromHydroLevelToString(double d)
	{
		std::ostringstream stream;
		stream << std::setprecision(4);
		stream << d;
		return stream.str();
	}


	double fromStringToHydroLevel(const Yuni::String& value)
	{
		double result;
		const double maxLevel = 100.;
		double result_tmp;

		std::string val = value.to<std::string>();
		try
		{
			result_tmp = stod(val);
		}
		catch (std::invalid_argument&)
		{
			return -1.;
		}

		if (result_tmp < 0.)
			result = -1.;
		else
		{
			if (result_tmp > maxLevel)
				result = maxLevel;
			else
				result = result_tmp;
		}
		return result;
	}


	uint fromStringToTSnumber(const Yuni::String& value)
	{
		uint result;
		const uint maxTSnumber = 10000;
		double result_dbl;

		std::string val = value.to<std::string>();
		try
		{
			result_dbl = stod(val);
		}
		catch (std::invalid_argument&)
		{
			return 0;
		}

		if (result_dbl < 0.)
			result = 0;
		else
		{
			if (result_dbl > maxTSnumber)
				result = maxTSnumber;
			else
				result = (uint)result_dbl;
		}
		return result;
	}


} // namespace ScenarioBuilder
} // namespace Data
} // namespace Antares
