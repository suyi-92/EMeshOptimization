// Copyright (c) 2024, 电子科技大学电子科学与工程学院，计算机仿真技术实验室
// All rights reserved.
// File Name: EMeshOptimization.h
// Description: Mesh optimization
// Current Version: 1.0
// Author: Longwei Deng
// Completion Date: August 30, 2024

#ifndef EMMPMESH_EMESHOPTIMIZATION_EMESHOPTIMIZATION_H_
#define EMMPMESH_EMESHOPTIMIZATION_EMESHOPTIMIZATION_H_

#ifdef EMESHOPTIMIZATION_EXPORTS
#define E_MESH_OPTIMIZATION_API _declspec(dllexport)
#else
#define E_MESH_OPTIMIZATION_API _declspec(dllimport)
#endif

class EMOVertex;
class EMORegion;

#include <vector>
#include <string>
#include <map>

class EMeshOptimization
{
private:
    // Stores the 3D coordinates of all mesh vertices and the size value of each vertex.
    std::vector<EMOVertex> vertices_;
    std::map<int, std::vector<EMOVertex>> verticesPartitions_;
    std::vector<EMOVertex> partVertices_;
    // Stores all mesh elements, with each mesh element containing two pieces of information:
    // 1. An int array vertexID_ that stores four int values (aID, bID, cID, and dID) in order,
    //    representing the IDs of the vertices (a, b, c, and d) that make up the current mesh element.
    //    These IDs correspond to the positions of the vertices in the vertices_ container. The storage
    //    order of the vertex IDs follows these rules: the first three IDs correspond to vertices (a, b, c)
    //    that uniquely determine a plane in space, and the fourth ID corresponds to vertex (d), which
    //    is "below" this plane. "Below" is defined as when viewed from "above" the plane, the vertices a, b,
    //    and c appear in counterclockwise order.
    // 2. An int array neigRegionID_ that stores four int values (raID, rbID, rcID, and rdID) in order,
    //    representing the IDs of the neighboring mesh elements (ra, rb, rc, and rd) of the current mesh element.
    //    These IDs correspond to the positions of the neighboring mesh elements in the regions_ container.
    //    The storage order of the neighboring mesh element IDs follows this rule: if vertexID_[i] is the ID of
    //    the i-th vertex of the current mesh element, then the ID of the neighboring mesh element "opposite" to
    //    this vertex must be stored in neigRegionID_[i].
    std::vector<EMORegion> regions_;
    std::map<int, std::vector<EMORegion>> regionsPartitions_;
    std::vector<EMORegion> partRegions_;

public:
    /************************************************************************
     * Function Description: Constructor
     * Input: None
     * Return Value: None
     * Author: Longwei Deng
     ************************************************************************/
    EMeshOptimization();

    /************************************************************************
     * Function Description: Destructor
     * Input: None
     * Return Value: None
     * Author: Longwei Deng
     ************************************************************************/
    ~EMeshOptimization();

    /************************************************************************
     * Function Description: Generates adjacency information for mesh elements
     * Input: None
     * Return Value: void
     * Author: Longwei Deng
     ************************************************************************/
    void GeneratesAdjacencyInformation();

    /************************************************************************
     * Function Description: Computes mesh quality information
     * Input: None
     * Return Value: void
     * Author: Longwei Deng
     ************************************************************************/
    void ComputesMeshQualityInformation();

    /************************************************************************
     * Function Description: Outputs mesh quality information
     * Input: None
     * Return Value: void
     * Author: Longwei Deng
     ************************************************************************/
    void OutputsMeshQualityInformation();

    /************************************************************************
     * Function Description: Use the proposed efficient three-dimensional mesh quality optimization method based on gradient-enhanced probabilistic model (GEPM) for optimization
     * Input: Param K: The whole optimization iteration count
     *        Param N: The continuous iteration count for a single node
     * Return Value: 1 indicates file read success, 0 indicates failure
     * Author: Longwei Deng
     ************************************************************************/
    void RunGEPM(const int &K, const int &N);

    /************************************************************************
     * Function Description: API Use the purely random optimization algorithm (GEPMB) for optimization
     * Input:  Param K: The whole optimization iteration count
     *        Param N: The continuous iteration count for a single node
     * Return Value: void
     * Author: Longwei Deng
     ************************************************************************/
    void RunGEPMB(const int &K, const int &N);

    /************************************************************************
     * Function Description: Use the gradient descent method (GEPMA) for optimization
     * Input: Param pEMeshOptimization: EMeshOptimization pointer make from EMeshOptimizationNew()
     *        Param K: The whole optimization iteration count
     * Return Value: void
     * Author: Longwei Deng
     ************************************************************************/
    void RunGEPMA(const int &K, const int &N);

