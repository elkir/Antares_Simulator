#include "ortools_utils.h"

#include <antares/logs.h>
#include <antares/study.h>
#include <antares/exception/AssertionError.hpp>
#include <antares/Enum.hpp>

#include <yuni/core/system/memory.h>

using namespace operations_research;


/**
 * Retourne la consommation actuelle de memoire
 */
size_t current_memory_usage(std::string const & message)
{
	Yuni::System::Memory::Usage memory;
	memory.available /= 1024 * 1024; // Mib
	memory.total   /= 1024 * 1024; // Mib

	Antares::logs.info() << message << ", system memory report: "
		<< memory.available << " Mib / "
		<< memory.total  << " Mib,  "
		<< (100. / memory.total * memory.available) << "% free";

	return memory.total - memory.available;
}

template<typename T_PROBLEM>
operations_research::MPSolver * convert_to_MPSolver(T_PROBLEM * problemeSimplexe);

void extract_from_MPSolver(operations_research::MPSolver * solver, PROBLEME_SIMPLEXE * problemeSimplexe);
void extract_from_MPSolver(operations_research::MPSolver * solver, PROBLEME_A_RESOUDRE * problemeSimplexe);

void change_MPSolver_objective(operations_research::MPSolver * solver, double * costs, int nbVar);
void change_MPSolver_rhs(operations_research::MPSolver * solver, double * rhs, char * sens, int nbRow);
void change_MPSolver_variables_bounds(operations_research::MPSolver * solver, double * bMin, double * bMax, int nbVar, PROBLEME_SIMPLEXE * problemeSimplexe);

void transferVariables(operations_research::MPSolver * solver, double * bMin, double * bMax, double * costs, int nbVar) {
	MPObjective* const objective = solver->MutableObjective();
	for (int idxVar = 0; idxVar < nbVar; ++idxVar) {
		std::ostringstream oss;
		oss << "x" << idxVar;
		double min_l = 0.0;
		if(bMin != NULL) {
			min_l = bMin[idxVar];
		}
		double max_l = bMax[idxVar];
		auto x = solver->MakeNumVar(min_l, max_l, oss.str());
		objective->SetCoefficient(x, costs[idxVar]);
	}
}

void transferRows(operations_research::MPSolver * solver, double * rhs, char * sens, int nbRow) {
	for (int idxRow = 0; idxRow < nbRow; ++idxRow) {
		double bMin = -MPSolver::infinity(), bMax = MPSolver::infinity();
		if (sens[idxRow] == '=') {
			bMin = bMax = rhs[idxRow];
		}
		else if (sens[idxRow] == '<') {
			bMax= rhs[idxRow];
		}
		else if (sens[idxRow] == '>') {
			bMin = rhs[idxRow];
		}
		std::ostringstream oss;
		oss << "c" << idxRow;
		MPConstraint* const ct = solver->MakeRowConstraint(bMin, bMax, oss.str());
	}
}

void transferMatrix(operations_research::MPSolver * solver, int * indexRows, int * terms, int * indexCols, double * coeffs, int nbRow) {
	auto variables = solver->variables();
	auto constraints = solver->constraints();

	for (int idxRow = 0; idxRow < nbRow; ++idxRow) {
		MPConstraint* const ct = constraints[idxRow];
		int debutLigne = indexRows[idxRow];
		for (int idxCoef = 0; idxCoef < terms[idxRow]; ++idxCoef)
		{
			int pos = debutLigne + idxCoef;
			ct->SetCoefficient(variables[indexCols[pos]], coeffs[pos]);
		}
	}
}

MPSolver * convert_to_MPSolver(PROBLEME_SIMPLEXE * problemeSimplexe) {

    //Define solver used depending on global solver option
    MPSolver::OptimizationProblemType solverType = Antares::Data::OrtoolsUtils().getLinearOptimProblemType(Antares::Data::OrtoolsUtils::OrtoolsEnumUsed);

	// Create the linear solver instance
	MPSolver * solver = new MPSolver("simple_lp_program", solverType);

	// Create the variables and set objective cost.
	transferVariables(solver, problemeSimplexe->Xmin, problemeSimplexe->Xmax, problemeSimplexe->CoutLineaire,  problemeSimplexe->NombreDeVariables);

	// Create constraints and set coefs
	transferRows(solver, problemeSimplexe->SecondMembre, problemeSimplexe->Sens, problemeSimplexe->NombreDeContraintes);
	transferMatrix(solver, problemeSimplexe->IndicesDebutDeLigne, problemeSimplexe->NombreDeTermesDesLignes, problemeSimplexe->IndicesColonnes, problemeSimplexe->CoefficientsDeLaMatriceDesContraintes, problemeSimplexe->NombreDeContraintes);

	return solver;
}

