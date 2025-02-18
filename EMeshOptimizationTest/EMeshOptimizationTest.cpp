#include "EMeshOptimization.h" // Include the header file of the EMeshOptimization object

#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
#ifdef MSMPI
#include <mpi.h>
#endif // MSMPI

void GeneralOpti()
{
	// Create a new EMeshOptimization object
	EMeshOptimization* pEMeshOptimization = NULL;
	pEMeshOptimization = EMeshOptimizationNew();

	// Set the parameters of the EMeshOptimization object
	if (EMeshOptimizationInitialMeshImportFromBINWithMoreInfo(pEMeshOptimization, "..\\mesh\\X-51", "X-51_D1_bin") != 1)
		return;
	//if (EMeshOptimizationInitialMeshImportFromBINWithMoreInfo(pEMeshOptimization, "..\\mesh\\R60", "R60_D1_bin") != 1)
	//	return 0;

	// Output the mesh quality information of the initial mesh
	std::cout << "\nThe mesh info before optimized:\n";
	EMeshOptimizationOutputsMeshQualityInformation(pEMeshOptimization);

	// Record the start time of the mesh optimization algorithm
	std::cout << "\nOptimization start..." << std::endl;
	auto start = std::chrono::steady_clock::now();

	// Run the mesh optimization algorithm
	EMeshOptimization_GEPM(pEMeshOptimization);
	//EMeshOptimization_GEPMA(pEMeshOptimization);
	//EMeshOptimization_GEPMB(pEMeshOptimization);
	//EMeshOptimization_LS(pEMeshOptimization);

	// Record the end time of the mesh optimization algorithm
	auto end = std::chrono::steady_clock::now();
	std::cout << "Optimization end!" << std::endl;

	// Output the time cost of the mesh optimization algorithm, use seconds as the unit
	std::chrono::duration<double> elapsedTime = end - start;
	std::cout << "\nThe time cost of the mesh optimization algorithm: " << elapsedTime.count() << " s" << std::endl;

	// Output the mesh quality information of the optimized mesh
	std::cout << "\nThe mesh info after optimized:\n";
	EMeshOptimizationOutputsMeshQualityInformation(pEMeshOptimization);

	// Export the optimized mesh to a TXT file
	//if (EMeshOptimizationExportOptimizedMeshToTXT(pEMeshOptimization, "..\\mesh\\result\\X-51", "X-51_D1_OUT") != 1)
	//    return 0;
	//if (EMeshOptimizationExportOptimizedMeshToTXT(pEMeshOptimization, "..\\mesh\\result\\R60", "R60_D1_OUT") != 1)
	//	return 0;

	// Delete the EMeshOptimization object
	EMeshOptimizationDelete(pEMeshOptimization);
}

void MSMPIOpti()
{
#ifdef MSMPI
	// Get the rank and size of the MPI process
	int rank = 0, size = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Record the start and end time of the mesh optimization algorithm
	auto start_opti = std::chrono::steady_clock::now();
	auto end_opti = std::chrono::steady_clock::now();

	// Create a new EMeshOptimization object
	EMeshOptimization* pEMeshOptimization = NULL;
	pEMeshOptimization = EMeshOptimizationNew();
	if (rank == 0)
	{
		// Set the parameters of the EMeshOptimization object
		if (EMeshOptimizationInitialMeshImportFromBINWithMoreInfo(pEMeshOptimization, "..\\mesh\\X-51", "X-51_D1_bin") != 1)
			return;
		//if (EMeshOptimizationInitialMeshImportFromBINWithMoreInfo(pEMeshOptimization, "..\\mesh\\R60", "R60_D1_bin") != 1)
		//	return 0;

		// Output the mesh quality information of the initial mesh
		std::cout << "\nThe mesh info before optimized:\n";
		EMeshOptimizationOutputsMeshQualityInformation(pEMeshOptimization);

		// Domain decomposition
		std::cout << "\nDomain decomposition start..." << std::endl;
		std::cout << "Current number of partitions: " << size << std::endl;
		EMeshOptimizationDomainDecomposition(pEMeshOptimization);
		std::cout << "Domain decomposition end!" << std::endl;

		// Record the start time of the mesh optimization algorithm
		std::cout << "\nOptimization start..." << std::endl;
		start_opti = std::chrono::steady_clock::now();
	}

	// Run the mesh optimization algorithm
	EMeshOptimization_GEPM_MSMPI(pEMeshOptimization);
	//EMeshOptimization_GEPMA_MSMPI(pEMeshOptimization);
	//EMeshOptimization_GEPMB_MSMPI(pEMeshOptimization);
	//EMeshOptimization_LS_MSMPI(pEMeshOptimization);

	if (rank == 0)
	{
		// Record the end time of the mesh optimization algorithm
		end_opti = std::chrono::steady_clock::now();
		std::cout << "Optimization end!" << std::endl;

		// Output the time cost of the mesh optimization algorithm, use seconds as the unit
		std::chrono::duration<double> elapsedTime = end_opti - start_opti;
		std::cout << "\nThe time cost of the mesh optimization algorithm: " << elapsedTime.count() << " s" << std::endl;

		// Output the mesh quality information of the optimized mesh
		std::cout << "\nThe mesh info after optimized:\n";
		EMeshOptimizationOutputsMeshQualityInformation(pEMeshOptimization);

		// Export the optimized mesh to a TXT file
		//if (EMeshOptimizationExportOptimizedMeshToTXT(pEMeshOptimization, "..\\mesh\\result\\X-51", "X-51_D1_OUT") != 1)
		//    return 0;
		//if (EMeshOptimizationExportOptimizedMeshToTXT(pEMeshOptimization, "..\\mesh\\result\\R60", "R60_D1_OUT") != 1)
		//	return 0;
	}

	// Delete the EMeshOptimization object
	EMeshOptimizationDelete(pEMeshOptimization);
#endif // MSMPI
}

int main(int argc, char* argv[])
{
#ifdef MSMPI // MSMPI optimization

	MPI_Init(&argc, &argv);
	MSMPIOpti();
	MPI_Finalize();

#else // Normal single process optimization

	GeneralOpti();

#endif // MSMPI

	return 0;
}