    /************************************************************************
     * Function Description: Use the Laplacian smoothing (LS) for optimization
     * Input: Param K: The whole optimization iteration count
     * Return Value: void
     * Author: Longwei Deng
     ************************************************************************/
    void RunLS(const int &K);

    /************************************************************************
     * Function Description: Perform domain decomposition
     * Input: Param domainCount: Number of partitions
     * Return Value: void
     * Author: Longwei Deng
     ************************************************************************/
    void DomainDecomposition();

    /************************************************************************
     * Function Description: Use the proposed efficient three-dimensional mesh quality optimization method based on gradient-enhanced probabilistic model (GEPM) for optimization, for MS-MPI
     * Input: Param K: The whole optimization iteration count
     *        Param N: The continuous iteration count for a single node
     * Return Value: 1 indicates file read success, 0 indicates failure
     * Author: Longwei Deng
     ************************************************************************/
    void RunGEPM_MSMPI(const int &K, const int &N);

    /************************************************************************
     * Function Description: Use the gradient descent method (GEPMA) for optimization, for MS-MPI
     * Input: Param pEMeshOptimization: EMeshOptimization pointer make from EMeshOptimizationNew()
     *        Param K: The whole optimization iteration count
     * Return Value: void
     * Author: Longwei Deng
     ************************************************************************/
    void RunGEPMA_MSMPI(const int &K, const int &N);

    /************************************************************************
     * Function Description: Use the purely random optimization algorithm (GEPMB) for optimization, for MS-MPI
     * Input: Param K: The whole optimization iteration count
     *        Param N: The continuous iteration count for a single node
     * Return Value: void
     * Author: Longwei Deng
     ************************************************************************/
    void RunGEPMB_MSMPI(const int &K, const int &N);

    /************************************************************************
     * Function Description: Use the Laplacian smoothing (LS) for optimization, for MS-MPI
     * Input: Param K: The whole optimization iteration count
     * Return Value: void
     * Author: Longwei Deng
     ************************************************************************/
    void RunLS_MSMPI(const int &K);

    // Accessor functions
    void SetVertices(const std::vector<EMOVertex> &vertices);

    void AddVertex(const EMOVertex &vertex);

    void GetVertices(std::vector<EMOVertex> &vertices) const;

    void SetRegions(const std::vector<EMORegion> &regions);

    void AddRegion(const EMORegion &region);

    void GetRegions(std::vector<EMORegion> &regions) const;

private:
    /************************************************************************
     * Function Description: Distribute each partition to a single node, used for MS-MPI
     * Input: Param K: The whole optimization iteration count
     *        Param N: The continuous iteration count for a single node
     * Return Value: 1 indicates file read success, 0 indicates failure
     * Author: Longwei Deng
     ************************************************************************/
    void DistributeData();

    /************************************************************************
     * Function Description: Collect results from all nodes, used for MS-MPI
     * Input: Param K: The whole optimization iteration count
     *        Param N: The continuous iteration count for a single node
     * Return Value: 1 indicates file read success, 0 indicates failure
     * Author: Longwei Deng
     ************************************************************************/
    void CollectResults();

    /************************************************************************
     * Function Description: Serialize vertex data
     * Input: Param K: The whole optimization iteration count
     *        Param N: The continuous iteration count for a single node
     * Return Value: 1 indicates file read success, 0 indicates failure
     * Author: Longwei Deng
     ************************************************************************/
    std::vector<char> SerializeVertexVector(const std::vector<EMOVertex> &vertices);

    /************************************************************************
     * Function Description: Deserialize vertex data
     * Input: Param K: The whole optimization iteration count
     *        Param N: The continuous iteration count for a single node
     * Return Value: 1 indicates file read success, 0 indicates failure
     * Author: Longwei Deng
     ************************************************************************/
    std::vector<EMOVertex> DeserializeVertexVector(const std::vector<char> &buffer);

    /************************************************************************
     * Function Description: Serialize region data
     * Input: Param K: The whole optimization iteration count
     *        Param N: The continuous iteration count for a single node
     * Return Value: 1 indicates file read success, 0 indicates failure
     * Author: Longwei Deng
     ************************************************************************/
    std::vector<char> SerializeRegionVector(const std::vector<EMORegion> &vertices);

    /************************************************************************
     * Function Description: Deserialize region data
     * Input: Param K: The whole optimization iteration count
     *        Param N: The continuous iteration count for a single node
     * Return Value: 1 indicates file read success, 0 indicates failure
     * Author: Longwei Deng
     ************************************************************************/
    std::vector<EMORegion> DeserializeRegionVector(const std::vector<char> &buffer);
};