MPSolver * convert_to_MPSolver(PROBLEME_A_RESOUDRE * problemeAResoudre) {

    //Define solver used depending on global solver option
    MPSolver::OptimizationProblemType solverType = Antares::Data::OrtoolsUtils().getMixedIntegerOptimProblemType(Antares::Data::OrtoolsUtils::OrtoolsEnumUsed);

	MPSolver * solver = new MPSolver("simple_lp_program",solverType);

	// Create the variables and set objective cost.
	transferVariables(solver, problemeAResoudre->Xmin, problemeAResoudre->Xmax, problemeAResoudre->CoutLineaire,  problemeAResoudre->NombreDeVariables);

	// Create constraints and set coefs
	transferRows(solver, problemeAResoudre->SecondMembre, problemeAResoudre->Sens, problemeAResoudre->NombreDeContraintes);
	transferMatrix(solver, problemeAResoudre->IndicesDebutDeLigne, problemeAResoudre->NombreDeTermesDesLignes, problemeAResoudre->IndicesColonnes, problemeAResoudre->CoefficientsDeLaMatriceDesContraintes, problemeAResoudre->NombreDeContraintes);

	return solver;
}

void extract_from_MPSolver(MPSolver * solver, PROBLEME_A_RESOUDRE * problemePne) {
	auto & variables = solver->variables();
	int nbVar = problemePne->NombreDeVariables;

	// Extracting variable values and reduced costs
	for (int idxVar = 0; idxVar < nbVar; ++idxVar) {
		auto & var = variables[idxVar];
		problemePne->X[idxVar] = var->solution_value();
	}

	auto & constraints = solver->constraints();
	int nbRow = problemePne->NombreDeContraintes;
	for (int idxRow = 0; idxRow < nbRow; ++idxRow) {
		auto & row = constraints[idxRow];
		problemePne->VariablesDualesDesContraintes[idxRow] = row->dual_value();
	}
}

void extract_from_MPSolver(MPSolver * solver, PROBLEME_SIMPLEXE * problemeSimplexe) {
	auto & variables = solver->variables();
	int nbVar = problemeSimplexe->NombreDeVariables;

	// Extracting variable values and reduced costs
	for (int idxVar = 0; idxVar < nbVar; ++idxVar) {
		auto & var = variables[idxVar];
		problemeSimplexe->X[idxVar] = var->solution_value();
		problemeSimplexe->CoutsReduits[idxVar] = var->reduced_cost();
	}

	auto & constraints = solver->constraints();
	int nbRow = problemeSimplexe->NombreDeContraintes;
	for (int idxRow = 0; idxRow < nbRow; ++idxRow) {
		auto & row = constraints[idxRow];
		problemeSimplexe->CoutsMarginauxDesContraintes[idxRow] = row->dual_value();
	}
}

void change_MPSolver_objective(MPSolver * solver, double * costs, int nbVar) {
	auto & variables = solver->variables();
	for (int idxVar = 0; idxVar < nbVar; ++idxVar) {
		auto & var = variables[idxVar];
		solver->MutableObjective()->SetCoefficient(var, costs[idxVar]);
	}
}

void change_MPSolver_variables_bounds(MPSolver * solver, double * bMin, double * bMax,  int nbVar, PROBLEME_SIMPLEXE * problemeSimplexe) {
	auto & variables = solver->variables();
	for (int idxVar = 0; idxVar < nbVar; ++idxVar) {
		double min_l = (
			(problemeSimplexe->TypeDeVariable[idxVar] == VARIABLE_NON_BORNEE) || (problemeSimplexe->TypeDeVariable[idxVar] == VARIABLE_BORNEE_SUPERIEUREMENT) ?
			-MPSolver::infinity() :
			bMin[idxVar]);
		double max_l = (
			(problemeSimplexe->TypeDeVariable[idxVar] == VARIABLE_NON_BORNEE) || (problemeSimplexe->TypeDeVariable[idxVar] == VARIABLE_BORNEE_INFERIEUREMENT) ?
			MPSolver::infinity() :
			bMax[idxVar]);
		auto & var = variables[idxVar];
		var->SetBounds(min_l, max_l);
	}
}

void change_MPSolver_rhs(MPSolver * solver, double * rhs, char * sens, int nbRow) {
	auto & constraints = solver->constraints();
	for (int idxRow = 0; idxRow < nbRow; ++idxRow) {
		if (sens[idxRow] == '=')
			constraints[idxRow]->SetBounds(rhs[idxRow], rhs[idxRow]);
		else if (sens[idxRow] == '<')
			constraints[idxRow]->SetBounds(- MPSolver::infinity(), rhs[idxRow]);
		else if (sens[idxRow] == '>')
			constraints[idxRow]->SetBounds(rhs[idxRow], MPSolver::infinity());
	}
}

