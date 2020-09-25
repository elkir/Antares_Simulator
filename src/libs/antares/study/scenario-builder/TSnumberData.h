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
#ifndef __LIBS_STUDY_SCENARIO_BUILDER_DATA_TS_NUMBER_H__
# define __LIBS_STUDY_SCENARIO_BUILDER_DATA_TS_NUMBER_H__


# include "scBuilderDataInterface.h"

using namespace Yuni;

namespace Antares
{
namespace Data
{
namespace ScenarioBuilder
{


	/*!
	** \brief Rules for TS numbers, for all years and a single timeseries
	*/
	class TSNumberData : public dataInterface
	{
	public:
		//! Matrix
		typedef Matrix<Yuni::uint32> MatrixType;

	public:
		
		// We use default constructor and destructor 

		//! \name Data manupulation
		//@{
		/*!
		** \brief Reset data from the study
		*/
		bool reset(const Study& study);

		/*!
		** \brief Export the data into a mere INI file
		*/
		void saveToINIFile(const Study& study, Yuni::IO::File::Stream& file) const;

		/*!
		** \brief Assign a single value
		**
		** \param index An area index or a thermal cluster index
		** \param year  A year
		** \param value The new TS number
		*/
		void set(uint index, uint year, uint value);
		//@}

		//! \name Rules matrix
		//@{
		/*!
		** \brief Resize to a given number of years
		*/
		void resize(uint nbYears);

		//! Get the overlay matrix
		MatrixType& overlay();
		//@}


	protected:
		virtual
		CString<512, false> get_prefix() const = 0;

		virtual
		uint get_tsGenCount(const Study& study) const = 0;

	protected:
		//! All TS number overlay (0 if auto)
		MatrixType pTSNumberRules;

	}; // class TSNumberData

	// class TSNumberData : inline functions
	inline void TSNumberData::resize(uint nbYears)
	{
		pTSNumberRules.resize(pTSNumberRules.height, nbYears);
	}

	inline TSNumberData::MatrixType& TSNumberData::overlay()
	{
		return pTSNumberRules;
	}

	inline void TSNumberData::set(uint areaindex, uint year, uint value)
	{
		assert(areaindex < pTSNumberRules.width);
		if (year < pTSNumberRules.height)
			pTSNumberRules[areaindex][year] = value;
	}


	// =============== TSNumberData derived classes ===============

	// Load ...
	class loadTSNumberData : public TSNumberData
	{
	public:
		void apply(const Study& study);
		CString<512, false> get_prefix() const;
		uint get_tsGenCount(const Study& study) const;
	};

	inline CString<512, false> loadTSNumberData::get_prefix() const { return "l,"; }



	// Wind ...
	class windTSNumberData : public TSNumberData
	{
	public:
		void apply(const Study& study);
		CString<512, false> get_prefix() const;
		uint get_tsGenCount(const Study& study) const;
	};

	inline CString<512, false> windTSNumberData::get_prefix() const { return "w,"; }


	// Solar ...
	class solarTSNumberData : public TSNumberData
	{
	public:
		void apply(const Study& study);
		CString<512, false> get_prefix() const;
		uint get_tsGenCount(const Study& study) const;
	};

	inline CString<512, false> solarTSNumberData::get_prefix() const { return "s,"; }


	// Hydro ...
	class hydroTSNumberData : public TSNumberData
	{
	public:
		void apply(const Study& study);
		CString<512, false> get_prefix() const;
		uint get_tsGenCount(const Study& study) const;
	};

	inline CString<512, false> hydroTSNumberData::get_prefix() const { return "h,"; }


	// Thermal ...
	class thermalTSNumberData : public TSNumberData
	{
	public:
		thermalTSNumberData() : pArea(NULL) {}

		bool reset(const Study& study);
		void saveToINIFile(const Study& study, Yuni::IO::File::Stream& file) const;

		void attachArea(const Area* area) { pArea = area; }

		void set(const Antares::Data::ThermalCluster* cluster, const uint year, uint value);
		uint get(const Antares::Data::ThermalCluster* cluster, const uint year) const;
		void apply(const Study& study);
		CString<512, false> get_prefix() const;
		uint get_tsGenCount(const Study& study) const;

	private:
		//! The attached area, if any
		const Area* pArea;
		//! The map between clusters and there line index
		std::map<const ThermalCluster*, uint> clusterIndexMap;
	};

	inline void thermalTSNumberData::set(const Antares::Data::ThermalCluster* cluster, const uint year, uint value)
	{
		assert(cluster != nullptr);
		if (clusterIndexMap.find(cluster) == clusterIndexMap.end())
			clusterIndexMap[cluster] = cluster->areaWideIndex;
		if (year < pTSNumberRules.height)
			pTSNumberRules[clusterIndexMap[cluster]][year] = value;
	}

	inline uint thermalTSNumberData::get(const Antares::Data::ThermalCluster* cluster, const uint year) const
	{
		assert(cluster != nullptr);
		if (clusterIndexMap.find(cluster) != clusterIndexMap.end() && year < pTSNumberRules.height)
		{
			uint index = clusterIndexMap.at(cluster);
			return pTSNumberRules[index][year];
		}

		return 0;
	}

	inline CString<512, false> thermalTSNumberData::get_prefix() const { return "t,"; }



} // namespace ScenarioBuilder
} // namespace Data
} // namespace Antares


#endif // __LIBS_STUDY_SCENARIO_BUILDER_DATA_TS_NUMBER_H__