/************************************************************************
 * Function Description: API Constructor
 * Input: None
 * Return Value: EMeshOptimization *
 * Author: Longwei Deng
 ************************************************************************/
E_MESH_OPTIMIZATION_API EMeshOptimization *EMeshOptimizationNew();

/************************************************************************
 * Function Description: API Destructor
 * Input: Param pEMeshOptimization: EMeshOptimization pointer make from EMeshOptimizationNew()
 * Return Value: void
 * Author: Longwei Deng
 ************************************************************************/
E_MESH_OPTIMIZATION_API void EMeshOptimizationDelete(EMeshOptimization *&pEMeshOptimization);

/************************************************************************
 * Function Description: API Initial mesh import from txt. Applicable for reading normal mesh information.
                         Vertices include coordinate information, size information, and boundary point status.
                         Mesh elements include vertex ID information that makes up the mesh element.
 * Input: Param pEMeshOptimization: EMeshOptimization pointer make from EMeshOptimizationNew()
 *        Param folder: Folder path
 *        Param filename: File name
 * Return Value: 1 indicates file read success, 0 indicates failure
 * Author: Longwei Deng
 ************************************************************************/
E_MESH_OPTIMIZATION_API int EMeshOptimizationInitialMeshImportFromTXT(EMeshOptimization *pEMeshOptimization, const std::string &folder, const std::string &filename);

/************************************************************************
 * Function Description: API Initial mesh import from txt. Applicable for reading normal mesh information with more infomation.
                         Vertices include coordinate information, size information, boundary point status and the ID of any mesh element that includes the current vertex within the triangulation.
                         Mesh elements include vertex ID information that makes up the mesh element.
 * Input: Param pEMeshOptimization: EMeshOptimization pointer make from EMeshOptimizationNew()
 *        Param folder: Folder path
 *        Param filename: File name
 * Return Value: 1 indicates file read success, 0 indicates failure
 * Author: Longwei Deng
 ************************************************************************/
E_MESH_OPTIMIZATION_API int EMeshOptimizationInitialMeshImportFromTXTWithMoreInfo(EMeshOptimization *pEMeshOptimization, const std::string &folder, const std::string &filename);

/************************************************************************
 * Function Description: API Initial mesh import from bin. Applicable for reading normal mesh information.
                         Vertices include coordinate information, size information, and boundary point status.
                         Mesh elements include vertex ID information that makes up the mesh element.
 * Input: Param pEMeshOptimization: EMeshOptimization pointer make from EMeshOptimizationNew()
 *        Param folder: Folder path
 *        Param filename: File name
 * Return Value: 1 indicates file read success, 0 indicates failure
 * Author: Longwei Deng
 ************************************************************************/
E_MESH_OPTIMIZATION_API int EMeshOptimizationInitialMeshImportFromBIN(EMeshOptimization *pEMeshOptimization, const std::string &folder, const std::string &filename);

/************************************************************************
 * Function Description: API Initial mesh import from bin. Applicable for reading normal mesh information.
                         Vertices include coordinate information, size information, boundary point status and the ID of any mesh element that includes the current vertex within the triangulation.
                         Mesh elements include vertex ID information that makes up the mesh element.
 * Input: Param pEMeshOptimization: EMeshOptimization pointer make from EMeshOptimizationNew()
 *        Param folder: Folder path
 *        Param filename: File name
 * Return Value: 1 indicates file read success, 0 indicates failure
 * Author: Longwei Deng
 ************************************************************************/
E_MESH_OPTIMIZATION_API int EMeshOptimizationInitialMeshImportFromBINWithMoreInfo(EMeshOptimization *pEMeshOptimization, const std::string &folder, const std::string &filename);

/************************************************************************
 * Function Description: API Export optimized mesh to txt.
 * Input: Param pEMeshOptimization: EMeshOptimization pointer make from EMeshOptimizationNew()
 *        Param folder: Folder path
 *        Param filename: File name
 * Return Value: 1 indicates file read success, 0 indicates failure
 * Author: Longwei Deng
 ************************************************************************/
E_MESH_OPTIMIZATION_API int EMeshOptimizationExportOptimizedMeshToTXT(EMeshOptimization *pEMeshOptimization, const std::string &folder, const std::string &filename);

/************************************************************************
 * Function Description: API Outputs mesh quality information
 * Input: Param pEMeshOptimization: EMeshOptimization pointer make from EMeshOptimizationNew()
 * Return Value: void
 * Author: Longwei Deng
 ************************************************************************/
E_MESH_OPTIMIZATION_API void EMeshOptimizationOutputsMeshQualityInformation(EMeshOptimization *pEMeshOptimization);

