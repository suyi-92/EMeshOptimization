# EMeshOptimization

## Table of Contents

- [Project Description](#project-description)
- [Features](#features)
- [Installation](#installation)
- [Mesh file analysis](#Mesh-file-analysis)
- [FAQ](#faq)
- [License](#license)
- [Acknowledgments](#acknowledgments)

---

## Project Description

This project implements all mesh optimization algorithms from the paper *“An Efficient Three-Dimensional Mesh Quality Optimization Method Based on Gradient-Enhanced Probabilistic Model”*, aiming to optimize the quality of 3D tetrahedral meshes. We extracted these mesh quality optimization algorithms from our engineering code and packaged them into a dynamic link library (DLL). A set of API functions is provided for use and independent testing. The dynamic link library is fully encapsulated in C++, and we recommend using Visual Studio 2022 IDE for a better user experience.

## Features

- The mesh data provided in this project is fully open and only contains some common internal data. Therefore, users can preprocess the mesh data they are interested in based on the provided mesh data file examples, then use this project to read, optimize, and output the data.
- This project implements all optimization methods mentioned in the paper *"An Efficient Three-Dimensional Mesh Quality Optimization Method Based on Gradient-Enhanced Probabilistic Model"* and provides some hyperparameter settings for users to test and reproduce the results.
- This project is completely independent of the mesh generation process.
- The project provides reproducible mesh data for all optimization data presented in the paper, allowing users to test and validate the results themselves.
- Due to floating-point errors and differences in users' computers, the final optimized results obtained by the **GD-OBS** (the gradient descent method) and **LS** (the Laplacian smoothing) algorithms may not fully match the results in the paper, with *slight* differences within a minimal range, these differences fall within acceptable deviations.
- Since the **GEPM** (the proposed efficient three-dimensional mesh quality optimization method based on gradient-enhanced probabilistic model) and **PROA** (the purely random optimization algorithm) algorithms are based on probabilistic implementations, the final optimized results may not fully match those in the paper, with *small* differences within a certain range, these differences fall within acceptable deviations.
- The *"EMeshOptimization.h"* header file provides detailed descriptions of various data and API functions, including the functionalities and input parameters. The K and N hyperparameters correspond exactly to those described in the paper.

## Installation

Step-by-step instructions for installing your project so that users can quickly get started.

### Prerequisites

This project does not rely on any external libraries. The repository for this project can be found at https://github.com/suyi-92/EMeshOptimization.git. This is a dynamic link library implemented in C++, and it is recommended to include and use it through Visual Studio 2022 IDE for the best experience.

The `EMeshOptimizationTest` project in the repository is a sample project we created. Testers can directly open and use it, or they can build their own project or integrate it into an existing project based on the configurations and the steps provided below.

### Steps to Use the Library

1. **Clone the Repository**

   Clone the repository from GitHub to your local machine:

   ```bash
   git clone https://github.com/suyi-92/EMeshOptimization.git
   ```

2. **Create a New Project in Visual Studio 2022**

   - Open Visual Studio 2022 and create a new C++ project by selecting `File > New > Project`.


   - Choose a **Console Application** or any suitable C++ project type.


   - In the project settings, make sure to set the project to use **x64** architecture (if applicable).


3. **Build the Solution**

   Once the project is loaded, navigate to the `Build > Build Solution` option in Visual Studio. This will compile the dynamic link library (`.dll`) for the project.

4. **Include the Library in Your Own Project**

   To use the library in your own C++ project, follow these steps:

   - Add the path to the `EMeshOptimization.dll` and `EMeshOptimization.h` files in your project’s include and library directories.
   - Ensure that your project is configured to link against the `EMeshOptimization.lib` file generated during the build process.

5. **Example Code Usage**

   Here is an example of how to use the library in your own C++ code:

   ```cpp
   #include "EMeshOptimization.h" // Include the header file of the EMeshOptimization object
   
   int main()
   {
       // Create a new EMeshOptimization object
       EMeshOptimization *pEMeshOptimization = NULL;
       pEMeshOptimization = EMeshOptimizationNew();
   
       // Set the parameters of the EMeshOptimization object
       // EMeshOptimizationInitialMeshImportFromTXTWithMoreInfo(pEMeshOptimization, cParam->projectPath_ + "..\\mesh\\X-51", "X-51_D5");
       if (EMeshOptimizationInitialMeshImportFromBINWithMoreInfo(pEMeshOptimization, "..\\mesh\\R60", "R60_D1_bin") != 1)
           return 0;
   
       // Output the mesh quality information of the initial mesh
       EMeshOptimizationOutputsMeshQualityInformation(pEMeshOptimization);
   
       // Run the mesh optimization algorithm
       //EMeshOptimization_GEPM(pEMeshOptimization, 3, 200);
       //EMeshOptimization_PROA(pEMeshOptimization, 3, 350);
       //EMeshOptimization_GDOBS(pEMeshOptimization, 3);
       EMeshOptimization_LS(pEMeshOptimization, 3);
   
       // Output the mesh quality information of the optimized mesh
       EMeshOptimizationOutputsMeshQualityInformation(pEMeshOptimization);
   
       // Export the optimized mesh to a .txt file
       if (EMeshOptimizationExportOptimizedMeshToTXT(pEMeshOptimization, "..\\mesh\\result\\R60", "R60_D1_bin") != 1)
           return 0;
   
       // Delete the EMeshOptimization object
       EMeshOptimizationDelete(pEMeshOptimization);
   
       return 0;
   }
   ```

   It is important to note the parameter settings for the mesh file input and output functions, as the file path may need to be adjusted based on your specific environment. The other function parameters are set to default values, but you can modify them for testing according to the descriptions provided in the paper.

6. **Run the Program**

   After successfully linking the library and writing your code, you can build and run your project as usual. Visual Studio 2022 will handle the execution, and you should be able to see the results of your mesh optimization.

7. **For Specialization**

   You can independently choose the relevant API functions from the *"EMeshOptimization.h"* header file for diverse testing and verification. For detailed usage, refer to step 5.

## Mesh file analysis

Due to the file size limit of GitHUb, the current repository only contains mesh files with a small number of mesh units. The complete mesh file can be found at [this link](https://drive.google.com/drive/folders/1ziiWzmorx82NiVJPxWI0yoBrPpk_Lzrg?usp=sharing).

The mesh data provided in this project is fully open and only contains some common internal data. For the input file of the API function `EMeshOptimizationInitialMeshImportFromTXTWithMoreInfo`, we recommend the following format:

1. **Number of vertices**

   Example:

   ```txt
   Number of vertices
   ```

   Example for R60_D1:
   ```txt
   84105
   ```

2. **Vertex data**: 

   - Three double values representing the 3D coordinates of the vertex.
   - One double value representing the size of the vertex.
   - One int value indicating whether the vertex is a boundary point (1 for yes, 0 for no).
   - One int value representing the ID of any mesh element that includes the current vertex within the triangulation

   Example:

   ```txt
   x y z size boundaryFlag regionID
   ```

   Example for R60_D1:

   ```txt
   0 -16.277494568468668 -203.9901324771873 0.53484439849853516 1 537
   ```

   Repeat this for each vertex.

3. **Number of mesh elements**

   Example:

   ```txt
   Number of elements
   ```

   Example for R60_D1:

   ```txt
   411815
   ```

4. **Mesh element data**:
   
   - The vertex IDs that form the mesh element.
   
   Example:
   ```txt
   vertexID1 vertexID2 vertexID3 vertexID4
   ```
   
   Example for R60_D1:
   
   ```txt
   40541 52944 75534 76075
   ```

​	Repeat this for each mesh element.

And for the API function `EMeshOptimizationInitialMeshImportFromTXT`, we simply do not require the `regionID`, as this attribute will be automatically detected and generated within the program. All other information should strictly follow the format outlined above.

For these two API functions `EMeshOptimizationInitialMeshImportFromBIN` and `EMeshOptimizationInitialMeshImportFromBINWithMoreInfo`, the data requirements are exactly the same as the information mentioned above, with the only difference being that the data format is in binary.

For the file output API function `EMeshOptimizationExportOptimizedMeshToTXT`, we will output only the number of vertices and the 3D coordinates of each vertex, along with the number of mesh elements and the vertex IDs that form each mesh element, as follows:

```txt
84105
0 -16.277494568468668 -203.9901324771873
......
411815
40541 52944 75534 76075
```

## FAQ



## License



## Acknowledgments



---