void ORTOOLS_EcrireJeuDeDonneesLineaireAuFormatMPS(operations_research::MPSolver * solver, size_t numSpace, int const n) {
		auto& study = *Antares::Data::Study::Current::Get();

		int const year = study.runtime->currentYear[numSpace] + 1;
		int const week = study.runtime->weekInTheYear[numSpace] + 1;
		std::stringstream buffer;
		buffer << study.folderOutput << Yuni::IO::Separator << "problem-" << year << "-" << week << "-" << n << ".mps";
		solver->Write(buffer.str());
}

std::string getRunName(std::string const & prefix, size_t numSpace, int numInterval, int numOptim) {
	auto& study = *Antares::Data::Study::Current::Get();

	int const year = study.runtime->currentYear[numSpace] + 1;
	int const week = study.runtime->weekInTheYear[numSpace] + 1;
	std::stringstream buffer;
	buffer << prefix << " for year=" << year << ", week=" << week << ", interval="<< numInterval << ", optimisation=" << numOptim;
	return buffer.str();
}

bool solveAndManageStatus(operations_research::MPSolver * solver, int & resultStatus, MPSolverParameters& params) {
	auto status = solver->Solve(params);

	if (status == MPSolver::OPTIMAL || status == MPSolver::FEASIBLE) {
		resultStatus = OUI_SPX;
	}
	else {
		resultStatus = NON_SPX;
	}

	return resultStatus == OUI_SPX;
}

void * solveProblem(PROBLEME_SIMPLEXE * Probleme, void * ProbSpx) {

	operations_research::MPSolver * solver = nullptr;

	if (ProbSpx == NULL) {
		solver = convert_to_MPSolver(Probleme);
		//solver->EnableOutput();
	}
	else {
		solver = (MPSolver *)ProbSpx;
	}

	MPSolverParameters params;

	if(solveAndManageStatus(solver, Probleme->ExistenceDUneSolution, params)) {
		extract_from_MPSolver(solver, Probleme);
	}

	return solver;
}

void * solveProblem(PROBLEME_A_RESOUDRE * Probleme, void * ProbSpx) {

	operations_research::MPSolver * solver = nullptr;

	if (ProbSpx == NULL) {
		solver = convert_to_MPSolver(Probleme);
		//solver->EnableOutput();
	}
	else {
		solver = (MPSolver *)ProbSpx;
	}

	MPSolverParameters params;
	if (Probleme->FaireDuPresolve == NON_PNE) {
		params.SetIntegerParam(MPSolverParameters::PRESOLVE, MPSolverParameters::PRESOLVE_OFF);
	}
	else
	{
		params.SetIntegerParam(MPSolverParameters::PRESOLVE, MPSolverParameters::PRESOLVE_ON);
	}

	if(solveAndManageStatus(solver, Probleme->ExistenceDUneSolution, params)) {
		extract_from_MPSolver(solver, Probleme);
	}

	delete solver;
	solver = nullptr;

	return solver;
}

extern "C" {

void * ORTOOLS_Simplexe(PROBLEME_SIMPLEXE * Probleme, void * ProbSpx) {
	return solveProblem(Probleme, ProbSpx);
}

void * ORTOOLS_Simplexe_PNE(PROBLEME_A_RESOUDRE * Probleme, void * ProbSpx) {
	return solveProblem(Probleme, ProbSpx);
}

void ORTOOLS_ModifierLeVecteurCouts(void * ProbSpx, double * costs, int nbVar) {
	MPSolver * solver = (MPSolver *)ProbSpx;
	change_MPSolver_objective(solver, costs, nbVar);
}

void ORTOOLS_ModifierLeVecteurSecondMembre(void * ProbSpx, double * rhs, char * sens, int nbRow) {
	MPSolver * solver = (MPSolver *)ProbSpx;
	change_MPSolver_rhs(solver, rhs, sens, nbRow);
}

void ORTOOLS_CorrigerLesBornes(void * ProbSpx, double * bMin, double * bMax, int * typeVar, int nbVar, PROBLEME_SIMPLEXE * Probleme) {
	MPSolver * solver = (MPSolver *)ProbSpx;
	Probleme->TypeDeVariable = typeVar;
	change_MPSolver_variables_bounds(solver, bMin, bMax, nbVar, Probleme);
}

void ORTOOLS_LibererProbleme(void * ProbSpx) {
	MPSolver * solver = (MPSolver *)ProbSpx;
	delete solver;
}

}


