package main

//extract features from image, convert to greyscale, histogram etc. use PCA algorithm
// Y (dependant variable) X independent variable
/*
If a Y variable exists and is part of your data, then separate your data into Y and X, as defined above — we’ll mostly be working with X. (Note: if there exists no column for Y, that’s okay — skip to the next point!)
Take the matrix of independent variables X and, for each column, subtract the mean of that column from each entry. (This ensures that each column has a mean of zero.)
Decide whether or not to standardize. Given the columns of X, are features with higher variance more important than features with lower variance, or is the importance of features independent of the variance? (In this case, importance means how well that feature predicts Y.) If the importance of features is independent of the variance of the features, then divide each observation in a column by that column’s standard deviation. (This, combined with step 2, standardizes each column of X to make sure each column has mean zero and standard deviation 1.) Call the centered (and possibly standardized) matrix Z.
Take the matrix Z, transpose it, and multiply the transposed matrix by Z. (Writing this out mathematically, we would write this as ZᵀZ.) The resulting matrix is the covariance matrix of Z, up to a constant.
(This is probably the toughest step to follow — stick with me here.) Calculate the eigenvectors and their corresponding eigenvalues of ZᵀZ. This is quite easily done in most computing packages— in fact, the eigendecomposition of ZᵀZ is where we decompose ZᵀZ into PDP⁻¹, where P is the matrix of eigenvectors and D is the diagonal matrix with eigenvalues on the diagonal and values of zero everywhere else. The eigenvalues on the diagonal of D will be associated with the corresponding column in P — that is, the first element of D is λ₁ and the corresponding eigenvector is the first column of P. This holds for all elements in D and their corresponding eigenvectors in P. We will always be able to calculate PDP⁻¹ in this fashion. (Bonus: for those interested, we can always calculate PDP⁻¹ in this fashion because ZᵀZ is a symmetric, positive semidefinite matrix.)
Take the eigenvalues λ₁, λ₂, …, λp and sort them from largest to smallest. In doing so, sort the eigenvectors in P accordingly. (For example, if λ₂ is the largest eigenvalue, then take the second column of P and place it in the first column position.) Depending on the computing package, this may be done automatically. Call this sorted matrix of eigenvectors P*. (The columns of P* should be the same as the columns of P, but perhaps in a different order.) Note that these eigenvectors are independent of one another.
Calculate Z* = ZP*. This new matrix, Z*, is a centered/standardized version of X but now each observation is a combination of the original variables, where the weights are determined by the eigenvector. As a bonus, because our eigenvectors in P* are independent of one another, each column of Z* is also independent of one another!*/
//If Y variable exists and is part of the data, then separate your data into Y and X, as defined above -- we'll mostly be working with X.
//map onto SVM, hard margin, gaussian RBF kernel
//use SMO/coordinate ascent to solve SVM

import (
	"os"

	"gocv.io/x/gocv"
)

func pca() {
	//image matrix
	image_folder := os.Args[1]
	os.Chdir(image_folder)
	img := gocv.NewMat()
}
