#include "EMeshOptimization.h" // Include the header file of the EMeshOptimization object

int main()
{
	// Create a new EMeshOptimization object
	EMeshOptimization* pEMeshOptimization = NULL;
	pEMeshOptimization = EMeshOptimizationNew();

	// Set the parameters of the EMeshOptimization object
	if (EMeshOptimizationInitialMeshImportFromTXTWithMoreInfo(pEMeshOptimization, "..\\mesh\\X-51", "X-51_D1") != 1)
		return 0;
	//if (EMeshOptimizationInitialMeshImportFromBINWithMoreInfo(pEMeshOptimization, "..\\mesh\\R60", "R60_D1_bin") != 1)
	//	return 0;

	// Output the mesh quality information of the initial mesh
	EMeshOptimizationOutputsMeshQualityInformation(pEMeshOptimization);

	// Run the mesh optimization algorithm
	//EMeshOptimization_GEPM(pEMeshOptimization, 3, 200);
	//EMeshOptimization_PROA(pEMeshOptimization, 3, 350);
	//EMeshOptimization_GDOBS(pEMeshOptimization, 3);
	EMeshOptimization_LS(pEMeshOptimization, 3);

	// Output the mesh quality information of the optimized mesh
	EMeshOptimizationOutputsMeshQualityInformation(pEMeshOptimization);

	// Export the optimized mesh to a TXT file
	if (EMeshOptimizationExportOptimizedMeshToTXT(pEMeshOptimization, "..\\mesh\\result\\X-51", "X-51_D1_OUT") != 1)
		return 0;
	//if (EMeshOptimizationExportOptimizedMeshToTXT(pEMeshOptimization, "..\\mesh\\result\\R60", "R60_D1_OUT") != 1)
	//	return 0;

	// Delete the EMeshOptimization object
	EMeshOptimizationDelete(pEMeshOptimization);

	return 0;
}