namespace Antares {
    namespace Data {


        bool OrtoolsUtils::OrtoolsUsed = false;
		OrtoolsSolver OrtoolsUtils::OrtoolsEnumUsed = OrtoolsSolver::sirius;


        OrtoolsUtils::OrtoolsUtils()
        {
            //TODO JMK : Values must be adequacy with kOptimizationProblemTypeNames for ortools linear_solver/linear_solver.cc file

            _solverLinearProblemOptimStringMap[OrtoolsSolver::sirius]       = "sirius_lp";  //TODO JMK : not defined in current ortools RTE branch.
            _solverMixedIntegerProblemOptimStringMap[OrtoolsSolver::sirius] = "sirius_mip"; //TODO JMK : not defined in current ortools RTE branch.

            _solverLinearProblemOptimStringMap[OrtoolsSolver::coin]       = "clp";
            _solverMixedIntegerProblemOptimStringMap[OrtoolsSolver::coin] = "cbc";

            _solverLinearProblemOptimStringMap[OrtoolsSolver::xpress]       = "xpress_lp";
            _solverMixedIntegerProblemOptimStringMap[OrtoolsSolver::xpress] = "xpress_mip";

            _solverLinearProblemOptimStringMap[OrtoolsSolver::glop_scip]       = "glop";
            _solverMixedIntegerProblemOptimStringMap[OrtoolsSolver::glop_scip] = "scip";

            _solverLinearProblemOptimStringMap[OrtoolsSolver::cplex]       = "cplex_lp";  //TODO JMK : not defined in current ortools RTE branch.
            _solverMixedIntegerProblemOptimStringMap[OrtoolsSolver::cplex] = "cplex_mip"; //TODO JMK : not defined in current ortools RTE branch.

            _solverLinearProblemOptimStringMap[OrtoolsSolver::gurobi]       = "gurobi_lp";
            _solverMixedIntegerProblemOptimStringMap[OrtoolsSolver::gurobi] = "gurobi_mip";

            _solverLinearProblemOptimStringMap[OrtoolsSolver::glpk]       = "glpk_lp";
            _solverMixedIntegerProblemOptimStringMap[OrtoolsSolver::glpk] = "glpk_mip";

            _solverLinearProblemOptimStringMap[OrtoolsSolver::glop_cbc]       = "glop";
            _solverMixedIntegerProblemOptimStringMap[OrtoolsSolver::glop_cbc] = "cbc";

            /* TODO JMK : see how we can get optimization problem type with current ortools RTE branch (can't use enum because of compile switch)

            _solverLinearProblemOptimMap[OrtoolsSolver::sirius]       = MPSolver::OptimizationProblemType::SIRIUS_LINEAR_PROGRAMMING;
            _solverMixedIntegerProblemOptimMap[OrtoolsSolver::sirius] = MPSolver::OptimizationProblemType::SIRIUS_MIXED_INTEGER_PROGRAMMING;

            _solverLinearProblemOptimMap[OrtoolsSolver::coin]       = MPSolver::OptimizationProblemType::CLP_LINEAR_PROGRAMMING;
            _solverMixedIntegerProblemOptimMap[OrtoolsSolver::coin] = MPSolver::OptimizationProblemType::CBC_MIXED_INTEGER_PROGRAMMING;

            _solverLinearProblemOptimMap[OrtoolsSolver::xpress]       = MPSolver::OptimizationProblemType::XPRESS_LINEAR_PROGRAMMING;
            _solverMixedIntegerProblemOptimMap[OrtoolsSolver::xpress] = MPSolver::OptimizationProblemType::XPRESS_MIXED_INTEGER_PROGRAMMING;

            _solverLinearProblemOptimMap[OrtoolsSolver::glop_scip]       = MPSolver::OptimizationProblemType::GLOP_LINEAR_PROGRAMMING;
            _solverMixedIntegerProblemOptimMap[OrtoolsSolver::glop_scip] = MPSolver::OptimizationProblemType::SCIP_MIXED_INTEGER_PROGRAMMING;

            _solverLinearProblemOptimMap[OrtoolsSolver::cplex]       = MPSolver::OptimizationProblemType::CPLEX_LINEAR_PROGRAMMING;
            _solverMixedIntegerProblemOptimMap[OrtoolsSolver::cplex] = MPSolver::OptimizationProblemType::CPLEX_MIXED_INTEGER_PROGRAMMING;

            _solverLinearProblemOptimMap[OrtoolsSolver::gurobi]       = MPSolver::OptimizationProblemType::GUROBI_LINEAR_PROGRAMMING;
            _solverMixedIntegerProblemOptimMap[OrtoolsSolver::gurobi] = MPSolver::OptimizationProblemType::GUROBI_MIXED_INTEGER_PROGRAMMING;

            _solverLinearProblemOptimMap[OrtoolsSolver::glpk]       = MPSolver::OptimizationProblemType::GLPK_LINEAR_PROGRAMMING;
            _solverMixedIntegerProblemOptimMap[OrtoolsSolver::glpk] = MPSolver::OptimizationProblemType::GLPK_MIXED_INTEGER_PROGRAMMING;

            _solverLinearProblemOptimMap[OrtoolsSolver::glop_cbc]       = MPSolver::OptimizationProblemType::GLOP_LINEAR_PROGRAMMING;
            _solverMixedIntegerProblemOptimMap[OrtoolsSolver::glop_cbc] = MPSolver::OptimizationProblemType::CBC_MIXED_INTEGER_PROGRAMMING;

             */
        }