/************************************************************************
 * Function Description: API Use the proposed efficient three-dimensional mesh quality optimization method based on gradient-enhanced probabilistic model (GEPM) for optimization
 * Input: Param pEMeshOptimization: EMeshOptimization pointer make from EMeshOptimizationNew()
 *        Param K: The whole optimization iteration count
 *        Param N: The continuous iteration count for a single node
 * Return Value: void
 * Author: Longwei Deng
 ************************************************************************/
E_MESH_OPTIMIZATION_API void EMeshOptimization_GEPM(EMeshOptimization *pEMeshOptimization, const int &K = 3, const int &N = 200);

/************************************************************************
 * Function Description: API Use the gradient descent method (GEPMA) for optimization
 * Input: Param pEMeshOptimization: EMeshOptimization pointer make from EMeshOptimizationNew()
 *        Param K: The whole optimization iteration count
 * Return Value: void
 * Author: Longwei Deng
 ************************************************************************/
E_MESH_OPTIMIZATION_API void EMeshOptimization_GEPMA(EMeshOptimization *pEMeshOptimization, const int &K = 3, const int &N = 5);

/************************************************************************
 * Function Description: API Use the purely random optimization algorithm (GEPMB) for optimization
 * Input: Param pEMeshOptimization: EMeshOptimization pointer make from EMeshOptimizationNew()
 *        Param K: The whole optimization iteration count
 *        Param N: The continuous iteration count for a single node
 * Return Value: void
 * Author: Longwei Deng
 ************************************************************************/
E_MESH_OPTIMIZATION_API void EMeshOptimization_GEPMB(EMeshOptimization *pEMeshOptimization, const int &K = 3, const int &N = 350);

/************************************************************************
 * Function Description: API Use the Laplacian smoothing (LS) for optimization
 * Input: Param pEMeshOptimization: EMeshOptimization pointer make from EMeshOptimizationNew()
 *        Param K: The whole optimization iteration count
 * Return Value: void
 * Author: Longwei Deng
 ************************************************************************/
E_MESH_OPTIMIZATION_API void EMeshOptimization_LS(EMeshOptimization *pEMeshOptimization, const int &K = 3);

/************************************************************************
 * Function Description: API Perform domain decomposition
 * Input: Param pEMeshOptimization: EMeshOptimization pointer make from EMeshOptimizationNew()
 *        Param domainCount: Number of partitions
 * Return Value: void
 * Author: Longwei Deng
 ************************************************************************/
E_MESH_OPTIMIZATION_API void EMeshOptimizationDomainDecomposition(EMeshOptimization *pEMeshOptimization);

/************************************************************************
* Function Description: API Use the proposed efficient three-dimensional mesh quality optimization method based on gradient-enhanced probabilistic model (GEPM) for optimization, for MS-MPI
* Input: Param K: The whole optimization iteration count
*        Param N: The continuous iteration count for a single node
* Return Value: 1 indicates file read success, 0 indicates failure
* Author: Longwei Deng
************************************************************************/
E_MESH_OPTIMIZATION_API void EMeshOptimization_GEPM_MSMPI(EMeshOptimization *pEMeshOptimization, const int &K = 3, const int &N = 200);

/************************************************************************
* Function Description: API Use the gradient descent method (GEPMA) for optimization, for MS-MPI
* Input: Param pEMeshOptimization: EMeshOptimization pointer make from EMeshOptimizationNew()
*        Param K: The whole optimization iteration count
* Return Value: void
* Author: Longwei Deng
************************************************************************/
E_MESH_OPTIMIZATION_API void EMeshOptimization_GEPMA_MSMPI(EMeshOptimization *pEMeshOptimization, const int &K = 3, const int &N = 5);

/************************************************************************
* Function Description: API Use the purely random optimization algorithm (GEPMB) for optimization, for MS-MPI
* Input: Param K: The whole optimization iteration count
*        Param N: The continuous iteration count for a single node
* Return Value: void
* Author: Longwei Deng
************************************************************************/
E_MESH_OPTIMIZATION_API void EMeshOptimization_GEPMB_MSMPI(EMeshOptimization *pEMeshOptimization, const int &K = 3, const int &N = 350);

/************************************************************************
* Function Description: API Use the Laplacian smoothing (LS) for optimization, for MS-MPI
* Input: Param K: The whole optimization iteration count
* Return Value: void
* Author: Longwei Deng
************************************************************************/
E_MESH_OPTIMIZATION_API void EMeshOptimization_LS_MSMPI(EMeshOptimization *pEMeshOptimization, const int &K = 3);

#endif // EMMPMESH_EMESHOPTIMIZATION_EMESHOPTIMIZATION_H_