        bool OrtoolsUtils::isOrtoolsSolverAvailable(OrtoolsSolver ortoolsSolver) {
            bool result = false;

			try
			{
				result = MPSolver::SupportsProblemType(getLinearOptimProblemType(ortoolsSolver));
				result &= MPSolver::SupportsProblemType(getMixedIntegerOptimProblemType(ortoolsSolver));
			}
			catch (AssertionError& ex)
			{
				result = false;
			}

            return result;
        }

        std::list<OrtoolsSolver> OrtoolsUtils::getAvailableOrtoolsSolver() {

            std::list<OrtoolsSolver> result;

            std::list<OrtoolsSolver> solverList = Enum::enumList<Antares::Data::OrtoolsSolver>();

            for  (OrtoolsSolver solver : solverList)
            {
                if (isOrtoolsSolverAvailable(solver)){
                    result.push_back(solver);
                }
            }

            return result;
        }

        std::list<std::string> OrtoolsUtils::getAvailableOrtoolsSolverName() {
            std::list<std::string> result;

            std::list<OrtoolsSolver> solverList = getAvailableOrtoolsSolver();

            for  (OrtoolsSolver solver : solverList)
            {
                result.push_back(Enum::toString(solver));
            }

            return result;
        }

        MPSolver::OptimizationProblemType OrtoolsUtils::getLinearOptimProblemType(const OrtoolsSolver& ortoolsSolver) {

            //TODO JMK : see how we can get optimization problem type with current ortools RTE branch (can't use enum because of compile switch)
            //MPSolver::OptimizationProblemType result = _solverLinearProblemOptimMap.at(ortoolsSolver)

            //For now we are using string to get optimization problem type
            MPSolver::OptimizationProblemType result = MPSolver::OptimizationProblemType::GLOP_LINEAR_PROGRAMMING;


            if (!MPSolver::ParseSolverType(_solverLinearProblemOptimStringMap.at(ortoolsSolver), &result))
            {
                throw AssertionError("Unsupported Linear OrtoolsSolver for solver " + Enum::toString(ortoolsSolver));
            }

            return result;
        }

        MPSolver::OptimizationProblemType OrtoolsUtils::getMixedIntegerOptimProblemType(const OrtoolsSolver& ortoolsSolver) {

            //TODO JMK : see how we can get optimization problem type with current ortools RTE branch (can't use enum because of compile switch)
            //MPSolver::OptimizationProblemType result = _solverMixedIntegerProblemOptimMap.at(ortoolsSolver)

            //For now we are using string to get optimization problem type
            MPSolver::OptimizationProblemType result = MPSolver::OptimizationProblemType::GLOP_LINEAR_PROGRAMMING;


            if (!MPSolver::ParseSolverType(_solverMixedIntegerProblemOptimStringMap[ortoolsSolver], &result))
            {
				throw AssertionError("Unsupported Mixed Integer OrtoolsSolver for solver " + Enum::toString(ortoolsSolver));
            }

            return result;
        }

    namespace Enum {

        template <>
        const std::initializer_list<std::string>& getNames<OrtoolsSolver>() {

            //Enum must be stored in lower case and without spaces because values  are trimmed and lowered in ini load
            static std::initializer_list<std::string> s_ortoolsSolverNames{
                    "sirius",
                    "coin",
                    "xpress",
                    "glop-scip",
                    "cplex",
                    "gurobi",
                    "glpk",
                    "glop-cbc"
            };

            return s_ortoolsSolverNames;
        }
    } // namespace Enum

} // namespace Data
} // namespace Antares